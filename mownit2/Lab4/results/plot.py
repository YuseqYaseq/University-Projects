import matplotlib.pyplot as plt
import os

file_name = "results.txt"

with open(file_name) as data:
  data = data.read().split('\n')
  freq = []
  re = []
  im = []
  for i, full_line in enumerate(data):
    if full_line is '':
      continue
    full_line = full_line.replace('(', '')
    full_line = full_line.replace(')', '')
    line = full_line.split(',')
    freq.append(float(i))
    re.append(float(line[0]))
    im.append(float(line[1]))
  
  plt.stem(freq, re, 'b')
  plt.xlabel("freq")
  plt.ylabel("re")
  plt.grid(axis='y')
  plt.show()
  
  plt.stem(freq, im, 'r')
  plt.xlabel("freq")
  plt.ylabel("im")
  plt.grid(axis='y')
  plt.show()
