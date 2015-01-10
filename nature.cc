#include "nature.h"

Nature::Nature()
{

}

Nature::~Nature()
{
  
  free(human);  
  free(beast);
}

Nature::Nature(int m_origin_h, int m_origin_b)
{
  origin_h        = m_origin_h;
  total_num_h     = m_origin_h;
  live_num_h      = 0;
  dead_num_h      = 0;
  female_num_h    = 0;
  male_num_h      = 0;
  inc_rate_h      = 0;
  birth_rate_h    = 0;
  death_rate_h    = 0;
  gender_ratio_h  = 0;


  origin_b        = m_origin_b;
  total_num_b     = m_origin_b;
  live_num_b      = 0;
  dead_num_b      = 0;
  female_num_b    = 0;
  male_num_b      = 0;
  inc_rate_b      = 0;
  birth_rate_b    = 0;
  death_rate_b    = 0;
  gender_ratio_b  = 0;

}
void Nature::init(int m_origin_h, int m_origin_b)
{
  day             = 0;
  origin_h        = m_origin_h;
  total_num_h     = m_origin_h;
  live_num_h      = 0;
  dead_num_h      = 0;
  female_num_h    = 0;
  male_num_h      = 0;
  inc_rate_h      = 0;
  birth_rate_h    = 0;
  death_rate_h    = 0;
  gender_ratio_h  = 0;
  

  origin_b        = m_origin_b;
  total_num_b     = m_origin_b;
  live_num_b      = 0;
  dead_num_b      = 0;
  female_num_b    = 0;
  male_num_b      = 0;
  inc_rate_b      = 0;
  birth_rate_b    = 0;
  death_rate_b    = 0;
  gender_ratio_b  = 0;

//  log.open();
  int i, m, n;
  size_h = total_num_h * 2;
  size_b = total_num_b * 2;
  human  = (Human *)malloc(sizeof( Human )*size_h);
  beast  = (Beast *)malloc(sizeof( Beast )*size_h);
  /*set oroginal humans half male and half female, in case all male*/
  for(m = 0; m < total_num_h ; m++)
  {
    human[m].Init(m, -1, -1);
    human[m].SetGender((m%2==0) ? FEMALE : MALE);
    human[m].SetAge((Crandom.genrand_int31() % 20) + 1);
    human[m].gene_intelligence = 30 + Crandom.genrand_int31() % 70;
    human[m].gene_strength     = 30 + Crandom.genrand_int31() % 70;
  }
  //beast
  for(m = 0; m < total_num_b ; m++)
  {
    beast[m].Init(m, -1, -1);
    beast[m].SetGender((m%2==0) ? FEMALE : MALE);
    beast[m].SetAge((Crandom.genrand_int31() % 8) + 1);
  }
  
  log.write(day, "nature.init");

} 
double Nature::get_distance(Human h1, Human h2)
{
  double value = 0;
  double x1    = h1.position.x;
  double y1    = h1.position.y;
  double x2    = h2.position.x;
  double y2    = h2.position.y;
  value = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
  return value;
}

void Nature::reset_map()
{
  int w, h, m, n;
  int pos;
  for(h = 0; h < MAX_Y; h++ )
  {
    pos = h * (MAX_X + 2) + MAX_X + 1;
    map[pos-1] = '|';
    map[pos] = '\n';
    
    for(w = 0; w < MAX_X; w++)
    {
      pos        = h * (MAX_X + 2) + w;
      map[pos]   = ' ';
    }
  }
  map[MAX_XY -1] = '\0';
  for(m = 0; m < MAX_X * MAX_Y; m++)
  {
    pos_h[m] = 0;
    pos_b[m] = 0;
  }
  //log.write(day, "nature.reset_map");

}
void Nature::sex()
{
  int m, n;
  for(m = 0; m < total_num_h; m++)
  {
    for( n = 0; n < total_num_h; n++)
    {
      if(human[m].gender == MALE          &&
         human[n].gender == FEMALE        )
      {
        sex_h(human[m], human[n]);
      }
      else if(human[m].gender == FEMALE   &&
              human[n].gender == MALE     )
      {
        sex_h(human[n], human[m]);
      }
    }
  }
  //beast
  for(m = 0; m < total_num_b; m++)
  {
    for( n = 0; n < total_num_b; n++)
    {
      if(beast[m].gender == MALE          &&
         beast[n].gender == FEMALE        )
      {
        sex_b(beast[m], beast[n]);
      }
      else if(beast[m].gender == FEMALE   &&
              beast[n].gender == MALE     )
      {
        sex_b(beast[n], beast[m]);
      }
    }
  }

}

