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

    def run_algorithm(self, method, test_case, ds=None):
        if not method or method == 'fastest':
            method = self.fastest
        start = time.time()
        if self.sfi:
            args = (f'./{self.algorithm}/tests/{test_case}.txt', )
            if ds:
                args = (f'./{self.algorithm}/tests/{test_case}.txt', ds)
        else:
            args = (f'./{self.algorithm}/tests/{test_case}a.txt', f'./{self.algorithm}/tests/{test_case}b.txt')
        ans = getattr(self.algorithm_pkg, method)(*args)
        if round(ans, 4) != self.answers[test_case]:
            print('WRONG ANSWER')
        total_time = time.time() - start
        return round(ans, 4), round(total_time, 3), test_case
