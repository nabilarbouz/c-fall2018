//Nabil Arbouz, MS Visual Studio, Windows 10
//Assignment 3

//preprocessor directives
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>

//namespace
using namespace std;

//global variables
const string INPUT_PATH_1 = "c:/text_files/VTSMX.csv";
const string MODIFIED_IO_PATH = "c:/text_files/VTSMXmodified.csv";
const int COLS = 2;
const int ROWS = 500;
const int DATE = 0;
const int CLOSE = 1;

//prototypes
void read_original_file(ifstream& input_file, ofstream& out_file);
void gather_data_for_array(int date_and_close[][COLS], int Rows,
   ifstream& input_file);
void sort_2d_array(int date_and_close[][COLS], int Rows);
void swap_rows(int row_1[], int row_2[]);
void swap_element(int& a, int& b);
void output_current_date_close(const int date_close[][COLS], const int rows);
void output_last_5_closes(const int date_close[][COLS], int rows);
void output_oldest_5_closes(const int date_close[][COLS], int rows);
double calculate_50_day_avg(int date_close[][COLS], int rows);
double calculate_200_day_avg(int date_close[][COLS], int rows);
double calculate_gain_over_200MDA(double moving_200_avg, int date_close[][COLS], int rows);
string calculate_recommendation(double gain_over_200);
double calculate_percent_gain_ytd(int date_close[][COLS], int rows);
int sequential_search(int date_close[][COLS], int rows);
void output_highest_closes(int date_close[][COLS], int rows);

//main
int main()
{
   //declare arrays and variables
   int date_and_close[ROWS][COLS];
   double percent_gain_ytd, fifty_moving_avg,
      two_hundred_moving_avg, percent_gain_200;
   string recommendation;



   //open up files
   ifstream input_file;
   input_file.open(INPUT_PATH_1);
   if (input_file.fail())
   {
      cerr << "The file " << INPUT_PATH_1 << " could not be opened!" << endl;
      exit(1);
   }

   ofstream out_file;
   out_file.open(MODIFIED_IO_PATH);
   if (out_file.fail())
   {
      cerr << "The file " << MODIFIED_IO_PATH << " could not open!" << endl;
      exit(2);
   }

   //function call to read data from original file into modified file
   read_original_file(input_file, out_file);

   //close both files
   input_file.close();
   out_file.close();

   //reopen the modified file to be read
   ifstream input_file_2;
   input_file_2.open(MODIFIED_IO_PATH);
   if (input_file_2.fail())
   {
      cerr << "The input file " << MODIFIED_IO_PATH << " did not open!";
      exit(3);
   }

   //call to function to fill 2d array from modified file
   gather_data_for_array(date_and_close, ROWS,
      input_file_2);

   //close the modified file
   input_file_2.close();

   //call to output current date and close;
   output_current_date_close(date_and_close, ROWS);
   //call to output last five closes;
   output_last_5_closes(date_and_close, ROWS);
   //call to output oldest five closes;
   output_oldest_5_closes(date_and_close, ROWS);
   //call to calculate 50 day moving average;
   fifty_moving_avg = calculate_50_day_avg(date_and_close, ROWS);
   //call to calculate 200 day moving average;
   two_hundred_moving_avg = calculate_200_day_avg(date_and_close, ROWS);
   //calculate the gain over the 200 day moving average;
   percent_gain_200 = calculate_gain_over_200MDA(two_hundred_moving_avg, date_and_close, ROWS);
   //calculate recomendation to buy, sell, or hold;
   recommendation = calculate_recommendation(percent_gain_200);
   //calculate percent gain ytd;
   percent_gain_ytd = calculate_percent_gain_ytd(date_and_close, ROWS);




   //sort the array to find the highest closes
   sort_2d_array(date_and_close, ROWS);

   //call to output the highest closes
   output_highest_closes(date_and_close, ROWS);

   //ouput percent gain ytd
   cout << setprecision(2) << fixed;
   cout << "Percent gain YTD: " << percent_gain_ytd << "%" << endl << endl;

   //output 50 day moving avg
   cout << setprecision(2) << fixed;
   cout << "50 Day Moving Average: $" << fifty_moving_avg << endl;

   //output the 200 day moving avg
   cout << setprecision(2) << fixed;
   cout << "200 Day Moving Average: $" << two_hundred_moving_avg << endl;

   //output the percent gain over 200 day moving average
   cout << setprecision(2) << fixed;
   cout << "Percent gain over 200 Day Moving Average: " << percent_gain_200 << "%" << endl;
   
   //output the recommendation
   cout << "Recommendation: " << recommendation << endl;

   return 0;
}

