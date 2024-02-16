
def brute_force(file_path):
    """ This is just quick sort, then return nums[k] """

    file_contents = open(file_path).read().split(', {')
    k = int(file_contents[0][1:]) - 1
    nums = list(map(int, file_contents[1][:-2].split(', ')))
    return 0


def built_in_sort(file_path):
    file_contents = open(file_path).read().split(', {')
    k = int(file_contents[0][1:]) - 1
    nums = list(map(int, file_contents[1][:-2].split(', ')))
    nums.sort()
    return nums[k]


def median_of_medians(file_path):
    file_contents = open(file_path).read().split(', {')
    k = int(file_contents[0][1:]) - 1
    nums = list(map(int, file_contents[1][:-2].split(', ')))
    return 0


def quick_select(file_path):
    file_contents = open(file_path).read().split(', {')
    k = int(file_contents[0][1:]) - 1
    nums = list(map(int, file_contents[1][:-2].split(', ')))
    return 0


def random_select(file_path):
    file_contents = open(file_path).read().split(', {')
    k = int(file_contents[0][1:]) - 1
    nums = list(map(int, file_contents[1][:-2].split(', ')))
    return 0
