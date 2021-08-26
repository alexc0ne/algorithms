#include "quick_sort.h"
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <random>
#include <utility>



size_t get_random_in_range(size_t begin, size_t end)
{
    using namespace std::chrono;

    auto seed = system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::uniform_int_distribution<size_t> u(begin, end - 1);

    return u(e);
}



// in-place
void quick_sort(std::vector<int> & a)
{
    if (a.empty()) return;

    size_t begin = 0;
    size_t end = a.size();
    sort(begin, end, a);
}



std::pair<int, int> partition3(size_t begin,
                               size_t end,
                               std::vector<int> & a)
{
    size_t idx = get_random_in_range(begin, end);
    int pivot = a[idx];


    size_t begin_eq = begin;
    size_t begin_gr = begin;


    for (size_t i = begin; i < end; ++i)
    {
        if (a[i] > pivot) continue;

        if (a[i] == pivot)
        {
            std::swap(a[begin_gr], a[i]);
            ++begin_gr;
            continue;
        }

        //if (a[i] < pivot)
        std::swap(a[begin_gr], a[i]);
        std::swap(a[begin_eq], a[begin_gr]);
        ++begin_eq;
        ++begin_gr;
    }

    return {begin_eq, begin_gr};
}


// with recursion
void sort(size_t begin, size_t end, std::vector<int> & a)
{
    if (end - begin <= 1) return;


    std::pair<int, int> begin_eq_gr = partition3(begin, end, a);


    sort(begin, begin_eq_gr.first, a);
    sort(begin_eq_gr.second, end, a);
}


// to avoid recursion one can put a pair of pointers (begin, end)
// to the stack and while stack is not empty, pop a pair from
// there, partition and put again onto stack

// without recursion
/*
void sort(size_t begin, size_t end, std::vector<int> & a)
{
    std::stack<std::pair<int, int>> pending;
    pending.emplace(begin, end);

    std::pair<int, int> curr;
    std::pair<int, int> part;
    while (!pending.empty())
    {
        curr = pending.top();
        pending.pop();

        if (curr.second - curr.first <= 1) continue;

        part = partition3(curr.first, curr.second, a);
        pending.emplace(curr.first, part.first);
        pending.emplace(part.second, curr.second);
    }
}
*/


