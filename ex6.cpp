//Nabil Arbouz, Visual Studio, Windows 10
//Lab Exercise 6

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

enum Type { Even, Odd };

union Value
{
   int i;
   double d;
};

struct Number
{
   Type type;
   Value value;
};

const string TypeString[2] = { "even","odd" };

void assign(Number& a);
void print(const Number& a);

int main()
{
   Number var[10];
   for (int i = 0; i < 10; i++)
      assign(var[i]);
   for (int i = 0; i < 10; i++)
      print(var[i]);
}

void assign(Number& a)
{
   int random_num;
   random_num = (rand() % 100) + 1;

   if (random_num % 2 == 0)
   {
      a.type = Even;
      a.value.i = random_num;
   }
   else
   {
      a.type = Odd;
      a.value.d = pow(random_num, 0.5);
   }
}

void print(const Number& a)
{
   cout << "Number is " << TypeString[a.type] << " "
      << (a.type == Even ? a.value.i : a.value.d)  << endl;
}