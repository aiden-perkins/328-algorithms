# Algorithms

A collection of algorithms I have learned in my CECS 328 course, we don't have to code these, but I thought it would be a cool challenge to see the differences between the speed of the brute force algorithm and the optimized algorithm.
I did some in c++ so the improvements could be quantified and I didn't have to deal with whether a function I was using in python was compiled in C or not causing the timing to be incosistent.

**Things I've learned:**

* Python's max function can be weirdly slow.
* In c++, using vector<>.size() also seems to be slow.
* Parsing text files is a nightmare in c++.

### Running the Algorithms (python)

* You will need python 3 and numpy, which can be installed with `pip install numpy`

To run an algorithm simply:
```bash
python3 main.py [OPTIONS]
```

| Option                 | Value                                   | Description                                                                                                       |
|:-----------------------|:----------------------------------------|:------------------------------------------------------------------------------------------------------------------|
| -a, --algorithm        | algorithm name                          | The algorithm that you wish to run.                                                                               |
| -tc, --test-case       | 0 - 10                                  | Specify the test case to run, will do all by default.                                                             |
| -m, --method           | `brute_force` \| `fastest` \| `[other]` | Which method to run, using `brute_force` may take a while depending on the problem, will do `fastest` by default. |
| -la, --list-algorithms | N/A                                     | Lists the available algorithms you can run.                                                                       |
| -lm, --list-methods    | algorithm name                          | Lists the available methods that the given algorithm has implemented.                                             |

So for example:

```python3 main.py -a ClosestPointPair -tc 10```

Would run the fastest implementation of ClosestPointPair on test case 10.

### Running the Algorithms (c++)

* Cmake requirements are in [CMakeLists.txt](CMakeLists.txt)

Once it is compiled, just run it from in the root directory following these arguments:

```bash
./algorithms (algorithm name) [method] [test case]
```

The algorithm name is required, and if no method is provided then it will run the fastest, and if no test case is provided then it will run them all.
So for example:
`./algorithms MaxContiguousSubsequence kadane`
will run the kadane method on the MaxContiguousSubsequence problem on all test cases.

### Todo

* Confirm the given answers are correct from the ans.txt file for c++.
* Try using arrays instead of vectors in c++.

| Algorithm                   | Problem                                   | Lecture Name                       | Instructions | Test Cases | Example | Brute Force | Fastest | C++ |
|:----------------------------|:------------------------------------------|:-----------------------------------|:-------------|:-----------|:--------|:------------|:--------|:----|
| ClosestPointPair            | Closest Point Pair                        | Introduction to Recursion          | ✓            | ✓          | ✓       | ✓           | ✓       | ✓   |
| StrassenAlgorithm           | Matrix Multiplication                     | D&C: Strassen's Algorithm          | ✓            | ✓          | ✓       | ✓           | ✓       | ✓   |
| MaxContiguousSubsequence    | Max Continuous Subsequence Sum            | D&C: Fast Fourier Transform I      | ✓            | ✓          | ✓       | ✓           | ✓       | ✓   |
| DeterministicOrderSelection | Kth smallest element in an unordered list | D&C: Deterministic order selection | ✓            | ✓          | ✓       | ✓           |         |     |
| KnapsackProblem             | 0/1 Knapsack Problem                      | DP I: 0-1 Knapsack Problem         | ✓            | ✓          | ✓       |             |         |     |
| MatrixChainMultiplication   |                                           | DP II                              |              |            |         |             |         |     |
| AllPairsShortestPath        | Shortest path in a graph                  | DP: APSP                           | ✓            | ✓          | ✓       |             |         |     |
| MinimumSpanningTrees        |                                           | Greedy: MST (Kruskal/Prim)         |              | ✓          | ✓       |             |         |     |
| HuffmanEncoding             |                                           | Greedy: Huffman coding             |              | ✓          | no ans  |             |         |     |

### Runtime

This is the amount of time it took to run on my laptop, in seconds. DNF stands for did not finish in under an hour.

