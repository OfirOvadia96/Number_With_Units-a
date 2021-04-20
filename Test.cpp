#include "NumberWithUnits.hpp"
#include "doctest.h"
#include <array>
using namespace std;
using namespace ariel;

/* */
string random_type(){
    array<string,11> types = {"km" , "cm" , "m" , "ton" , "kg" , "g" , "USD" , "ILS",
    "hour" , "min" , "sec"};
    string random_type = types.at(rand()%11); //random type from the list types
    return random_type;
}
/*check all the boolean operators */
TEST_CASE("Boolean operators"){

    NumberWithUnits ton (1 , "ton");
    NumberWithUnits kg (1000 , "kg");

    NumberWithUnits hours(1, "hours");
    NumberWithUnits min(60, "min");

    NumberWithUnits shekel(3.33,"ILS");
    NumberWithUnits dolar(1,"USD");

    NumberWithUnits km(1 , "km");
    NumberWithUnits m(1000 , "m");
    /*  check operator ==  */
    CHECK(km == m);
    CHECK(dolar == shekel); //3.33shekel == 1 dolar
    CHECK(ton == kg); //1000 kg == 1 ton
    CHECK(min == hours); // 60min == 1 hour
    /* check operator !=  */
    CHECK_FALSE(km != m);
    CHECK_FALSE(dolar != shekel);
    CHECK_FALSE(ton != kg); 
    CHECK_FALSE(min != hours); 

    /* checks operator <  */
    for(int i=0; i<100; i++){
        double less_then_km = rand()%1000; // 0 - 999
        double less_then_dolar = double(rand()%4 + 0.32); // 0 - 3.32
        double less_then_ton = rand()%1000; // 0 - 999
        double less_then_hour = rand()%60; // 0- 59
        
        m.set_value(less_then_km);
        shekel.set_value(less_then_dolar);
        min.set_value(less_then_hour);
        kg.set_value(less_then_ton);

        CHECK(m < km);
        CHECK(shekel < dolar);
        CHECK(min < hours);
        CHECK(kg < ton);
    }
    /* checks operator >  and != */
    for(int i=0; i<100; i++){
        double big_then_km = rand()%INTMAX_MAX + 1001; // 1001 - max_int
        double big_then_dolar = rand()%INTMAX_MAX + 3.34; //3.34 - mat_int
        double big_then_hour = rand()%INTMAX_MAX + 61; // 61 - max_int
        double big_then_ton = rand()%INTMAX_MAX + 1001; // 1001 - max_int

        m.set_value(big_then_km);
        shekel.set_value(big_then_dolar);
        min.set_value(big_then_hour);
        kg.set_value(big_then_ton);

        CHECK(m > km);
        CHECK(shekel > dolar);
        CHECK(min > hours);
        CHECK(kg > ton);
        
        CHECK(m != km);
        CHECK(shekel != dolar);
        CHECK(min != hours);
        CHECK(kg != ton);
    }
    m.set_value(1);
    min.set_value(1);
    kg.set_value(1);
    NumberWithUnits seconds(60 , "sec");
    NumberWithUnits gram(1000 , "g");
    NumberWithUnits cm (100 , "cm");
    /*  check operator ==  */
    CHECK(cm == m); // 1000cm == 1 m
    CHECK(seconds == min); // 60seconds == 1 min
    CHECK(gram == kg); // 1000gram == 1 kg

    /* check operator !=  */
    CHECK_FALSE(cm != m);
    CHECK_FALSE(seconds != min); 
    CHECK_FALSE(gram != kg); 

    /* check operator < and != */
    for(int i=0; i<100; i++){
        double less_then_m = rand()%100; // 0- 99
        double less_then_min = rand()%60; // 0 - 59
        double less_then_kg = rand()%1000; // 0 - 999

        cm.set_value(less_then_m);
        gram.set_value(less_then_kg);
        seconds.set_value(less_then_kg);

        CHECK(cm < m);
        CHECK(seconds < min);
        CHECK(gram < kg);

        CHECK(cm != m);
        CHECK(seconds != min);
        CHECK(gram != kg);
   }
    /* check operator > and !=  */
    //big then bigger unit 
    for(int i=0; i<100; i++){
        double big_then_m = rand()%INTMAX_MAX + 101; // 101 - max_int
        double big_then_min = rand()%INTMAX_MAX +61; // 61 - max_int
        double big_then_kg = rand()%INTMAX_MAX +1001; // 1001 - max_int

        cm.set_value(big_then_m);
        gram.set_value(big_then_kg);
        seconds.set_value(big_then_min);

        CHECK(cm > m);
        CHECK(seconds > min);
        CHECK(gram > kg);

        CHECK(cm != m);
        CHECK(seconds != min);
        CHECK(gram != kg);
   }
}

