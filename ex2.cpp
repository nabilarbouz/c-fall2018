//Nabil Arbouz, Microsoft V.S., Windows 10
//Lab Exercise #2

//preprocessor directives
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cmath>

//namespace
using namespace std;

//global named constants
const int ARRAY_SIZE_ROWS = 12, COLS = 2;
const double PI = 3.1416;
const string INPUT_PATH = "c:/text_files/names_radius.txt";
const string OUTPUT_PATH = "c:/text_files/firstname_circumference.txt";

//prototypes
void gather_data(string names[][COLS], double radius[], ifstream& in_file);
void calculate_circumference(double radius[], double circumference[]);
void output_data(string names[][COLS], double circumference[], ofstream& out_file);

//main
int main()
{
   string names[ARRAY_SIZE_ROWS][COLS];
   double radius[ARRAY_SIZE_ROWS], circumference[ARRAY_SIZE_ROWS];

   ifstream in_file;
   in_file.open(INPUT_PATH);
   if (!in_file)
   {
      cerr << "The file " << INPUT_PATH << " did not open" << endl;
      exit(1);
   }

   ofstream out_file;
   out_file.open(OUTPUT_PATH);
   if (!out_file)
   {
      cerr << "The file " << OUTPUT_PATH << " did not open" << endl;
      exit(1);
   }

   gather_data(names, radius, in_file);
   calculate_circumference(radius, circumference);
   output_data(names ,circumference, out_file);


   in_file.close();
   out_file.close();

   return 0;
}

void gather_data(string names[][COLS], double radius[], ifstream& in_file)
{
   for (int index = 0; index < ARRAY_SIZE_ROWS; index++)
   {
      for (int j = 0; j < COLS; j++)
      {
         in_file >> names[index][j];
      }

      in_file >> radius[index];
   }

}

void calculate_circumference(double radius[], double circumference[])
{
   for (int index = 0; index < ARRAY_SIZE_ROWS; index++)
   {
      circumference[index] = 2.0 * PI * radius[index];
   }
}

void output_data(string names[][COLS], double circumference[], ofstream& out_file)
{
   const int FIRST_NAME = 0, LAST_NAME = 1;

   out_file << setprecision(2) << fixed;

   for (int index = 0; index < ARRAY_SIZE_ROWS; index++)
   {
      out_file << left << setw(11) << names[index][FIRST_NAME];
      out_file << right << setw(11) << circumference[index] << endl;
   }
}