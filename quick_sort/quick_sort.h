#pragma once
#include <vector>
#include <random>
#include <chrono>
#include <stdexcept>
#include <iostream>



size_t get_random_in_range(size_t begin, size_t end);
void quick_sort(std::vector<int> & a);
std::pair<int, int> partition3(size_t begin,
                               size_t end,
                               std::vector<int> & a);
void sort(size_t begin, size_t end, std::vector<int> & a);

