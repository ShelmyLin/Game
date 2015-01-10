#ifndef _GLOBAL_H
#define _GLOBAL_H
#define SLEEP_TIME              500000 //refresh time, unit: us
#define FIGHT_RATE              3     // one beast can fight 3 humans, human win possibility = 100 * (num_human / (double)(num_beast * 3));
#define ESCAPE_RATE             50    // human has a 50% possibility to run away
#define FEMALE                  true
#define MALE                    false
#define LIVING                  true
#define DEAD                    false
#define ADULT                   true
#define YOUNG                   false

#define MAX_X                   100
#define MAX_Y                   30
#define MAX_XY                  3061

//for human
#define COME_BACK               1
#define HANG_OUT                2
#define HUNT_OUT                3
#define HOME_X                  10
#define HOME_Y                  5
#define MATURITY_FEMALE         4300    // 12 * 360  //female maturity eailier than male
#define MATURITY_MALE           5040    // 14 * 360
#define MATURITY_RANDOM         720     //  2 * 360 eg. 12 * 360 + random() % (2 * 360);
#define SURVIVAL_RATE_BABY      0.8     // when a baby is born, his survival rate is 0.7 and increase as time passes by
#define SURVIVAL_RATE_ADULT     0.998   // a adult's survival rate
#define SURVIVAL_RATE_INDEX     0.0019  // for female and male have a different maruruty time, so male should add an index to keep the balance
#define MAX_LIFE_TIME           21600   // 60 * 360 = 21600
#define BECOME_OLD              14400   // 40 * 360 = 14400, from this day on, human becomes old and his survival rate decreases
#define PREGNANT_DAY            300     //   
#define STOP_PREGNANT           12600   // 35 * 360 = 12600, from this day on, female stop be pregnant
#define PREGNANT_RATE           40      // 50%
#define MAX_SEX_TIME            1       // for a male or female, the most time that he/she will have sex
#define STRENGTH_MAX            100
#define INTELLIGENCE_MAX        100
#define EXPERIENCE_MAX          100

//for beast
#define COME_BACK_B             4
#define HANG_OUT_B              5
#define HUNT_OUT_B              6
#define HOME_X_B                90
#define HOME_Y_B                25
#define MATURITY_FEMALE_B       1080    // 3 * 360 from wikipedia-tiger
#define MATURITY_MALE_B         1440    // 4 * 360
#define MATURITY_RANDOM_B       360     //  1 * 360 eg. 6 * 360 + random() % (1 * 360);
#define SURVIVAL_RATE_BABY_B    0.3     // when a baby is born, his survival rate is 0.7 and increase as time passes by
#define SURVIVAL_RATE_ADULT_B   0.9   // a adult's survival rate
#define SURVIVAL_RATE_INDEX_B   0.0009  // for female and male have a different maruruty time, so male should add an index to keep the balance
#define MAX_LIFE_TIME_B         9360    // 26 * 360 = 9360
#define BECOME_OLD_B            7200    // 20 * 360 = 7200, from this day on, beast becomes old and his survival rate decreases
#define PREGNANT_DAY_B          112     // from wikipedia-tiger  
#define STOP_PREGNANT_B         7200    // 20 * 360 = 7200, from this day on, female stop be pregnant
#define PREGNANT_RATE_B         99      // 99%
#define MAX_SEX_TIME_B          1       // for a male or female, the most time that he/she will have sex
#define BABY_NUM_B              3       // 3-4 from wikipedia
#define WANT_SEX_DAY_B          4       // female wants to have sex only a few days
#define WANT_SEX_B              true    // during want-sex period, YES--from wikipedia
#define REFUSE_SEX_B            false            
#define STRENGTH_MAX_B          100
#define INTELLIGENCE_MAX_B      100
#define EXPERIENCE_MAX_B        100

struct Point{

    unsigned int x;
    unsigned int y;
};


#endif
