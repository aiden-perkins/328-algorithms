import numpy as np

def readFile(file):
    with open(file) as f:
        #{{1, 13, 408}, {1, 14, 356}, {1, 15, 539}, {1, 18, 832}, {1, 20, 766}}
        #1, 13, 408}, {1, 14, 356}, {1, 15, 539}, {1, 18, 832}, {1, 20, 766
        #['1, 13, 408', '1, 14, 356', '1, 15, 539', '1, 18, 832', '1, 20, 766']
        # Splits the given 
        array = f.read()[2:-2].split("}, {")
        for i, x in enumerate(array):
            array[i] = x.split(", ")
            #[[1, 13, 408], [1, 14, 356], [1, 15, 539], [1, 18, 832], [1, 20, 766]]
        return np.array(array, dtype=int)

def apsp(i, j, k, graph):
    """
    Recursive function that 

    Args:
        i (int): Starting vertex of the graph
        j (int): Ending vertex of the graph
        k (int): The number of edges to search through on the graph 
        graph (list): Graph of all the vertices, edges, and distances

    Returns:
        grid (list): The matrix of the length of the shortest distance between every vertex of the graph
    """
    # Initializes the matrix assuming all the points are not connected to each other (dist = inf)
    grid = np.full((1000, 1000), float('inf'), dtype=int)
    
    # Goes through every start-end vertex and finds the shortest path to that vertex
    # d_ij^k =                                          the distance between i and j given # of edges k
    # w_ij                              if k = 1        if k = 1, then return the length of the edge from i to j, or graph(i, j)[2]
    # min_v in V   d_iv^k-1 + w_vj      otherwise       finds the minimum of every intermediate vertex v from i to v in k-1 edges plus the distance between v and j    
    for x in range(len(grid)):
        for y in range(len(grid)):
            if k == 1:
                grid[x][y] = vertexWeight(x, y, graph)
            else:
                minimums = []
                for z in range(len(grid)):
                    
                    pass
                
    return grid

def vertexWeight(i, j, graph):
    indices = np.where(graph[:, 0] == i)
    try:
        return graph[np.where(graph[indices[0][0]:indices[0][-1] + 1, 1] == j)[:][0], 2]
    except:
        return [float('inf')]

def apsp2(graph):
    #(Path length, Start vertex, End vertex)
    grid = np.full((1000, 1000), float('inf'))
    
#FW(V, E, w):
#   for all vertices u
    for y in range(1000):
        grid[y][y] = 0
#       for all vertices v
#           dist[u, v, 0] = w(u to v)
    for e in graph:
        grid[e[0]-1][e[1]-1] = e[2]
        grid[e[1]-1][e[0]-1] = e[2]
#   
#   for r = 1 to V
    for v in range(2, 1000):
        print(v)
#       for all vertices u
        for i in range(1000):
#           for all vertices v
            for j in range(1000):
#               if dist[u, v, r - 1] < dist[u, r, r - 1] + dist[r, v, r - 1]
                if grid[i][j] > grid[i][v] + grid[v][j]:
                    grid[i][j] = grid[i][v] + grid[v][j]
#               
    return grid
    
def main():
    # Checks the correct answers for later on
    correctAnswers = {
        "1":106,
        "2":86,
        "3":93,
        "4":98,
        "5":86,
        "6":92,
        "7":98,
        "8":82,
        "9":107,
        "10":155
    }
    questions = {
        "1":    [970, 374],
        "2":    [96, 116],
        "3":    [793, 942],
        "4":    [90, 103],
        "5":    [370, 316],
        "6":    [642, 8],
        "7":    [69, 374],
        "8":    [253, 727],
        "9":    [374, 116],
        "10":   [265, 509]
    }
    cont = True

    # List of vertices
    #vertices = readFile(f"All Pairs Shortest Path\\graph.txt")
    vertices = readFile(f"All Pairs Shortest Path\\test.txt")
    print(vertices)

    dist = apsp2(vertices)
    print(dist)

    # Continuous loop
    while cont:
        inp1 = int(input("What is the starting vertex?: "))
        inp2 = int(input("What is the ending vertex?: "))
        try:
            print(f"Distance from {inp1} to {inp2} is {dist[inp1-1][inp2-1]}")
        except:
            continue
        """inp = input("Which question are you finding the answer for?: ")
        distance = dist[questions[inp][0]][questions[inp][1]]
        print(f"Distance from {questions[inp][0]} to {questions[inp][1]} is {distance}")"""
        
        tf = {"y":True, "n":False, "yes":True, "no":False}
        while True:
            # Makes sure you input it properly
            try:
                cont = tf[input("Continue running? (Y/N): ").lower()]
                break
            except:
                print("Only input Y/N")
    
main()