void read_original_file(ifstream& input_file, ofstream& out_file)
{
   //variables
   string buffer;
   string hyphen_buffer, comma_buffer;
   int day, month, year, date, volume;
   string price;

   //get rid of the first line of the file.
   getline(input_file, buffer);

   while (!input_file.eof())
   {
      //get the year
      getline(input_file, hyphen_buffer, '-');
      if (input_file.eof()) break;
      year = stoi(hyphen_buffer);
      //get the month
      getline(input_file, hyphen_buffer, '-');
      month = stoi(hyphen_buffer);
      //get the day
      getline(input_file, comma_buffer, ',');
      day = stoi(comma_buffer);
      //create a date and store to to the first element in each row.
      date = (year * 10000) + (month * 100) + day;
      out_file << date << ' ';

      //read price lines

      for (int index = 0; index < 5; index++)
      {
         getline(input_file, price, ',');
         out_file << price << ' ';
      }

      //read and output volume
      input_file >> volume;
      out_file << volume << endl;
   }

}

void gather_data_for_array(int date_and_close[][COLS], int rows,
   ifstream& input_file)
{
   double buffer;
   double close;

   for (int index = 0; index < rows; index++)
   {

      //get the date
      input_file >> date_and_close[index][DATE];

      //skip the next 5 values;
      for (int x = 0; x < 3; x++)
      {
         input_file >> buffer;
      }

      //get the close;
      input_file >> close;
      date_and_close[index][CLOSE] = round((close * 100));

      for (int j = 0; j < 2; j++)
      {
      input_file >> buffer;
      }
   }
}

void sort_2d_array(int date_and_close[][COLS], int Rows)
{
   int min_position;

   for (int index = 0; index < Rows - 1; index++)
   {
      min_position = index;
      
      for (int j = (index + 1); j < Rows; j++)
      {
         if (date_and_close[min_position][CLOSE] > date_and_close[j][CLOSE])
         {
            min_position = j;
         }
      }

      if (min_position != index)
      {
         swap_rows(date_and_close[index], date_and_close[min_position]);
      }
   }

}

void swap_rows(int row_1[], int row_2[])
{
   swap(row_1[DATE], row_2[DATE]);
   swap(row_1[CLOSE], row_2[CLOSE]);
}

void swap_element(int& a, int& b)
{
   int temp;
   temp = a;
   a = b;
   b = temp;
}

void output_current_date_close(const int date_close[][COLS], const int rows)
{
   int month, day, year;
   double close_price;

   month = (date_close[rows - 1][DATE] % 10000) / 100;
   year = ((date_close[rows - 1][DATE] / 10000) % 2000);
   day = (date_close[rows - 1][DATE] % 100);

   close_price = static_cast<double>(date_close[rows - 1][CLOSE]) / 100.0;
   
   //print out the date
   cout << "Current Date: " << month << "/";
   if (day < 10)
      cout << "0" << day << "/";
   else
      cout << day << "/";
   cout << year << endl;

   //print out the closing price;
   cout << "Current Close: $" << close_price << endl << endl;
}

