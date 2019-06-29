from dimacs import *
import os
from random import randint


def solve1(graph):
    min = len(graph)
    best_solution = []
    full_e = edgeList(graph)
    for i in range(20):
        edges = edgeList(graph)
        solution = []
        for j in range(len(full_e)):
            no = randint(0, len(edges) - 1)
            v1, v2 = edges[no]
            del edges[no]
            if v1 in solution or v2 in solution:
                continue
            solution.append(v1)
            solution.append(v2)
        if len(solution) < min:
            min = len(solution)
            best_solution = solution
    return best_solution


def solve2(_graph):
    graph = _graph.copy()
    edges = edgeList(graph)
    c = []
    while not isVC(edges, c):
        n, length = 0, 0
        for i, v in enumerate(graph):
            if len(v) > length:
                n, length = i, len(v)
        c.append(n)
        graph[n] = set()
        for v_list in graph:
            v_list.discard(n)
    return c


