#include <iostream>
#include <random>
#include <set>
#include "ShuffleArray.h"

bool testShuffle();
bool testConsistent();
bool testUnique();

int main()
{
    std::cout << "TestShuffle: " << (testShuffle() ? "Success" : "Fail") << "\n";
    std::cout << "TestConsistent: " << (testConsistent() ? "Success" : "Fail") << "\n";
    std::cout << "TestUnique: " << (testUnique() ? "Success" : "Fail") << "\n";
}

// test if values gets shuffled
bool testShuffle() {
    const size_t testRuns = 32;
    const size_t N = 10032;

    // initialize array 
    auto arr = ConstantShuffle::ShuffleArray<int, N, std::mt19937>(std::mt19937(32));

    for (int runs = 0; runs < testRuns; ++runs)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            arr[i] = i;
        }
        arr.shuffle();

        size_t numFixPoints = 0;
        for (std::size_t i = 0; i < N; ++i)
        {
            if (arr[i] == i)
                ++numFixPoints;
        }

        // test if at least half of the values moved
        if (numFixPoints > N / 2)
            return false;
    }

    return true;
}

// test if values stay if read again
bool testConsistent() {
    const size_t testRuns = 32;
    const size_t N = 10032;

    // initialize array 
    auto arr = ConstantShuffle::ShuffleArray<int, N, std::mt19937>(std::mt19937(1024));
    for (std::size_t i = 0; i < N; ++i)
    {
        arr[i] = i;
    }

    for (int runs = 0; runs < testRuns; ++runs)
    {
        arr.shuffle();
        std::array<int, N> copy;
        for (std::size_t i = 0; i < N; ++i)
        {
            copy[i] = arr[i];
        }

        // check if repeated reading results in same values
        for (std::size_t i = 0; i < N; ++i)
        {
            if (copy[i] != arr[i])
                return false;
        }
    }

    return true;
}

// test that each index points to a unique value
bool testUnique() {
    const size_t testRuns = 32;
    const size_t N = 10032;

    // initialize array 
    auto arr = ConstantShuffle::ShuffleArray<int, N, std::mt19937>(std::mt19937(21));
    for (std::size_t i = 0; i < N; ++i)
    {
        arr[i] = i;
    }

    for (int runs = 0; runs < testRuns; ++runs)
    {
        arr.shuffle();
        std::set<int> discovered;
        for (std::size_t i = 0; i < N; ++i)
        {
            // check if two indices have same value
            if (not discovered.insert(arr[i]).second) {
                return false;
            }
        }
    }

    return true;
}