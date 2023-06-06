import cv2
import os
from disparity import *

def main():
    data_path = '../data/'
    res_path = '../pred/'    
    test_imgs = ["Reindeer", "Dolls", "Art"]
    if not os.path.exists(res_path):
        os.makedirs(res_path)
    dataset = load_img(data_path)

    idx = 0
    for data in dataset:
        disparity = calc(data[0], data[1])
        if not os.path.exists(res_path):
            os.makedirs(res_path + test_imgs[idx])
        cv2.imwrite(res_path+test_imgs[idx]+"/disp1.png", disparity)
        idx += 1
    avg = test(res_path)
    print("The average PSNR is: {:.4f}".format(avg))
if __name__ == "__main__":
    main()