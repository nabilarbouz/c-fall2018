//Nabil Arbouz, Assignment 2, MS Visual Studio, Windows 10
//This program searches a dictionary list for keywords
//and outputs the missing keywords.

//preprocessor directives
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>

//namespace
using namespace std;

//function prototypes
void output_file_header(ofstream& out_file);
void gather_data(string list[], int array_size, ifstream& in_file);
void sort_array(string list[], int array_size);
void swap(string& entry_1, string& entry_2);
int find_keywords(string dictionary_list[], string keyword_list[],
   int dictionary_size, int keyword_size, ofstream& out_file);
void output_nfound_keyword(string keyword, ofstream& out_file);
void output_kw_not_found(int num_words);

//named constants
const string INPUT_PATH_1 = "c:/text_files/unsorted_dictionary.txt";
const string INPUT_PATH_2 = "c:/text_files/keywords.txt";
const string OUTPUT_PATH = "c:/text_files/keywords_not_found.txt";

//array sizes (*not required to pass global named constants
//as arguments to functions but did anyways for practice)
const int DICTIONARY_SIZE = 16000;
const int KEYWORDS_SIZE = 84;

//main
int main()
{
   //open up the files
   ifstream in_file_1;
   in_file_1.open(INPUT_PATH_1);
   if (in_file_1.fail())
   {
      cerr << "The input file " << INPUT_PATH_1 << " did not open!";
      exit(1);
   }

   ifstream in_file_2;
   in_file_2.open(INPUT_PATH_2);
   if (in_file_2.fail())
   {
      cerr << "The input file " << INPUT_PATH_2 << " did not open!";
      exit(2);
   }
   
   ofstream out_file;
   out_file.open(OUTPUT_PATH);
   if (out_file.fail())
   {
      cerr << "The output file " << OUTPUT_PATH << " did not open!";
      exit(3);
   }
   
   //declare variables
   string dictionary[DICTIONARY_SIZE];
   string keywords[KEYWORDS_SIZE];
   int kw_not_found;

   //function calls
   output_file_header(out_file);

   gather_data(dictionary, DICTIONARY_SIZE, in_file_1);

   gather_data(keywords, KEYWORDS_SIZE, in_file_2);

   sort_array(dictionary, DICTIONARY_SIZE);

   sort_array(keywords, KEYWORDS_SIZE);

   kw_not_found = find_keywords(dictionary, keywords, 
      DICTIONARY_SIZE, KEYWORDS_SIZE, out_file);

   output_kw_not_found(kw_not_found);
   

   //close files
   in_file_1.close();
   in_file_2.close();
   out_file.close();

   return 0;
}

//gather the data from the text files
void gather_data(string list[], int array_size, ifstream& in_file)
{

   for (int index = 0; index < array_size; index++)
   {
      in_file >> list[index];
   }

}

//selection sort for an array
void sort_array(string list[], int array_size)
{
   int min_position;

   for (int index = 0; index < array_size - 1; index++)
   {
      min_position = index;
      
      for(int j = (index + 1); j < array_size; j++)
      {
         if (list[min_position] > list[j])
         {
            min_position = j;
         }
      }
     
      if (min_position != index)
      {
         swap(list[index], list[min_position]);
      }
   }
}

//swap function
void swap(string& entry_1, string& entry_2)
{
   string temp; 
   temp = entry_1;
   entry_1 = entry_2;
   entry_2 = temp;
}

//binary search function
int find_keywords(string dictionary_list[], string keyword_list[],
   int dictionary_size, int keyword_size, ofstream& out_file)
{
   int not_found_counter = 0;
   
   for (int index = 0; index < keyword_size; index++)
   {
      int low, 
         high, 
         middle, 
         found;

      low = 0;
      high = dictionary_size - 1;
      found = -1;

      while (low <= high)
      {
         middle = (low + high) / 2;
         if (keyword_list[index] < dictionary_list[middle])
         {
            high = middle - 1;
         }
         else if (keyword_list[index] > dictionary_list[middle])
         {
            low = middle + 1;
         }
         else
         {
            found = middle;
            break;
         }
      }

      //call function to output keyword that was not found.
      //and update counter for keywords not found.
      if (found == -1)
      {
         output_nfound_keyword(keyword_list[index], out_file);
         not_found_counter++;
      }
   }
   
   return not_found_counter;
}

//output number of words not found to console
void output_nfound_keyword(string keyword, ofstream& out_file)
{
   out_file << keyword << endl;
}

//output the file header for keywords not in dictionary
void output_file_header(ofstream& out_file)
{
   out_file << "keywords not in the dictionary" << endl;
}

//output the number of key words not found
void output_kw_not_found(int num_words)
{
   cout << "Number of keywords not found = " << num_words << endl;
}