TEST_CASE("operators add + /sub -  for two NumberWithUnits"){
    NumberWithUnits ton (1 , "ton");
    NumberWithUnits kg (1000 , "kg");
    NumberWithUnits gram(1000 , "g");
    NumberWithUnits ans_weight(1 , "ton");
   
    /* check + and - with two NumberWithUnits */

    /*check for weight units*/
    for(int i=0; i < 100; i++){
        double ton_rand = rand()% INTMAX_MAX +1; // 1 - max_int
        double kg_rand = rand()% INTMAX_MAX +1; // 1 - max_int
        double g_rand = rand()% INTMAX_MAX +1; // 1 - max_int


        ton.set_value(ton_rand);
        kg.set_value(kg_rand);
        gram.set_value(g_rand);

        ans_weight.set_value((ton_rand+(kg_rand/1000)));
        ans_weight.set_type("ton");
        CHECK((ton+kg) == ans_weight);
        
        ans_weight.set_value(((ton_rand*1000)+kg_rand));
        ans_weight.set_type("kg");
        CHECK((kg+gram) == ans_weight);

        ans_weight.set_type("kg");
        ans_weight.set_value(kg_rand+(g_rand*1000));
        CHECK((kg+gram) == ans_weight);

        ans_weight.set_type("g");
        ans_weight.set_value((kg_rand/1000)+g_rand);
        CHECK((gram+kg) == ans_weight);

        ans_weight.set_value(ton_rand-(kg_rand/1000));
        ans_weight.set_type("ton");
        CHECK((ton-kg) == ans_weight);

        ans_weight.set_value(kg_rand-(ton_rand*1000));
        ans_weight.set_type("kg");
        CHECK((kg-ton) == ans_weight);

        ans_weight.set_value(kg_rand - (g_rand*1000));
        ans_weight.set_type("kg");
        CHECK((kg-gram) == ans_weight);

        ans_weight.set_value(g_rand - (kg_rand/1000));
        ans_weight.set_type("g");
        CHECK((gram-kg) == ans_weight);

    }
    /* check for time units */
    NumberWithUnits hours(1, "hours");
    NumberWithUnits min(60, "min");
    NumberWithUnits seconds(60 , "sec");
    NumberWithUnits ans_time(1 , "hours");
    for(int i=0; i<50; i++){
        double rand_hours = rand()%INTMAX_MAX +1;// 1-max_int
        double rand_min = rand()%INTMAX_MAX +1; //1-max_int
        double rand_seconds = rand()%INTMAX_MAX +1; // 1-max_int
        hours.set_value(rand_hours);
        min.set_value(rand_min);
        seconds.set_value(rand_seconds);
        
        ans_time.set_value(rand_hours+(rand_min/60));
        CHECK((hours+min) == ans_time);
        
        ans_time.set_value(rand_hours-(rand_min/60));
        CHECK((hours-min) == ans_time);

        ans_time.set_type("min");
        ans_time.set_value(rand_min+(rand_hours*60));
        CHECK((min+hours) == ans_time);
        
        ans_time.set_value(rand_min-(rand_hours*60));
        CHECK((min-hours) == ans_time);

        ans_time.set_value(rand_min+(rand_seconds/60));
        CHECK((min+seconds) == ans_time);
        
        ans_time.set_value(rand_min-(rand_seconds/60));
        CHECK((min-seconds) == ans_time);

        ans_time.set_type("seconds");
        ans_time.set_value(rand_seconds+(rand_min*60));
        CHECK((seconds+min) == ans_time);
        
        ans_time.set_value(rand_seconds-(rand_min*60));
        CHECK((seconds-min) == ans_time);
    }

    /* check for money units */
    NumberWithUnits shekel(3.33,"ILS");
    NumberWithUnits dolar(1,"USD");
    NumberWithUnits ans_money(1,"USD");

    for(int i=0; i<50; i++){
        double rand_dolar = rand()%INTMAX_MAX +1; // 1- max_int
        double rand_shekel = rand()%INTMAX_MAX +1; // 1- max_int
        dolar.set_value(rand_dolar);
        shekel.set_value(rand_shekel);

        ans_money.set_value(rand_dolar+(rand_shekel*3.33));
        CHECK((dolar+shekel) == ans_money);

        ans_money.set_value(rand_dolar-(rand_shekel*3.33));
        CHECK((dolar-shekel) == ans_money);

        ans_money.set_type("ILS");
        ans_money.set_value((rand_dolar/3.33)+rand_shekel);
        CHECK((shekel+dolar) == ans_money);

        ans_money.set_value(rand_shekel-(rand_dolar/3.33));
        CHECK((shekel-dolar) == ans_money);
    }
    /* check for distances units */
    NumberWithUnits km(1 , "km");
    NumberWithUnits m(1000 , "m");
    NumberWithUnits cm (100 , "cm");
    NumberWithUnits ans_dist (1 , "km");

    for(int i=0; i<100; i++){
        double rand_km = rand()%INTMAX_MAX +1; // 1- max_int
        double rand_m = rand()%INTMAX_MAX +1; // 1- max_int
        double rand_cm = rand()%INTMAX_MAX +1; // 1- max_int
        km.set_value(rand_km);
        m.set_value(rand_m);
        cm.set_value(rand_cm);

        ans_dist.set_value(rand_km+(rand_m/1000));
        CHECK((km+m) == ans_dist);

        ans_dist.set_value(rand_km-(rand_m/1000));
        CHECK((km-m) == ans_dist);

        ans_dist.set_type("m");
        ans_dist.set_value(rand_m+(rand_km*1000));
        CHECK((m+km) == ans_dist);

        ans_dist.set_value(rand_m-(rand_km*1000));
        CHECK((m-km) == ans_dist);

        ans_dist.set_type("cm");
        ans_dist.set_value(rand_m+(rand_cm/100));
        CHECK((m+cm) == ans_dist);

        ans_dist.set_value(rand_m-(rand_cm/100));
        CHECK((m-cm) == ans_dist);

        ans_dist.set_value(rand_cm+(rand_m*100));
        CHECK((cm+m) == ans_dist);

        ans_dist.set_value(rand_cm-(rand_m*100));
        CHECK((cm-m) == ans_dist);
    }
    
}

