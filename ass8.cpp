//Nabil Arbouz, Visual Studio, Windows 10
//Assignment 8

#define _CRT_SECURE_NO_WARNINGS

//preprocessor directives
#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>

//namespace
using namespace std;

//initialize the time
const time_t now = time(0);
const struct tm* time_info = localtime(&now);

//date class
class Date
{
private:

   int month, 
      day,
      year;

public:

   static const string NAMES_OF_MONTH[12];
   static const int DAYS_PER_MONTH[13];


   //CONSTRUCTORS
   Date(); //default constructor that will provide current date
   Date(int m, int d, int y); //constructor that takes three int arguments for the date
   Date(string d); //constructor that will take a string as a time and parse it

   //overloaded operator protypes
   Date& operator++ (); //prefix ++ overload
   Date& operator--(); //prefix -- overload
   Date operator-(int) const; //binary - overload
   double operator-(const Date&) const; //binary - overload
   void operator!() const; //overloaded bang operator
   bool operator>(const Date&) const; //overloaded greater than operator
   bool operator<(const Date&) const; //overloaded less than operator

   //friend functions
   friend ostream& operator<<(ostream&, const Date&); //left-shift operator overload
   friend Date operator+(const Date&, int); //overloaded +
   friend Date operator+(int, const Date&); //overloaded + 

};

