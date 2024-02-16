
def split_and_solve(nums):
    if len(nums) == 1:
        return nums[0]
    middle = len(nums) // 2
    return max(split_and_solve(nums[:middle]), split_and_solve(nums[middle:]), solve_middle(nums, middle))


def solve_middle(nums, middle):
    current_sum = 0
    right_max_subseq = float('-inf')
    for num in nums[middle:]:
        current_sum += num
        if right_max_subseq < current_sum:
            right_max_subseq = current_sum
    current_sum = 0
    left_max_subseq = float('-inf')
    for num in nums[:middle + 1][::-1]:
        current_sum += num
        if left_max_subseq < current_sum:
            left_max_subseq = current_sum
    return max(left_max_subseq + right_max_subseq - nums[middle], left_max_subseq, right_max_subseq)


def divide_and_conquer(file_path):
    nums = [int(a) for a in open(file_path).read()[1:-1].split(', ')]
    return split_and_solve(nums)


def brute_force(file_path):
    nums = [int(a) for a in open(file_path).read()[1:-1].split(', ')]
    max_contig_subseq = 0
    for i in range(len(nums)):
        for j in range(i + 1, len(nums) + 1):
            current_sum = sum(nums[i:j])
            if current_sum > max_contig_subseq:
                max_contig_subseq = current_sum
    return max_contig_subseq


def kadane(file_path):
    nums = [int(a) for a in open(file_path).read()[1:-1].split(', ')]
    current_sum = 0
    max_contig_subseq = float('-inf')
    for num in nums:
        current_sum = max(num, current_sum + num)
        max_contig_subseq = max(current_sum, max_contig_subseq)
    return max_contig_subseq