bool Nature::sex_h(Human &h1, Human &h2)   /*h1 male, h2 female*/
{
  bool value = false;
  if( h1.live         == LIVING             && 
      h1.maturity     == ADULT              &&
      h1.sex_time     < MAX_SEX_TIME        &&
      h1.task         == HANG_OUT           &&
      h2.live         == LIVING             &&
      h2.maturity     == ADULT              &&
      h2.sex_time     < MAX_SEX_TIME        &&
      h2.pregnant_day <= 2 * 30              )  // female can still have sex at the beginning of pregnant(may be 2 months)
  {
    h1.sex_time ++;
    h2.sex_time ++;
    char s[100];
    sprintf(s, "female human %d and male %d are having sex",
           h2.id,
           h1.id);
    string str = s;
    log.write(day, str);

    if(h2.pregnant    == false              && 
       Crandom.genrand_int31() % 100 < PREGNANT_RATE        )
    {
      h2.pregnant   = true;
      h2.id_partner = h1.id;  // to record babies' parents
      h1.id_partner = h2.id;
      char s[100];
      sprintf(s, "female human %d is pregnant", h2.id);
      string str = s;
      log.write(day, str);
    }
    value = true;
  }
  return value;
}

bool Nature::sex_b(Beast &h1, Beast &h2)   /* h1 male, h2 female */
{
  bool value = false;
  if( h1.live         == LIVING             && 
      h1.sex_state    == WANT_SEX_B         &&
      h2.live         == LIVING             &&
      h2.sex_state    == WANT_SEX_B          )  // female can still have sex at the beginning of pregnant(may be 2 months)
  {
    char s[100];
    sprintf(s, "female beast %d and male %d are having sex", h2.id, h1.id);
    string str = s;
    log.write(day, str);

    if(h2.pregnant == false                  &&
       Crandom.genrand_int31() % 100 < PREGNANT_RATE_B       )
    {
      h2.pregnant   = true;
      h1.id_partner = h2.id;
      h2.id_partner = h1.id;
      sprintf(s, "female beast %d is pregnant", h2.id);
      string str = s;
      log.write(day, str);

    }
    value = true;
  }
  return value;
}

void Nature::human_grow()
{
    // human grow every day
    int m, n;
    int babyNum   = 0;
    live_num_h    = 0;
    male_num_h    = 0;
    female_num_h  = 0;
    dead_num_h    = 0;
    hunt_num_h    = 0;
    for(m = 0; m < total_num_h; m++)
    {
      int num;
      human[m].sex_time = 0; // set the sex time back to 0, after they wake up ,they refresh//
      num = human[m].Grow();
      if(num > 0)
      {
          
        total_num_h += num;
        if(total_num_h >= size_h)
        {
          size_h = total_num_h * 2;
          human = (Human *)realloc(human, sizeof( Human ) * size_h);   // realloc takes a lot of time, so just double it when needed
          char s[100];
          sprintf(s, "realloc for human, total = %d, size = %d",
                  total_num_h,
                  size_h);
          string str = s;
          log.write(day, str);
        }

        for(n = total_num_h - num; n < total_num_h; n++)
        {
          int id_father = human[m].id_partner; 
          int id_mother = human[m].id;
          human[n].Init(n, id_father, id_mother);
          human[n].gene_intelligence = 0.5 * (human[id_father].gene_intelligence + human[id_mother].gene_intelligence);
          human[n].gene_strength = 0.5 * (human[id_father].gene_strength + human[id_mother].gene_strength);
          
          char s[100];
          sprintf(s, "female human %d gives born a cute baby, gene intelligence: %2.4f, gene strength: %2.4f",
                  m,
                  human[n].gene_intelligence,
                  human[n].gene_strength);
          string str = s;
          log.write(day, str);
        }
      }

      if(human[m].live == LIVING && human[m].gender == FEMALE)
      {
        live_num_h   ++;
        female_num_h ++;
      }
      else if(human[m].live == LIVING && human[m].gender == MALE)
      {
        live_num_h ++;
        male_num_h ++;
      }
      else
      {
        dead_num_h ++;
      }

      if(human[m].task != HANG_OUT && human[m].live == LIVING)
      {
        hunt_num_h ++;
      }
    }
    gender_ratio_h = male_num_h / (double)female_num_h;

  //log.write(day, "nature.human_grow");
}

