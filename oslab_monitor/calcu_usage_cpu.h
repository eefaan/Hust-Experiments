#ifndef CALCU_USAGE_CPU_H
#define CALCU_USAGE_CPU_H

#include <string>
#include <regex>
#include <fstream>
using namespace std;

class calcu_usage_cpu
{
public:
    calcu_usage_cpu();
    calcu_usage_cpu(string file_name);
    ~calcu_usage_cpu();

public:
    string file_name;
    string show_usage(double &n);
};

#endif // CALCU_USAGE_CPU_H
