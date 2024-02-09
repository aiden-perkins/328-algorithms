from collections import Counter
import heapq

class node:
    def __init__(self, freq, char, left=None, right=None):
        self.freq = freq
        self.char = char
        self.left = left
        self.right = right
        self.huff = ""

    def __lt__(self, other):
        return self.freq < other.freq
    
def printNodes(node, frqs, val=""):
    newVal = val + str(node.huff)
    sumBits = 0

    if node.left:
        sumBits += printNodes(node.left, frqs, newVal)
    if node.right:
        sumBits += printNodes(node.right, frqs, newVal)

    if not node.left and not node.right:
        print(f"{node.char} -> {newVal}, {node.freq * len(newVal)} bits")
        sumBits += node.freq * len(newVal)

    return sumBits
        
def huffman(frqs):
    nodes = []
    for x in range(len(frqs)):
        heapq.heappush(nodes, node(frqs[x][1], frqs[x][0]))

    while len(nodes) > 1:
        left = heapq.heappop(nodes)
        right = heapq.heappop(nodes)

        left.huff = 0
        right.huff = 1

        newNode = node(left.freq+right.freq, left.char+right.char, left, right)
        heapq.heappush(nodes, newNode)
    
    return(printNodes(nodes[0], frqs))

def main():
    correctAnswers = {
        "1":32,
        "2":53,
        "3":71,
        "4":2344,
        "5":4723,
        "6":9469,
        "7":23770,
        "8":47541,
        "9":953156,
        "10":2383679
    }
    cont = True

    while cont:
        # Reads the given file
        file = input("String file: ")
        with open(f"Huffman Encoding\\Test Cases\\{file}.txt") as f:
            string = f.read()
        # Sorts the file by the frequency of each character in descending order
        freq = sorted(dict(Counter(string)).items(), key=lambda kv: (kv[1], kv[0]), reverse=True)

        # Writes the 2D list of frequencies into a file
        """with open(f"Huffman Encoding\\Test Frequencies\\{file}.txt", "w") as f:
            for x in range(len(freq) - 1):
                f.write(f"'{freq[x][0]}': {freq[x][1]},\n")
            f.write(f"'{freq[len(freq)-1][0]}': {freq[len(freq)-1][1]}")"""

        # Prints the string found in the file and the frequency of each character in the string
        print(f"String: {string}\n"
              f"Frequency of each character: \n{freq}")
        
        # Creates and prints out the heap tree
        bits = huffman(freq)
        print(f"# Bits of encoded string: {bits}")

        # Function to choose whether to run the code again or not
        tf = {"y":True, "n":False, "yes":True, "no":False}
        while True:
            try:
                cont = tf[input("Continue running? (Y/N) ").lower()]
                break
            except:
                print("Only input Y/N")
    
main()