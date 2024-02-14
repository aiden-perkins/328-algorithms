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
| -lm, --list-methods    | algorithm name                          | Lists the available methods that the given algorithm has implemented.                                             |

So for example:

```python3 main.py -a ClosestPointPair -tc 10```

Would run the fastest implementation of ClosestPointPair on test case 10.

### Todo

| Algorithm                   | Instructions | Test Cases | Example | Brute Force | Fastest  | C++ |
|:----------------------------|:-------------|:-----------|:--------|:------------|:---------|:----|
| ClosestPointPair            | ✓            | ✓          | ✓       | ✓           | ✓        | ✓   |
| StrassenAlgorithm           | ✓            | ✓          | ✓       | ✓           | ✓        | ✓   |
| MaxContiguousSubsequence    | ✓            | ✓          | ✓       | ✓           | ✓        |     |
| DeterministicOrderSelection | ✓            | ✓          | ✓       |             |          |     |
| MatrixChainMultiplication   |              |            |         |             |          |     |
| AllPairsShortestPath        |              | ✓          |         |             |          |     |
| MinimumSpanningTrees        |              | ✓          | ✓       |             |          |     |
| HuffmanEncoding             |              | ✓          | no ans  |             |          |     |
| KnapsackProblem             |              | ✓          |         |             |          |     |

### Runtime

This is the amount of time it took to run on my laptop, in seconds. DNF stands for did not finish in under an hour.

| Algorithm                                       | 0 | 1 | 2 | 3 | 4 | 5    | 6      | 7       | 8     | 9     | 10     |
|:------------------------------------------------|:--|:--|:--|:--|:--|:-----|:-------|:--------|:------|:------|:-------|
| ClosestPointPair - python - brute force         | 0 | 0 | 0 | 0 | 0 | 0    | 1.96   | 8.20    | 35.14 | DNF   | DNF    |
| ClosestPointPair - python - divide and conquer  | 0 | 0 | 0 | 0 | 0 | 0    | 0.02   | 0.03    | 0.08  | 2.64  | 5.70   |
| ClosestPointPair - c++ - brute force            | 0 |   |   |   |   |      |        |         |       |       |        |
| ClosestPointPair - c++ - divide and conquer     | 0 |   |   |   |   |      |        |         |       |       |        |
| StrassenAlgorithm - python - brute force        | 0 | 0 | 0 | 0 | 0 | 0.95 | 540.62 | 4211.46 | DNF   | DNF   | DNF    |
| StrassenAlgorithm - python - divide and conquer | 0 | 0 | 0 | 0 | 0 | 0    | 1.12   | 8.12    | 8.83  | 60.91 | 62.15  | 
| StrassenAlgorithm - python - strassen           | 0 | 0 | 0 | 0 | 0 | 0    | 0.74   | 3.45    | 3.96  | 20.27 | 21.42  |
| StrassenAlgorithm - python - python @           | 0 | 0 | 0 | 0 | 0 | 0    | 1.71   | 5.44    | 16.72 | 54.20 | 124.40 |
| StrassenAlgorithm - python - numpy dot          | 0 | 0 | 0 | 0 | 0 | 0    | 1.06   | 3.18    | 17.32 | 54.21 | 119.80 |
| StrassenAlgorithm - c++ - brute force           | 0 |   |   |   |   |      |        |         |       |       |        |
| StrassenAlgorithm - c++ - divide and conquer    | 0 |   |   |   |   |      |        |         |       |       |        |
| StrassenAlgorithm - c++ - strassen              | 0 |   |   |   |   |      |        |         |       |       |        |
