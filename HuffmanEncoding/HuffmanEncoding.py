from collections import Counter


def huffman(file_path):
    frequencies = Counter(open(file_path).read())
    nodes = list(frequencies.items())
    nodes.sort(key=lambda x: x[1], reverse=True)
    while len(nodes) > 1:
        smallest_node = nodes.pop()
        next_smallest = nodes.pop()
        new_weight = smallest_node[1] + next_smallest[1]
        new_node = ((smallest_node, next_smallest), new_weight)
        # It would be simpler to just append it to the end and then sort, but that would be slow on other languages and
        # wouldn't make sense to do when I know it's already sorted I just need to find the right spot to insert, if I
        # wanted to go a stepfurther I could use a binary search, but greedy algorithms are fast so maybe next time.
        for idx, (_, weight) in enumerate(nodes):
            if new_weight > weight:
                nodes.insert(idx, new_node)
                break
        else:
            nodes.append(new_node)
        # If the above code is running slow on an extremly large input, the below 2 lines might be better due to the
        # fact that python's sort function is made in C and not python.
        # nodes.append(new_node)
        # nodes.sort(key=lambda x: x[1], reverse=True)
    depth_tracker = []
    current_depth = 0
    while nodes:
        new_nodes = []
        for node, _ in nodes:
            if isinstance(node, tuple):
                new_nodes.append(node[0])
                new_nodes.append(node[1])
            else:
                depth_tracker.append((node, current_depth))
        nodes = new_nodes
        current_depth += 1
    return sum(map(lambda x: x[1] * frequencies[x[0]], depth_tracker))
