#include <vector>
#include <stdexcept>
#include "binary_heap.h"



void BinaryHeap::siftDown(int i)
{
    int j;
    int left;
    int right;
    while (true)
    {
        j = i;

        left = 2 * i + 1;
        right = left + 1;
 
        if (left < v_.size() and v_[left] < v_[j])
            j = left;

        if (right < v_.size() and v_[right] < v_[j])
            j = right;

        if (j == i)
            break;

        std::swap(v_[i], v_[j]);
        i = j;
    }
}



void BinaryHeap::siftUp(int i)
{
    int parent = (i - 1) / 2;        
    while (i > 0 and v_[i] < v_[parent])
    {
        std::swap(v_[i], v_[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}



BinaryHeap::BinaryHeap() {}



BinaryHeap::BinaryHeap(const std::vector<int> & v) : v_(v)
{
    if (v_.size() != 0)
        for (int i = v_.size() - 1; i >= 0; --i)
            siftDown(i);
}



std::vector<int> BinaryHeap::toVector() const
{
    std::vector<int> v(v_);
    return v;
}



bool BinaryHeap::isEmpty() const { return v_.empty(); }



void BinaryHeap::insert(int x)
{
    int i = v_.size();
    v_.push_back(x);
    siftUp(i);
}



int BinaryHeap::removeMin()
{
    if (v_.empty())
        throw std::runtime_error("removing element from empty heap");

    int res = v_.front();
    std::swap(v_.front(), v_.back());
    v_.pop_back();
    siftDown(0);

    return res;
}



