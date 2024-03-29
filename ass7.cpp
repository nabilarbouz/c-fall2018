//Nabil Arbouz, MS Visual Studio, Windows 10
//Assignment 7

#define _CRT_SECURE_NO_WARNINGS

//preprocessor directives
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

//namespace
using namespace std;

//Date class
class Date 
{
private:

   unsigned int month;
   unsigned int day;
   unsigned int year;

public:
   
   Date();

   Date(unsigned int, unsigned int, unsigned int);

   int get_month() const { return month; }

   int get_day() const { return day; }

   int get_year() const { return year; }

   void increment_date();
   
   void print_date() const;

   void letTimePass();

};

//Human Class
class Human
{
private:
   string name;
   Date birthday;
   bool is_alive;

public:

   Human(const string& n, const Date& b);

   string get_name() const { return name; }

   Date get_birthday() const { return birthday; }

   bool get_is_alive() const { return is_alive; }

   int age() const;

   float roll_the_dice(unsigned short age) const;

   void die() { is_alive = false; print_obituary(); }

   void print_human() const;

   void print_obituary() const;

};

//Population Class
class Population
{
private:
   Human** people;
   short size;

public:

   Population(int);
   ~Population();

   void print() const;

   void examinePopulation();

   int getNumberLiving() const;
  
};

const time_t now = time(0);
const struct tm* current_time = localtime(&now);
Date TODAY;   
unsigned DaysPerMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
const string NAMES[] =
{
    "Luis","Arbouz","Nathan","Christine","Jorge","Chase","Jamie","Ryan",
    "James","Kyle","Sunan","Houman","Sofia","Joy","Chen","Donovan",
    "Jason","William","Yuqin","Alex","Mohammed","Yusuf","Dalver",
    "Dustin","Thomas","Lawrence","Zuiyun","Udyog","Umar","Gursewak","Robabeh",
    "Shanli","Norman","Colin","Manmeet Singh","Rajesh","Janice","Atiq",
    "Ayumi","Richard","Rose Marie","Tina Marie","Miles","Mengqing","Shu Hui","Yujing"
};

//main
int main()
{
   const int OriginalPopulationSize = 46;

   srand(time(0));
   Population World(OriginalPopulationSize);
   World.print();

   // let time pass until half of the world's Population dies
   do
   {
      TODAY.letTimePass();
      World.examinePopulation();
   } while (World.getNumberLiving() > OriginalPopulationSize / 2);

   World.print();
}

Date::Date()
   :
   month(static_cast<int>(current_time->tm_mon + 1)),
   day(static_cast<int>(current_time->tm_mday)),
   year(static_cast<int>(current_time->tm_year + 1900))
{
}

Date::Date(unsigned int m, unsigned int d, unsigned int y)
   :month(m),
   day(d),
   year(y)
{
}

void Date::increment_date()
{
   day++;
   
   //check if the year is a leap year that is divisible by 400;
   if ((year % 400) == 0 && (month == 2) && (day > DaysPerMonth[month] + 1))
   {
       month++;
       day = 1;
 
   }
   
   //if the year is not divisible by 400, we need to check if it is
   //divisible by 100; If it is, then it is not a leap year
   else if ((year % 100) == 0 && (day > DaysPerMonth[month]))
   {
      month++;
      day = 1;
   }

   //if the previous two conditions arent met, we will check if
   //it is divisible by 4;
   else if ((year % 4) == 0 && month == 2 && (day > DaysPerMonth[month] + 1))
   {
      month++;
      day = 1;
   }
   
   //this will catch anthing that did not meet the conditions above;
   else if (day > DaysPerMonth[month])   
   {
      month++;
      day = 1;
   }

   //check if December was incremented and then move the date
   //up to January of next year;
   if (month > 12)
   {
      year++;
      month = 1;
   }
}

void Date::print_date() const
{
   cout << setfill('0') << setw(2) << month << "/"
      << setfill('0') << setw(2) << day << "/"
      << year;
}

void Date::letTimePass()
{
   int random_number;
   random_number = rand() % 365 + 1;

   for (int i = 0; i < random_number; i++)
   {
      increment_date();
   }

}

Human::Human(const string& n, const Date& b)
   :
   name(n),
   birthday(b),
   is_alive(true)
{
}

int Human::age() const
{
   int age;
   age = ((TODAY.get_year()) - (birthday.get_year()));

   if ((TODAY.get_month()) > (birthday.get_month()))
   {
      return age;
   }
   if ((TODAY.get_month()) < (birthday.get_month()))
   {
      return age - 1;
   }
   if ((TODAY.get_month()) == (birthday.get_month()))
   {
      if ((TODAY.get_day()) >= (birthday.get_day()))
      {
         return age;
      }
      else
      {
         return age - 1;
      }
   }
   return age;
}

float Human::roll_the_dice(unsigned short age) const
{
   return static_cast<float>(age)*(rand() % 100) / 10000.;
}

void Human::print_human() const
{
   cout << name << " was born on ";
   birthday.print_date();
   cout << " is ";
   cout << age() << endl;
}

void Human::print_obituary() const
{
   TODAY.print_date();
   cout << " " << name << " died at the age of "
      << age() << endl;
}

Population::Population(int num_of_people)
   :size(num_of_people), 
   people(new Human*[num_of_people])
{
   for (int i = 0; i < size; i++)
   {
      int m = rand() % static_cast<int>(current_time->tm_mon +1) + 1;
      int d = rand() % (DaysPerMonth[m]) + 1;
      int y = rand() % 99;
      
      if (y < 19) y += 2000;
      else y += 1900;

      Date* bday = new Date(m, d, y);

      people[i] = new Human(NAMES[i], *bday);

      delete bday;
      bday = nullptr;
   }
}

Population::~Population()
{
   for (int i = 0; i < size; i++)
   {
      delete people[i];
      people[i] = nullptr;
   }
   delete[] people;
   people = nullptr;
}

void Population::print() const
{
   cout << "-----------------------------------------------" << endl;
   cout << "Today is ";
   TODAY.print_date();
   cout << endl;
   for (int i = 0; i < size; i++)
   {
      if (people[i]->get_is_alive() == true)
      {
         people[i]->print_human();
      }
   }
   cout << "-----------------------------------------------" << endl;
}

void Population::examinePopulation()
{
   for (int i = 0; i < size; i++)
   {
      if ( (people[i]->get_is_alive() == true) && 
         (people[i]->roll_the_dice(people[i]->age()) > 0.5) )
      {
         people[i]->die();
      }
   }
}

int Population::getNumberLiving() const
{
   int living_counter = 0; 

   for (int i = 0; i < size; i++)
   {
      if (people[i]->get_is_alive() == true)
      {
         living_counter++;
      }
   }
   return living_counter;
}