//Nabil Arbouz, MS Visual Studio, Windows 10
//Assignment 6
//Skunk

//preprocessor directives
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime>

//namespace
using namespace std;

//number of players game is programmed for
const int NUM_OF_PLAYERS = 3;

//personality types of players
const int CHICKEN = 1;
const int DARING = 2;
const int WILD = 4;

enum PLAYER_ID { PLAYER_1, PLAYER_2, PLAYER_3 };

struct Dice
{
   int dice_1;
   int dice_2;
};

class Player
{

private:

   string name;
   int points;
   int number_of_rolls_pt;
   int turn_total;
   Dice player_dice;

public:
   //input players name prototype
   void set_player_name();

   //member function that will roll 6-sided dice
   void roll_dice();

   //constructor prototype
   Player();

   //get_name prototype
   string get_name() const;

   //reset total prototype
   void reset_turn_total();

   //reset the points back to 0
   void reset_points();

   //get the points
   int get_points() const;

   //output the roll
   void output_roll() const;

   //validate the rolls
   bool validate_rolls();

   //set personality for rolls
   void set_roll_personality(int type);

   //check for a winner member function
   bool validate_point_total();

   //get number of rolls per turn
   int get_num_of_rolls() const;

   //get turn total prototype
   int get_turn_total() const;
};

//constructor function
Player::Player()
{
   set_player_name();
   points = 0;
}

//member function that prompts the user for a player's name
void Player::set_player_name()
{
   cout << "Please enter a player name: ";
   getline(cin, name);
}

//member function that will roll 6-sided dice
void Player::roll_dice()
{
   player_dice.dice_1 = rand() % 6 + 1;
   player_dice.dice_2 = rand() % 6 + 1;
}

//get_name member function
//returns the name of the Player
string Player::get_name() const
{
   return name;
}

//function to reset the turn total to 0
//if the user rolls a 1;
void Player::reset_turn_total()
{
   turn_total = 0;
}

//function to reset the overall points for a player
// if they roll a SKUNK (two "1s" on a single roll) 
void Player::reset_points()
{
   points = 0;
}

//getter function to return points
int Player::get_points() const
{
   return points;
}

//member function to print out the rolls of the dice
void Player::output_roll() const
{
   cout << right << setw(3) << " "
      << "You rolled " << player_dice.dice_1 << " and "
      << player_dice.dice_2 << left << setw(3) << ".";
      if(player_dice.dice_1 != 1 && player_dice.dice_2 != 1)
      cout << "That's " << (player_dice.dice_1 + player_dice.dice_2) << endl;
      else cout << "That's " << turn_total << endl;
}

bool Player::validate_rolls()
{

   //check if the user had a clean roll without "1"s.
   if (player_dice.dice_1 != 1 && player_dice.dice_2 != 1)
   {
      turn_total += (player_dice.dice_1 +
         player_dice.dice_2);
      output_roll();
      points += (player_dice.dice_1 +
         player_dice.dice_2);
      return false;
   }

   //check to see if the player got two "1" rolls
   else if (player_dice.dice_1 == 1 && player_dice.dice_2 == 1)
   {
      reset_turn_total();
      reset_points();
      cout << right << setw(3) << " " << "You rolled " << player_dice.dice_1 << " and "
         << player_dice.dice_2 << left <<setw(3) << "."
         << "That's a SKUNK!!!" << endl;
      return true;
   }

   //check if the user rolled a "1" and another number
   else if (player_dice.dice_1 == 1 || player_dice.dice_2 == 1)
   {
      //if the player rolls a "1", we will subtract the points
      //they've collected during the turn
      points -= turn_total;
      reset_turn_total();
      //if a "1" roll takes them below 0 if we take away their turn total
      //this "if" statement will set it back to "0".
      if (points < 0)
      {
         reset_points();
      }
      output_roll();
      return true;
   }
   return true;
}

//member function to set number of rolls
void Player::set_roll_personality(int type)
{
   number_of_rolls_pt = type;
}

//check for winner member function
bool Player::validate_point_total()
{
   if (points >= 100)
   {
      return true;
   }
   else
      return false;
}

//get the number of turns
int Player::get_num_of_rolls() const
{
   return number_of_rolls_pt;
}

int Player::get_turn_total() const
{
   return turn_total;
}

//function prototypes;
void game_play(Player players[]);

int main()
{
   //seed at the start of the program for random numbers
   srand(static_cast<int>(time(0)));

   //create array for the three players;
   Player players[NUM_OF_PLAYERS];

   cout << endl;

   //set personalities for the number of players;
   players[PLAYER_1].set_roll_personality(CHICKEN);
   players[PLAYER_2].set_roll_personality(DARING);
   players[PLAYER_3].set_roll_personality(WILD);

   //start the game
   game_play(players);

   return 0;
}

void game_play(Player players[])
{

   //set the player counter to 0 for keeping track of 
   //whose turn it is, starting with PLAYER 1
   int player_counter = 0;

   //this flag will keep track of someone rolling a "1";
   bool rolled_1_flag = false;

   //this loop will continue as long as no one has won the game
   while (!players[player_counter].validate_point_total())
   {
      // print out which player is up
      cout << players[player_counter].get_name() << ", it is your turn" << endl;

      //rolls and validations for each roll

         //reset the turn_total for the player;
      players[player_counter].reset_turn_total();

      //loop through how many turns they would like to take based on personality
      for (int turn = 0; turn < players[player_counter].get_num_of_rolls(); turn++)
      {
         //roll the dice
         players[player_counter].roll_dice();

         //check if the user rolled a "1";
         rolled_1_flag = players[player_counter].validate_rolls();

         //this line checks for a winner after a roll and will fall through to the output
         //of the turn points and total update. 
         if (players[player_counter].validate_point_total())
         {
            break;
         }

         //if the player rolled a "1", it will break from the play loop.
         if (rolled_1_flag == true)
            break;
      }

      //print out the points for the turn;
      cout << setw(2) << " " 
         << "Points for the turn = " << players[player_counter].get_turn_total()
         << setw(3) << "." 
         << "Total points = " << players[player_counter].get_points() << endl;

      //set the turn total back to 0;
      players[player_counter].reset_turn_total();

      //check for a winner    
      if (players[player_counter].validate_point_total())
      {
         cout << endl << endl;
         cout << players[player_counter].get_name() << " won the game with "
            << players[player_counter].get_points() << " points!" << endl;
         break;
      }

      //update the player
      player_counter++;

      cout << endl;

      //check if the counter has gone over the bounds of the amount of players
      //if it has gone over, reset it back to zero;
      if (player_counter == (NUM_OF_PLAYERS))
      {
         player_counter = 0;
      }
   }
}