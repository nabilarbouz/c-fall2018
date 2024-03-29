// Nabil Arbouz, Windows 10, MS Visual Studio
// Lab Exercise #1

//preprocessor directives
#include <iostream>
#include <iomanip>
#include <ctime>

//namespace
using namespace std;

//main function
int main()
{
   //declare & initialize constant for range
   const int RANGE = 50;

   //declare variables
   double num_1, num_2;
   double avg_num;

   //use the clock time to randomize 
   srand(time(0));

   //loop for 16 random numbers
   for (int idx = 0; idx < 16; idx++)
   {
      //generate the numbers
      num_1 = rand() % RANGE + 1;
      num_2 = rand() % RANGE + 1;

      //divide first number by second number 
      //and store it.
      avg_num = num_1 / num_2;

      //use manipulators for 4 sig figs and
      //print the avg_num to the console.
      cout << setprecision(4) << fixed;
      cout << avg_num << endl;

   }

   return 0;

}
