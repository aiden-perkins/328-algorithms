import heapq
from collections import defaultdict


def k_find(parent, x):
    if parent[x] != x:
        parent[x] = k_find(parent, parent[x])
    return parent[x]


def k_union(rank, parent, x, y):
    px, py = k_find(parent, x), k_find(parent, y)
    if rank[px] < rank[py]:
        parent[px] = py
    else:
        parent[py] = px
        if rank[px] == rank[py]:
            rank[px] += 1


def kruskal(file_path):
    raw_edges = open(file_path).read()[2:-2].split('}, {')
    edges = []
    vertices = set()
    for raw_edge in raw_edges:
        start, end, weight = raw_edge.split(', ')
        edges.append((float(weight), int(start) - 1, int(end) - 1))
        vertices.add(start)
        vertices.add(end)
    parent = list(range(len(vertices)))
    rank = [0] * len(vertices)
    total_weight = 0
    for weight, start, end in sorted(edges):
        if k_find(parent, start) != k_find(parent, end):
            k_union(rank, parent, start, end)
            total_weight += weight
    return total_weight


def prim(file_path):
    raw_edges = open(file_path).read()[2:-2].split('}, {')
    adj_list = defaultdict(list)
    vertex_count = set()
    for raw_edge in raw_edges:
        start, end, weight = raw_edge.split(', ')
        start, end, weight = 2 ** (int(start) - 1), 2 ** (int(end) - 1), float(weight)
        adj_list[start].append((end, weight))
        adj_list[end].append((start, weight))
        vertex_count.add(start)
        vertex_count.add(end)
    vertex_count = (2 ** len(vertex_count)) - 1
    total_weight = 0
    visited = 0
    next_edges = [(0, 1, 1)]
    while visited != vertex_count:
        weight, start, end = heapq.heappop(next_edges)
        if not end & visited:
            visited |= end
            total_weight += weight
            for neighbor, new_weight in adj_list[end]:
                if not neighbor & visited:
                    heapq.heappush(next_edges, (new_weight, end, neighbor))
    return total_weight
