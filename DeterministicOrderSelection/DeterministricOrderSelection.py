import numpy as np


def partition(nums, left, right):
    pivot_v = nums[right - 1]
    swap_i = left
    for i in range(left, right - 1):
        if nums[i] <= pivot_v:
            nums[swap_i], nums[i] = nums[i], nums[swap_i]
            swap_i += 1
    nums[swap_i], nums[right - 1] = nums[right - 1], nums[swap_i]
    return swap_i


def quick_sort(nums, left, right):
    if len(nums[left:right]) <= 1:
        return
    pivot = partition(nums, left, right)
    quick_sort(nums, left, pivot)
    quick_sort(nums, pivot + 1, right)


def brute_force(file_path):
    file_contents = open(file_path).read().split(', {')
    k = int(file_contents[0][1:]) - 1
    nums = list(map(int, file_contents[1][:-2].split(', ')))
    quick_sort(nums, 0, len(nums))
    return nums[k]


def built_in_sort(file_path):
    file_contents = open(file_path).read().split(', {')
    k = int(file_contents[0][1:]) - 1
    nums = np.array(list(map(int, file_contents[1][:-2].split(', '))))
    nums.sort()
    return nums[k]


def select(nums, k):
    if len(nums) <= 100:
        return sorted(nums)[k - 1]
    medians = []
    for i in range(((len(nums) - 1) // 5) + 1):
        group = sorted(nums[i * 5:(i * 5) + 5])
        medians.append(group[len(group) // 2])
    median = select(medians, len(nums) // 10)
    # TODO: maybe use partition function, its probably faster
    left = []
    right = []
    for num in nums:
        if num < median:
            left.append(num)
        if num > median:
            right.append(num)
    if len(left) + 1 == k:
        return median
    if k < len(left) + 1:
        return select(left, k)
    return select(right, k - len(left) - 1)


def median_of_medians(file_path):
    file_contents = open(file_path).read().split(', {')
    k = int(file_contents[0][1:])
    nums = list(map(int, file_contents[1][:-2].split(', ')))
    return select(nums, k)


def quick_select_recursion(nums, k):
    if len(nums) == 1:
        return nums[0]
    pivot = partition(nums, 0, len(nums))
    if pivot == k:
        return nums[k]
    elif k < pivot:
        return quick_select_recursion(nums[:pivot], k)
    elif k > pivot:
        return quick_select_recursion(nums[pivot + 1:], k - pivot - 1)


def quick_select(file_path):
    file_contents = open(file_path).read().split(', {')
    k = int(file_contents[0][1:]) - 1
    nums = list(map(int, file_contents[1][:-2].split(', ')))
    return quick_select_recursion(nums, k)
