from dimacs import *
import os
from brute_force import v_cover


directory = os.fsencode("graph")
for file in os.listdir(directory):
     filename = os.fsdecode(file)
     if filename.endswith("e40"):
         print(v_cover("graph\\" + filename))
         continue
     else:
         continue

title = "graph/e5"
print()