void Nature::beast_grow()
{
    // beast grow every day
    int m, n;
    int babyNum   = 0;
    live_num_b    = 0;
    male_num_b    = 0;
    female_num_b  = 0;
    dead_num_b    = 0;
    hunt_num_b    = 0;
    for(m = 0; m < total_num_b; m++)
    {
      int num;
      beast[m].sex_time = 0; // set the sex time back to 0, after they wake up ,they refresh//
      num = beast[m].Grow();
      if(num > 0)
      {
          
        char s[100];
        sprintf(s, "female beast %d gives born %d cute baby(ies)",
                m, num);
        string str = s;
        log.write(day, str);
        
        total_num_b += num;
        if(total_num_b >= size_b)
        {
          size_b = total_num_b * 2;
          beast = (Beast *)realloc(beast, sizeof( Beast ) * size_b);   // realloc takes a lot of time, so just double it when needed
          char s[100];
          sprintf(s, "realloc for beast, total = %d, size = %d",
                  total_num_b,
                  size_b);
          string str = s;
          log.write(day, str);
        }

        for(n = total_num_b - num; n < total_num_b; n++)
        {
          int id_father = beast[m].id_partner; 
          int id_mother = beast[m].id;
          beast[n].Init(n, id_father, id_mother);
        }
      }

      if(beast[m].live == LIVING && beast[m].gender == FEMALE)
      {
        live_num_b   ++;
        female_num_b ++;
      }
      else if(beast[m].live == LIVING && beast[m].gender == MALE)
      {
        live_num_b ++;
        male_num_b ++;
      }
      else
      {
        dead_num_b ++;
      }

      if(beast[m].task != HANG_OUT_B && beast[m].live == LIVING)
      {
        hunt_num_b ++;
      }
    }
    gender_ratio_b = male_num_b / (double)female_num_b;

  //log.write(day, "nature.beast_grow");
}

