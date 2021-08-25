#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <map>
#include <set>


template <typename Collection>
std::string Join(const Collection& collection, char separator)
// два условия на коллекцию:
// 1. по ней можно итерироваться range-based for'ом
// 2. её элементы можно выводить в поток
{
    std::stringstream ss;
    bool first = true;
    for (const auto& item : collection)
    {
        if (!first)
        {
            ss << separator << ' ';
        }
        first = false;
        ss << item;
    }
    return ss.str();
}

template <typename First, typename Second>
std::ostream& operator<< (std::ostream& out, const std::pair<First, Second>& p)
{
    return out << "<" << p.first << ", " << p.second << ">";
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v)
{
    return out << "[" << Join(v, ',') << "]";
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::set<T>& v)
{
    return out << "(" << Join(v, ',') << ")";
}

template <typename Key, typename Value>
std::ostream& operator<< (std::ostream& out, const std::map<Key, Value>& m)
{
    return out << "{" << Join(m, ',') << "}";
}

