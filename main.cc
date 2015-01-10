/* Written by Xiongmin Lin <linxiongmin@gmail.com>, ISIMA, Clermont-Ferrand *
 * (c) 2014. All rights reserved.                                           */


#include <iostream>
#include <math.h>
#include "nature.h"
#include "log.h"
using namespace std;
int main()
{
    int origin_h;
    int origin_b;
    cout<<"please input the original number of humans and beasts"<<endl;
    cin>>origin_h;
    cin>>origin_b;
    Nature nature;
    nature.init(origin_h, origin_b);
    nature.timefly();
    return 0;
}

