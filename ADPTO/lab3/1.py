import pycosat
import random         # bibliotega liczb pseudolosowych
import time
from dimacs import *

#if pycosat.solve([[-1, -2], [1, 2], [-1, 2], [1, -2]]) == u'UNSAT':
#    print("Z")

zad = 2

if zad == 1:
    k = 3
    n = 10
    S = [1,-1]            # lista +/-
    V = range(1,n+1)      # lista zmiennych 1...n
    T = 100
    results = []
    a = 1.0
    while a < 10.0:
        x = random.choice(V)*random.choice(S)  # losowo wybrana zmienna z losowym negowaniem
        num = 0
        for t in range(T):
            clause = [[random.choice(V)*random.choice(S) for _ in range(k)] for _ in range(int(n * a))]
            if pycosat.solve(clause) != u'UNSAT':
                num += 1
        results.append((a, num))
        a += 0.1

    saveCNF("aaa", results)
if zad == 2:
    k = 2
    graph = loadGraph("graph/e10")
    x = []

    # x za wierzchołki
    for i, v in enumerate(graph):
        x.append([k*i + c for c in range(1, k + 1)])
        for c in range(1, k + 1):
            for c2 in range(1, c):
                x.append([-k * i -c, -k * i -c2])
    
    # x za krawędzie
    for v1, v2 in edgeList(graph):
        for c in range(1, k + 1):
            x.append([-(v1 * k + c), -(v2 * k + c)])
    x = pycosat.solve(x)
    if isinstance(x, str):
        print("Nie da sie")
    else:
        x = list(filter(lambda z: z > 0, x))
        for i in range(len(graph)):
            color = x[i] % k
            print(i, ": ", color, '\t\t', graph[i])