void output_last_5_closes(const int date_close[][COLS], int rows)
{
   int month, day, year;
   double close_price;
   string date;
   
   cout << "The latest five closes are:" << endl;

   for (int index = rows - 1; index > (rows - 6); index--)
   {

         month = (date_close[index][DATE] % 10000) / 100;
         year = ((date_close[index][DATE] / 10000) % 2000);
         day = (date_close[index][DATE] % 100);

         close_price = static_cast<double>(date_close[index][CLOSE]) / 100.0;

         if (month < 10)
            date = ("0" + to_string(month) + "/");
         else
            date = (to_string(month) + "/");


         if (day < 10)
            date +=  ("0" + to_string(day) + "/");
         else
            date += (to_string(day) + "/");

         date += to_string(year);

         cout << left << setw(11) << date;
         cout << "$" << close_price << endl;

   }

   cout << endl;
}

void output_oldest_5_closes(const int date_close[][COLS], int rows)
{
   int month, day, year;
   double close_price;
   string date;

   cout << "The oldest five closes are:" << endl;

   for (int index = 0; index <5; index++)
   {

      month = (date_close[index][DATE] % 10000) / 100;
      year = ((date_close[index][DATE] / 10000) % 2000);
      day = (date_close[index][DATE] % 100);

      close_price = static_cast<double>(date_close[index][CLOSE]) / 100.0;

      if (month < 10)
         date = ("0" + to_string(month) + "/");
      else
         date = (to_string(month) + "/");


      if (day < 10)
         date += ("0" + to_string(day) + "/");
      else
         date += (to_string(day) + "/");

      date += to_string(year);

      cout << left << setw(11) << date;
      cout << "$" << close_price << endl;

   }
   cout << endl;
}

double calculate_50_day_avg(int date_close[][COLS], int rows)
{
   int total = 0;

   for (int index = (rows - 1); index > rows - 51; index--)
   {
      total += date_close[index][CLOSE];
   }

   return (static_cast<double>(total) / 50) / 100.0;
}

double calculate_200_day_avg(int date_close[][COLS], int rows)
{
   int total = 0;

   for (int index = (rows - 1); index > rows - 201; index--)
   {
      total += date_close[index][CLOSE];
   }

   return (static_cast<double>(total) / 200) / 100.0;
}

double calculate_gain_over_200MDA(double moving_200_avg, int date_close[][COLS], int rows)
{
   double percent_gain;

   percent_gain = ((static_cast<double>(date_close[rows - 1][CLOSE]) / 100.0) - moving_200_avg)
      / moving_200_avg;

   return (percent_gain  * 100.0);
}

string calculate_recommendation(double gain_over_200)
{
   if (gain_over_200 > 5.0)
   {
      return "Sell";
   }
   else if (gain_over_200 < -5.0)
   {
      return "Buy";
   }
   else
   {
      return "Hold";
   }
}

double calculate_percent_gain_ytd(int date_close[][COLS], int rows)
{
   int position;
   double percent_gain_ytd;

   position = sequential_search(date_close, rows);

   percent_gain_ytd = (static_cast<double>(date_close[rows - 1][CLOSE] - date_close[position][1]) 
      / date_close[position][1]) * 100.0;
 
   return percent_gain_ytd;
}

int sequential_search(int date_close[][COLS], int rows)
{
   int search_value = 2017;
   
   for (int index = rows - 1; index >= 0; index--)
   {
      if ((date_close[index][DATE] / 10000) == search_value)
         return index;
   }

   return -1;
}

void output_highest_closes(int date_close[][COLS], int rows)
{
   int month, day, year;
   double close_price;
   string date;

   cout << "The latest five closes are:" << endl;

   for (int index = rows - 1; index > (rows - 6); index--)
   {

      month = (date_close[index][DATE] % 10000) / 100;
      year = ((date_close[index][DATE] / 10000) % 2000);
      day = (date_close[index][DATE] % 100);

      close_price = static_cast<double>(date_close[index][CLOSE]) / 100.0;

      if (month < 10)
         date = ("0" + to_string(month) + "/");
      else
         date = (to_string(month) + "/");


      if (day < 10)
         date += ("0" + to_string(day) + "/");
      else
         date += (to_string(day) + "/");

      date += to_string(year);

      cout << left << setw(11) << date;
      cout << "$" << close_price << endl;

   }
   cout << endl;
}