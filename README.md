# Algorithms

A collection of algorithms I have learned in my CECS 328 course, we don't have to code these, but I thought it would be a cool challenge to see the differences between the speed of the brute force algorithm and the optimized algorithm.
I did some in c++ so the improvements could be quantified and I didn't have to deal with whether a function I was using in python was compiled in C or not causing the timing to be incosistent.

**Things I've learned:**

* Python's max function can be [weirdly slow](https://stackoverflow.com/questions/56281691/why-is-max-function-so-much-slower-when-comparing-2-elements-vs-direct-compari).
* In c++, using vector<>.size() also seems to be slow.
* Parsing text files is a nightmare in c++.
* The deepcopy function in the copy library in python is expensive.

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

* Try using arrays instead of vectors in c++.

| Algorithm                   | Problem                                   | Lecture Name                       | Instructions | Test Cases | Example | Timed | Python | C++ |
|:----------------------------|:------------------------------------------|:-----------------------------------|:-------------|:-----------|:--------|:------|:-------|:----|
| ClosestPointPair            | Closest Point Pair                        | Introduction to Recursion          | ✓            | ✓          | ✓       | ✓     | ✓      | ✓   |
| StrassenAlgorithm           | Matrix Multiplication                     | D&C: Strassen's Algorithm          | ✓            | ✓          | ✓       | ✓     | ✓      | ✓   |
| MaxContiguousSubsequence    | Max Continuous Subsequence Sum            | D&C: Fast Fourier Transform I      | ✓            | ✓          | ✓       | ✓     | ✓      | ✓   |
| DeterministicOrderSelection | Kth smallest element in an unordered list | D&C: Deterministic order selection | ✓            | ✓          | ✓       | ✓     | ✓      | ✓   |
| KnapsackProblem             | 0/1 Knapsack Problem                      | DP I: 0-1 Knapsack Problem         | ✓            | ✓          | ✓       | ✓     | ✓      | ✓   |
| MatrixChainMultiplication   | Min multiplications in matrix chain       | DP II: Matrix Chain Multiplication | ✓            | ✓          | ✓       |       | ✓      | ✓   |
| AllPairsShortestPath        | Shortest path to all pairs in a graph     | DP: APSP                           | ✓            | ✓          | ✓       |       |        |     |
| MinimumSpanningTrees        |                                           | Greedy: MST (Kruskal/Prim)         |              | ✓          | ✓       |       |        |     |
| HuffmanEncoding             |                                           | Greedy: Huffman coding             |              | ✓          | no ans  |       |        |     |

### Runtime

- Times are in seconds.
- For c++, if it ran in 25 or less ms, then I just put 0.
- DNF means that it did not finish in under an hour.
- Times are from running the algorithms on my laptop, the specs are:
  * intel i7 11800h 8c/16t @ 2.30 GHz
  * 16gb 3200 MHz SODIMM
  * RTX 3050 Ti Mobile
  * Micron 2300 NVMe 512gb

