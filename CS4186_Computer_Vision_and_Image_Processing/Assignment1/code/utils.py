import torch
import torchvision
from torchvision import transforms
from tqdm import tqdm
import glob
import os
import cv2

def load_data(data_path, mode):
    if mode == 'CNN':
        preprocess = transforms.Compose(
            [
                transforms.Resize(256),
                transforms.CenterCrop(224),
                transforms.ToTensor(),
                transforms.Normalize(
                mean=[0.485, 0.456, 0.406],
                std=[0.229, 0.224, 0.225]),
            ]
        )
        data_set = torchvision.datasets.ImageFolder(
            root=data_path, transform=preprocess)
        data_loader = torch.utils.data.DataLoader(
            data_set, batch_size=1, shuffle=False)
        return data_loader
    elif mode == 'SIFT_Color_Hist':
        dataset = []
        image_files = glob.glob(os.path.join(data_path, '*jpg'))
        image_files = sorted(image_files)
        
        for i in tqdm(range(len(image_files))):
            data = {}
            data['img'] = cv2.imread(image_files[i])
            data['path'] = image_files[i]
            dataset.append(data)
        return dataset
    
def save_result(result_lists,res_path):
    write_str = ''
    for i in range(len(result_lists)):
        result_list = result_lists[i]
        query_str = 'Q' + str(int(i + 1)) + ':'
        result_str = ''
        for result in result_list:
            result_str += (' ' + result['path'].split('/')[-1].split('.')[0])
        write_str += (query_str + result_str + '\n')
    with open(res_path,'w') as f:
        f.write(write_str)