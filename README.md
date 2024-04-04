# Algorithms

A collection of algorithms I have learned in my CECS 328 course, we don't have to code these, but I thought it would be a cool challenge to see the differences between the speed of the brute force algorithm and the optimized algorithm.
I did some in c++ so the improvements could be quantified and I didn't have to deal with whether a function I was using in python was compiled in C or not causing the timing to be incosistent.

**Things I've learned:**

* Python's max function can be [weirdly slow](https://stackoverflow.com/questions/56281691/why-is-max-function-so-much-slower-when-comparing-2-elements-vs-direct-compari).
* Parsing text files is a nightmare in c++.
* The deepcopy function in the copy library in python is expensive.
* Arrays are lightning fast, only time I should use vectors is for input parsing.
* 2D Arrays/Pointers have a lot of differences compared to 1D arrays, caused the strassen abomination.

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

First, make the cmake cache with (you can add a directory so everything gets put in one folder):

```bash
cmake -DCMAKE_BUILD_TYPE=Release
```

Then you can build the algorithms executable (if you added a directory above then you need to put it after `--build ` in this command):

```bash
cmake --build --target algorithms
```

Once it is compiled, just run it from in the root directory following these arguments:

```bash
./algorithms (algorithm name) [method] [test case]
```

The algorithm name is required, and if no method is provided then it will run the fastest, and if no test case is provided then it will run them all.
So for example:
`./algorithms MaxContiguousSubsequence kadane`
will run the kadane method on the MaxContiguousSubsequence problem on all test cases.

### Todo

* Test different values of the base case for strassen to find the best and fastest (c++ & python).
* Create a way to run each test case either 1000 times or 1 hour of runs whichever happens first, for a better average time (c++ & python).
* Sub one second strassen with pthreads.
* When using 2D arrays in c++, if the reason I use dynamic memory allocation is only because the later test cases don't fit in the stack, switch it to use the stack depending on the size.

| Algorithm                   | Problem                                   | Lecture Name                       | Ran 1K/Hour |
|:----------------------------|:------------------------------------------|:-----------------------------------|:------------|
| ClosestPointPair            | Closest Point Pair                        | Introduction to Recursion          |             |
| StrassenAlgorithm           | Matrix Multiplication                     | D&C: Strassen's Algorithm          |             |
| MaxContiguousSubsequence    | Max Continuous Subsequence Sum            | D&C: Fast Fourier Transform I      |             |
| DeterministicOrderSelection | Kth smallest element in an unordered list | D&C: Deterministic order selection |             |
| KnapsackProblem             | 0/1 Knapsack Problem                      | DP I: 0-1 Knapsack Problem         |             |
| MatrixChainMultiplication   | Min multiplications in a matrix chain     | DP II: Matrix Chain Multiplication |             |
| AllPairsShortestPath        | Shortest path of all pairs in a graph     | DP: APSP                           |             |
| MinimumSpanningTrees        | Minimum spanning tree of a graph          | Greedy: MST (Kruskal/Prim)         |             |
| HuffmanEncoding             | String compression                        | Greedy: Huffman coding             |             |

### Runtime

- Times are in seconds.
- If it ran in 25 or less ms, then I just put 0.
- DNF means that it did not finish in under an hour.
- Times are from running the algorithms on my laptop, the specs are:
  * intel i7 11800h 8c/16t @ 2.30 GHz
  * 16gb 3200 MHz SODIMM
  * RTX 3050 Ti Mobile
  * Micron 2300 NVMe 512gb

| ClosestPointPair (points)   | 0. 5 | 1. 5 | 2. 10 | 3. 20 | 4. 50 | 5. 100 | 6. 5K | 7. 10K | 8. 20K | 9. 500K | 10. 1M  |
|:----------------------------|:-----|:-----|:------|:------|:------|:-------|:------|:-------|:-------|:--------|:--------|
| python - brute force        | 0    | 0    | 0     | 0     | 0     | 0      | 2.065 | 8.538  | 35.974 | DNF     | DNF     |
| python - divide and conquer | 0    | 0    | 0     | 0     | 0     | 0      | 0     | 0.031  | 0.078  | 2.643   | 5.636   |
| c++ - brute force           | 0    | 0    | 0     | 0     | 0     | 0      | 0.031 | 0.085  | 0.297  | 166.465 | 688.185 |
| c++ - divide and conquer    | 0    | 0    | 0     | 0     | 0     | 0      | 0     | 0      | 0      | 0.333   | 0.643   |

