#pragma once

#include <chrono>
#include <string>
#include <iostream>

using namespace std::chrono;
using std::string;

template <typename T>
class TimeCost final
{
public:
    TimeCost(const string& name, const string& unit):_name(name), _unit(unit), _start(system_clock::now()) {}
    TimeCost(const string& name):_name(name), _start(system_clock::now()) {
        if(typeid(T) == typeid(std::chrono::milliseconds)) _unit = "ms";
        else if(typeid(T) == typeid(std::chrono::microseconds)) _unit = "us";
        else if(typeid(T) == typeid(std::chrono::nanoseconds)) _unit = "ns";
        else if(typeid(T) == typeid(std::chrono::seconds)) _unit = "s";
    }
    void start() { _start = system_clock::now(); _showAtDctor = false; }
    void end() { show_cost(); }

    ~TimeCost() { if(_showAtDctor) show_cost(); }

    TimeCost(const TimeCost&) = delete;
    TimeCost& operator=(const TimeCost&) = delete;

private:
    void show_cost()
    {   
        _cost = duration_cast<T>(system_clock::now() - _start);
        std::cout << _name << " TimeCost "<< _cost.count() << _unit << std::endl;
    }   

    string _name;
    string _unit;
    system_clock::time_point _start;
    T _cost;
    bool _showAtDctor = true;
};

using msCost = TimeCost<std::chrono::milliseconds>;
using usCost = TimeCost<std::chrono::microseconds>;
using nsCost = TimeCost<std::chrono::nanoseconds>;