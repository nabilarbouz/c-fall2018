//Nabil Arbouz, MS Visual Studio, Windows 10
//Lab Exercise 8

#include <iostream>
#include <string>

using namespace std;

class Square {
private:
   int side;
   string color;
   
public:
   Square(int = 4, string = "green");
   void display() const;
};

int main()
{
   Square object1;
   Square object2(6, "blue");
   Square object3(10, "yellow");

   object1.display();
   object2.display();
   object3.display();
}

Square::Square(int x, string shade)
   :side(x), color(shade)
{
} 

void Square::display() const
{
   cout << "I am a " << color
      << " Square with an area of " << (side * side) << endl;
}
