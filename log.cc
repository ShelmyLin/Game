#include "log.h"
Log::Log()
{
  open();
}

Log::~Log()
{
  // close the log file
  file.close();
}

void Log::open()
{
  // create a new log file "log.txt" in current dictionary
  getwd(curdict);
  sprintf(file_name,"%s//log.txt", curdict);
  file.open(file_name);
}

void Log::write(int day, string str)
{
  // write the log message into log file
  file<<current_date_time()<<"  ";
  file<<"[day = "<<day<<"] ";  
  file<<str<<endl;
}

string Log::current_date_time()
 {
  // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return buf;
}


