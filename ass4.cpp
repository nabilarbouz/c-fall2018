//Nabil Arbouz, MS Visual Studio, Windows 10
//Assignment 4

#define _CRT_SECURE_NO_WARNINGS

//preprocessor directives
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cctype>

//namespace
using namespace std;

//global constants
const char INPUT_PATH_DICT[100] = "c:/text_files/ass4_unsorted_words.txt";
const char INPUT_PATH_SPEECH[100] = "c:/text_files/ass4_ihaveadream.txt";
const long int SIZE_OF_DICT = 23907;

//function prototypes
void gather_dictionary(char* word[]);
void sort_dictionary(char* word[]);
void swap_strings(char* &a, char* &b);
void gather_and_check_speech_line(char* word_list[]);
int check_spelling(const char* search_value, char* word_list[]);

//main 
int main()
{
   //declare char pointer array for holding dictionary words
   char* dict_words[SIZE_OF_DICT];

   //call to fill the dictioanry
   gather_dictionary(dict_words);

   //call to sort the dictionary
   sort_dictionary(dict_words);

   //call to grab and check one line at a time from the speech file;
   gather_and_check_speech_line(dict_words);

   //release the memory
   for (int index = 0; index < SIZE_OF_DICT; index++)
   {
      delete[] dict_words[index];
   }

   return 0;
}

void gather_dictionary(char* word[])
{
   //open the dictionary file
   ifstream input_file(INPUT_PATH_DICT);
   if (input_file.fail())
   {
      cerr << "The input file " << INPUT_PATH_DICT
         << "did not open!" << endl;
      exit(1);
   }

   char buffer[100];

   for (int i = 0; i < SIZE_OF_DICT; i++)
   {
      input_file >> buffer;
      //store in lower case
      for (size_t i = 0; i < strlen(buffer); i++)
      {
         buffer[i] = tolower(buffer[i]);
      }
      word[i] = new char[(strlen(buffer) + 1)];
      strcpy(word[i], buffer);
   }

   input_file.close();
}

void sort_dictionary(char* word[])
{
   int min_position;

   for (int i = 0; i < SIZE_OF_DICT - 1; i++)
   {
      min_position = i;
      for (int j = (i + 1); j < SIZE_OF_DICT; j++)
      {
         if (strcmp(word[j], word[min_position]) < 0)
         {
            min_position = j;
         }

      }
      if (min_position != i)
      {
         swap_strings(word[i], word[min_position]);
      }
   }
}

void swap_strings(char* &a, char* &b)
{
   char* temp;
   temp = a;
   a = b;
   b = temp;
}


void gather_and_check_speech_line(char* word_list[])
{

   ifstream input_file(INPUT_PATH_SPEECH);
   if (!input_file)
   {
      cerr << "The file " << INPUT_PATH_SPEECH << " did not open";
      exit(2);
   }

   int found;
   char* ptr_to_word;
   char line_buffer[1000], word_buffer[32], original_word[32];
   int line = 1;

   while (!(input_file.eof()))
   {

      input_file.getline(line_buffer, 1000);

      if (input_file.eof()) break;

      ptr_to_word = strtok(line_buffer, "\"- ,.-\n?*(){}!:;");
      strcpy(word_buffer, ptr_to_word);
      word_buffer[strlen(word_buffer)] = 0;
      //copy original word in order to print to console if word is misspelled
      strcpy(original_word, word_buffer);
      original_word[strlen(original_word)] = 0;

      //convert the word to lowercase before sending it to the search
      for (size_t i = 0; i < strlen(word_buffer); i++)
      {
         word_buffer[i] = tolower(word_buffer[i]);
      }
      //check first word of the line for spelling
      found = check_spelling(word_buffer, word_list);

      //check for "s" at the end of a word if word is mispelled
      if (found == -1 && (word_buffer[strlen(word_buffer) - 1] == 's'))
      {
         strncpy(word_buffer, word_buffer, strlen(word_buffer) - 1);
         word_buffer[strlen(word_buffer) - 1] = 0;
         //check if the word is correct without the "s" at the end
         found = check_spelling(word_buffer, word_list);
      }


      //if it is misspelled even without an "s" at the end , this if block will trigger;
      if (found == -1)
      {
         cout << "Misspelled word, " << original_word << " on line " << line << endl;
      }

      //this while loop will read and test words until the end of the line
      //it applies the same logic as checking the first word of the line
      while (ptr_to_word != NULL)
      {
         ptr_to_word = strtok(NULL, "\"- ,.-\n?!:;");
         if (ptr_to_word == NULL)
            break;
         strcpy(word_buffer, ptr_to_word);
         strcpy(original_word, word_buffer);
         original_word[strlen(original_word)] = 0;

         for (size_t i = 0; i < strlen(word_buffer); i++)
         {
            word_buffer[i] = tolower(word_buffer[i]);
         }

         found = check_spelling(word_buffer, word_list);

         //check if the incorrect word has an "s" at the end
         if (found == -1 && (word_buffer[strlen(word_buffer) - 1] == 's'))
         {
            strncpy(word_buffer, word_buffer, strlen(word_buffer) - 1);
            word_buffer[strlen(word_buffer) - 1] = 0;
            found = check_spelling(word_buffer, word_list);
         }

         if (found == -1)
         {
            cout << "Misspelled word, " << original_word << " on line " << line << endl;
         }
      }

      line++;
   }

   input_file.close();
}

int check_spelling(const char* search_value, char* word_list[])
{
   int low, middle, high;

   low = 0;
   high = SIZE_OF_DICT - 1;

   while (low <= high)
   {
      middle = (low + high) / 2;
      if (strcmp(search_value, word_list[middle]) < 0)
      {
         high = middle - 1;
      }
      else if (strcmp(search_value, word_list[middle]) > 0)
      {
         low = middle + 1;
      }
      else if (strcmp(search_value, word_list[middle]) == 0)
      {
         return 1;
      }
   }

   return -1;
}