/* Written by Xiongmin Lin <linxiongmin@gmail.com>, ISIMA, Clermont-Ferrand *
 * (c++) 2014. All rights reserved.                                         */

#include "player.h"
Player::Player()
{
  live         = LIVING;
  gender       = MALE;
  id           = 0;
  level        = 0;
  money        = 0;
     
  intelligence = 0;
  strength     = 0;
  experience   = 0;
  
  hp           = 0;
  mp           = 0;
  position.x   = 0;
  position.y   = 0;
  dest.x       = 0;
  dest.y       = 0;
  phy_attack   = 0;  
  phy_armor    = 0;
  mag_armor    = 0;
}
Player::~Player()
{

}


bool Player::move()
{
  
  int x  = 0;
  int y  = 0;
  bool r = false;
  if(position.x != dest.x && position.y != dest.y)
  {
    x = (dest.x - position.x) > 0 ? 1 : -1;
    y = (dest.y - position.y) > 0 ? 1 : -1;
  }
  else if(position.x != dest.x)
  {
    x = (dest.x - position.x) > 0 ? 1 : -1;
  }
  else if(position.y != dest.y)
  {
    y = (dest.y - position.y) > 0 ? 1 : -1;
  }
  else
  {
    r = true;
  }
  position.x += x;
  position.y += y;
  return r;
}

void Player::Show()
{
   printf("id = %d, level = %d, experience = %d, phy_attack = %d, phy_armor = %d, mag_armor = %d, money = %d\n",
          id, level, experience, phy_attack, phy_armor, mag_armor, money);

}