| Algorithm                                                | 0 | 1 | 2 | 3 | 4 | 5    | 6       | 7       | 8      | 9       | 10      |
|:---------------------------------------------------------|:--|:--|:--|:--|:--|:-----|:--------|:--------|:-------|:--------|:--------|
| ClosestPointPair - python - brute force                  | 0 | 0 | 0 | 0 | 0 | 0    | 1.96    | 8.20    | 35.14  | DNF     | DNF     |
| ClosestPointPair - python - divide and conquer           | 0 | 0 | 0 | 0 | 0 | 0    | 0.02    | 0.03    | 0.08   | 2.64    | 5.70    |
| ClosestPointPair - c++ - brute force                     | 0 | 0 | 0 | 0 | 0 | 0    | 0.46    | 1.90    | 8.01   | DNF     | DNF     |
| ClosestPointPair - c++ - divide and conquer              | 0 | 0 | 0 | 0 | 0 | 0    | 0       | 0       | 0      | 0.88    | 1.86    |
| StrassenAlgorithm - python - brute force                 | 0 | 0 | 0 | 0 | 0 | 0.95 | 540.62  | 4211.46 | DNF    | DNF     | DNF     |
| StrassenAlgorithm - python - divide and conquer          | 0 | 0 | 0 | 0 | 0 | 0    | 1.12    | 8.12    | 8.83   | 60.91   | 62.15   | 
| StrassenAlgorithm - python - strassen                    | 0 | 0 | 0 | 0 | 0 | 0    | 0.74    | 3.45    | 3.96   | 20.27   | 21.42   |
| StrassenAlgorithm - python - python @                    | 0 | 0 | 0 | 0 | 0 | 0    | 1.71    | 5.44    | 16.72  | 54.20   | 124.40  |
| StrassenAlgorithm - python - numpy dot                   | 0 | 0 | 0 | 0 | 0 | 0    | 1.06    | 3.18    | 17.32  | 54.21   | 119.80  |
| StrassenAlgorithm - c++ - brute force                    | 0 | 0 | 0 | 0 | 0 | 0    | 10.53   | 99.27   | 100.13 | 1036.20 | 1018.39 |
| StrassenAlgorithm - c++ - divide and conquer             | 0 | 0 | 0 | 0 | 0 | 0    | 10.13   | 80.91   | 83.00  | 664.17  | 667.40  |
| StrassenAlgorithm - c++ - strassen                       | 0 | 0 | 0 | 0 | 0 | 0    | 6.46    | 44.76   | 45.48  | 330.79  | 335.02  |
| MaxContiguousSubsequence - python - brute force          | 0 | 0 | 0 | 0 | 0 | 0.14 | 1457.06 | DNF     | DNF    | DNF     | DNF     |
| MaxContiguousSubsequence - python - divide and conquer   | 0 | 0 | 0 | 0 | 0 | 0    | 0       | 0.09    | 0.39   | 2.05    | 4.26    |
| MaxContiguousSubsequence - python - kadane               | 0 | 0 | 0 | 0 | 0 | 0    | 0       | 0       | 0.03   | 0.19    | 0.37    |
| MaxContiguousSubsequence - c++ - brute force             | 0 | 0 | 0 | 0 | 0 | 0.09 | 716.23  | DNF     | DNF    | DNF     | DNF     |
| MaxContiguousSubsequence - c++ - divide and conquer      | 0 | 0 | 0 | 0 | 0 | 0    | 0       | 0.06    | 0.23   | 1.21    | 2.50    |
| MaxContiguousSubsequence - c++ - kadane                  | 0 | 0 | 0 | 0 | 0 | 0    | 0       | 0       | 0      | 0.07    | 0.14    |
| DeterministicOrderSelection - python - brute force       | 0 | 0 | 0 | 0 | 0 | 0    | 0.08    | 2.21    | 4.90   | 8.21    | 14.22   |
| DeterministicOrderSelection - python - built in sort     | 0 | 0 | 0 | 0 | 0 | 0    | 0       | 0.27    | 0.55   | 0.83    | 1.40    |
| DeterministicOrderSelection - python - median of medians | 0 | 0 | 0 | 0 | 0 |      |         |         |        |         |         |
| DeterministicOrderSelection - python - quick select      | 0 | 0 | 0 | 0 | 0 | 0    | 0       | 0.28    | 0.75   | 1.33    | 1.77    |
| DeterministicOrderSelection - c++ - brute force          | 0 | 0 | 0 | 0 | 0 |      |         |         |        |         |         |
| DeterministicOrderSelection - c++ - built in sort        | 0 | 0 | 0 | 0 | 0 |      |         |         |        |         |         |
| DeterministicOrderSelection - c++ - median of medians    | 0 | 0 | 0 | 0 | 0 |      |         |         |        |         |         |
| DeterministicOrderSelection - c++ - quick select         | 0 | 0 | 0 | 0 | 0 |      |         |         |        |         |         |