| StrassenAlgorithm (n x n)   | 0. 3 (4) | 1. 3 (4) | 2. 4 | 3. 5 (8) | 4. 10 (16) | 5. 100 (128) | 6. 1K (1024) | 7. 1.5K (2048) | 8. 2K (2048) | 9. 2.5K (4096) | 10. 3K (4096) |
|:----------------------------|:---------|:---------|:-----|:---------|:-----------|:-------------|:-------------|:---------------|:-------------|:---------------|:--------------|
| python - brute force        | 0        | 0        | 0    | 0        | 0          | 0.955        | 527.769      | DNF            | DNF          | DNF            | DNF           |
| python - divide and conquer | 0        | 0        | 0    | 0        | 0          | 0            | 1.158        | 8.089          | 8.752        | 61.469         | 62.317        |
| python - strassen           | 0        | 0        | 0    | 0        | 0          | 0            | 0.705        | 3.221          | 3.769        | 19.539         | 20.643        |
| python - numpy dot          | 0        | 0        | 0    | 0        | 0          | 0            | 1.064        | 3.270          | 16.195       | 51.726         | 118.541       |
| c++ - brute force           | 0        | 0        | 0    | 0        | 0          | 0            | 0.889        | 13.006         | 13.283       | 425.552        | 420.609       |
| c++ - divide and conquer    | 0        | 0        | 0    | 0        | 0          | 0            | 0.743        | 5.118          | 5.311        | 40.168         | 39.809        |
| c++ - strassen              | 0        | 0        | 0    | 0        | 0          | 0            | 0.488        | 2.671          | 2.920        | 17.495         | 18.041        |

| MaxContiguousSubsequence (numbers) | 0. 11 | 1. 10 | 2. 20 | 3. 50 | 4. 200 | 5. 500 | 6. 10K   | 7. 50K   | 8. 200K | 9. 1M | 10. 2M |
|:-----------------------------------|:------|:------|:------|:------|:-------|:-------|:---------|:---------|:--------|:------|:-------|
| python - brute force               | 0     | 0     | 0     | 0     | 0      | 0.142  | 1438.271 | DNF      | DNF     | DNF   | DNF    |
| python - divide and conquer        | 0     | 0     | 0     | 0     | 0      | 0      | 0        | 0.094    | 0.392   | 2.197 | 4.396  |
| python - kadane                    | 0     | 0     | 0     | 0     | 0      | 0      | 0        | 0        | 0.031   | 0.189 | 0.391  |
| c++ - brute force                  | 0     | 0     | 0     | 0     | 0      | 0      | 14.575   | 1835.635 | DNF     | DNF   | DNF    |
| c++ - divide and conquer           | 0     | 0     | 0     | 0     | 0      | 0      | 0        | 0        | 0.036   | 0.133 | 0.265  |
| c++ - kadane                       | 0     | 0     | 0     | 0     | 0      | 0      | 0        | 0        | 0.028   | 0.097 | 0.184  |

| DeterministicOrderSelection (numbers) | 0. 10 | 1. 10 | 2. 20 | 3. 50 | 4. 100 | 5. 1K | 6. 50K | 7. 1M | 8. 2M | 9. 3M | 10. 5M |
|:--------------------------------------|:------|:------|:------|:------|:-------|:------|:-------|:------|:------|:------|:-------|
| python - brute force                  | 0     | 0     | 0     | 0     | 0      | 0     | 0.078  | 2.237 | 4.923 | 8.206 | 14.286 |
| python - built in sort                | 0     | 0     | 0     | 0     | 0      | 0     | 0      | 0.267 | 0.563 | 0.828 | 1.447  |
| python - median of medians            | 0     | 0     | 0     | 0     | 0      | 0     | 0      | 0.642 | 1.297 | 2.001 | 3.451  |
| python - quick select                 | 0     | 0     | 0     | 0     | 0      | 0     | 0      | 0.298 | 0.750 | 1.335 | 1.818  |
| c++ - brute force                     | 0     | 0     | 0     | 0     | 0      | 0     | 0      | 0.259 | 0.505 | 0.753 | 1.246  |
| c++ - built in sort                   | 0     | 0     | 0     | 0     | 0      | 0     | 0      | 0.268 | 0.520 | 0.784 | 1.298  |
| c++ - median of medians               | 0     | 0     | 0     | 0     | 0      | 0     | 0      | 0.211 | 0.453 | 0.672 | 1.152  |
| c++ - quick select                    | 0     | 0     | 0     | 0     | 0      | 0     | 0      | 0.216 | 0.417 | 0.622 | 1.032  |

| KnapsackProblem (bricks/capacity)      | 0. 10/68 | 1. 8/50 | 2. 10/66 | 3. 15/92 | 4. 20/139 | 5. 50/310 | 6. 100/604 | 7. 300/1878 | 8. 1K/6229 | 9. 2K/12607 | 10. 5K/31222    |
|:---------------------------------------|:---------|:--------|:---------|:---------|:----------|:----------|:-----------|:------------|:-----------|:------------|:----------------|
| python - brute force                   | 0        | 0       | 0        | 0        | 0.236     | DNF       | DNF        | DNF         | DNF        | DNF         | DNF             |
| python - dynamic programming recursion | 0        | 0       | 0        | 0        | 0         | 0         | 0          | 0.189       | 2.472      | 10.393      | DNF<sup>1</sup> |
| python - dynamic programming           | 0        | 0       | 0        | 0        | 0         | 0         | 0          | 0.142       | 1.672      | 7.333       | 46.907          |
| c++ - brute force                      | 0        | 0       | 0        | 0        | 0         | DNF       | DNF        | DNF         | DNF        | DNF         | DNF             |
| c++ - dynamic programming recursion    | 0        | 0       | 0        | 0        | 0         | 0         | 0          | 0           | 0.070      | 0.242       | 1.416           |
| c++ - dynamic programming              | 0        | 0       | 0        | 0        | 0         | 0         | 0          | 0           | 0          | 0.076       | 0.437           |

