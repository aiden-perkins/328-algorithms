
def brute_force(file_path):
    nums = [int(a) for a in open(file_path).read()[1:-1].split(', ')]
    max_contig_subseq = 0
    for i in range(len(nums)):
        for j in range(i + 1, len(nums) + 1):
            current_sum = sum(nums[i:j])
            if current_sum > max_contig_subseq:
                max_contig_subseq = current_sum
    return max_contig_subseq
