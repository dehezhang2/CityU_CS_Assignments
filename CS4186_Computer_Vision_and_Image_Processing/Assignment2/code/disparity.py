import cv2
import numpy as np
import math
from PIL import Image

def load_img(data_dir):
    dataset = []
    for i in range(1,4):
        left_img = cv2.imread(data_dir + str(i) + '/view1.png')
        right_img = cv2.imread(data_dir + str(i) + '/view5.png')
        gt = cv2.imread(data_dir + str(i) + '/disp1.png')
        dataset.append([left_img, right_img, gt])
    return dataset

def calc(image_left, image_right, window_size = 5, alpha = 207, beta = 0, min_dis = 6, dis_range = 15, 
          lmbda = 61000,sigma = 1.5, disp12MaxDiff = 250, uniquenessRatio = 5, 
          speckleWindowSize = 111, speckleRange = 17, preFilterCap = 63):
    # Change the image to gray scale
    image_left = cv2.cvtColor(image_left, cv2.COLOR_BGR2GRAY)
    image_right = cv2.cvtColor(image_right, cv2.COLOR_BGR2GRAY)
    
    # inialize the SGBM matcher and calculate disparity maps for two images
    matcher_left = cv2.StereoSGBM_create(
        minDisparity = min_dis,
        numDisparities = 16*dis_range,
        blockSize = window_size,
        P1 = 8 * 3 * window_size,
        P2 = 32 * 3 * window_size,
        
        disp12MaxDiff = disp12MaxDiff,
        uniquenessRatio = uniquenessRatio,
        speckleWindowSize = speckleWindowSize,
        speckleRange = speckleRange,
        preFilterCap = preFilterCap,
        
        mode = cv2.STEREO_SGBM_MODE_SGBM_3WAY
    )
    matcher_right = cv2.ximgproc.createRightMatcher(matcher_left)
    disparity_left = matcher_left.compute(image_left, image_right)  
    disparity_right = matcher_right.compute(image_right, image_left)

    # Fast Global Smoother
    lmbda = lmbda
    sigma = sigma
    w_filter = cv2.ximgproc.createDisparityWLSFilter(matcher_left=matcher_left)
    w_filter.setSigmaColor(sigma)
    w_filter.setLambda(lmbda)
    
    
    disparity = w_filter.filter(disparity_left, image_left, None, disparity_right)
    disparity = cv2.normalize(src=disparity, dst=disparity, beta=beta, alpha=alpha, norm_type=cv2.NORM_MINMAX)
    disparity = np.uint8(disparity)

    res = np.stack([disparity, disparity, disparity], axis=2)    
    return disparity

def psnr(img1, img2):
    mse = np.mean( ((img1 - img2)) ** 2 )
    if mse == 0:
        return 'INF'
    PIXEL_MAX = 255.0
    return 20 * math.log10(PIXEL_MAX / math.sqrt(mse))

def test(result_path):
    test_imgs = ["Art", "Dolls", "Reindeer"]    
    cnt = 0
    res = ''
    for index in range(3):
        gt_names = "../gt/"+test_imgs[index]+"/disp1.png"
        gt_img = np.array(Image.open(gt_names),dtype=float)
       
        
        pred_names =  result_path+test_imgs[index]+"/disp1.png"
        pred_img = np.array(Image.open(pred_names),dtype=float)
        [h,l] = gt_img.shape
        gt_img = gt_img[:, 250:l]
        pred_img = pred_img[:, 250:l]
        pred_img[gt_img==0]= 0

        peaksnr = psnr(pred_img,gt_img)
        res += 'The Peak-SNR value is {:.4f} \n'.format(peaksnr)
        cnt += peaksnr
    with open(result_path+'PSNR_results.txt', 'w') as f:
        f.write(res)
    return cnt/3.0