/*check operators ++ , --  */
TEST_CASE("self math operators"){
    double random_value = rand()%INTMAX_MAX +1; // 1-max_int
    string rand_type = random_type();
    
    NumberWithUnits current(random_value , rand_type);
    NumberWithUnits should_be(random_value+1,rand_type);
    
    for(int i=0; i<10; i++){
        //current++;
        CHECK(should_be == current); // check for ++

        should_be.set_value(random_value); // like -1;
        //current--;
        CHECK(should_be == current); // check for --
        random_value = rand()%INTMAX_MAX +1; // (1-max_int) and again get random value
        current.set_value(random_value);
        should_be.set_value(random_value);

    }
}

/* check operators *= , *   */
TEST_CASE("multiply operators"){
    string rand_type = random_type();
    double random_value = rand()%INTMAX_MAX; // 0-max_int
    double multiplier = rand()%INTMAX_MAX; //0- max_int

    NumberWithUnits current1(random_value , rand_type);
    NumberWithUnits current2(random_value , rand_type);
    NumberWithUnits current3(random_value , rand_type);
    NumberWithUnits should_be_multyply((random_value*multiplier),rand_type);
    
    for(int i=0; i<50; i++){
    current1 *= multiplier;
    CHECK(current1 == should_be_multyply);
    CHECK((current2*multiplier) == should_be_multyply);
    CHECK((multiplier*current3) == should_be_multyply);
    random_value = rand()%INTMAX_MAX; //0 - max_int
    current1.set_value(random_value);
    current2.set_value(random_value);
    current3.set_value(random_value);
    }
}
    /*check operators +(), -() */
TEST_CASE("unary operrators"){
    string rand_type = random_type();
    double random_value = rand()%INTMAX_MAX; // 0 - max_int
        
    NumberWithUnits current(random_value , rand_type);
    NumberWithUnits should_be(random_value , rand_type);
        
    for(int i=0; i<20; i++){
        +(current);
        CHECK(should_be == current);
        -(current);
        should_be.set_value(-random_value);
        CHECK(should_be == current);
        random_value = rand()%INTMAX_MAX; // 0 - max_int
        current.set_value(random_value);
        should_be.set_value(random_value);
    }

}