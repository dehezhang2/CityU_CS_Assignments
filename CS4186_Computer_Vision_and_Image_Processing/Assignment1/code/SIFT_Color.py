import cv2
import numpy as np
from scipy.spatial import distance
from tqdm import tqdm

class CombinedImageSearcher:
    def __init__(self):
        self.sift = cv2.xfeatures2d.SIFT_create()
        self.bf = cv2.BFMatcher(cv2.NORM_L1, crossCheck=True)
    
    def sift_score(self, query, data):
        matches = self.bf.match(query['des'], data['des'])
        # Use homography to filter out incorrect matches
        src_pts = np.float32([query['kp'][m.queryIdx].pt for m in matches]).reshape(-1, 1, 2)
        dst_pts = np.float32([data['kp'][m.trainIdx].pt for m in matches]).reshape(-1, 1, 2)
        M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 5.0)
        # The score of the similarity between each query image and each image inside the
        # database is assigned as the number of correct matches.
        score = np.sum(mask)
        return score

    def color_score(self, x, y):
        intersection = np.minimum(x, y)
        sum_intersection = np.sum(intersection)
        match_score = sum_intersection / np.sum(x)
        return match_score


    def extract_feature(self, img):
        feature = {}
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        color_bin = cv2.calcHist([rgb], [0, 1, 2], None, [8, 8, 8],
                    [0, 256, 0, 256, 0, 256])
        keypoints, descriptors = self.sift.detectAndCompute(img,None)
        feature['color_hist'] = color_bin
        sift_feature = {}
        sift_feature['kp'] = keypoints
        sift_feature['des'] = descriptors
        feature['sift'] = sift_feature
        return feature
    
    def extract_features(self, images):
        for i in tqdm(range(len(images))):
            images[i]['feature'] = self.extract_feature(images[i]['img'])
            del images[i]['img']
        return images
    
    def image_search(self, query, data):
        result_lists = []
        for query_img in query:
            result_list = []
            for i in tqdm(range(len(data))):
                result = {}
                result['path'] = data[i]['path']
                result['sift_score'] = self.sift_score(\
                                        query_img['feature']['sift'],\
                                        data[i]['feature']['sift'])
                
                result['color_score'] = self.color_score(\
                                        query_img['feature']['color_hist'],\
                                        data[i]['feature']['color_hist'])

                result_list.append(result)
            result_list = sorted(result_list, key = lambda i: \
                                (i['sift_score'], i['color_score'] ), reverse = True)
            result_lists.append(result_list)
        return result_lists


