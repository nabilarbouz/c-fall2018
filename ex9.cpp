//Nabil Arbouz, MS Visual Studio, Windows 10
//Lab Exercise 9

#include <iostream>

class Circle
{
   static double Pi;
   float radius;
public:
   Circle(float = 5.0);
   static void changePi(double);
   friend void displayArea(const Circle& object);
};

double Circle::Pi = 3.14;

Circle::Circle(float r)
   :radius(r)
{
}

void Circle::changePi(double p)
{
   Pi = p;
}

void displayArea(const Circle& object)
{
   std::cout << "The area is " 
      << (object.radius * object.radius * object.Pi) 
      << std::endl;
}

int main()
{
   Circle c(10.0);
   displayArea(c);
   Circle::changePi(3.1416);
   displayArea(c);
}

