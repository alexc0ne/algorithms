#pragma once
#include <sstream>



struct Node
{
    int val_;
    Node * next_ = nullptr;
    Node * prev_ = nullptr;

    explicit Node(int val) : val_(val) {}
};



class List
{
private:

    int size_ = 0;
    Node * head_ = nullptr;
    Node * tail_ = nullptr;

    Node * iterate(int pos) const;

public:

    friend std::ostream & operator<<(std::ostream & out, const List & l);

    List() = default;
    ~List();

    int size() const;
    void pop_back();
    void pop_front();
    void push_back(int val);
    void push_front(int val);
    void insert_after(int pos, int val);
    void erase_after(int pos);
    int get(int pos) const;
};


std::ostream & operator<<(std::ostream & out, const List & l);

