import cv2
import os
import glob
import re

def crop_image(data_dir):
    # read all images and bounding boxes into "data"
    data = {}
    img_path = os.path.join(data_dir, '*jpg')
    img_files = glob.glob(img_path)
    cnt = 0
    
    for img_file in img_files:
        img = cv2.imread(img_file)
        img_number = re.search('(\d+)', img_file).group(1)
        bouding_box_file = os.path.join(data_dir, img_number + '.txt')
        cnt += 1

        if os.path.isfile(bouding_box_file):
            # if bounding box infomation is given, read the information and crop the image
            f = open(bouding_box_file, 'r').read()
            info = re.split('\s', f)
            x = int(info[0])
            y = int(info[1])
            width = int(info[2])
            height = int(info[3])
            
            img = img[y:y + height, x:x + width]
            cv2.imwrite(img_file, img)
            
        print("%d finished"%(cnt))
crop_image('../ug_data/database/Images')
crop_image('../ug_data/query/Images')
crop_image('../ug_data/examples/example_query')