//initialize the static memebers
const string Date::NAMES_OF_MONTH[] = { "January", "February", "March",
"April", "May", "June", "July", "August", "September", "October", "November", "December" };
const int Date::DAYS_PER_MONTH[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

Date::Date()
   :month(time_info->tm_mon + 1), 
   day(time_info->tm_mday),
   year(time_info->tm_year + 1900)
{}

Date::Date(int m, int d, int y)
   :month(m), 
   day(d), 
   year(y + 2000)
{}

Date::Date(string d)
   : month(stoi(d.substr(0,2))),
      day(stoi(d.substr(3,2))),
   year(stoi(d.substr(6,2)) + 2000)
{}

//overloaded ++ operator with leap year logic implemented
Date& Date::operator++()
{
   day++;

   //check if the year is a leap year that is divisible by 400;
   if ((year % 400 == 0) && (month == 2) && (day > DAYS_PER_MONTH[month] + 1))
   {
      month++;
      day = 1;
   }
   
   //if the year is not divisible by 400, we need to check if it is
   //divisible by 100; If it is, then it is not a leap year
   else if ((year % 100) == 0 && (day > DAYS_PER_MONTH[month]) && (year % 400 != 0))
   {
      month++;
      day = 1;
   }
   

   //if the previous two conditions arent met, we will check if
   //it is divisible by 4;
   else if ((year % 4) == 0 && month == 2 &&(day > DAYS_PER_MONTH[month] + 1))
   {   
      month++;
      day = 1;
   }
   
   //this will catch anthing that did not meet the conditions above;
   else if (day > DAYS_PER_MONTH[month] && (year % 4 != 0) && (year % 100) != 0 && (year % 400 != 0))
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

   return *this;
}

Date& Date::operator--()
{
   day--;

   
   //check if the year is a leap year that is divisible by 400;
   if ((year % 400) == 0 && (month == 3) && (day == 0))
   {
      month--;
      day = 29;
   }

   //if the year is not divisible by 400, we need to check if it is
   //divisible by 100; If it is, then it is not a leap year
   else if ((year % 100) == 0 && (day == 0) && (year % 400 != 0))
   {
      month--;
      day = DAYS_PER_MONTH[month];
   }

   //if the previous two conditions arent met, we will check if
   //it is divisible by 4;
   else if ((year % 4) == 0 && month == 3 && day == 0)
   {
      month--;
      day = 29;
   }

   //this will catch anthing that did not meet the condition above;
   else if (day == 0)
   {
      month--;
      day = DAYS_PER_MONTH[month];
   }
   

   //check if January was decremented and then move the date
   //back to December of the previous year;
   if (month == 0)
   {
      year--;
      month = 12;
      day = DAYS_PER_MONTH[month];
   }

   return *this;
}

//overloaded insertion operator
ostream& operator<<(ostream& stream, const Date& obj)
{
   stream << setw(2) << setfill('0') << obj.month << "/"
      << setw(2) << setfill('0') << obj.day << "/"
      << obj.year;
   return stream;
}

Date operator+(const Date& obj, int num)
{
   Date temp;
   temp = obj;
   for (int i = 0; i < num; i++)
   {
      ++temp;
   }
   return temp;
}

Date operator+( int num, const Date& obj)
{
   Date temp;
   temp = obj;
   for (int i = 0; i < num; i++)
   {
      ++temp;
   }
   return temp;
}

Date Date::operator-(int num) const
{
   Date temp;
   temp = *this;

   for (int i = 0; i < num; i++)
   {
      --temp;
   }
   return temp;
}

double Date::operator-(const Date& subtractor) const
{
   double obj_days = 0;
   double subtractor_days = 0;
   
   for (int i = 1; i < month; i++)
   {
      obj_days += DAYS_PER_MONTH[i];
   }
   obj_days += day;
   obj_days += (year * 365.25);

   for (int i = 1; i < subtractor.month; i++)
   {
      subtractor_days += DAYS_PER_MONTH[i];
   }
   subtractor_days += subtractor.day;
   subtractor_days += (subtractor.year * 365.25);

   return (obj_days - subtractor_days);
}

void Date::operator!() const
{
   string date_to_print;
   date_to_print = NAMES_OF_MONTH[month - 1];
   date_to_print += ' ';
   date_to_print += to_string(day);
   date_to_print += ", ";
   date_to_print += to_string(year);
   cout << date_to_print << endl;
}

bool Date::operator<(const Date& obj) const
{
   double this_days = 0;
   double obj_days = 0;

   for (int i = 1; i < month; i++)
   {
      this_days += DAYS_PER_MONTH[i];
   }
   this_days += day;
   this_days += (year * 365.25);

   for (int i = 1; i < obj.month; i++)
   {
      obj_days += DAYS_PER_MONTH[i];
   }
   obj_days += obj.day;
   obj_days += (obj.year * 365.25);

   return (this_days < obj_days) ? true : false;
}

bool Date::operator>(const Date& obj) const
{
   double this_days = 0;
   double obj_days = 0;

   for (int i = 1; i < month; i++)
   {
      this_days += DAYS_PER_MONTH[i];
   }
   this_days += day;
   this_days += (year * 365.25);

   for (int i = 1; i < obj.month; i++)
   {
      obj_days += DAYS_PER_MONTH[i];
   }
   obj_days += obj.day;
   obj_days += (obj.year * 365.25);

   return (this_days > obj_days) ? true : false;
}



int main()
{
   // Constructors
   Date today;
   Date feb2818(2, 28, 18);
   Date feb2800("02/28/00");
   Date NewYearsDay("01-01-19");

   // Increment and decrement operators
   cout << today << endl;
   ++today;
   cout << today << endl;
   --today;
   cout << today << endl << endl;

   cout << feb2818 << endl;
   cout << ++feb2818 << endl;
   cout << --feb2818 << endl << endl;

   cout << feb2800 << endl;
   cout << ++feb2800 << endl;
   cout << --feb2800 << endl << endl;

   cout << NewYearsDay << endl;
   --NewYearsDay;
   cout << NewYearsDay << endl;
   ++NewYearsDay;
   cout << NewYearsDay << endl << endl;

   // Test plus operators
   cout << "30 days from now: " << today + 30 << endl;
   cout << "one hundred days from now: " << 100 + today << endl << endl;

   // Test minus operators
   Date twentyYearsAgo = today - static_cast<int>(round(20 * 365.25));
   Date final("12/10/18");
   cout << "Days until the final = " << final - today << endl;

   // Test the ! operator
   cout << "Today is ";
   !today;
   cout << "Twenty years ago was ";
   !twentyYearsAgo;
   cout << endl;

   // Test logic operators
   cout << boolalpha;
   cout << feb2800 << " < " << NewYearsDay << " ? " << (feb2800 < NewYearsDay) << endl;
   cout << feb2818 << " < " << NewYearsDay << " ? " << (feb2818 < NewYearsDay) << endl;
   cout << feb2818 << " > " << NewYearsDay << " ? " << (feb2818 > NewYearsDay) << endl;
}