
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
