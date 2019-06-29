from pulp import *
from dimacs import *


def solve_graph_colouring(graph, k):
    n = len(graph)
    edges = edgeList(graph)

    x = [[LpVariable("x" + str(i) + "," + str(j), cat="Binary") for i in range(n)] for j in range(k)]
    y = [LpVariable("y" + str(i), cat="Binary") for i in range(k)]

    model = LpProblem("test", LpMinimize)

    # min func
    min_eq = y[0]
    for j in range(1, k):
        min_eq += y[j]
    model += min_eq

    # min + vertices
    for j in range(k):
        equation = x[j][0]
        for i in range(1, n):
            equation += x[j][i]
        equation = y[j] * n >= equation
        model += equation

    # vertices
    for i in range(n):
        equation = x[0][i]
        for j in range(1, k):
            equation += x[j][i]
        model += equation == 1

    # edges
    for (v1, v2) in edges:
        for j in range(k):
            model += x[j][v1] + x[j][v2] <= 1

    #print(model)
    model.solve()
    # print(LpStatus[model.status])

    colours = []
    for i in range(n):
        for j in range(k):
            # print(int(x[j][i].value()), end='')
            if x[j][i].value() == 1.0:
                colours.append(j)
                break
        # print()

    colours_used = 0
    for j in range(k):
        colours_used += y[j].value()
    return colours, colours_used


directory = os.fsencode("graph")
for file in os.listdir(directory):
    filename = os.fsdecode(file)
    if filename.endswith(".sol"):
        continue
    else:
        k = 500
        g = loadGraph("graph/" + filename)
        if filename.endswith("20"):
            print("check ", filename)
            print(solve_graph_colouring(g, k))