void Nature::human_task()
{
    int m, n;
    for(m = 0; m < total_num_h; m++)
    {
      if(human[m].live     == LIVING         &&   // when a male become an adult, he goes out for hunting
         human[m].task     == HANG_OUT       &&
         human[m].gender   == MALE           &&
         human[m].maturity == ADULT          )
      {

        int rand = Crandom.genrand_int31() % 10;
        if(rand <= 1)
        {
          human[m].task = HUNT_OUT;
          Point dest;
          int xx = HOME_X_B - HOME_X;
          int yy = HOME_Y_B - HOME_Y;
          dest.x = Crandom.genrand_int31() % xx ;
          dest.x += HOME_X;
          dest.y = Crandom.genrand_int31() % yy ;
          dest.y += HOME_Y;
          human[m].reached = false;
          human[m].SetDest(dest);

          char s[1000];
          sprintf(s, "male human %d is hunting out from point(%d, %d) to point(%d, %d), S: %2.2f, I: %2.2f, E:%2.2f",
                  m,
                  human[m].position.x,
                  human[m].position.y,
                  dest.x, dest.y,
                  human[m].strength,
                  human[m].intelligence,
                  human[m].experience );
          string str = s;
          log.write(day, str);
        }
        else
        {
          char s[100];
          sprintf(s, "male human %d is having a rest at point(%d, %d)",
                  m,
                  human[m].position.x,
                  human[m].position.y);
          string str = s;
          //log.write(day, str);

        }
      }
      if(human[m].live     == LIVING         &&    // male goes back home when he finishes hunting
              human[m].reached  == true           &&
              human[m].task     == HUNT_OUT       &&
              human[m].gender   == MALE           &&
              human[m].maturity == ADULT          )
      {
        human[m].task = COME_BACK;
        Point dest = human[m].home;
        human[m].reached = false;
        human[m].SetDest(dest);
        human[m].experience += 5;
        if(human[m].experience >= EXPERIENCE_MAX)
        {
          human[m].experience = EXPERIENCE_MAX;
        } 
        char s[100];
        sprintf(s, "male human %d is coming back from point(%d, %d) to point(%d, %d)",
                m,
                human[m].position.x, 
                human[m].position.y,
                dest.x, dest.y);
        string str = s;
        log.write(day, str);
 
        
      }
      if(human[m].live     == LIVING    &&
              human[m].reached  == true      &&
              human[m].task     == COME_BACK &&
              human[m].gender   == MALE      &&
              human[m].maturity == ADULT      )
      {
        //when man comes back, he may go out for hunting again after 10~14 days// here, just set 1 day, go out immediately, modify later
        char s[100];
        string str = s;
        int rand = Crandom.genrand_int31() % 10;
        if(rand <= 1)
        {
          human[m].task = HUNT_OUT;
          Point dest;
          int xx =  HOME_X_B - HOME_X;
          int yy =  HOME_Y_B - HOME_Y;
          dest.x =  Crandom.genrand_int31() % xx ;
          dest.x += HOME_X;
          dest.y =  Crandom.genrand_int31() % yy ;
          dest.y += HOME_Y;

          human[m].reached = false;
          human[m].SetDest(dest);

          char s[1000];
          sprintf(s, "male human %d is hunting out from point(%d, %d) to point(%d, %d), S: %2.2f, I: %2.2f, E: %2.2f",
                  m,
                  human[m].position.x,
                  human[m].position.y,
                  dest.x, dest.y,
                  human[m].strength,
                  human[m].intelligence,
                  human[m].experience );
          string str = s;
          log.write(day, str);

        }
        else
        {
          //Point dest;
          //int xx = 10;
          //int yy = 5;
          //dest.x = Crandom.genrand_int31() % xx;
          //dest.y = Crandom.genrand_int31() % yy;
          human[m].task = HANG_OUT;
          //human[m].SetDest(dest);

          sprintf(s, "male human %d is having a rest at point (%d, %d) ",
                  m,
                  human[m].position.x,
                  human[m].position.y);
          str = s;
          //log.write(day, str);

        }
      }
      if(human[m].live   == LIVING   &&
         (human[m].gender == FEMALE  || human[m].maturity == YOUNG))
      {
        //Point dest;
        //int xx = 10;
        //int yy = 5;
        //dest.x = Crandom.genrand_int31() % xx;
        //dest.y = Crandom.genrand_int31() % yy;
        human[m].task = HANG_OUT;
        //human[m].SetDest(dest);
        char s[100];
        sprintf(s, "human %d is hanging out at point(%d, %d) ",
                m,
                human[m].position.x,
                human[m].position.y);
        string str = s;
        //log.write(day, str);

      }


      if(human[m].live == LIVING)
      {
        human[m].move(); 
        int pos = human[m].position.y * (MAX_X + 2) + human[m].position.x;
        map[pos] = 'h';

        if(human[m].task     == COME_BACK &&
           human[m].gender   == MALE      &&
           human[m].maturity == ADULT )
         {
           map[pos] = 'H';
         }

        if(human[m].task == HUNT_OUT)
        {
          pos = human[m].dest.y * (MAX_X + 2) + human[m].dest.x;
          map[pos] = '#';
        }

        pos    = human[m].position.x + human[m].position.y * MAX_X;
        pos_h[pos] ++; 
      }
    }
}

