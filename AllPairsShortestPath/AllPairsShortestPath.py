from collections import defaultdict
import heapq


def dijkstras_array(file_path):
    pair = tuple(int(a) - 1 for a in open(file_path).read()[1:-1].split(', '))
    graph_path = './AllPairsShortestPath/graph.txt'
    edges = [tuple(int(a) for a in edge.split(', ')) for edge in open(graph_path).read()[2:-2].split('}, {')]
    vertices = set(list(map(lambda x: x[0], edges)) + list(map(lambda x: x[1], edges)))
    vertex_count = len(vertices)
    adj_matrix = [[0 for _ in range(vertex_count)] for _ in range(vertex_count)]
    for edge in edges:
        adj_matrix[edge[0] - 1][edge[1] - 1] = edge[2]
        adj_matrix[edge[1] - 1][edge[0] - 1] = edge[2]
    distance_mins = [float('inf') for _ in range(vertex_count)]
    finished = [False for _ in range(vertex_count)]
    distance_mins[pair[0]] = 0
    for _ in range(vertex_count):
        current_idx = -1
        current_cost = float('inf')
        for i, distance in enumerate(distance_mins):
            if distance < current_cost and not finished[i]:
                current_cost = distance
                current_idx = i
        if current_idx == -1:
            return
        finished[current_idx] = True
        for i in range(vertex_count):
            if not finished[i] and adj_matrix[current_idx][i] != 0:
                new_cost = distance_mins[current_idx] + adj_matrix[current_idx][i]
                if new_cost < distance_mins[i]:
                    distance_mins[i] = new_cost
    return distance_mins[pair[1]]


def dijkstras_min_heap(file_path):
    graph_path = './AllPairsShortestPath/graph.txt'
    edges = [tuple(int(a) for a in edge.split(', ')) for edge in open(graph_path).read()[2:-2].split('}, {')]
    pair = tuple(int(a) - 1 for a in open(file_path).read()[1:-1].split(', '))
    adj_list = defaultdict(list)
    cost = {}
    for edge in edges:
        adj_list[edge[0] - 1].append(edge[1] - 1)
        adj_list[edge[1] - 1].append(edge[0] - 1)
        cost[edge[:-1]] = edge[2]
        cost[edge[:-1][::-1]] = edge[2]
    queue = [(0, pair[0])]
    distance_mins = defaultdict(lambda: float('inf'))
    distance_mins[pair[0]] = 0
    while queue:
        current_cost, current_vertex = heapq.heappop(queue)
        for new_vertex in adj_list[current_vertex]:
            new_cost = current_cost + cost[(current_vertex + 1, new_vertex + 1)]
            if new_cost < distance_mins[new_vertex]:
                distance_mins[new_vertex] = new_cost
                heapq.heappush(queue, (new_cost, new_vertex))
    return distance_mins[pair[1]]


def build_data_structure(file_path):
    edges = [tuple(int(a) for a in edge.split(', ')) for edge in open(file_path).read()[2:-2].split('}, {')]
    vertices = set(list(map(lambda x: x[0], edges)) + list(map(lambda x: x[1], edges)))
    vertex_count = len(vertices)
    adj_matrix = [[float('inf') for _ in range(vertex_count)] for _ in range(vertex_count)]
    for edge in edges:
        adj_matrix[edge[0] - 1][edge[1] - 1] = edge[2]
        adj_matrix[edge[1] - 1][edge[0] - 1] = edge[2]
        adj_matrix[edge[0] - 1][edge[0] - 1] = 0
        adj_matrix[edge[1] - 1][edge[1] - 1] = 0
    for i in range(vertex_count):
        print(i)
        for j in range(vertex_count):
            for k in range(j + 1, vertex_count):
                possible = adj_matrix[j][i] + adj_matrix[i][k]
                if adj_matrix[j][k] > possible:
                    adj_matrix[j][k] = possible
                    adj_matrix[k][j] = possible
    return adj_matrix


def floyd_warshall(file_path, data_structure):
    pair = tuple(int(a) - 1 for a in open(file_path).read()[1:-1].split(', '))
    return data_structure[pair[0]][pair[1]]
