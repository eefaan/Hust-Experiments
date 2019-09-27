#include "calcu_usage_memory.h"
#include <QDebug>
#include <QString>
calcu_usage_memory::calcu_usage_memory()
{

}

calcu_usage_memory::calcu_usage_memory(string file):
    file_name(file)
{

}

calcu_usage_memory::~calcu_usage_memory(){}

string calcu_usage_memory::show_usage(double &mem_n, double&swap_n)
{
    fstream fs;
    string line;
    string result;
    string patterm;
    regex re(patterm);
    smatch sm;
    double total;
    double free;
    char buffer[1000];
    fs.open(file_name, fstream::in);
    if(!fs.is_open()){
        return string("open file failed!");
    }

    fs.getline(buffer,1000);
    line=buffer;

    patterm = "MemTotal:";
    re = regex(patterm);
    if(regex_search(line,sm,re)){
        line = sm.suffix();
        patterm = "[0-9]+";
        re = regex(patterm);
        regex_search(line, sm, re);
        total = stod(sm.str());
    }
    else {
        return "mem data read error!";
    }

    fs.getline(buffer,1000);
    line=buffer;
    patterm = "MemFree:";
    re = regex(patterm);
    if(regex_search(line,sm,re)){
        line = sm.suffix();
        patterm = "[0-9]+";
        re = regex(patterm);
        regex_search(line, sm, re);
        free = stod(sm.str());
    }
    else {
        return "mem data read error!";
    }

    // make result
    double me_num = (1.0-(free/total))*100;
    mem_n = me_num;
    result += "memory:";
    result += to_string(me_num);
    result += "%";



    for(int i=0; i<13; i++){
        fs.getline(buffer,1000);
        line=buffer;
    }
    patterm = "SwapTotal:";
    re = regex(patterm);
    if(regex_search(line,sm,re)){
        line = sm.suffix();
        patterm = "[0-9]+";
        re = regex(patterm);
        regex_search(line, sm, re);
        total = stod(sm.str());
    }
    else {
        return "swap data read error!";
    }
    fs.getline(buffer,1000);
    line=buffer;
    patterm = "SwapFree:";
    re = regex(patterm);
    if(regex_search(line,sm,re)){
        line = sm.suffix();
        patterm = "[0-9]+";
        re = regex(patterm);
        regex_search(line, sm, re);
        free = stod(sm.str());
    }
    else {
        return "swap data read error!";
    }
    swap_n = (1.0-(free/total))*100;

    return result;
}