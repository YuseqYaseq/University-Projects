from pulp import *
from dimacs import *


def solve(graph):
    n = len(graph)
    edges = edgeList(graph)

    x = [LpVariable("x" + str(i), lowBound=0, upBound=1, cat="Integer") for i in range(n)]

    model = LpProblem("test", LpMinimize)

    min_equation = x[0]
    for var in x[1:]:
        min_equation += var

    model += min_equation
    for (v1, v2) in edges:
        model += x[v1] + x[v2] >= 1

    model.solve()

    c = []
    for var in x:
        if var.value() == 1.0:
            c.append(var.name[1:])
    return c


directory = os.fsencode("graph")
for file in os.listdir(directory):
    filename = os.fsdecode(file)
    if filename.endswith(".sol"):
        continue
    else:
        print("check ", filename)
        g = loadGraph("graph/" + filename)
        if filename.startswith("s"):
            c = solve(g)
            saveSolution("graph/" + filename + ".sol", c)
