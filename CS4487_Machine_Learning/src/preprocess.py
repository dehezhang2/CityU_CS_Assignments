import numpy as np
import torch

def remove_high_freq(img):
    f = torch.rfft(img, 2)
    resb = f[:,0:5:,0:5]
    # print(f)
    return resb.flatten()
def whitening(X):
    """
    Function to compute ZCA whitening matrix (aka Mahalanobis whitening).
    INPUT:  X: [M x N] matrix.
        Rows: Variables
        Columns: Observations
    OUTPUT: ZCAMatrix: [M x M] matrix
    """
    # Covariance matrix [column-wise variables]: Sigma = (X-mu)' * (X-mu) / N
    sigma = np.cov(X, rowvar=True) # [M x M]
    # Singular Value Decomposition. X = U * np.diag(S) * V
    U,S,V = np.linalg.svd(sigma)
        # U: [M x M] eigenvectors of sigma.
        # S: [M x 1] eigenvalues of sigma.
        # V: [M x M] transpose of U
    # Whitening constant: prevents division by zero
    epsilon = 1e-5
    # ZCA Whitening matrix: U * Lambda * U'
    ZCAMatrix = np.dot(U, np.dot(np.diag(1.0/np.sqrt(S + epsilon)), U.T)) # [M x M]
    return ZCAMatrix

def from_cifar_to_np(loader):
    X = []
    Y = []
    for i, data in enumerate(loader, 0):
        inputs, labels = data
        X.append(inputs.numpy())
        Y.append(labels.numpy())
    X = np.concatenate(X)
    Y = np.concatenate(Y)
    return (X, Y)

def from_submit_to_np(loader):
    X = []
    for i, data in enumerate(loader, 0):
        X.append(data)
    X = np.concatenate(X)
    return X