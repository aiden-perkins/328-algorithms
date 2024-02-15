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

* Confirm the given answers are correct from the ans.txt file.
* Maybe merge the different methods of an algorithm in one file in the folder instead of each method getting its own.
* Run strassen/cpp c++ on laptop for better times.
* Run all mcss on laptop with everything closes.
* Try using arrays instead of vectors in c++.

| Algorithm                   | Instructions | Test Cases | Example | Brute Force | Fastest  | C++ |
|:----------------------------|:-------------|:-----------|:--------|:------------|:---------|:----|
| ClosestPointPair            | ✓            | ✓          | ✓       | ✓           | ✓        | ✓   |
| StrassenAlgorithm           | ✓            | ✓          | ✓       | ✓           | ✓        | ✓   |
| MaxContiguousSubsequence    | ✓            | ✓          | ✓       | ✓           | ✓        | ✓   |
| DeterministicOrderSelection | ✓            | ✓          | ✓       |             |          |     |
| MatrixChainMultiplication   |              |            |         |             |          |     |
| AllPairsShortestPath        |              | ✓          |         |             |          |     |
| MinimumSpanningTrees        |              | ✓          | ✓       |             |          |     |
| HuffmanEncoding             |              | ✓          | no ans  |             |          |     |
| KnapsackProblem             |              | ✓          |         |             |          |     |

### Runtime

This is the amount of time it took to run on my laptop, in seconds. DNF stands for did not finish in under an hour.

| Algorithm                                              | 0 | 1 | 2 | 3 | 4 | 5    | 6      | 7       | 8      | 9       | 10      |
|:-------------------------------------------------------|:--|:--|:--|:--|:--|:-----|:-------|:--------|:-------|:--------|:--------|
| ClosestPointPair - python - brute force                | 0 | 0 | 0 | 0 | 0 | 0    | 1.96   | 8.20    | 35.14  | DNF     | DNF     |
| ClosestPointPair - python - divide and conquer         | 0 | 0 | 0 | 0 | 0 | 0    | 0.02   | 0.03    | 0.08   | 2.64    | 5.70    |
| ClosestPointPair - c++ - brute force                   | 0 | 0 | 0 | 0 | 0 | 0    | 0.87   | 3.45    | 14.04  | DNF     | DNF     |
| ClosestPointPair - c++ - divide and conquer            | 0 | 0 | 0 | 0 | 0 | 0    | 0.02   | 0.03    | 0.06   | 1.77    | 3.63    |
| StrassenAlgorithm - python - brute force               | 0 | 0 | 0 | 0 | 0 | 0.95 | 540.62 | 4211.46 | DNF    | DNF     | DNF     |
| StrassenAlgorithm - python - divide and conquer        | 0 | 0 | 0 | 0 | 0 | 0    | 1.12   | 8.12    | 8.83   | 60.91   | 62.15   | 
| StrassenAlgorithm - python - strassen                  | 0 | 0 | 0 | 0 | 0 | 0    | 0.74   | 3.45    | 3.96   | 20.27   | 21.42   |
| StrassenAlgorithm - python - python @                  | 0 | 0 | 0 | 0 | 0 | 0    | 1.71   | 5.44    | 16.72  | 54.20   | 124.40  |
| StrassenAlgorithm - python - numpy dot                 | 0 | 0 | 0 | 0 | 0 | 0    | 1.06   | 3.18    | 17.32  | 54.21   | 119.80  |
| StrassenAlgorithm - c++ - brute force                  | 0 | 0 | 0 | 0 | 0 | 0.04 | 18.03  | 194.89  | 190.56 | 1645.86 | 1584.95 |
| StrassenAlgorithm - c++ - divide and conquer           | 0 | 0 | 0 | 0 | 0 | 0.04 | 16.17  | 129.30  | 127.81 | 1024.22 | 1024.79 |
| StrassenAlgorithm - c++ - strassen                     | 0 | 0 | 0 | 0 | 0 | 0.03 | 10.76  | 75.83   | 75.75  | 542.05  | 545.16  |
| MaxContiguousSubsequence - python - brute force        | 0 | 0 | 0 | 0 | 0 | 0.21 |        |         |        |         |         |
| MaxContiguousSubsequence - python - divide and conquer | 0 | 0 | 0 | 0 | 0 | 0    | 0.04   | 0.12    | 0.52   | 2.66    | 5.89    |
| MaxContiguousSubsequence - python - kadane             | 0 | 0 | 0 | 0 | 0 | 0    | 0      | 0       | 0.09   | 0.44    | 0.84    |
| MaxContiguousSubsequence - c++ - brute force           | 0 | 0 | 0 | 0 | 0 | 0.14 |        |         |        |         |         |
| MaxContiguousSubsequence - c++ - divide and conquer    | 0 | 0 | 0 | 0 | 0 | 0    | 0.04   | 0.10    | 0.38   | 1.69    | 3.49    |
| MaxContiguousSubsequence - c++ - kadane                | 0 | 0 | 0 | 0 | 0 | 0    | 0      | 0       | 0.07   | 0.13    | 0.25    |
