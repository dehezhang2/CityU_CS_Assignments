import torch.nn as nn
import torch.nn.functional as F

'''
training:
Try seventyseven train at first
Try resnet secondly
'''

class BatchNormBlock(nn.Module):
    def __init__(self, in_depth, out_depth):
        super(BatchNormBlock, self).__init__()
        self.conv1 = nn.Conv2d(in_depth, out_depth, 5, padding=2)
        self.act1 = nn.PReLU()
        self.conv2 = nn.Conv2d(out_depth, out_depth, 3, padding=1)
        self.act2 = nn.PReLU()
        self.conv3 = nn.Conv2d(out_depth, out_depth, 3, padding=1)
        self.act3 = nn.PReLU()
        self.bn1 = nn.BatchNorm2d(10)
            
    def forward(self, x):
        x = self.conv1(x)
        x1 = self.act1(x)
        x = x1
        x = self.conv2(x)
        x = self.act2(x)
        x = self.conv3(x)
        # x = self.bn1(x)
        x = self.act3(x + x1)
        return x
    
class BasicBlock(nn.Module):
    
    def __init__(self, in_depth, hidden_depth, out_depth):
        super(BasicBlock, self).__init__()
        self.conv1 = nn.Conv2d(in_depth, hidden_depth, 3, padding=1)
        self.act1 = nn.PReLU()
        self.conv2 = nn.Conv2d(hidden_depth, out_depth, 3, padding=0)
        self.act2 = nn.PReLU()
            
    def forward(self, x):
        x = self.conv1(x)
        x = self.act1(x)
        
        x = self.conv2(x)
        x = self.act2(x)
        return x

class FCBlock(nn.Module):
    def __init__(self, in_depth, hidden_depth, out_depth):
        super(FCBlock, self).__init__()
        self.in_depth = in_depth
        self.out_depth = out_depth
        self.fc1 = nn.Linear(in_depth, hidden_depth)
        self.act1 = nn.PReLU()
        self.fc1_1 = nn.Linear(hidden_depth, out_depth)
            
    def forward(self, x):
        x_temp = x
        x = self.fc1(x)
        x = self.act1(x)
        x = self.fc1_1(x)
        x = self.act1(x + x_temp) if self.out_depth==self.in_depth else self.act1(x)
        return x
    
class WeakerNet(nn.Module):
    def __init__(self):
        super(WeakerNet, self).__init__()
        self.block1 = BatchNormBlock(3, 10)
        self.block2 = BatchNormBlock(10, 32)
        self.block3 = BasicBlock(32, 64, 128)
        
        self.block4 = BatchNormBlock(128, 256)
        self.block5 = BatchNormBlock(256, 512)
        self.block6 = BasicBlock(512, 256, 128)
        
        self.pool = nn.MaxPool2d(2, 2)
        
        self.block7 = FCBlock(128*36, 50, 128*36)
        self.block8 = FCBlock(128*36, 100, 50)
        

        self.fc = nn.Linear(50, 10)
        
        
    def forward(self, x):
        x = self.block1(x)
        x = self.block2(x)
        x = self.block3(x)
        x = self.pool(x)

        
        x = self.block4(x)
        x = self.block5(x)
        x = self.block6(x)
        x = self.pool(x)
        
        x = x.view(-1, 128*36)
        x = self.block7(x)
        x = self.block7(x)
        x = self.block8(x)
        x = self.fc(x)
        
        return x
def WeakerNet21():
    return WeakerNet()
        
        
        
        
        
        
    
        
    

        
        