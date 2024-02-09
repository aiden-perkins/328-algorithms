
def readFile(file):
    with open(file) as f:
        # Splits the list into the groups of vertex from, vertex to, and distance
        array = f.read()[2:-2].split("}, {")
        for i, x in enumerate(array):
            # Splits every individual group into their own individual elements
            array[i] = x.split(", ")
            # Loop to convert the values from strings to ints/floats
            for j, y in enumerate(array[i]):
                try:
                    # Converts the string ints to ints
                    array[i][j] = int(y)-1
                except:
                    # Distance is a float, so when converting the string float to an int fails, it instead converts it to a float
                    array[i][j] = float(y)
        return array
    
class Graph:
    """
    Graph object that stores the number of vertices and the graph of edges
    """
    def __init__(self, vertices):
        self.v = vertices
        self.graph = []

    def addEdge(self, u, v, w):
        """
        Adds the edges from the file onto the graph

        Args:
            u (int): starting vertex
            v (int): ending vertex
            w (float): distance from the starting vertex to ending vertex
        """
        self.graph.append([u, v, w])

    def find(self, parent, i):
        if parent[i] != i:
            parent[i] = self.find(parent, parent[i])
        return parent[i]
    
    def union(self, parent, rank, x, y):
        if rank[x] < rank[y]:
            parent[x] = y
        elif rank[x] > rank[y]:
            parent[y] = x

        else: 
            parent[y] = x
            rank[x] += 1

    def kruskalMST(self):
        # List of the edges added to the minimum spanning tree
        result = []
        i = 0
        e = 0

        self.graph = sorted(self.graph, key=lambda item: item[2])

        parent = []
        rank = []

        for node in range(self.v):
            parent.append(node)
            rank.append(0)

        while e < self.v - 1:
            u, v, w = self.graph[i]
            i += 1
            print(f"Iteration: {i}")
            x = self.find(parent, u)
            y = self.find(parent, v)

            if x != y:
                e += 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)

        minimumCost = 0
        print("Edges in the constructed MST: ")
        for u, v, weight in result:
            minimumCost += weight
            print(f"{u+1} -- {v+1} == {weight}")
        print("Minimum Spanning Tree", minimumCost)
    
def main():
    correctAnswers = {
        "example":24.1839,
        "1":22.1804,
        "2":31.5744,
        "3":42.6385,
        "4":86.1578,
        "5":150.9976,
        "6":242.213,
        "7":588.4477,
        "8":840.7071,
        "9":1098.8336,
        "10":1595.8486,
    }
    cont = True

    while cont:
        # Reads through the graph file and returns an array that looks like [[0, 1, 4], [0, 2, 6], [1, 3, 15]]
        graph = readFile(f"Minimum Spanning Trees\\Test Cases\\{input('Graph File: ')}.txt")
        # Prepares a set to find the number of vertices in the graph
        vertices = set()
        
        # Iterates through the graph and adds the vertices to the vertices set
        for e in graph:
            vertices.add(e[0])
            vertices.add(e[1])

        # 
        g = Graph(len(vertices))
        for e in graph:
            g.addEdge(e[0], e[1], e[2])
        g.kruskalMST()

        tf = {"y":True, "n":False, "yes":True, "no":False}
        while True:
            try:
                cont = tf[input("Continue running? (Y/N) ").lower()]
                break
            except:
                print("Only input Y/N")
        
main()