from dimacs import *
import copy
'''
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
'''

def vertex_cover(graph, k):
    if k == 0:
        if len(graph) == 0:
            return True
        else:
            return False
    else:
        edge = (0, graph[0])

        # remove 0
        graph1 = graph.copy()
        for vertex in graph1:
            for sec_v in vertex:
                if sec_v == 0:
                    vertex.remove(sec_v)
        del graph1[0]

        # remove graph[0]
        graph2 = graph.copy()
        for vertex in graph1:
            for sec_v in vertex:
                if sec_v == 0:
                    vertex.remove(sec_v)
        del graph1[0]

        if vertex_cover(graph1, k - 1):
            return True
        elif vertex_cover(graph2, k - 1):
            return True
        return False