| Algorithm                                                | 0 | 1 | 2 | 3 | 4     | 5     | 6        | 7       | 8       | 9        | 10              |
|:---------------------------------------------------------|:--|:--|:--|:--|:------|:------|:---------|:--------|:--------|:---------|:----------------|
| ClosestPointPair - python - brute force                  | 0 | 0 | 0 | 0 | 0     | 0     | 2.065    | 8.538   | 35.974  | DNF      | DNF             |
| ClosestPointPair - python - divide and conquer           | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0.031   | 0.078   | 2.643    | 5.636           |
| ClosestPointPair - c++ - brute force                     | 0 | 0 | 0 | 0 | 0     | 0     | 0.486    | 1.947   | 7.775   | DNF      | DNF             |
| ClosestPointPair - c++ - divide and conquer              | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0       | 0.047   | 1.049    | 2.173           |
| StrassenAlgorithm - python - brute force                 | 0 | 0 | 0 | 0 | 0     | 0.955 | 527.769  | DNF     | DNF     | DNF      | DNF             |
| StrassenAlgorithm - python - divide and conquer          | 0 | 0 | 0 | 0 | 0     | 0     | 1.158    | 8.089   | 8.752   | 61.469   | 62.317          | 
| StrassenAlgorithm - python - strassen                    | 0 | 0 | 0 | 0 | 0     | 0     | 0.705    | 3.221   | 3.769   | 19.539   | 20.643          |
| StrassenAlgorithm - python - python @                    | 0 | 0 | 0 | 0 | 0     | 0     | 1.706    | 5.422   | 16.341  | 51.384   | 123.500         |
| StrassenAlgorithm - python - numpy dot                   | 0 | 0 | 0 | 0 | 0     | 0     | 1.064    | 3.270   | 16.195  | 51.726   | 118.541         |
| StrassenAlgorithm - c++ - brute force                    | 0 | 0 | 0 | 0 | 0     | 0.034 | 10.596   | 100.985 | 101.064 | 1050.351 | 1035.277        |
| StrassenAlgorithm - c++ - divide and conquer             | 0 | 0 | 0 | 0 | 0     | 0.034 | 10.517   | 83.825  | 85.642  | 671.726  | 675.725         |
| StrassenAlgorithm - c++ - strassen                       | 0 | 0 | 0 | 0 | 0     | 0.034 | 6.666    | 47.376  | 47.576  | 337.875  | 338.177         |
| MaxContiguousSubsequence - python - brute force          | 0 | 0 | 0 | 0 | 0     | 0.142 | 1438.271 | DNF     | DNF     | DNF      | DNF             |
| MaxContiguousSubsequence - python - divide and conquer   | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0.094   | 0.392   | 2.197    | 4.396           |
| MaxContiguousSubsequence - python - kadane               | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0       | 0.031   | 0.189    | 0.391           |
| MaxContiguousSubsequence - c++ - brute force             | 0 | 0 | 0 | 0 | 0     | 0.100 | 756.062  | DNF     | DNF     | DNF      | DNF             |
| MaxContiguousSubsequence - c++ - divide and conquer      | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0.069   | 0.248   | 1.243    | 2.487           |
| MaxContiguousSubsequence - c++ - kadane                  | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0       | 0.042   | 0.148    | 0.299           |
| DeterministicOrderSelection - python - brute force       | 0 | 0 | 0 | 0 | 0     | 0     | 0.078    | 2.237   | 4.923   | 8.206    | 14.286          |
| DeterministicOrderSelection - python - built in sort     | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0.267   | 0.563   | 0.828    | 1.447           |
| DeterministicOrderSelection - python - median of medians | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0.642   | 1.297   | 2.001    | 3.451           |
| DeterministicOrderSelection - python - quick select      | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0.298   | 0.750   | 1.335    | 1.818           |
| DeterministicOrderSelection - c++ - brute force          | 0 | 0 | 0 | 0 | 0     | 0     | 0.029    | 0.395   | 0.810   | 1.276    | 1.938           |
| DeterministicOrderSelection - c++ - built in sort        | 0 | 0 | 0 | 0 | 0     | 0     | 0.030    | 0.385   | 0.762   | 1.154    | 1.839           |
| DeterministicOrderSelection - c++ - median of medians    | 0 | 0 | 0 | 0 | 0     | 0     | 0.028    | 0.276   | 0.672   | 0.978    | 1.755           |
| DeterministicOrderSelection - c++ - quick select         | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0.269   | 0.540   | 0.833    | 1.375           |
| KnapsackProblem - python - brute force                   | 0 | 0 | 0 | 0 | 0.236 | DNF   | DNF      | DNF     | DNF     | DNF      | DNF             |
| KnapsackProblem - python - dynamic programming recursion | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0.189   | 2.472   | 10.393   | DNF<sup>1</sup> |
| KnapsackProblem - python - dynamic programming           | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0.142   | 1.672   | 7.333    | 46.907          |
| KnapsackProblem - c++ - brute force                      | 0 | 0 | 0 | 0 | 0.100 | DNF   | DNF      | DNF     | DNF     | DNF      | DNF             |
| KnapsackProblem - c++ - dynamic programming recursion    | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 1.405   | 29.909  | 251.501  | 3775.238        |
| KnapsackProblem - c++ - dynamic programming              | 0 | 0 | 0 | 0 | 0     | 0     | 0        | 0       | 0.109   | 0.422    | 2.608           |

_DNF<sup>1</sup>.  Python crashed due to recursion limits, would probably finish otherwise._
