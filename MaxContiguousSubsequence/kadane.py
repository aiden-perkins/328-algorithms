
def kadane(file_path):
    nums = [int(a) for a in open(file_path).read()[1:-1].split(', ')]
    current_sum = 0
    max_contig_subseq = float('-inf')
    for num in nums:
        current_sum = max(num, current_sum + num)
        max_contig_subseq = max(current_sum, max_contig_subseq)
    return max_contig_subseq
