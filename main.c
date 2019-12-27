#include <stdio.h>
//#include <stdbool.h>
//#include <stdlib.h>
#include <time.h>
//#include <math.h>

//int is_leap_year(int year);
void panselinos_pasxa(int year, struct tm *p);

//const int days_per_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const int standar_holidays [8][2] = {{1,0},{6,0}, {25,2},{1,4}, {15,7}, {28,9}, {25,11}, {26,11}};
const char * sh[8] = {"Πρωτοχρονιά","Θεοφάνεια","25η Μαρτίου","Πρωτομαγιά","Δεκαπεντάυγουστος","28η Οκτωβρίου",
"Χριστούγεννα","Δεύτερη μέρα Χριστουγέννων"};
const char * other_holidays[7]= {"Καθαρά Δευτέρα","Αγίου Θεοδώρου","Σάββατο του Λαζάρου", 
"Κυριακή των Βαίων","Της Αναστάσεως","Του Θωμά","Των Μυροφόρων"}; 
//αγίου γεωργίου 23 απριλίου εάν το πάσχα πέφγτει πιο μετά 1 μέρα μετά το πασχα
const int diffs[7]={-48,-43,-8,-7,0,7,14};

const double moon_cycle =29.53;
const int genenthlia[]= {27,7};
const double sex_per_day=24*60*60;

int main(int argc, char **argv)
{
    int year=0;
    printf("Ποιό έτος θες να δεις  : ");
    scanf("%d",&year);
    //struct tm voll_moon = {.tm_year=1991-1900, .tm_mday =1, .tm_mon=0};// ={1991,0,1};
    //struct tm geburstag = {.tm_mday =27, .tm_mon=6, .tm_year=year-1900};
    //struct tm mar21 = {.tm_mday =21, .tm_mon=2, .tm_year=year-1900};
    //time_t t1_1_1991 = mktime(&voll_moon);
    //time_t t2 = mktime(&geburstag);
    //time_t t21_mar_y = mktime(&mar21);
    
    //printf("First voll moon in %s\n", asctime(&voll_moon));
    //printf("Du hast Geburstag am %s\n", asctime(&geburstag));
    //printf("21 Mar is %s\n", asctime(&mar21));
    
    //double days_21mar = difftime(t21_mar_y,t1_1_1991)/(24*60*60);
    
    
    //double moon_cycles = difftime(t21_mar_y,t1_1_1991)/(29.53*sex_per_day);
    //printf("moon cycles %f\n",moon_cycles);
    
    //time_t t_next_vm =t1_1_1991+ceil(moon_cycles)*29.53*sex_per_day;
    
    //printf("Voll moon after 21 Mar %d is in %s \n",year, ctime(&t_next_vm));
    
    struct tm ps = {.tm_year = 2020-1900, .tm_mday=0, .tm_mon=0};
    //time_t ppasxa = mktime(&ps);   
    panselinos_pasxa(year, &ps);
    //time_t ppasxa = mktime(&ps);
    //printf("Voll moon prin pasxa me ipologismo sinartisis : %s \n",asctime(&ps));
    //printf ("Voll moon is in day %d\n", ps.tm_wday);
    struct tm pasxa;
    pasxa = ps;
    pasxa.tm_mday=ps.tm_mday+7-ps.tm_wday;
    time_t pasxat = mktime(&pasxa);
    printf("Το πάσχα του %d είναι στις %s\n",year, ctime(&pasxat));
    
    printf("Σταθερές γιορτές του %d\n\n",year);
    //for (int i = 2018; i<2028;i++)
    /*{
        pnslns_pasxa(i, &ps);
        ppasxa = mktime(&ps);
        printf("Voll moon prin pasxa me ipologismo sinartisis : %s \n",asctime(&ps));
    }*/
    //printf("Today is  %s", gmtime(&today));
    for (int i=0;i<8;i++)
    {
        printf("%d\t", i+1);
        printf("%s : ",sh[i]);
        struct tm h = {.tm_year=year-1900, .tm_mday =standar_holidays[i][0], .tm_mon=standar_holidays[i][1]};
        time_t d = mktime(&h);
        printf("%s\n", ctime(&d)); 
    }
    
    printf("Κινητές γιορτές του %d\n\n",year);
   
    for (int i=0;i<7;i++)
    {
        printf("%d\t", i+1);
        printf("%s : ",other_holidays[i]);
        time_t d = pasxat + diffs[i]*sex_per_day;
        printf("%s\n", ctime(&d)); 
    }
    
    getchar();
    return 0;
}
/*
int is_leap_year(int year)
{
    bool leap_year = (year%100==0)?(year%400==0):(year%4==0);
    return leap_year?1:0;
}
*/
void panselinos_pasxa(int year,struct tm *p )
{
    int month=0, day=0;
    int p1 = year-2;
    int p2 = p1%19;
    int p3 = p2*11;
    int p4 = p3%30;//epakti
    int p5 = 44-p4;
    if (p4>23)
        month=3;
    else
        month=2;
    day=p5+13;
    p->tm_year=year-1900;
    if (month ==2 && day>31)
    {
        p->tm_mon = month+1;
        p->tm_mday=day-31;
         //printf("Entos sinartisis etos %d minas %d mera %d \n", year, month,day);
        return;
    }
    if (month ==3 && day>30)
    {
        p->tm_mon = month+1;
        p->tm_mday=day-30;
         //printf("Entos sinartisis etos %d minas %d mera %d\n", year, month,day);
        return;
    }
    //printf("Entos sinartisis etos %d minas %d mera %d \n", year, month,day);
    p->tm_mday=day;
    p->tm_mon=month;
}

 /*time_t now;
  struct tm newyear;
  double seconds;

  time(&now);  get current time; same as: now = time(NULL)  
  newyear = *localtime(&now);

  newyear.tm_hour = 0; newyear.tm_min = 0; newyear.tm_sec = 0;
  newyear.tm_mon = 0;  newyear.tm_mday = 1;

  seconds = difftime(now,mktime(&newyear));*/
