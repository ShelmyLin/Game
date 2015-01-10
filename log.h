#ifndef _LOG_H
#define _LOG_H
#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>
using namespace std;

class Log{

public:
   Log();
  ~Log();
private:
  ofstream file;
  char curdict[100];               ///< current dictionary
  char file_name[100];             ///< the name of the log file
private:
  void close();                    ///< close log file
  string current_date_time();      ///< get current time
public:
  void write(int day, string str); ///< write log the message into log file 
  void open();                     ///< create a new log file "log.txt" in current dictionary

};

#endif
