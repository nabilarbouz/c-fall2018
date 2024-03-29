//Nabil Arbouz, Microsoft V.S., Windows 10
//Assignment 1

//this program will read a shopping list with prices
//for each item and then produce an invoice with tax.

//preprocessor directives
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

//namespace
using namespace std;

//function prototypes
void gather_data(string &name_list, double &price_list, ifstream &in_file);
double calculate_tax(string name_list, double price_list);
double calculate_sub_total(double price, double tax_amount);
double calculate_total_cost(double sub_total);
void output_header(ofstream &out_file);
void output_data_lines(string name, double cost, double tax,
   double sub_total, ofstream& out_file);
void output_total(double total, ofstream &out_file);

//main function
int main()
{
   //path name constants
   const string INPUT_PATH_NAME = "c:/text_files/shopping_list.txt";
   const string OUTPUT_PATH_NAME = "c:/text_files/shopping_report.txt";

   //declare   variables
   string item_name;
   double item_price;
   double item_tax;
   double sub_total_price;
   double total_cost;
   string buffer; //will hold first line of file

   //open the input file
   //creat ifstream object
   ifstream in_file;
   in_file.open(INPUT_PATH_NAME);
   //check for succesful open
   if (in_file.fail())
   {
      cerr << "The file " << INPUT_PATH_NAME
         << " could not be opened." << endl;
      exit(1);
   }

   //open output file
   ofstream out_file;
   out_file.open(OUTPUT_PATH_NAME);
   //check for successful open
   if (out_file.fail())
   {
      cerr << " The file" << OUTPUT_PATH_NAME
         << " could not be opened." << endl;
      exit(1);
   }

   //get rid of the file heading of the input file
   getline(in_file, buffer);

   //print the header file to the output file
   output_header(out_file);

   //loop to gather and process data from file
   while (!in_file.eof())
   {
      //function calls
      gather_data(item_name, item_price, in_file);
         if (in_file.eof()) break;
      item_tax = calculate_tax(item_name, item_price);
      sub_total_price = calculate_sub_total(item_price,
         item_tax);
      total_cost = calculate_total_cost(sub_total_price);
      output_data_lines(item_name, item_price, item_tax,
         sub_total_price, out_file);
   }

   //print out total at end of report;
   output_total(total_cost, out_file);

   //close the files
   in_file.close();
   out_file.close();

   return 0;
}

void gather_data(string &name_list, double &price_list, ifstream &in_file)
{
   in_file >> name_list;
   in_file >> price_list;
}

double calculate_tax(string name_list, double price_list)
{
   const double TAX_RATE = .09;
   double tax_amount;

   if ((!(name_list == "banana")) && (!(name_list == "water")))
   {
      tax_amount = price_list * TAX_RATE;
   }
   else
   {
      tax_amount = 0.0;
   }
      
   return tax_amount;
}

double calculate_sub_total(double price, double tax_amount)
{
   double sub_total;
      sub_total = price + tax_amount;
      return sub_total;
}

double calculate_total_cost(double sub_total)
{
   static double total = 0;
   total += sub_total;
   return total;
}

void output_header(ofstream &out_file)
{

   out_file << left << setw(12) << "Item"
      << right << setw(10) << "Cost"
      << right << setw(8) << "Tax"
      << right << setw(12) << "Subtotal"
      << endl;

   out_file << left << setw(12) << "-----------"
      << right << setw(10) << "------"
      << right << setw(8) << "-----"
      << right << setw(12) << "--------"
      << endl;

}


void output_data_lines(string name, double cost, double tax,
   double sub_total, ofstream& out_file)
{


   out_file << setprecision(2) << fixed;
   out_file << left << setw(12) << name
      << right << setw(10) << cost
      << right << setw(8) << tax
      << right << setw(12) << sub_total
      << endl;

}

void output_total(double total, ofstream &out_file)
{

   out_file << right << setw(42) << "--------" << endl;

   out_file << right << setw(30) << "Total"
      << right << setw(12) << total
      << endl;

}