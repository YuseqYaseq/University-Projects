import matplotlib.pyplot as plt
import os


for i, file_name in enumerate(os.listdir("results/rectangles/")):
    print(file_name)
    y_rect = []
    y_trap = []
    y_simp = []
    y_mont = []
    x = []
    file_name = str(i+1) + ".txt"
    with open("results/rectangles/" + file_name) as data:
        data = data.read().split('\n')
        for full_line in data:
          if full_line == '':
            continue
          line = full_line.split(' ')
          y_rect.append(line[1])
          x.append(line[0])
    
    with open("results/trapezes/" + file_name) as data:
        data = data.read().split('\n')
        for full_line in data:
          if full_line == '':
            continue
          line = full_line.split(' ')
          y_trap.append(line[1])
    
    with open("results/simpsons/" + file_name) as data:
        data = data.read().split('\n')
        for full_line in data:
          if full_line == '':
            continue
          line = full_line.split(' ')
          y_simp.append(line[1])

    with open("results/montecarlo/" + file_name) as data:
        data = data.read().split('\n')
        for full_line in data:
          if full_line == '':
            continue
          line = full_line.split(' ')
          y_mont.append(line[1])
    
    plt.figure(figsize=(20,10))
    plt.yscale("log")
    plt.plot(x, y_rect, color='r', label='Rectangles method')
    plt.plot(x, y_trap, color='b', label='Trapezes method')
    plt.plot(x, y_simp, color='g', label='Simpson\'s method')
    plt.plot(x, y_mont, color='c', label='Basic Monte Carlo method')
    plt.legend()
    plt.xlabel("iterations/numbers of divisions")
    plt.ylabel("average difference from solution")
    plt.title("Plot " + str(i+1))
    plt.grid(axis='y')
    plt.savefig("Plot " + str(i+1))
    plt.clf()


#generate pi
for i, file_name in enumerate(os.listdir("results/pi/")):
    print(file_name)
    y = []
    x = []
    file_name = str(i+1) + ".txt"
    with open("results/pi/" + file_name) as data:
        data = data.read().split('\n')
        for full_line in data:
          if full_line == '':
            continue
          line = full_line.split(' ')
          y.append(line[1])
          x.append(line[0])
    
    plt.figure(figsize=(20,10))
    #plt.yscale("log")
    plt.plot(x, y, color='b', label='Basic Monte Carlo method')
    plt.legend()
    plt.xlabel("iterations/numbers of divisions")
    plt.ylabel("average difference from solution")
    plt.title("Pi approximation")
    plt.grid(axis='y')
    plt.savefig("Plot " + str(i+5))
    plt.clf()
