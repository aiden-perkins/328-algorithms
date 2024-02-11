# Algorithms

A collection of algorithms I have learned in my CECS 328 course, we don't have to code these, but I thought it would be a cool challenge to see the differences between the speed of the brute force algorithm and the optimized algorithm.
I did some in c++ so the improvements could be quantified and I didn't have to deal with whether a function I was using in python was compiled in C or not causing the timing to be incosistent.

### Running the Algorithms (python)

* You will need python 3 and numpy, which can be installed with `pip install numpy`

To run an algorithm simply:
```bash
python3 main.py [OPTIONS]
```

| Option                 | Value                                   | Description                                                                                                       |
|:-----------------------|:----------------------------------------|:------------------------------------------------------------------------------------------------------------------|
| -a, --algorithm        | algorithm name                          | The algorithm that you wish to run.                                                                               |
| -tc, --test-case       | 1 - 11                                  | Specify the test case to run, will do all by default. Not all algorithms will have 11 test cases.                 |
| -m, --method           | `brute_force` \| `fastest` \| `[other]` | Which method to run, using `brute_force` may take a while depending on the problem, will do `fastest` by default. |
| -la, --list-algorithms | N/A                                     | Lists the available algorithms you can run.                                                                       |
| -lc, --list-test-cases | algorithm name                          | Lists the available test cases for the given algorithm.                                                           |
| -lm, --list-methods    | algorithm name                          | Lists the available methods that the given algorithm has implemented.                                             |

So for example:

```python3 main.py -a ClosestPointPair -tc 10```

Would run the fastest implementation of ClosestPointPair on test case 10.

### Todo

| Algorithm                   | Instructions | Test Cases            | Example (Case & Answer) | Brute Force | Fastest | Answers | Other Code |
|:----------------------------|:-------------|:----------------------|:------------------------|:------------|:--------|:--------|:-----------|
| AllPairsShortestPath        |              | ✓                     |                         |             |         | ✓       | ✓          |
| ClosestPointPair            | ✓            | ✓                     | ✓                       | ✓           | ✓       | ✓       | N/A        |
| DeterministicOrderSelection | ✓            | ✓                     | ✓                       |             |         | ✓       | ✓          |
| FastFourierTransform        | ✓            | missing 7             | ✓                       |             |         |         |            |
| HuffmanEncoding             |              | ✓                     | missing answer          |             |         | ✓       | ✓          |
| KnapsackProblem             |              | ✓                     |                         |             |         | ✓       | ✓          |
| MinimumSpanningTrees        |              | ✓                     | ✓                       |             |         | ✓       | ✓          |
| StrassenAlgorithm           |              | missing 2, 7, 9, & 10 |                         | ✓           | ✓       | ✓       | N/A        |
