import importlib
import os
import time


class Algorithm:
    def __init__(self, algorithm, fastest, single_file_input):
        self.algorithm_pkg = importlib.import_module(algorithm)
        self.tests = list(os.listdir(algorithm + '/tests/'))
        if not single_file_input:
            self.tests = list(zip(self.tests[::2], self.tests[1::2]))
        else:
            self.tests = [(a, ) for a in self.tests]
        self.algorithm_methods = dir(self.algorithm_pkg)[9:]
        self.fastest = fastest
        self.algorithm = algorithm

    def run_algorithm(self, method, test_case):
        if not method or method == 'fastest':
            method = self.fastest
        start = time.time()
        ans = getattr(self.algorithm_pkg, method)(*self.tests[test_case - 1])
        total_time = time.time() - start
        return round(ans, 3), round(total_time, 4), test_case
