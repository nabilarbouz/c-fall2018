//Nabil Arbouz, MS Visual Studio, Windows 10
// Lab Exercise Extra Credit

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

class Node
{
   string item;
   int count;
   Node* next;
public:
   Node(string item = "", int cnt = 0, Node* nxt = 0);
   string get_item() const;
   int get_count() const;
   Node* get_next() const;
   void set_next(Node* ptr);
   Node& operator++();            // increment the count in a Node
   Node& operator--();            // decrement the count in a Node
   bool operator<(string value) const;
};

ostream& operator<<(ostream& out, const Node& n)
{
   out << left << setw(12) << n.get_item();
   out << right << setw(4) << n.get_count();
   return out;
}

class List
{
   Node* top;
public:
   List();
   List(const List&);
   ~List();
   Node* get_top() const;
   Node* find(string value) const;
   Node* findNodeBefore(string value) const;
   List& operator+=(string);            // add to the linked list
   List& operator-=(const string&);     // subtract from the linked list
};

ostream& operator<<(ostream& out, const List& l)
{
   Node* temp = l.get_top();
   out << endl << "Item       Quantity" << endl;
   out << left;
   while (temp != 0)
   {
      out << *temp << endl;
      temp = temp->get_next();
   }
   return out;
}

void processTransactions(const string& filename, List& list);

int main()
{
   List list;
   processTransactions("c:/text_files/ass9data.txt", list);
   List temp = list;
   cout << temp << endl;
}


void Node::set_next(Node* ptr)
{
   next = ptr;
}

Node& Node::operator++()
{
   count++;
   return *this;
}

Node& Node::operator--()
{
   count--;
   return *this;
}

bool Node::operator<(string value) const
{
   return item < value;
}

Node::Node(string arg1, int ct, Node* nxt)
   : item(arg1), count(ct), next(nxt)
{
}

string Node::get_item() const
{
   return item;
}

int Node::get_count() const
{
   return count;
}

Node* Node::get_next() const
{
   return next;
}

List::List() :top(0)
{ }

List::~List()
{
   Node* temp = top;
   while (temp != 0)
   {
      top = top->get_next();
      delete temp;
      temp = top;
   }
}

Node* List::get_top() const
{
   return top;
}

Node* List::find(string target) const
{
   Node* temp = top;
   while (temp != 0)
   {
      if (temp->get_item() == target) return temp;
      temp = temp->get_next();
   }
   return 0;
}

// Return pointer to Node before the Node that contains target
Node* List::findNodeBefore(string target) const
{
   if (top->get_item() == target) return 0;
   Node* temp = top;
   while (temp->get_next() != 0)
   {
      if (temp->get_next()->get_item() == target) return temp;
      temp = temp->get_next();
   }
   return 0;
}

List& List::operator+=(string value)
{
   // Case 1: insert into an empty list
   if (!top)
   {
      top = new Node(value, 1, 0);
      return *this;
   }

   // Case 2: Node already exists (increment count)
   Node* temp = find(value);
   if (temp)
   {
      ++*temp;      // increment the count in the Node
      return *this;
   }

   // Case 3: Insert new node at the beginning of the list?
   if (value < top->get_item())
   {
      temp = new Node(value, 1, top);
      top = temp;
      return *this;
   }

   // Case 4: Insert new node after some node already in the list
   temp = top;

   // The temp pointer examines the "next" node value
   while (temp->get_next() && (*temp->get_next()) < value)
   {
      temp = temp->get_next();
   }
   // temp now points to the "target" node after which the new one will be inserted

   // Create the new node
   Node* newNode = new Node(value, 1, temp->get_next());

   // Set the next pointer of the target node to point to the new node
   temp->set_next(newNode);

   // return the linked list
   return *this;
}


