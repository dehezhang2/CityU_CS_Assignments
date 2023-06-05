import torch.nn as nn
import torch.nn.functional as F

MULTIPLY_LEVEL = 2

'''
training:
batch_size: 32
momentum: 0.9 
adam, lr: 1e-3, weight decay: 0.001, 8 epoches
'''

class NetBlock(nn.Module):
    def __init__(self, in_depth, out_depth):
        super(NetBlock, self).__init__()
        
        self.act0 = nn.ReLU()
        
        self.conv1 = nn.Conv2d(in_depth, out_depth, 3, padding=1)
        self.bn1 = nn.BatchNorm2d(out_depth)
        self.act1 = nn.ReLU()
        
        self.conv2 = nn.Conv2d(out_depth, out_depth, 3, padding=1)
        
        if in_depth == out_depth:
            self.side = nn.Identity()
        else:
            self.side = nn.Conv2d(in_depth, out_depth, 1)

    def forward(self, x):
        x = self.act0(x)
        m = self.conv1(x)
        m = self.bn1(m)
        m = self.act1(m)
        m = self.conv2(m)
        s = self.side(x)
        
        return m + s
    
class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv0 = nn.Conv2d(3, 16, 3, padding=1)
        self.bn0 = nn.BatchNorm2d(16)
        
        self.block1 = NetBlock(16, 32 * MULTIPLY_LEVEL)
        self.block2 = NetBlock(32 * MULTIPLY_LEVEL, 32 * MULTIPLY_LEVEL)
        
        self.pool1 = nn.MaxPool2d(2, 2)    
        self.block3 = NetBlock(32 * MULTIPLY_LEVEL, 64 * MULTIPLY_LEVEL)
        self.block4 = NetBlock(64 * MULTIPLY_LEVEL, 64 * MULTIPLY_LEVEL)
        
        self.pool2 = nn.MaxPool2d(2, 2)   
        self.block5 = NetBlock(64 * MULTIPLY_LEVEL, 128 * MULTIPLY_LEVEL)
        self.block6 = NetBlock(128 * MULTIPLY_LEVEL, 128 * MULTIPLY_LEVEL)
        
        self.bn1 = nn.BatchNorm2d(128 * MULTIPLY_LEVEL)
        self.act1 = nn.ReLU()
        
        self.pool3 = nn.MaxPool2d(8, 8) 
        
        self.fc1 = nn.Linear(128 * MULTIPLY_LEVEL, 10)
        
        
    def forward(self, x):
        x = self.conv0(x)
        x = self.bn0(x)
        x = self.block1(x)
        x = self.block2(x)
        x = self.pool1(x)
        x = self.block3(x)
        x = self.block4(x)
        x = self.pool2(x)
        x = self.block5(x)
        x = self.block6(x)
        x = self.bn1(x)
        x = self.act1(x)
        x = self.pool3(x)
        x = x.view(-1, 128 * MULTIPLY_LEVEL)
        x = self.fc1(x)
        
        return x
def LargeNet():
    return Net()