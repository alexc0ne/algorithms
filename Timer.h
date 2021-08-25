#pragma once

#include <iostream>
#include <chrono>
#include <string>


class Timer
{
private:
    std::chrono::time_point<std::chrono::steady_clock> start, finish;
    std::string msg = "main";
public:
    Timer()
    {
        start = std::chrono::steady_clock::now();
    }
    Timer(const std::string& msg)
    {
        this->msg = msg;
        start = std::chrono::steady_clock::now();
    }
    ~Timer()
    {
        finish = std::chrono::steady_clock::now();
        std::cout << std::endl;
        std::cout << "\e[1m" << "Duration( " << msg << " ): " << "\e[0m"
                  << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
                  << " ms"
                  << std::endl;
    }
};
