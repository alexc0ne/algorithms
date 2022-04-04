/*
 *   no templates!
 *   no exceptions!
 *   no additional checks!
*/



#include "list.h"



std::ostream & operator<<(std::ostream & out, const List & l)
{
    std::stringstream ss;
    ss << "list = [";

    bool first = true;
    for (Node * ptr = l.head_; ptr != nullptr; ptr = ptr->next_)
    {
        if (!first) ss << ", ";
        first = false;
        ss << ptr->val_;
    }
    
    ss << "]";    
    out << ss.str();
    return out;
}



Node * List::iterate(int pos) const
{
    Node * ptr = head_;
    for (int i = 0; i < pos; ++i)
        ptr = ptr->next_;

    return ptr;
}



List::~List()
{
	while (size_) pop_back();
}



int List::size() const
{
    return size_;
}



void List::pop_back()
{
    if (!size_) return;
    
    if (size_ == 1) {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
        --size_;
        return;
    }

    Node * tmp = tail_;
    tail_ = tail_->prev_;

    if (tail_) tail_->next_ = nullptr;

    delete tmp;
    --size_;
}



void List::pop_front()
{
    if (!size_) return;
    
    if (size_ == 1) {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
        --size_;
        return;
    }

    Node * tmp = head_;
    head_ = head_->next_;

    if (head_) head_->prev_ = nullptr;

    delete tmp;
    --size_;
}



void List::push_back(int val)
{
    Node * new_item = new Node(val);
    ++size_;

    // if list NOT empty
    if (tail_)
    {
        new_item->prev_ = tail_;
        tail_->next_ = new_item;
        tail_ = new_item;
        return;
    }

    // list empty
    tail_ = new_item;
    head_ = tail_;
}



void List::push_front(int val)
{
    Node * new_item = new Node(val);
    ++size_;

    // if list NOT empty
    if (head_)
    {
        new_item->next_ = head_;
        head_->prev_ = new_item;
        head_ = new_item;
        return;
    }

    // list empty
    head_ = new_item;
    tail_ = head_;
}



void List::insert_after(int pos, int val)
{
    if (pos == -1)
    {
        push_front(val);
        return;
    }
    if (pos + 1 == size_)
    {
        push_back(val);
        return;
    }

    ++size_;
    Node * to_insert = new Node(val);
    Node * prev = iterate(pos);
    Node * next = prev->next_;

    to_insert->next_ = next;
    to_insert->prev_ = prev;

    next->prev_ = to_insert;
    prev->next_ = to_insert;
}



void List::erase_after(int pos)
{
    if (pos + 2 > size_)
        return;

    if (pos == -1)
    {
        pop_front();
        return;
    }

    if (pos + 2 == size_)
    {
        pop_back();
        return;
    }

    --size_;
    Node * prev = iterate(pos);
    Node * to_delete = prev->next_;
    Node * next = to_delete->next_;

    delete to_delete;
    prev->next_ = next;
    next->prev_ = prev;
}



int List::get(int pos) const
{
    Node * ptr = iterate(pos);
    return ptr->val_;
}

