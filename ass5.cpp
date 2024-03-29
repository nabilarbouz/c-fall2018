//Nabil Arbouz, MS Visual Studio, Windows 10
// Assignment 5

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cctype>

using namespace std;

//structured data definitions
struct NFL_Team
{
   string name;
   string conference;
   string division;
   unsigned short wins;
   unsigned short losses;
   unsigned short ties;
   double pct;
};


//global constants
const string TEAMS_INPUT_PATH = "c:/text_files/nfl_teams.txt";
const string SCORES_INPUT_PATH = "c:/text_files/nfl_scores_updated.txt";
const int NUM_OF_TEAMS = 32;
const int NUM_OF_DIV = 4;
const int NUM_OF_CONF = 2;

//prototypes
void gather_teams(NFL_Team nfl_array[], string division_names[],
   string conference_names[], ifstream& input_file);
void output_report(string division_names[],
   string conference_names[], NFL_Team nfl_array[]);
void analyze_scores(NFL_Team nfl_array[], ifstream& input_scores);
void update_win_loss_record(NFL_Team nfl_array[], string search_value, char win_loss_flag);
void calculate_record_pct(NFL_Team nfl_array[]);
double calculate_sort_key(NFL_Team team);
void sort_by_member(double keys[], NFL_Team nfl_array[]);
void sort_division_conference_names(string name_array[], int array_size);
void swap_members(NFL_Team& nfl_team_1, NFL_Team& nfl_team_2);
void swap_keys(double &a, double &b);
void swap_names(string &a, string& b);

//main
int main()
{
   ifstream input_teams(TEAMS_INPUT_PATH);
   if (input_teams.fail())
   {
      cerr << "The file" << TEAMS_INPUT_PATH << " did not open!";
      exit(1);
   }

   ifstream input_scores(SCORES_INPUT_PATH);
   if (!input_scores)
   {
      cerr << "The file " << SCORES_INPUT_PATH << "did not open!";
      exit(2);
   }

   //struct array for the teams
   NFL_Team nfl_array[NUM_OF_TEAMS];

   //array for holding the sort keys
   double sort_keys[NUM_OF_TEAMS];

   //string arrays for holding conference and division names
   string conference_names[2];
   string division_names[8];

   //get the team's name and conference/divsion information
   gather_teams(nfl_array, division_names, 
      conference_names, input_teams);
   
   //analyze scores;
   analyze_scores(nfl_array, input_scores);

   //calculate record percentage;
   calculate_record_pct(nfl_array);
   
   //calculate the sort keys
   for (int i = 0; i < NUM_OF_TEAMS; i++)
   {
      sort_keys[i] = calculate_sort_key(nfl_array[i]);
   }

   //sort the conference and division names for output
   sort_division_conference_names(division_names, NUM_OF_DIV);
   sort_division_conference_names(conference_names, NUM_OF_CONF);
   
   //sort the members by their sort keys
   sort_by_member(sort_keys, nfl_array);

   //output the report
   output_report(division_names, conference_names, nfl_array);
  
   input_teams.close();
   input_scores.close();

}

void gather_teams(NFL_Team nfl_array[], string division_names[], 
   string conference_names[], ifstream& input_file)
{
   string team_name, conference_name, division_name;
   string buffer;

   int team_count = 0;
   int division_count = 0;
   int conferernce_count = 0;

   //split up the file into conferences
   for (int i = 0; i < 2; i++)
   {
      getline(input_file, conference_name);
      conference_names[conferernce_count] = conference_name;
      conferernce_count++;

      getline(input_file,buffer);
      for (int i = 0; i < 4; i++)
      {
         getline(input_file, division_name);
         if (division_name.find("West") != string::npos)
         {
            division_names[division_count] = "West Division";
            division_name = "West Divsion";
         }
         else if (division_name.find("East") != string::npos)
         {
            division_names[division_count] = "East Division";
            division_name = "East Division";
         }
         else if (division_name.find("North") != string::npos)
         {
            division_names[division_count] = "North Division";
            division_name = "North Divsion";
         }
         else if (division_name.find("South") != string::npos)
         {
            division_names[division_count] = "South Division";
            division_name = "South Division";
         }
         division_count++;

         for (int j = 0; j < 4; j++)
         {
            getline(input_file, team_name);
            nfl_array[team_count].conference = conference_name;
            nfl_array[team_count].division = division_name;
            nfl_array[team_count].name = team_name;
            nfl_array[team_count].wins = 0;
            nfl_array[team_count].losses = 0;
            nfl_array[team_count].ties = 0;
            nfl_array[team_count].pct = 0.000;
            team_count++;
         }
         getline(input_file, buffer);
      }
      
   }
}

