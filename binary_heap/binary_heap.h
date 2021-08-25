#pragma once
#include <vector>



class BinaryHeap
{
private:

    std::vector<int> v_;

    void siftDown(int i);
    void siftUp(int i);


public:

    BinaryHeap();
    BinaryHeap(const std::vector<int> & v);

    std::vector<int> toVector() const;
    bool isEmpty() const;
    void insert(int x);
    int removeMin();
};

