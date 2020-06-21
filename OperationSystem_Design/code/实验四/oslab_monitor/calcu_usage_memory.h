#ifndef CALCU_USAGE_MEMORY_H
#define CALCU_USAGE_MEMORY_H

#include <string>
#include <regex>
#include <fstream>
using namespace std;

class calcu_usage_memory
{
public:
    calcu_usage_memory();
    calcu_usage_memory(string file_name);
    ~calcu_usage_memory();

public:
    string file_name;
    string show_usage(double &mem_n, double&swap_n);
};

#endif // CALCU_USAGE_MEMORY_H
