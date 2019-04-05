//Nabil Arbouz, MS Visual Studio, Windows 10
//Assignment 9(single file version)

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>

//Node Declaration
class Node
{
   int item_number;
   int item_quantity;
   Node* next;
public:
   Node(int d, int q, Node* n);
   int get_item_number() const;
   int get_item_quantity() const;
   Node* get_next() const;
   void set_next(Node* ptr);
   void operator++();
   void operator--();
};

std::ostream& operator<<(std::ostream&, const Node&);

//List Declaration
class List {
   Node* top;
public:
   List();
   ~List();
   void operator+ (int number);
   void operator-(int number); 
   Node* get_top() const;
   Node* find(int number) const;
};

std::ostream& operator<< (std::ostream& out, const List& object);

//Node Function Definitions
Node::Node(int d, int q, Node* n)
   :item_number(d), item_quantity(q), next(n)
{}

int Node::get_item_number() const
{
   return item_number;
}

int Node::get_item_quantity() const
{
   return item_quantity;
}

Node* Node::get_next() const
{
   return next;
}

void Node::set_next(Node* ptr)
{
   next = ptr;
}


void Node::operator++()
{
   item_quantity++;
}

void Node::operator--()
{
   item_quantity--;
}

std::ostream& operator<<(std::ostream& out, const Node& obj)
{
   out << std::right << std::setw(4) << std::setfill('0') << obj.get_item_number()
      << std::setw(8) << std::setfill(' ') << obj.get_item_quantity() << std::endl;
   return out;
}

//List Function Definitions
List::List()
   :top(nullptr)
{}

List::~List()
{
   Node* node_ptr = top;

   while (node_ptr != nullptr)
   {
      top = top->get_next();
      delete node_ptr;
      node_ptr = nullptr;
      node_ptr = top;
   }
}

Node* List::get_top() const
{
   return top;
}

Node* List::find(int number) const
{
   if (!top) return nullptr;
   Node* node_ptr = top;

   while (node_ptr != nullptr)
   {
      if (node_ptr->get_item_number() == number)
      {
         return node_ptr;
      }
      node_ptr = node_ptr->get_next();
   }
   return nullptr;
}

void List::operator+ (int number)
{
   Node* new_node;
   Node* node_ptr;
   Node* previous_ptr = nullptr;

   if (find(number) == nullptr)
   {
      new_node = new Node(number, 1, nullptr);

      if (!top)
      {
         top = new_node;
         new_node->set_next(nullptr);
      }
      else
      {
         node_ptr = top;
         previous_ptr = nullptr;

         while (node_ptr != nullptr && node_ptr->get_item_number() < number)
         {
            previous_ptr = node_ptr;
            node_ptr = node_ptr->get_next();
         }

         if (previous_ptr == nullptr)
         {
            top = new_node;
            new_node->set_next(node_ptr);
         }

         else
         {
            previous_ptr->set_next(new_node);
            new_node->set_next(node_ptr);
         }
      }
   }
   else
   {
      node_ptr = find(number);
      ++(*node_ptr);
   }
}


void List::operator-(int number)
{
   Node* node_ptr;
   Node* forward_node;

   if (find(number) == nullptr)
   {
      std::cerr << std::setfill('0') << std::setw(4) << number
         << " is not in the list!" << std::endl;
      return;
   }

   node_ptr = top;

   if (top->get_item_number() == number)
   {
      --(*top);
      if (top->get_item_quantity() == 0)
      {
         top = top->get_next();
         delete node_ptr;
         node_ptr = nullptr;
      }
      return;
   }

   while (node_ptr->get_next()->get_item_number() != number)
   {
      node_ptr = node_ptr->get_next();
   }

   --*(node_ptr->get_next());

   if (node_ptr->get_next()->get_item_quantity() == 0)
   {
      forward_node = node_ptr->get_next();
      node_ptr->set_next(forward_node->get_next());
      delete forward_node;
   }
}

std::ostream& operator<<(std::ostream& out, const List& object)
{
   std::cout << std::endl << std::left << std::setw(6) << "Item"
      << std::setw(10) << "Quantity" << std::endl;

   Node* node_ptr = object.get_top();

   while (node_ptr != nullptr)
   {
      out << *(node_ptr);
      node_ptr = node_ptr->get_next();
   }
   std::cout << std::endl;
   return out;
}

const std::string TRANSACTION_FILE_NAME = "c:/text_files/ass9data.txt";

int main()
{
   std::ifstream in_file;

   in_file.open(TRANSACTION_FILE_NAME);
   if (!in_file)
   {
      std::cerr << "The file" << TRANSACTION_FILE_NAME << " did not open!";
      exit(1);
   }

   List Transactions;

   std::string buffer;
   std::string command;
   std::string item_number;
   std::size_t space_pos;
   int line_counter = 0;

   while (!in_file.eof())
   {
      getline(in_file, buffer);
      line_counter++;
      if (in_file.eof()) break;

      if (buffer.empty())
      {
         continue;
      }

      space_pos = buffer.find(' ');
      command = buffer.substr(0, space_pos);
      item_number = buffer.substr(space_pos);

      if (command.find("add") != std::string::npos)
      {
         Transactions + (stoi(item_number));
      }
      else if (command.find("subtract") != std::string::npos)
      {
         Transactions - (stoi(item_number));
      }
      else if (command.find("print") != std::string::npos)
      {
         std::cout << Transactions;
      }
      else
      {
         std::cerr << "Bad Transaction: " << command << " in line #"
            << line_counter << std::endl;
      }
   }

   in_file.close();

   return 0;
}