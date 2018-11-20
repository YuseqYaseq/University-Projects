import matplotlib.pyplot as plt
import os


for i, file_name in enumerate(os.listdir("results/jacob")):
    print(file_name)
    y_jacob = []
    y_gauss = []
    y_sor   = []
    x = []
    with open("results/jacob/" + str(i)) as data:
        data = data.read().split('\n')
        for full_line in data:
          if full_line == '':
            continue
          line = full_line.split(' ')
          y_jacob.append(line[1])
          x.append(line[0])

    with open("results/gauss/" + str(i)) as data:
        data = data.read().split('\n')
        for full_line in data:
          if full_line == '':
            continue
          line = full_line.split(' ')
          y_gauss.append(line[1])

    with open("results/sor/" + str(i)) as data:
        data = data.read().split('\n')
        for full_line in data:
          if full_line == '':
            continue
          line = full_line.split(' ')
          y_sor.append(line[1])
    
    print(y_sor)
    plt.plot(x, y_jacob, color='r', label='Jacob method')
    plt.plot(x, y_gauss, color='b', label='Gauss-Seidel method')
    plt.plot(x, y_sor, color='g', label='SOR method')
    plt.legend()
    plt.xlabel("iterations")
    plt.ylabel("average difference from solution")
    plt.grid(axis='y')
    plt.show()
