import numpy as np
from torch import nn, optim, FloatTensor, load, save
import matplotlib.pyplot as plt

show = True
num_of_outputs = 10


class Flatten(nn.Module):
    def forward(self, x):
        return x.view(x.size()[0], -1)


class PrintLayer(nn.Module):
    def forward(self, x):
        if show:
            imgs = x.data.numpy()
            x_l = len(imgs[0]) * len(imgs[0][0][0])
            results = np.zeros((x_l, 1))
            for i in range(len(imgs)):
                row = imgs[i][0]
                for j in range(1, len(imgs[i])):
                    row = np.concatenate((row, imgs[i][j]))
                results = np.concatenate((results, row), axis=1)
            results = results[:, 1:]
            plt.imshow(results)
            plt.show()
        return x


class Model(object):

    def __init__(self, lr=1e-3):

        self.model = nn.Sequential(
            PrintLayer(),
            nn.Conv2d(1, 3, 3),
            PrintLayer(),
            nn.ReLU(),
            PrintLayer(),
            Flatten(),
            nn.Linear(2028, 50),
            nn.ReLU(),
            nn.Linear(50, num_of_outputs),
            nn.Softmax()
        )
        self.opt = optim.Adam(self.model.parameters(), lr=lr)
        self.y_predicted = None
        self.criterion = nn.BCELoss()
        self.loss = None
        self.target = None

    def forward(self, data, _target):
        self.y_predicted = self.model.forward(FloatTensor(data))

        self.target = []
        if not isinstance(_target, np.ndarray):
            self.target.append([int(k == _target) for k in range(num_of_outputs)])
        else:
            for i in np.array(_target):
                self.target.append([int(k == i) for k in range(num_of_outputs)])
        self.target = FloatTensor(self.target)

        return self.y_predicted

    def backward(self):
        if self.y_predicted is None:
            raise RuntimeError("Outputs not computed!")

        self.opt.zero_grad()
        self.loss = self.criterion(self.y_predicted, self.target)
        self.loss.backward()
        self.opt.step()

    def get_result(self):
        results = []
        for i, res in enumerate(self.y_predicted.data.numpy()):
            a_m = np.argmax(res)
            results.append([0 for _ in range(len(res))])
            results[i][a_m] = 1
        results = np.array(results)
        score = results == self.target.data.numpy()
        score = np.sum(score, axis=1)
        for i in range(len(score)):
            if score[i] != num_of_outputs:
                score[i] = 0
            else:
                score[i] = 1
        return np.sum(score) / len(score)

    def print_heat_map(self, _picture, label, block_width=3, block_height=3):
        global show
        s = show
        show = False
        x, y = _picture.shape
        picture = np.array(_picture).reshape((1, 1, x, y))
        map_width = x - block_width + 1
        map_height = y - block_height + 1
        heat_map = np.zeros((map_width, map_height))
        self.forward(picture, label)
        basic_prob = self.y_predicted[0][label]
        for i in range(map_width):
            for j in range(map_height):
                picture[0][0] = _picture
                picture[0][0][i:i+block_width, j:j+block_height] = np.zeros((block_width, block_height))
                self.forward(picture, label)
                heat_map[i][j] = abs(self.y_predicted[0][label].data - basic_prob).data
        plt.imshow(heat_map)
        plt.show()
        show = s

    def load_from_file(self, path):
        self.model.load_state_dict(load(path))

    def save_to_file(self, path):
        save(self.model.state_dict(), path)

