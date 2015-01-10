#ifndef _TASK_H
#define _TASK_H
#include <stdio.h>
#include <string.h>
using namespace std;
class Task
{
public:
  Task();
  ~Task();
public:
  string despn;             ///< describe the task
  unsigned int experience;
  unsigned int money;
  struct Point point_des;  // you can do the task around point_des 
  struct Point point_NPC;  
  int level;    // suitable for level player
};

#endif
