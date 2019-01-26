import matplotlib.pyplot as plt
import os

for file_name in os.listdir("results/"):
  print(file_name)
  with open("results/" + file_name) as data:
    size_c = []
    size_p = []
    time_c = []
    time_p = []
    data = data.read().split('\n')
    for full_line in data:
      line = full_line.split('\t')
      if line[0] is 'Type' or line[0] is '':
        continue
      if line[0] is 'P':
        size_p.append(int(line[1]))
        time_p.append(int(line[2]))
      if line[0] is 'C':
        size_c.append(int(line[1]))
        time_c.append(int(line[2]))
        
    #time_p = [x for _, x in sorted(zip(size_p, time_p))]
    #size_p = sorted(size_p)    
    
    #time_c = [x for _, x in sorted(zip(size_c, time_c))]
    #size_c = sorted(size_c)
    
    plt.scatter(size_p, time_p, color='r', label='Producers')
    plt.scatter(size_c, time_c, color='b', label='Consumers')
    plt.legend()
    plt.xlabel(file_name)
    plt.ylabel('time (ns)')
    plt.grid(axis='y')
    plt.show()
