import time

def brute(ls):
    current_sequence = []
    max_sum = 0
    prev = ls[0]
    for num in ls:
        if prev < num:
            current_sequence.append(num)
        else:
            s = sum(current_sequence) 
            if s > max_sum:
                max_sum = s
            current_sequence = [num]
        prev = num
    return max_sum

def read_file(file):
    f = open(file, 'r')
    matrix = [int(a) for a in f.read()[1:-1].split(', ')]
    f.close()
    return matrix

def read_filev2(file):
    f = open(file, 'r')
    m = {}
    for i, value in enumerate(f.read()[1:-1].split(', ')):
        m[str(i)] = int(value)
    f.close()
    return m

def main(file):
    start = time.time()
    ls = read_file(file)
    lsa = brute(ls)
    print(f'File {file} took {time.time() - start} seconds: {lsa}')
    """
    """

main('1.txt')
main('2.txt')
main('3.txt')
main('4.txt')
main('5.txt')
"""
main('6.txt')
main('7.txt')
main('8.txt')
main('9.txt')
main('10.txt')
"""
