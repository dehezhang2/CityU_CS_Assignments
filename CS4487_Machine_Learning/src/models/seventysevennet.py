import torch.nn as nn
import torch.nn.functional as F

'''
training:
momentum: 0.9 
adam, lr: 1e-3, weight decay: 0.002, 12 epoches
sgd, lr: 1e-4, weight decay: 0.002, 14 epoches
sgd, lr: 3e-5, weight decay: 0.002, 3 epoches
sgd, lr: 1e-4, weight decay: 0.002, 5 epoches
sgd, lr: 1e-5, weight decay: 0.002, 4 epoches
'''

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(3, 10, 5, padding=2)
        self.act1 = nn.PReLU()
        self.conv2 = nn.Conv2d(10, 10, 3, padding=1)
        self.act2 = nn.PReLU()
        self.conv3 = nn.Conv2d(10, 10, 3, padding=1)
        self.act3 = nn.PReLU()
        self.bn1 = nn.BatchNorm2d(10)  ## 
        self.pool = nn.MaxPool2d(2, 2)    
        
        self.conv4 = nn.Conv2d(10, 32, 5, padding=2)
        self.act4 = nn.PReLU()
        self.conv5 = nn.Conv2d(32, 32, 3, padding=1)
        self.act5 = nn.PReLU()
        self.conv5_1 = nn.Conv2d(32, 32, 3, padding=1)
        self.act5_1 = nn.PReLU()
        self.bn2 = nn.BatchNorm2d(32)  ## 
        
        self.conv6 = nn.Conv2d(32, 64, 3, padding=1)
        self.act6 = nn.PReLU()
        self.conv_ext = nn.Conv2d(64, 128, 3, padding=0)  # 4 * 4 -> 2 * 2
        self.act_ext = nn.PReLU()
        
        self.fc1 = nn.Linear(128, 50)
        self.act7 = nn.PReLU()
        self.fc1_1 = nn.Linear(50, 128)
        self.bn3 = nn.BatchNorm1d(128)
        self.act7_1 = nn.PReLU()
        self.fc2 = nn.Linear(128, 50)
        self.act8 = nn.PReLU()
        self.bottoleneck = nn.Linear(50, 128)
        self.actbt = nn.PReLU()
        self.fc3 = nn.Linear(128, 10)
        # self.sm  = nn.LogSoftmax()
        # drop layer 

    def forward(self, x):
        x = self.conv1(x)
        x1 = self.act1(x)
        x = x1
        x = self.conv2(x)
        x = self.act2(x)
        x = self.conv3(x)
        # x = self.bn1(x)
        x = self.act3(x + x1)
        x = self.pool(x) 
        
        x = self.conv4(x)        
        x4 = self.act4(x)
        x = x4
        x = self.conv5(x)
        x = self.act5(x)
        x = self.conv5_1(x)
        # x = self.bn2(x)
        x = self.act5_1(x + x4)
        x = self.pool(x) 
        

        x = self.conv6(x)
        x = self.act6(x)
        x = self.pool(x) 
        
        x = self.conv_ext(x)
        x = self.act_ext(x)
        x = self.pool(x) 
        
        x = x.view(-1, 128)
        x_s = x
        x = self.fc1(x)
        x = self.act7(x)
        x = self.fc1_1(x)
        # x = self.bn3(x)
        x = self.act7_1(x+x_s)
        x_7_1 = x
        x = self.fc2(x)
        x = self.act8(x)
        x = self.bottoleneck(x)
        x = self.actbt(x+x_7_1)
        x = self.fc3(x)
        # x = self.sm(x)
        return x
def SeventySevenNet():
    return Net()