List& List::operator-=(const string& value)
{
   Node* temp = find(value);
   if (temp)
   {
      if (temp->get_count() > 1)
      {
         --*temp;       // decrement the count in the Node
      }
      else
      {
         if (temp == top)
         {
            top = top->get_next();
            delete temp;
            temp = 0;
            return *this;;
         }

         Node* ptr2Prev = findNodeBefore(value);
         if (ptr2Prev)
         {
            ptr2Prev->set_next(temp->get_next());
            delete temp;
            temp = 0;
         }
      }
   }
   else
   {
      cerr << "Unable to remove " << value << endl;
   }
   return *this;
}


void processTransactions(const string& filename, List& list)
{
   ifstream fin(filename);
   if (!fin)
   {
      cerr << "Unable to open file " << filename << endl;
      exit(1);
   }
   string buffer, transactionType, dummy, numberString;
   string item;
   int lineNumber = 0;
   size_t spacePos;  // location of blank space in input line
   while (!fin.eof())
   {
      lineNumber++;
      getline(fin, buffer);

      if (fin.eof()) break;               // EOF check

      // A gnu compiler may store \r in the last byte.  If so, discard
      if (buffer.size() and buffer[buffer.size() - 1] == '\r')
         buffer.resize(buffer.size() - 1);

      if (buffer.size() < 1) continue;

      // get the first word of the line
      spacePos = buffer.find(' ');
      transactionType = buffer.substr(0, spacePos);

      if (transactionType == "add")
      {
         item = buffer.substr(spacePos + 1);
         list += item;
      }
      else if (transactionType == "subtract")
      {
         item = buffer.substr(spacePos + 1);
         if (!list.find(item)) {
            cout << "Unable to " << buffer << " in line #" << lineNumber << endl;
         }
         else list -= item;
      }
      else if (buffer == "print inventory")
      {
         cout << list << endl;
      }
      else
      {
         cout << "Bad transaction: " << transactionType << " in line #" << lineNumber << endl;
      }
   }
   fin.close();
}

List::List(const List& original_ptr)
{
   Node* temp = nullptr;
   Node* temp_ptr = nullptr;
   Node* node_cpy_ptr = original_ptr.get_top();
   Node* previous_node_cpy_ptr = nullptr;

   //case 1: nothing in the list
   if (original_ptr.get_top() == nullptr)
   {
      cout << "The list is empty, copy constructor does nothing";
   }
   //case 2: only 1 item in the list
   else if (node_cpy_ptr->get_next() == nullptr)
   {
      top = new Node(node_cpy_ptr->get_item(), node_cpy_ptr->get_count(), 0);
   }
   else
   {
      //take the copy pointers to the end of the original list
      while (node_cpy_ptr->get_next() != nullptr)
      {
         previous_node_cpy_ptr = node_cpy_ptr;
         node_cpy_ptr = node_cpy_ptr->get_next();
      }

      do
      {
         if (node_cpy_ptr == original_ptr.get_top()) previous_node_cpy_ptr = nullptr;
         temp = new Node(node_cpy_ptr->get_item(), node_cpy_ptr->get_count(), temp_ptr);
         temp_ptr = temp;
         top = temp;
         if (previous_node_cpy_ptr != nullptr)
         {
            node_cpy_ptr = previous_node_cpy_ptr;
            //these lines will get the previous pointer of the new node_cpy_ptr address
            previous_node_cpy_ptr = original_ptr.get_top();

            while (previous_node_cpy_ptr->get_next() != node_cpy_ptr)
            {
               previous_node_cpy_ptr = previous_node_cpy_ptr->get_next();
            }
         }
         //this if block handle the scenario when there are only 2 items left in the list
         if (previous_node_cpy_ptr == original_ptr.get_top())
         {
            node_cpy_ptr = original_ptr.get_top()->get_next();
            temp = new Node(node_cpy_ptr->get_item(), node_cpy_ptr->get_count(), temp_ptr);
            temp_ptr = temp;
            top = temp;
            node_cpy_ptr = original_ptr.get_top();
         }
      } while (previous_node_cpy_ptr != nullptr);
   }
}