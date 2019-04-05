//Nabil Arbouz, Visual Studio, Windows 10
//Lab Exercise 11

#include <iostream>
#include <string>

using namespace std;

class Pet
{
protected:
   string type;
   string name;
public:
   Pet(const string& arg1, const string& arg2);
   virtual void whoAmI() const;
   virtual string speak() const = 0;
};

Pet::Pet(const string& arg1, const string& arg2)
   :type(arg1), name(arg2)
{}

void Pet::whoAmI() const
{
   cout << "I am a "
      << type << " and my name is \"" << name << "\"" << endl;
}

class Dog : public Pet
{
public:
   Dog(const string& arg1, const string&arg2);
   void whoAmI() const;    // override the whoAmI() function
   string speak() const { return "Arf!"; }
};

Dog::Dog(const string& arg1, const string& arg2)
   :Pet(arg1,arg2)
{}

void Dog::whoAmI() const
{
   cout << "I am a great dog and you may call me \"" << name << "\"" << endl;
}

class Cat : public Pet
{
public:
   Cat(const string& arg1, const string& arg2);
   string speak() const { return "Meow!"; }
      // Do not override the whoAmI() function
};

Cat::Cat(const string& arg1, const string& arg2)
   : Pet(arg1,arg2)
{}

ostream& operator<<(ostream& out, const Pet& p)
{
   p.whoAmI();
   out << "I say " << p.speak();
   return out;
}

int main()
{
   Dog spot("dog", "Spot");
   Cat socks("cat", "Socks");
   Pet* ptr = &spot;
   cout << *ptr << endl;
   ptr = &socks;
   cout << *ptr << endl;
}