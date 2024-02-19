import importlib
import time


class Algorithm:
    def __init__(self, algorithm, fastest, single_file_input, has_example):
        self.algorithm_pkg = importlib.import_module(algorithm)
        self.sfi = single_file_input
        self.has_example = has_example
        self.answers = list(map(float, open(f'./{algorithm}/ans.txt').read()[:-1].split('\n')))
        self.algorithm_methods = dir(self.algorithm_pkg)[9:]
        self.fastest = fastest
        self.algorithm = algorithm

    def run_algorithm(self, method, test_case):
        if not method or method == 'fastest':
            method = self.fastest
        start = time.time()
        if self.sfi:
            ans = getattr(self.algorithm_pkg, method)(f'./{self.algorithm}/tests/{test_case}.txt')
        else:
            file_a_path = f'./{self.algorithm}/tests/{test_case}a.txt'
            file_b_path = f'./{self.algorithm}/tests/{test_case}b.txt'
            ans = getattr(self.algorithm_pkg, method)(file_a_path, file_b_path)
        if ans != self.answers[test_case]:
            print('WRONG ANSWER')
        total_time = time.time() - start
        return round(ans, 3), round(total_time, 4), test_case
