//Το Πάσχα του 2021 έχει κάποιο bug και εμφανίζεται μία εβδομάδα νωρίτερα !@$@#21

#include <stdio.h>
#include <time.h>

const int standar_holidays [8][2] = {{1,0},{6,0}, {25,2},{1,4}, {15,7}, {28,9}, {25,11}, {26,11}};
const char * sh[8] = {"Protoxronia","Theofania","25 Martiou","Protomagia","Dekapentaugoustos","28 Oktobriou","Xristougenna","Deuteri mera Xristougennon"};
//The 2 matrices should be in correspodense
const char * other_holidays[7]= {"Kathari Deutera","Agiou Theodorou","Savato tou Lazarou", "Kuriaki ton Baion","Tis Anastaseos","Tou Thoma","Tvn Miroforon"}; 
const int diffs[7]={-48,-43,-8,-7,0,7,14};
//The 2 matrices should be in correspodense month is 0-11 0->January
//Αγίου Γεωργίου 23 Απριλίου εάν το πάσχα πέφγτει πιο μετά 1 μέρα μετά το πασχα
const double sex_per_day=24*60*60;

void panselinos_pasxa(int year, struct tm *p);

int main(int argc, char **argv)
{
    int year=0;
    printf("Dose etos  : ");
    scanf("%d",&year);
    
    struct tm pasxa = {.tm_year = 2020-1900, .tm_mday=0, .tm_mon=0};
    panselinos_pasxa(year, &pasxa);
    pasxa.tm_mday=pasxa.tm_mday+7-pasxa.tm_wday;//posible bug
    time_t pasxat = mktime(&pasxa);
    printf("To pasxa tou %d peftei tin %s\n",year, ctime(&pasxat));
    
    printf("Statheres giortes tou %d\n\n",year);
    for (int i=0;i<8;i++)
    {
        printf("%d\t", i+1);
        printf("%s : ",sh[i]);
        struct tm h = {.tm_year=year-1900, .tm_mday =standar_holidays[i][0], .tm_mon=standar_holidays[i][1]};
        time_t d = mktime(&h);
        printf("%s\n", ctime(&d)); 
    }
    
    printf("Kinites giortes tou %d\n\n",year);
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

void panselinos_pasxa(int year,struct tm *p )
{
    //algorith is taken from http://www.eortologio.gr/arthra/paschalion.php
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
        return;
    }
    if (month ==3 && day>30)
    {
        p->tm_mon = month+1;
        p->tm_mday=day-30;
        return;
    }
    p->tm_mday=day;
    p->tm_mon=month;
}
 
