import torchvision
from torchvision import models
from torchvision import transforms
import torch
import torch.nn as nn
import os
import numpy as np
from scipy.spatial import distance

class CnnImageSearcher:
    def __init__(self):
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        net = models.alexnet(pretrained=True)
        modules = list(net.children())[:-2]
        self.model = nn.Sequential(*modules)
        # print(self.model)
        self.model.to(self.device)

    def extract_feature(self, data):
        cuda_feature = self.model(data[0].to(self.device))
        cuda_feature = torch.reshape(cuda_feature,(1, -1))
        # print(cuda_feature.shape)
        feature = cuda_feature.cpu().detach().numpy()[0]
        return feature
    
    def extract_features(self, data_loader, output_path = None):
        feature_list = list()
        filename_list = list()
        with torch.no_grad():
            for idx, data in enumerate(data_loader):
                input_file = data_loader.dataset.samples[idx]
                feature = self.extract_feature(data)
                feature_list.append(feature)
                filename_list.append(input_file[0])
                if (idx+1)%1000 == 0:
                    print('%d finished'%(idx + 1))

        if output_path != None:
            os.makedirs(output_path, exist_ok=True)
            np.save(os.path.join(output_path, "filenames_cnn.npy"), filename_list)
            np.save(os.path.join(output_path, "features_cnn.npy"), feature_list)
        
        return (feature_list, filename_list)
    
    def image_search(self, query_loader, data_feature_list, data_filename_list):
        result_lists = []
        with torch.no_grad():
            for idx, data in enumerate(query_loader):
                input_file = query_loader.dataset.samples[idx]
                query_feature = self.extract_feature(data)
                result_list = []
                for i in range(len(data_feature_list)):
                    result = {}
                    result['path'] = data_filename_list[i]
                    result['euc_dist'] = np.linalg.norm(data_feature_list[i] - query_feature)
                    result['cos_dist'] = distance.cosine(data_feature_list[i] , query_feature)
                    result_list.append(result)
                result_list = sorted(result_list, key = lambda i: (i['cos_dist']))
                result_lists.append(result_list)
        return result_lists


