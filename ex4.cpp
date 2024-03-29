//Nabil Arbouz, MS Visual Studio, Windows 10
//Lab Exercise 4

//preprocessor directives
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>

//namepsace
using namespace std;

//global constant
const string INPUT_PATH = "c:/text_files/ex4data.txt";

//prototype
int count_records(ifstream& in_file);


int main()
{

   int record_count = 0;

   ifstream in_file(INPUT_PATH);
   if (in_file.fail())
   {
      cerr << "The file " << INPUT_PATH << "did not open!" << endl;
      exit(1);
   }
   
   //determine how many records the file holds
   record_count = count_records(in_file);

   //allocate memory dynamically to store the data from the file
   string* stock_data_ptr = new string[record_count];

   //reopen the file
   in_file.open(INPUT_PATH);
   if (in_file.fail())
   {
      cerr << "The file " << INPUT_PATH << "did not open!" << endl;
      exit(1);
   }

   //store the lines dynamically
   for (int i = 0; i < record_count; i++)
   {
      getline(in_file, stock_data_ptr[i]);
   }

   //print out first two items;
   for (int i = 0; i < 2; i++)
   {
      cout << stock_data_ptr[i] << endl;
   }

   //print out last two items;
   for (int i = record_count - 2; i < record_count; i++)
   {
      cout << stock_data_ptr[i] << endl;
   }

   //release the allocated memory
   delete[] stock_data_ptr;

   return 0;
}

int count_records(ifstream& in_file)
{
   string temp;
   int counter = 0;

   while (!in_file.eof())
   {
      if (getline(in_file, temp)) counter++;
 
      else break;
   }

   //close the file
   in_file.close();

   return counter;
}