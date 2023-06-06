from __future__ import division
import numpy as np


# average precision
def ave_pre(array):
    ap = 0
    for idx, m in enumerate(array):
        ap_m = (idx + 1) / (m + 1)
        ap = ap + ap_m
    ap = ap / len(array)
    return ap


# read ground truth num of the relevant images
with open('./rank_groundtruth.txt') as f:
    rank_line = f.read().splitlines()
# read retrieved num of the relevant images
with open('./test_result_CNN.txt') as f:
    rank_result = f.read().splitlines()

# compute mean average precision
ap_sum = 0
for idx, line in enumerate(rank_result):
    line_str = line.split()
    query_num = int(line_str[0][1]) - 1
    result_num = [int(x) for x in line_str[1:]]
    rank_str = rank_line[idx].split()
    rank_gt = [int(x) for x in rank_str[1:]]
    find_idx = []
    for num in rank_gt:
        ind = np.where(np.array(result_num) == num)
        find_idx.extend(ind)
    find_idx = np.array(find_idx).reshape(len(find_idx),)
    find_idx = np.sort(find_idx)
    # print(find_idx)
    ap = ave_pre(find_idx)
    print ("Average Precision of Q%d: %.4f"%(idx+1, ap))
    ap_sum = ap_sum + ap
print ("Mean Average Precision: %f" %(ap_sum / len(rank_result)))