_DNF<sup>1</sup> - Python crashed due to recursion limits, would probably finish otherwise._

| MatrixChainMultiplication (matrices)   | 0. 4 | 1. 4 | 2. 5 | 3. 6 | 4. 20   | 5. 30 | 6. 40 | 7. 50 | 8. 100 | 9. 150 | 10. 200 |
|:---------------------------------------|:-----|:-----|:-----|:-----|:--------|:------|:------|:------|:-------|:-------|:--------|
| python - brute force                   | 0    | 0    | 0    | 0    | 242.921 | DNF   | DNF   | DNF   | DNF    | DNF    | DNF     |
| python - dynamic programming recursion | 0    | 0    | 0    | 0    | 0       | 0     | 0     | 0     | 0.062  | 0.203  | 0.470   |
| python - dynamic programming           | 0    | 0    | 0    | 0    | 0       | 0     | 0     | 0     | 0.031  | 0.109  | 0.251   |
| c++ - brute force                      | 0    | 0    | 0    | 0    | 5.600   | DNF   | DNF   | DNF   | DNF    | DNF    | DNF     |
| c++ - dynamic programming recursion    | 0    | 0    | 0    | 0    | 0       | 0     | 0     | 0     | 0      | 0      | 0       |
| c++ - dynamic programming              | 0    | 0    | 0    | 0    | 0       | 0     | 0     | 0     | 0      | 0      | 0       |

| AllPairsShortestPath - dijkstra (1K vertices/50k edges) | 0.    | 1.    | 2.    | 3.    | 4.    | 5.    | 6.    | 7.    | 8.    | 9.    | 10.   |
|:--------------------------------------------------------|:------|:------|:------|:------|:------|:------|:------|:------|:------|:------|:------|
| python - min heap                                       | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 |
| python - array                                          | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 | 0.141 |
| c++ - min heap                                          | 0.093 | 0.093 | 0.093 | 0.093 | 0.093 | 0.093 | 0.093 | 0.093 | 0.093 | 0.093 | 0.093 |
| c++ - array                                             | 0.036 | 0.036 | 0.036 | 0.036 | 0.036 | 0.036 | 0.036 | 0.036 | 0.036 | 0.036 | 0.036 |

| AllPairsShortestPath - floyd warshall (vertices/edges) | Graph. 1K/50K |
|:-------------------------------------------------------|:--------------|
| python                                                 | 42.527        |
| c++                                                    | 0.293         |

| MinimumSpanningTrees (vertices/edge) | 0. 10/13 | 1. 9/11 | 2. 15/26 | 3. 20/34 | 4. 50/126 | 5. 100/487 | 6. 200/2013 | 7. 500/6230 | 8. 750/14090 | 9. 1K/25185 | 10. 1.5K/56002 |
|:-------------------------------------|:---------|:--------|:---------|:---------|:----------|:-----------|:------------|:------------|:-------------|:------------|:---------------|
| python - prim                        | 0        | 0       | 0        | 0        | 0         | 0          | 0           | 0           | 0.047        | 0.062       | 0.189          |
| python - kruskal                     | 0        | 0       | 0        | 0        | 0         | 0          | 0           | 0.031       | 0.109        | 0.266       | 0.969          |
| c++ - prim min heap                  | 0        | 0       | 0        | 0        | 0         | 0          | 0           | 0           | 0            | 0.031       | 0.062          |
| c++ - prim array                     | 0        | 0       | 0        | 0        | 0         | 0          | 0           | 0           | 0.081        | 0.213       | 0.940          |
| c++ - kruskal                        | 0        | 0       | 0        | 0        | 0         | 0          | 0           | 0           | 0            | 0           | 0.046          |

| HuffmanEncoding (characters) | 0. 10 | 1. 10 | 2. 15 | 3. 20 | 4. 500 | 5. 1K | 6. 2K | 7. 5K | 8. 10K | 9. 200K | 10. 500K |
|:-----------------------------|:------|:------|:------|:------|:-------|:------|:------|:------|:-------|:--------|:---------|
| python - huffman             | 0     | 0     | 0     | 0     | 0      | 0     | 0     | 0     | 0      | 0       | 0        |
| c++ - huffman                | 0     | 0     | 0     | 0     | 0      | 0     | 0     | 0     | 0      | 0       | 0        |