void Nature::beast_task()
{
    int m, n;
    
    for(m = 0; m < total_num_b; m++)
    {
      if(beast[m].live     == LIVING         &&   // when a beast become an adult, he goes out for hunting
         beast[m].task     == HANG_OUT_B     &&
         beast[m].maturity == ADULT          )
      {

        int rand = Crandom.genrand_int31() % 3;
        if(rand <= 1)
        {
          beast[m].task = HUNT_OUT_B;
          Point dest;
          int xx = HOME_X_B - HOME_X;
          int yy = HOME_Y_B - HOME_Y;
          dest.x = Crandom.genrand_int31() % xx ;
          dest.x += HOME_X;
          dest.y = Crandom.genrand_int31() % yy ;
          dest.y += HOME_Y;
          beast[m].reached = false;
          beast[m].SetDest(dest);

          char s[100];
          sprintf(s, "beast %d is hunting out from point(%d, %d) to point(%d, %d)",
                  m,
                  beast[m].position.x,
                  beast[m].position.y,
                  dest.x, dest.y);
          string str = s;
          log.write(day, str);
        }
        else
        {
          char s[100];
          sprintf(s, "beast %d is having a rest at point(%d, %d)",
                  m,
                  beast[m].position.x,
                  beast[m].position.y);
          string str = s;
          //log.write(day, str);

        }
      }
      else if(beast[m].live     == LIVING         &&    // beast goes back home when he finishes hunting
              beast[m].reached  == true           &&
              beast[m].task     == HUNT_OUT_B     &&
              beast[m].maturity == ADULT          )
      {
        beast[m].task = COME_BACK_B;
        Point dest = beast[m].home;
        beast[m].reached = false;
        beast[m].SetDest(dest);
        
        char s[100];
        sprintf(s, "beast %d is coming back from point(%d, %d) to point(%d, %d)",
                m,
                beast[m].position.x, 
                beast[m].position.y,
                dest.x, dest.y);
        string str = s;
        log.write(day, str);
 
        
      }
      else if(beast[m].live     == LIVING      &&
              beast[m].reached  == true        &&
              beast[m].task     == COME_BACK_B &&
              beast[m].maturity == ADULT      )
      {
        //when beast comes back, he may go out for hunting again after 1 days// here, just set 3 day, go out immediately, modify later
        char s[100];
        string str = s;
        int rand = Crandom.genrand_int31() % 3;
        if(rand <= 1)
        {
          beast[m].task = HUNT_OUT_B;
          Point dest;
          int xx = HOME_X_B - HOME_X;
          int yy = HOME_Y_B - HOME_Y;
          dest.x = Crandom.genrand_int31() % xx ;
          dest.x += HOME_X;
          dest.y = Crandom.genrand_int31() % yy ;
          dest.y += HOME_Y;
          beast[m].reached = false;
          beast[m].SetDest(dest);

          sprintf(s, "beast %d is hunting out from point(%d, %d) to point(%d, %d)",
                  m,
                  beast[m].position.x,
                  beast[m].position.y,
                  dest.x, dest.y);
          str = s;
          log.write(day, str);

        }
        else
        {
          beast[m].task = HANG_OUT_B;
          sprintf(s, "beast %d is having a rest at point (%d, %d) ",
                  m,
                  beast[m].position.x,
                  beast[m].position.y);
          str = s;
          //log.write(day, str);

        }
      }
      else if(beast[m].live   == LIVING   &&
              beast[m].maturity == YOUNG   )
      {
        beast[m].task = HANG_OUT_B;
        char s[100];
        sprintf(s, "beast %d is having a rest at point(%d, %d)",
                m,
                beast[m].position.x,
                beast[m].position.y);
        string str = s;
        //log.write(day, str);

      }


      if(beast[m].live == LIVING)
      {
        beast[m].move(); 
        int pos = beast[m].position.y * (MAX_X + 2) + beast[m].position.x;
        //if(map[pos] == 'H' || map[pos] == 'h')
        //{
        //  map[pos] = 'X';   //when human and beast meet, they fight
        //}
        //else if(beast[m].task     == COME_BACK_B &&
         if(beast[m].task     == COME_BACK_B &&
            beast[m].maturity == ADULT        )
         {
           map[pos] = 'B';
         }
         else
         {
           map[pos] = 'b';
         }
        if(beast[m].task == HUNT_OUT_B)
        {
          pos = beast[m].dest.y * (MAX_X + 2) + beast[m].dest.x;
          map[pos] = '&';
        }
        pos    = beast[m].position.x + beast[m].position.y * MAX_X;
        pos_b[pos] ++;
      }

    }
}

