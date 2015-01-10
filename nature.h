#ifndef _NATURE_H
#define _NATURE_H
#include "beast.h"
#include "human.h"
#include "point.h"
#include "stdlib.h"
#include "log.h" 

class Nature{

public:
  Nature();
  Nature(int m_origin_h, int m_origin_b);         ///< the original number of human: m_origin_h, the original number of beast: m_origin_b
  ~Nature();
public:
  int timefly();                                  ///< the main function of Nature class, time flies every day, everything changes
  void init(int m_origin_h, int m_origin_b);      ///< initial the origin number of human and beast
public:
  double birth_rate_h;                            ///< the birth rate of human
  double death_rate_h;                            ///< the death rate of human
  double inc_rate_h;                              ///< the increase rate of human

  double birth_rate_b;                            ///< the birth rate of beast
  double death_rate_b;                            ///< the death rate of beast
  double inc_rate_b;                              ///< the increase rate of beast

public:
  double gender_ratio_h;                          ///< the gender ratio of male and female for human
  double gender_ratio_b;                          ///< the gender ratio of male and female for beast

  int origin_h;                                   ///< the original number of human
  int origin_female_h;                            ///< the original number of female human
  int origin_male_h;                              ///< the original number of male human


  int day;                                        ///< to mark the day that pasts
  int live_num_h;                                 ///< the living number of human
  int dead_num_h;                                 ///< the dead number of human
  int total_num_h;                                ///< the total number of human
  int size_h;                                     ///< to mark the size of human array
  int female_num_h;                               ///< the number of female human
  int male_num_h;                                 ///< the number of male human
  int hunt_num_h;                                 ///< the number of human that hunt out for food


  int origin_b;                                   ///< the origin number of beasts
  int origin_female_b;                            ///< the origin number of female beasts
  int origin_male_b;                              ///< the origin number of male beasts

  int live_num_b;                                 ///< the living number of beasts
  int dead_num_b;                                 ///< the dead number of beasts
  int total_num_b;                                ///< the total number of beasts
  int size_b;                                     ///< to mark the size of beast array
  int female_num_b;                               ///< the number of female beast
  int male_num_b;                                 ///< the number of male beast
  int hunt_num_b;                                 ///< the number of beast that hunt out for food
  char map[MAX_XY];                               ///< the map that records the state of nature
  int pos_h[MAX_XY];                              ///< to record the position of humans
  int pos_b[MAX_XY];                              ///< to tecord the position of beasts
private:
  Human *human;                                   ///< human array, the space was allocated dynamically
  Beast *beast;                                   ///< beast array, the space was allocated dymamically
  int babyNum_h;                                  ///< the new born babies
  Log log;                                        ///< log class, to record big event of the nature, it can also help to debug
  Random Crandom;
  bool sex_h(Human &h1, Human &h2);               ///< sex between male human h1 and female human h2
  bool sex_b(Beast &b1, Beast &b2);               ///< sex between male beast b1 and female beast b2
  void sex();                                     ///< all the sex activities
  void human_task();                              ///< the male goes out for hunting or coming back after hunting, move one step each day
  void human_grow();                              ///< human grows every day, add their age, having sex, give birth, and so on.
  void beast_task();                              ///< both male and female goes out for hunting
  void beast_grow();                              ///< beast grows every day, add their age, having sex, give birth, and so on.
  void reset_map();                               ///< every day, refresh the map
  double get_distance(Human h1, Human h2);        ///< get the distance between two humans
  void fight();                                   ///< human and beast fight when they meet,
  void fight_h_b(Point &p, int num_h, int num_b); ///< for a position, there are num_h humans and num_b beasts, they may fight, they may die
  void show();                                    ///< show the state of nature
};




#endif
