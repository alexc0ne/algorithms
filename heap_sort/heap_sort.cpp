#include "heap_sort.h"
#include "Output.h"
#include <vector>


void siftDown(std::vector<int> & v, int i, int heapSize)
{
    int j;
    int left;
    int right;
    while (true)
    {
        j = i;

        left = 2 * i + 1;
        right = left + 1;
 
        if (left < heapSize and v[left] < v[j])
            j = left;

        if (right < heapSize and v[right] < v[j])
            j = right;

        if (j == i)
            break;

        std::swap(v[i], v[j]);
        i = j;
    }
}



void make_heap(std::vector<int> & v)
{
    int end = v.size();
    for (int i = end - 1; i >= 0; --i)
        siftDown(v, i, end);
}



void heap_sort(std::vector<int> & v)
{
    if (v.empty()) return;


    make_heap(v);


    int n = v.size();
    for (int i = n - 1; i >= 0; --i)
    {
        std::swap(v.front(), v[i]);
        siftDown(v, 0, i);
    }

    for (int i = 0; i < n / 2; ++i)
        std::swap(v[i], v[n - 1 - i]);
}


