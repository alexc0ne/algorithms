#pragma once
#include <vector>


void siftDown(std::vector<int> & v, int i, int heapSize);
void make_heap(std::vector<int> & v);
void heap_sort(std::vector<int> & v);