void Nature::fight_h_b(Point &p, int num_h, int num_b)
{
  int i, j;
  int rate;  // the possibility that human wins the fight
  int rand;
  if(num_h != 0 && num_b != 0)
  {
    
    rand = Crandom.genrand_int31() % 100;
    if(rand <= ESCAPE_RATE)    // human escape
    {
      char s[100];
      sprintf(s, "%d human(s) and %d beast is(are) meeting point(%d, %d), human escapes successfully",
             num_h,
             num_b,
             p.x  ,
             p.y  );
      string str = s;
      log.write(day, str);

    }
    else
    {

      char s[100];
      sprintf(s, "%d human(s) is(are) fighting with %d beast(s) at point(%d, %d)",
             num_h,
             num_b,
             p.x  ,
             p.y  );
      string str = s;
      log.write(day, str);

      int pos = p.y * (MAX_X + 2) + p.x;
      map[pos] = 'X';                       //when human and beast meet, they fight

      rand = Crandom.genrand_int31() % 100;
      rate = 100 * (num_h / (double)(num_b * FIGHT_RATE + num_h));
      int human_index       = 0;  // human's intelligence, strength and experience can add his possibility to win the fight
      // find the human who stands there
      for(i = 0; i < total_num_h; i++)
      {
        if(human[i].position.x == p.x      &&
           human[i].position.y == p.y      &&
           human[i].live       == LIVING    )
        {
          human_index = 0.1 * (0.6 * human[i].strength + 0.2 * human[i].intelligence + 0.2 * human[i].experience);
          if(rand >= (rate + human_index))
          {
            human[i].live = DEAD;
            char s[1000];
            sprintf(s, "human %d is dead, GS: %2.2f, S: %2.2f, GI: %2.2f, I: %2.2f, E: %2.2f, survival rate: %d%% = %d%% + %d%%, rand = %d",
                    i, human[i].gene_strength,human[i].strength, human[i].gene_intelligence, human[i].intelligence, human[i].experience, rate + human_index, rate, human_index, rand);
            string str = s;
            log.write(day, str);

          }
          else
          {
            char s[1000];
            sprintf(s, "human %d is survive, GS: %2.2f, S: %2.2f, GI: %2.2f, I: %2.2f, E: %2.2f, survival rate: %d%% = %d%% + %d%%, rand = %d",
                    i, human[i].gene_strength,human[i].strength, human[i].gene_intelligence, human[i].intelligence, human[i].experience, rate + human_index, rate, human_index, rand);
            string str = s;
            log.write(day, str);
          }
        }
      }
      // find the beast who stands there
      for(i = 0; i < total_num_b; i++)
      {
        if(beast[i].position.x == p.x     &&
           beast[i].position.y == p.y     &&
           beast[i].live       == LIVING   )
        {
          if(rand <= rate)
          {
            beast[i].live = DEAD;
            char s[100];
            sprintf(s, "beast %d is dead, rand = %d",i, rand);
            string str = s;
            log.write(day, str);

          }
          else
          {
            char s[100];
            sprintf(s, "beast %d is survive, rand = %d",i, rand);
            string str = s;
            log.write(day, str);
          }
        }
      }
    }
  }



}


void Nature::fight()
{
  int m, n, p;
  for(m = 0, p = 0; m < MAX_Y; m++)
  {
    for(n = 0; n < MAX_X; n++, p++)
    {
      Point m_point(n, m);
      fight_h_b(m_point, pos_h[p], pos_b[p]);
    }
  }
}

int Nature::timefly()
{
  int return_value = 0;
  int i, m, n;

  while(true)
  {
    day++;
    sex();
    human_grow();
    beast_grow();
    reset_map();
    human_task();
    beast_task(); 
    fight();
    show();
    usleep(SLEEP_TIME);

  }


  return return_value;
}

void Nature::show()
{
  printf("\033[2J");
  //printf("At the beginning, there are %d humans, female: %d, male %d, after %d days\n", origin_m, origin_female_h, origin_male_h, day);
  int m;
  for(m = 0; m < MAX_X; m++)
  { 
    printf("-");
  }
  printf("\n");
  
  //show human information
  printf("   day   |  living humans (  male   female  )  |  dead humans  |  total humans  | hunting out\n");

  printf("   %-5d |      %-7d   (    %-6d %-5d )  |    %-5d      |     %-8d    %-8d\n",
            day, live_num_h, male_num_h, female_num_h, dead_num_h, live_num_h + dead_num_h, hunt_num_h);
  
  for(m = 0; m < MAX_X; m++)
  {
    printf("-");
  }
  printf("\n");

  //show beast information 
  printf("   day   |  living beasts (  male   female  )  |  dead beasts  |  total beasts | hunting out\n");

  printf("   %-5d |      %-7d   (    %-6d %-5d )  |    %-5d      |     %-8d    %-8d \n",
            day, live_num_b, male_num_b, female_num_b, dead_num_b, live_num_b + dead_num_b, hunt_num_b);
  for(m = 0; m < MAX_X; m++)
  {
    printf("-");
  }
  printf("\n");


  printf("human hunts for: #, beast hunts for &, when they meet, they fight\n");

  for(m = 0; m < MAX_X; m++)
  {
    printf("-");
  }
  printf("\n");





 
  printf("%s",map);
  
  for(m = 0; m < MAX_X; m++)
  { 
    printf("-");
  }
  printf("\n");


}
