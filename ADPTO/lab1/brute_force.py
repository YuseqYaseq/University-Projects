from dimacs import *

def select_set_vertices(i, k):
    count = 0
    solution = []
    d = 0
    while i > 0:
        if i % 2 == 1:
            count += 1
            solution.append(d)
        i //= 2
        d += 1
    if count == k:
        return solution
    else:
        return []


def vertex_cover(title, graph, k):
    # TODO czy to ma byc?
    #del graph[-1]

    for i in range(2**k):
        solution = select_set_vertices(i, k)
        if len(solution) != 0:
            solved = True
            edges = edgeList(graph)
            for edge in edges:
                if edge[0] not in solution and edge[1] not in solution:
                    solved = False
            if solved:
                saveSolution(title + ".sol", set(solution))
                return True
    return False

def v_cover(title):
    graph = loadGraph(title)
    for k in range(len(graph)):
        if vertex_cover(title, graph, k) == True:
            return True
    return False

