#pragma once


#include <iostream>
#include <chrono>
#include <assert.h>
#include <algorithm>


using namespace std;
using std::chrono::nanoseconds;

void make_low_entropy(int* low_entropy, int n, std::mt19937 &gen)
{
    std::uniform_int_distribution<int> dist(0, n-1);

    for(int i=0; i< 2 * (int) sqrt(n) ; ++i)
    {
        int first = dist(gen);
        int second = first;

        while (first == second)
        {
            second = dist(gen);
        }

        std::swap(low_entropy[first], low_entropy[second]);
    }
}

void copy(int* from, int* to, int n)
{
    for(int i=0; i<n; ++i)
        to[i] = from[i];
}


template<typename T>
nanoseconds calculate_time(T &str, int value)
{
    auto begin = std::chrono::steady_clock::now();
    str.insert(value);
    auto end = std::chrono::steady_clock::now();

    nanoseconds total(end - begin);
    return total;
}

template<class T>
nanoseconds timeit_search(T &data_structure, int target)
{
    auto begin = std::chrono::steady_clock::now();
    data_structure.search(target);
    auto end = std::chrono::steady_clock::now();

    nanoseconds total(end - begin);
    return total;
}
