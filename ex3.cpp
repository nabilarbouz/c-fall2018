//Nabil Arbouz, M.S. Visual Studio, Windows 10
//Lab Exercise #3

//preprocessor directives
#include <iostream>
#include <iomanip>
#include <cstdlib>

//namespace
using namespace std;

const int Cols = 9;   // Global const

// Put your function prototypes here //
void initialize(int a[][Cols], int Rows, int Cols);
void print(const int a[][Cols], int Rows, int Cols);
void printInHex(const int a[][Cols], int Rows, int Cols);



int main()
{
   const int Rows = 7;

   int a[Rows][Cols];
   initialize(a, Rows, Cols);
   print(a, Rows, Cols);
   printInHex(a, Rows, Cols);
}

void initialize(int a[][Cols], int Rows, int Cols)
{
   int value = 3;

   for (int i = 0; i < Rows; i++)
   {
      for (int j = 0; j < Cols; j++)
      {
         a[i][j] = value;
         value += 3;
      }
   }
}

void print(const int a[][Cols], int Rows, int Cols)
{
   for (int i = 0; i < Rows; i++)
   {
      for (int j = 0; j < Cols; j++)
      {
         cout << right << setw(5) << a[i][j];
      }
      cout << endl;
   }
   cout << endl;
}

void printInHex(const int a[][Cols], int Rows, int Cols)
{
   for (int i = 0; i < Rows; i++)
   {
      for (int j = 0; j < Cols; j++)
      {
         cout << right << setw(5) << hex << a[i][j];
      }
      cout << endl;
   }
   cout << endl;
}