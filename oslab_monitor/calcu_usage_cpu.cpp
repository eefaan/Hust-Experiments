#include "calcu_usage_cpu.h"
#include <QDebug>
#include <QString>
calcu_usage_cpu::calcu_usage_cpu()
{

}

calcu_usage_cpu::calcu_usage_cpu(string file):
    file_name(file)
{

}

calcu_usage_cpu::~calcu_usage_cpu(){}

string calcu_usage_cpu::show_usage()
{
    fstream fs;
    string line;
    string result;
    char buffer[1000];
    fs.open(file_name, fstream::in);
    if (!fs.is_open()){
        return string("open file failed!");
    }

    fs.getline(buffer,1000);
    line=buffer;

    // re
    string patterm("cpu[\\d]*");
    regex re(patterm);
    smatch sm;

     while(regex_search(line, sm, re)){
        string name(sm.str());
//        qDebug() << QString::fromStdString(line);

        line = sm.suffix();
//        qDebug() << QString::fromStdString(line);
        patterm = "[0-9]+";
        re = regex(patterm);
        regex_search(line, sm, re);
        double user = stod(sm.str());
        line = sm.suffix();
        regex_search(line, sm, re);
        int nice = stoi(sm.str());
        line = sm.suffix();
        regex_search(line, sm, re);
        int system = stoi(sm.str());
        line = sm.suffix();
        regex_search(line, sm, re);
        int idle = stoi(sm.str());
        double us_num = 100*(user+nice+system)/(user+nice+system+idle);
        result += (name+":");
        result += to_string(us_num);
        result += "% ";

//        qDebug() << QString::fromStdString(result);
        fs.getline(buffer,1000);
        line=buffer;
        patterm = "cpu[\\d]*";
        re = regex(patterm);
//        qDebug() << "nextline:"+QString::fromStdString(line);
    }
//    qDebug() << QString::fromStdString(result);
    return result;
}
