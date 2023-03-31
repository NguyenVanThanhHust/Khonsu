import torch
import torch.nn as nn

if __name__ == '__main__':
    w = torch.empty(3, 5)
    nn.init.uniform_(w)
    print(w)
