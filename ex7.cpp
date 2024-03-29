//Nabil Arbouz, MS Visual Studio, Windows 10
//Lab 7
// This program demonstrates a simple class.
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Rectangle class declaration.
class Rectangle
{
private:
   double width;
   double length;
   string color;
public:
   void setWidth(double);
   void setLength(double);
   void setColor(string);
   double getWidth() const;
   double getLength() const;
   double getArea() const;
   string getColor() const;
};

//**************************************************
// setWidth assigns a value to the width member.   *
//**************************************************

void Rectangle::setWidth(double w)
{
   width = w;
}

//**************************************************
// setLength assigns a value to the length member. *
//**************************************************

void Rectangle::setLength(double len)
{
   length = len;
}

//**************************************************
// setColor assigns a color to the color member. *
//**************************************************

void Rectangle::setColor(string shade)
{
   color = shade;
}

//**************************************************
// getWidth returns the value in the width member. *
//**************************************************

double Rectangle::getWidth() const
{
   return width;
}

//****************************************************
// getLength returns the value in the length member. *
//****************************************************

double Rectangle::getLength() const
{
   return length;
}

//*****************************************************
// getArea returns the product of width times length. *
//*****************************************************

double Rectangle::getArea() const
{
   return width * length;
}

//*****************************************************
// getColor returns the color of the rectangle member *
//*****************************************************

string Rectangle::getColor() const
{
   return color;
}

//*****************************************************
// Function main                                      *
//*****************************************************

int main()
{
   Rectangle box; // Define an instance of the Rectangle class
   double rectWidth; // Local variable for width
   double rectLength; // Local variable for length
   string rectColor; // Local variable for color

   // Get the rectangle's width and length from the user.
   cout << "This program will calculate the area of a\n";
   cout << "rectangle. What is the width? ";
   cin >> rectWidth;
   cout << "What is the length? ";
   cin >> rectLength;
   cout << "What is the color? ";
   cin >> rectColor;

   // Store the width and length and color of the rectangle
   // in the box object.
   box.setWidth(rectWidth);
   box.setLength(rectLength);
   box.setColor(rectColor);

   // Display the rectangle's data.
   cout << "Here is the rectangle's data:\n";
   cout << "Width: " << box.getWidth() << endl;
   cout << "Length: " << box.getLength() << endl;
   cout << "Area: " << box.getArea() << endl;
   cout << "Color: " << box.getColor() << endl;
   return 0;
}