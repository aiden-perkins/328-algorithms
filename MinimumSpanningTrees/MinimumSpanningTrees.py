import heapq
from collections import defaultdict


def kruskal(file_path):
    raw_edges = open(file_path).read()[2:-2].split('}, {')
    edges = []
    vertices = set()
    for raw_edge in raw_edges:
        start, end, weight = raw_edge.split(', ')
        edges.append((float(weight), int(start) - 1, int(end) - 1))
        vertices.add(start)
        vertices.add(end)
    edge_count = len(vertices)
    edges.sort()
    tree = []
    tree_vertices = set()
    total_cost = 0
    while len(tree_vertices) < edge_count or len(tree) > 1:
        for i, (weight, start, end) in enumerate(edges):
            for small_tree in tree:
                if len(small_tree.intersection({start, end})) == 2:
                    break
            else:
                tree_vertices.add(start)
                tree_vertices.add(end)
                total_cost += weight
                del edges[i]
                prev_tree_start = False
                prev_tree_start_idx = None
                prev_tree_end = False
                prev_tree_end_idx = None
                for j, small_tree in enumerate(tree):
                    if start in small_tree:
                        prev_tree_start = True
                        prev_tree_start_idx = j
                    if end in small_tree:
                        prev_tree_end = True
                        prev_tree_end_idx = j
                if prev_tree_end and prev_tree_start:
                    old_start = tree[prev_tree_start_idx]
                    old_end = tree[prev_tree_end_idx]
                    tree.append(old_start.union(old_end))
                    if prev_tree_start_idx > prev_tree_end_idx:
                        del tree[prev_tree_start_idx]
                        del tree[prev_tree_end_idx]
                    else:
                        del tree[prev_tree_end_idx]
                        del tree[prev_tree_start_idx]
                elif not prev_tree_end and not prev_tree_start:
                    tree.append({start, end})
                elif prev_tree_end:
                    tree[prev_tree_end_idx].add(start)
                else:
                    tree[prev_tree_start_idx].add(end)
                break
    return total_cost


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
