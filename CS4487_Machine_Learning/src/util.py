import csv
import torch
import numpy as np
import time

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

classes = ('plane', 'car', 'bird', 'cat',
           'deer', 'dog', 'frog', 'horse', 'ship', 'truck')

def trainNN(net, trainloader, optimizer, criterion, n_epoch=2) : 
    print('Training starts')

    for epoch in range(n_epoch):  # loop over the dataset multiple times

        running_loss = 0.0
        for i, data in enumerate(trainloader, 0):
            # get the inputs
            # inputs, labels = data
            # inputs = inputs.to(device)
            # labels = labels.to(device)
            inputs, labels = data[0].to(device), data[1].to(device)

            # zero the parameter gradients
            optimizer.zero_grad()

            # forward + backward + optimize
            outputs = net(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()

            # print statistics
            running_loss += loss.item()
            if i % 100 == 99:    # print every 2000 mini-batches
                print('[%d, %5d] double loss: %.7f' %
                      (epoch + 1, i + 1, running_loss / 12800))
                running_loss = 0.0
                
def cal_accuracy(net, testloader):
    correct = 0
    total = 0
    with torch.no_grad():
        for data in testloader:
            images, labels = data[0].to(device), data[1].to(device)
            outputs = net(images)
            _, predicted  = torch.max(outputs.data, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()
    return correct / total

def cal_class_accuracy(net, testloader):
    class_correct = list(0. for i in range(10))
    class_total = list(0. for i in range(10))
    with torch.no_grad():
        for data in testloader:
            images, labels = data
            images = images.to(device)
            labels = labels.to(device)
            outputs = net(images)
            _, predicted = torch.max(outputs, 1)
            c = (predicted == labels).squeeze()
            for i in range(4):
                label = labels[i]
                class_correct[label] += c[i].item()
                class_total[label] += 1


    for i in range(10):
        print('Accuracy of %5s : %2d %%' % (
            classes[i], 100 * class_correct[i] / class_total[i]))

def get_submit_result(net, submitloader):
    res_per = []
    with torch.no_grad():
        for i, data in enumerate(submitloader, 0):
            inputs = data.to(device)
            # forward + backward + optimize
            outputs = net(inputs)
            for o in outputs:
                res_per.append(o)
    res_labels = [int(torch.max(t,0)[1]) for t in res_per]
    return res_labels

def export_to_file(csv_name, res_labels):
    with open('./results/'+csv_name, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['Index', 'Category'])
        for i, l in enumerate(res_labels):
            writer.writerow((i, l))
                        
def print_accracy(sset, ratio):
    t = time.localtime()
    stime = time.strftime("%m-%d %H:%M:%S", t)
    print('%s: Accuracy of the network on the %s: %f %%' % (
        stime,
        sset, 
        100 * ratio)
    )

    