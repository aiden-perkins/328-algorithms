cmake_minimum_required(VERSION 3.27)
project(algorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(algorithms
        main.cpp
        ClosestPointPair/ClosestPointPair.cpp
        ClosestPointPair/ClosestPointPair.h
        StrassenAlgorithm/StrassenAlgorithm.cpp
        StrassenAlgorithm/StrassenAlgorithm.h
        MaxContiguousSubsequence/MaxContiguousSubsequence.cpp
        MaxContiguousSubsequence/MaxContiguousSubsequence.h
        DeterministicOrderSelection/DeterministicOrderSelection.cpp
        DeterministicOrderSelection/DeterministicOrderSelection.h
        KnapsackProblem/KnapsackProblem.cpp
        KnapsackProblem/KnapsackProblem.h
        MatrixChainMultiplication/MatrixChainMultiplication.cpp
        MatrixChainMultiplication/MatrixChainMultiplication.h
)