void output_report(string division_names[], 
   string conference_names[], NFL_Team nfl_array[])
{
   int team_counter = 31;
   for (int i = 1; i > -1; i--)
   {
      cout << conference_names[i] << endl << endl;

      for (int index = 3; index > -1; index--)
      {
         cout << setw(22) << left << division_names[index]
            << setw(6) << left << "W" << setw(6) << left << "L"
            << setw(6) << left << "T" << right << setw(6) 
            << "Pct" << endl;


         for (int j = 3; j > -1; j--)
         {
            cout << setw(22) << left << nfl_array[team_counter].name
               << setw(6) << left << nfl_array[team_counter].wins
               << setw(6) << left << nfl_array[team_counter].losses
               << setw(6) << left << nfl_array[team_counter].ties;
            if(nfl_array[team_counter].pct == 1.0) cout << right << setw(6) << setprecision(4) <<showpoint
               << nfl_array[team_counter].pct << endl;
            else cout << right << setw(6) << setprecision(3) << showpoint
               << nfl_array[team_counter].pct << endl;
            team_counter--;
         }
         cout << endl;
      }
   }
}

void analyze_scores(NFL_Team nfl_array[], ifstream& input_scores)
{
   string line_buffer, string_buffer;
   string winner, loser, date_buffer;
   int winner_points, loser_points;
   int space_position;
   bool line_complete;


   while (!input_scores.eof())
   {
      line_complete = false;
      line_buffer.clear();
      string_buffer.clear();
      winner.clear();
      loser.clear();

      getline(input_scores, line_buffer);
      //if (input_scores.eof()) break;

      //find the first space to get rid of the date
      space_position = line_buffer.find(' ');
      line_buffer = line_buffer.substr(space_position + 1);

      //grab the next word after getting rid of the date
      winner = line_buffer.substr(0, line_buffer.find(' '));

      //chop the first word of the winners name from the line buffer
      line_buffer = line_buffer.substr(winner.length() + 1);

       //grab the second word of the winners name and add it to winner
      string_buffer = line_buffer.substr(0, line_buffer.find(' '));
      winner += " ";
      winner += line_buffer.substr(0, line_buffer.find(' '));

      //chop the second word of the winners name from the line buffer;
      line_buffer = line_buffer.substr(string_buffer.length() + 1);

      //check for third word of name or points
      string_buffer = line_buffer.substr(0, line_buffer.find(' '));
      if ((string_buffer.find(',')) == string::npos)
      {
         winner += " ";
         winner += string_buffer;
      }
      else
      {
         winner_points = stoi(string_buffer.substr(0, string_buffer.length() - 1));
      }

      //chop off either the points or the third part of the name from the string
      line_buffer = line_buffer.substr(string_buffer.length() + 1);

      //check for points or first part of the losing team
      string_buffer = line_buffer.substr(0, line_buffer.find(' '));
      if ((string_buffer.find(',')) == string::npos)
      {
         loser = string_buffer;
      }
      else
      {
         winner_points = stoi(string_buffer.substr(0, string_buffer.length() - 1));
      }

      //chop the string buffer from the line buffer
      line_buffer = line_buffer.substr(string_buffer.length() + 1);

      //check for first part of the loser's name or the second part;
      string_buffer = line_buffer.substr(0, line_buffer.find(' '));
      if (loser.length() > 0)
      {
         loser += " ";
         loser += string_buffer;
      }
      else
      {
         loser = string_buffer;
      }

      //chop the string buffer from the line buffer;
      line_buffer = line_buffer.substr(string_buffer.length() + 1);

      //check for loser's score or another part of the losers name
      string_buffer = line_buffer.substr(0, line_buffer.find(' '));
      if (isalpha(string_buffer[0]) || (string_buffer == "49ers"))
      {
         loser += " ";
         loser += string_buffer;
      }
      else
      {
         //if this activates, initiate the search to hand out the W's and L's
         loser_points = stoi(string_buffer);
         line_complete = true;
      }
      //chop the string buffer from the line buffer;
      if(line_complete == false) line_buffer = line_buffer.substr(string_buffer.length() + 1);

      //check for loser's score or another part of the losers name.
      if(line_complete == false) string_buffer = line_buffer.substr(0, line_buffer.find(' '));
      if ((isalpha(string_buffer[0]) || (string_buffer == "49ers")) && line_complete == false)
      {
         loser += " ";
         loser += string_buffer;
      }
      else
      {
         //if this activates, initiate the search to hand out the W's and L's
         loser_points = stoi(string_buffer);
         line_complete = true;
      }

      //chop the string buffer from the line buffer;
      if (line_complete == false) line_buffer = line_buffer.substr(string_buffer.length() + 1);

      //check for loser's score or another part of the losers name.
      if (line_complete == false) string_buffer = line_buffer.substr(0, line_buffer.find(' '));
      if ((isalpha(string_buffer[0]) || (string_buffer == "49ers")) && line_complete == false)
      {
         loser += " ";
         loser += string_buffer;
      }
      else
      {
         //if this activates, initiate the search to hand out the W's and L's
         loser_points = stoi(string_buffer);
         line_complete = true;
      }

      //update the win-loss record for each team
      //check for a tie
      if (winner_points == loser_points)
      {
         update_win_loss_record(nfl_array, winner, 'T');
         update_win_loss_record(nfl_array, loser, 'T');
      }
      else
      {
         update_win_loss_record(nfl_array, winner, 'W');
         update_win_loss_record(nfl_array, loser, 'L');
      }
   }

}


