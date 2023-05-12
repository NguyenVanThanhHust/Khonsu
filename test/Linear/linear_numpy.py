import os, sys
import numpy as np
import math 

import matplotlib
import matplotlib.pyplot as plt

from sklearn.datasets import make_blobs

from loguru import logger

class CrossEntropyLoss():
    def forward(self, pred, gt):
        batch_size = gt.shape[0]
        cost = 1/ batch_size * (pred - gt)**2
        return cost
    
    def backward(self, pred, gt):
        batch_size = gt.shape[0]
        cost = 1/ batch_size * (pred - gt)
        return cost
    
class Linear():
    def __init__(self, name="linear", input_dim=None, output_dim=None) -> None:
        self.name = name
        self.in_dim = input_dim
        self.out_dim = output_dim
        self.w = None
        self.b = None
        self.name = name
        self.cache = {}
        self.init()

    def init(self):
        self.w = np.random.rand(self.in_dim, self.out_dim) * np.sqrt(2 / self.in_dim)
        self.b = np.zeros((1, self.out_dim))

    def forward(self, input_tensor, training=True):
        output_tensor = np.dot(input_tensor, self.w) + self.b
        if training:
            self.cache["input_tensor"] = input_tensor
            self.cache["output_tensor"] = output_tensor
        return output_tensor

    def backward(self, d_output):
        input_tensor = self.cache["input_tensor"]
        output_tensor = self.cache["output_tensor"]
        batch_size = input_tensor.shape[0]
        dw = 1/batch_size * np.dot(input_tensor.T, d_output)
        db = 1/batch_size * d_output.sum(axis=0, keepdims=True)
        assert dw.shape == self.w.shape, "expect same shape, get {} for self.w and {} for dw".format(self.w.shape, dw.shape)
        self.cache.update({'dw':dw, 'db':db})
        return dw

    def update_params(self, alpha=0.01):
        dw, db = self.cache['dw'], self.cache['db']
        self.w = self.w - alpha*dw
        self.b = self.b - alpha*db

    def get_params(self):
        return self.w, self.b

    def get_output_dim(self):
        return self.out_dim
    
    def __repr__(self) -> str:
        if "input_tensor" in self.cache.keys():
            return self.name + " input dim: " + str(self.in_dim) + " output dim: " + str(self.out_dim) + " input tensor shape: " + str(self.cache["input_tensor"].shape)
        else:
            return self.name + " input dim: " + str(self.in_dim) + " output dim: " + str(self.out_dim) 
        

def test_linear_forward():
    batch_size = 2
    input_dim = 8
    output_dim = 4
    input_tensor = np.random.rand(batch_size, input_dim)
    linear_layer = Linear("linear", input_dim, output_dim)
    true_output = np.dot(input_tensor, linear_layer.get_params()[0]) + linear_layer.get_params()[1]
    compute_output = linear_layer.forward(input_tensor)
    np.testing.assert_array_almost_equal(compute_output, true_output)


def main():
    np.random.seed(42)
    print("Test forward")
    test_linear_forward()
    print("Forward pass")
    print("Test backward")
    TRAIN_SIZE, TEST_SIZE = 2000, 400
    BATCH_SIZE = 16
    NUM_ITER = int(TRAIN_SIZE / BATCH_SIZE) - 1
    NUM_TEST = int(TEST_SIZE / BATCH_SIZE) - 1
    RANDOM_SEED = 42

    X_data, y_data = make_blobs((TRAIN_SIZE + TEST_SIZE), n_features=2, centers=2, random_state=RANDOM_SEED)
    y_label = []
    for y in y_data:
        if y == 0:
            y_label.append([1, 0])
        else:
            y_label.append([0, 1])
    y_label = np.array(y_label)
    
    X_train, y_train = X_data[:TRAIN_SIZE], y_label[:TRAIN_SIZE]
    X_test, y_test = X_data[TRAIN_SIZE:], y_label[TRAIN_SIZE:]
    
    linear_layer = Linear("linear", 2, 2)

    acc = 0.0
    tp = 0
    size = 0
    for it in range(NUM_TEST):
        x, y = X_test[it*BATCH_SIZE: (it+1)*BATCH_SIZE], y_test[it*BATCH_SIZE: (it+1)*BATCH_SIZE]
        pred_y = linear_layer.forward(x)
        y = np.argmax(y, axis=1)
        pred_y = np.argmax(pred_y, axis=1)
        tp += np.sum(pred_y == y)
        size += BATCH_SIZE                    
        # logger.info("iter {}, acc {}".format(it, tp/size ))

    print("Accuracy: ", tp/size)
    loss_fn = CrossEntropyLoss()
    for i in range(8):
        for it in range(NUM_ITER):
            x, y = X_train[it*BATCH_SIZE: (it+1)*BATCH_SIZE], y_train[it*BATCH_SIZE: (it+1)*BATCH_SIZE]
            pred_y = linear_layer.forward(x)
            loss = loss_fn.forward(pred_y, y)
            loss_deri = loss_fn.backward(pred_y, y)
            linear_layer.backward(loss_deri)
            linear_layer.update_params()
            # logger.info("iter {}, loss {}".format(it, loss.mean()))

        for it in range(NUM_TEST):
            x, y = X_test[it*BATCH_SIZE: (it+1)*BATCH_SIZE], y_test[it*BATCH_SIZE: (it+1)*BATCH_SIZE]
            pred_y = linear_layer.forward(x)
            y = np.argmax(y, axis=1)
            pred_y = np.argmax(pred_y, axis=1)
            tp += np.sum(pred_y == y)
            size += BATCH_SIZE                    
            # logger.info("iter {}, acc {}".format(it, tp/size ))
        print("Epoch ", i, "Accuracy: ", tp/size)

if __name__ == "__main__":
    main()
    