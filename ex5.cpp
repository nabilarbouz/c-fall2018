//Nabil Arbouz, MS Visual Studio, Windows 10
//Lab Exercise 5

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

struct Game
{
   string winner_name;
   string loser_name;
   int winner_score;
   int loser_score;
};

const string INPUT_PATH = "c:/text_files/lab5input.txt";
const string OUTUT_PATH = "c:/text_files/lab5output.txt";

//prototypes
int determine_file_size(ifstream& input_file);
void analyze_line( ifstream& input_file, ofstream& out_file);
void output_results(const Game& sport_game, ofstream& out_file);



int main()
{
   int num_lines;

   ifstream in_file(INPUT_PATH);
   if (!in_file)
   {
      cerr << "The file " << INPUT_PATH << " did not open!";
      exit(1);
   }

   ofstream out_file(OUTUT_PATH);
   if (out_file.fail())
   {
      cerr << "The file " << OUTUT_PATH << " did not open!";
      exit(2);
   }


   num_lines = determine_file_size(in_file);

   for (int i = 0; i < num_lines; i++)
   {
      analyze_line(in_file, out_file);
   }

   in_file.close();
   out_file.close();

   return 0;
}

int determine_file_size(ifstream& input_file)
{
   int line_counter = 0;
   string line_buffer;

   while(!input_file.eof())
   {
      if (getline(input_file, line_buffer))
      {
         line_counter++;
      }

      if (input_file.eof()) break;
   }

   input_file.clear();
   input_file.seekg(0, ios::beg);

   return line_counter;
}

void analyze_line(ifstream& input_file, ofstream& out_file)
{

   Game sport_game;
   string buffer;
   input_file >> sport_game.winner_name;

   input_file >> buffer;

   if (buffer.find(',') == string::npos)
      sport_game.winner_name += (" " + buffer);
   else
      sport_game.winner_score = 
      stoi((buffer.substr(0, (buffer.size() - 1))));

   input_file >> buffer;

   if (!(isalpha(buffer[0])))
      sport_game.winner_score =
      stoi((buffer.substr(0, (buffer.size() - 1))));
   else
      sport_game.loser_name = buffer;

   input_file >> buffer;

   if (!(isalpha(buffer[0])))
   {
      sport_game.loser_score = stoi(buffer);
      output_results(sport_game, out_file);
      return;
   }
   else if ((sport_game.loser_name).length() > 0)
      sport_game.loser_name += (" " + buffer);
   else
      sport_game.loser_name = buffer;

   input_file >> buffer;

   if (!(isalpha(buffer[0])))
   {
      sport_game.loser_score = stoi(buffer);
      output_results(sport_game, out_file);
      return;
   }
   else if ((sport_game.loser_name).length() > 0)
      sport_game.loser_name += (" " + buffer);
   else
      sport_game.loser_name = buffer;

   input_file >> buffer;

   sport_game.loser_score = stoi(buffer);
   output_results(sport_game, out_file);

}

void output_results(const Game& sport_game, ofstream& out_file)
{
   cout << sport_game.winner_name << " over " << sport_game.loser_name
     << " "  << sport_game.winner_score << " to " << sport_game.loser_score
      << endl;

   out_file << sport_game.winner_name << " over " << sport_game.loser_name
      << " " << sport_game.winner_score << " to " << sport_game.loser_score
      << endl;

}