void update_win_loss_record(NFL_Team nfl_array[], string search_value, char win_loss_flag)
{
   bool found = false;
   int counter = 0;

   if (win_loss_flag == 'W')
   {
      while (found == false)
      {
         if (nfl_array[counter].name == search_value)
         {
            nfl_array[counter].wins++;
            return;
         }
         else
         {
            counter++;
         }
      }
   }

   if (win_loss_flag == 'L')
   {
      while (found == false)
      {
         if (nfl_array[counter].name == search_value)
         {
            nfl_array[counter].losses++;
            return;
         }
         else
         {
            counter++;
         }
      }
   }

   if (win_loss_flag == 'T')
   {
      while (found == false)
      {
         if (nfl_array[counter].name == search_value)
         {
            nfl_array[counter].ties++;
            return;
         }
         else
         {
            counter++;
         }
      }
   }
}

void calculate_record_pct(NFL_Team nfl_array[])
{
   for (int i = 0; i < 32; i++)
   {
      if(nfl_array[i].ties > 0)
      nfl_array[i].pct = (static_cast<double>(nfl_array[i].wins + 0.5) * nfl_array[i].ties) /
         (nfl_array[i].wins + nfl_array[i].losses + nfl_array[i].ties);
      else
         nfl_array[i].pct = static_cast<double>(nfl_array[i].wins) /
         (nfl_array[i].wins + nfl_array[i].losses);
   }
}

void sort_by_member(double keys[], NFL_Team nfl_array[])
{
   bool swap_happened;

   do
   {
      swap_happened = false;
      for (int i = 0; i < NUM_OF_TEAMS - 1; i++)
      {
         if (keys[i] < keys[i + 1])
         {
            swap_members(nfl_array[i], nfl_array[i + 1]);
            swap_keys(keys[i], keys[i + 1]);
            swap_happened = true;
         }
      }
   } while (swap_happened);
}

double calculate_sort_key(NFL_Team team)
{
   double key = (100 * team.conference[0])
      + (team.division[0])
      + (1-team.pct);
   return key;
}

void swap_members(NFL_Team& nfl_team_1, NFL_Team& nfl_team_2)
{
   string temp_name, temp_conference, temp_division;
   unsigned short temp_wins, temp_losses, temp_ties;
   double temp_pct;

   temp_conference = nfl_team_1.conference;
   temp_name = nfl_team_1.name;
   temp_division = nfl_team_1.division;
   temp_wins = nfl_team_1.wins;
   temp_losses = nfl_team_1.losses;
   temp_ties = nfl_team_1.ties;
   temp_pct = nfl_team_1.pct;

   nfl_team_1.conference = nfl_team_2.conference;
   nfl_team_1.name = nfl_team_2.name;
   nfl_team_1.division = nfl_team_2.division;
   nfl_team_1.wins = nfl_team_2.wins;
   nfl_team_1.losses = nfl_team_2.losses;
   nfl_team_1.ties = nfl_team_2.ties;
   nfl_team_1.pct = nfl_team_2.pct;

   nfl_team_2.conference = temp_conference;
   nfl_team_2.name = temp_name;
   nfl_team_2.division = temp_division;
   nfl_team_2.wins = temp_wins;
   nfl_team_2.losses = temp_losses;
   nfl_team_2.ties = temp_ties;
   nfl_team_2.pct = temp_pct;
}

void swap_keys(double &a, double &b)
{
   double temp;
   temp = a;
   a = b;
   b = temp;
}

void sort_division_conference_names(string name_array[], int array_size)
{
   bool swap_happened;

   do
   {
      swap_happened = false;
      for (int i = array_size-1; i > 0; i--)
      {
         if (name_array[i] > name_array[i - 1])
         {
            swap_names(name_array[i], name_array[i - 1]);
            swap_happened = true;
         }
      }
   } while (swap_happened);
}

void swap_names(string &a, string& b)
{
   string temp;
   temp = a;
   a = b;
   b = temp;
}
