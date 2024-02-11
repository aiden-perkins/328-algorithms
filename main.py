import argparse
from algorithm import Algorithm


def display_results(results):
    """
    I was originally going to use this function to make the output clean,
    however I failed to realize that I would rather the answers be printed
    as they were found instead of waiting for all the test cases to finish,
    so for now this will just sit here unused.
    """
    answers = [f'{a[0]:<.3f}' for a in results]
    times = [f'{a[1]:<.4f}' for a in results]
    tests = [str(a[2]) + '.' for a in results]
    max_ans = max([len(a) for a in answers])
    max_test = max([len(a) for a in tests])
    for i in range(len(answers)):
        print(f'{tests[i]:<{max_test}} {answers[i]:<{max_ans}} | took {times[i]} seconds.')


if __name__ == '__main__':
    raw_algorithms = {
        'ClosestPointPair': ('divide_and_conquer', True, True),
        'StrassenAlgorithm': ('strassen', False, False),
        'MaxContiguousSubsequence': ('kadane', True, True),
    }
    algorithms = {}
    for raw_algorithm in raw_algorithms:
        algorithms[raw_algorithm] = Algorithm(raw_algorithm, *raw_algorithms[raw_algorithm])
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-a',
        '--algorithm',
        help='The algorithm that you wish to run',
        choices=raw_algorithms
    )
    parser.add_argument(
        '-tc',
        '--test-case',
        help='Specify the test case to run, will do all by default',
        type=int,
        choices=range(11)
    )
    parser.add_argument(
        '-m',
        '--method',
        help='Which method to run, using brute_force may take a while depending on the problem, will do fastest by default'
    )
    parser.add_argument(
        '-la',
        '--list-algorithms',
        help='Lists the available algorithms to run',
        action='store_true'
    )
    parser.add_argument(
        '-lm',
        '--list-methods',
        help='Lists the available methods that the given algorithm has implemented',
        choices=raw_algorithms
    )
    args = parser.parse_args()
    if args.list_algorithms:
        for algorithm in raw_algorithms:
            print(algorithm)
    if args.list_methods:
        [print(a) for a in algorithms[args.list_methods].algorithm_methods]
    if args.algorithm:
        algo = algorithms[args.algorithm]
        tests_to_run = [args.test_case]
        start = 0 if algo.has_example else 1
        if args.test_case is None:
            tests_to_run = list(range(start, 11))
        for test_case in tests_to_run:
            ans, total_time, test_num = algo.run_algorithm(args.method, test_case)
            print(f'{test_num}. {ans:<.3f} | took {total_time:<.4f} seconds.')