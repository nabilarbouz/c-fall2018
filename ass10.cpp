//Nabil Arbouz, MS Visual Studio, Windows 10
//Assignment 10

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>

const double PI = 3.14159265359;
const std::string INPUT_FILE = "c:/text_files/ass10input.txt";

class GeometricSolid
{
public:
   virtual std::string name() const = 0;
   virtual double volume() const = 0;
   virtual double surface_area()  const = 0;
};

class Circular : public GeometricSolid
{
protected:
   double radius;
   double height;
public:
   Circular(double r = 0, double h = 0);
};

Circular::Circular(double r, double h)
   : radius(r), height(h)
{}

class Rectangular : public GeometricSolid
{
protected:
   double length;
   double width;
   double height;
public:
   Rectangular(double l = 0, double w = 0, double h = 0);
};

Rectangular::Rectangular(double l, double w, double h)
   :length(l), width(w), height(h)
{}

class Cylinder : public Circular
{
public:
   Cylinder(double r, double h);
   static const std::string solid_name;
   std::string name() const { return solid_name; }

   double volume() const { return (PI * pow(radius, 2) * height); }
   double surface_area() const { return (2. * PI * radius * (radius + height)); }
};

const std::string Cylinder::solid_name = "cylinder";

Cylinder::Cylinder(double r, double h)
   :Circular(r,h)
{}

class Sphere : public Circular
{
public:
   Sphere(double r);
   static const std::string solid_name;
   std::string name() const { return solid_name; }

   double volume() const { return ((4. / 3) * PI * pow(radius, 3)); }
   double surface_area() const { return (4 * PI * pow(radius, 2)); }
};

const std::string Sphere::solid_name = "sphere";

Sphere::Sphere(double r)
   : Circular(r)
{}

class RectangularPrism : public Rectangular
{
public:
   RectangularPrism(double l, double w, double h);
   RectangularPrism(double l);
   static const std::string solid_name;
   std::string name() const { return solid_name; }

   double volume() const { return (length * width * height); }
   double surface_area() const { return (2. * ((length * width) + 
      (length * height) + (width * height))); }
};

const std::string RectangularPrism::solid_name = "rectangular prism";

RectangularPrism::RectangularPrism(double l, double w, double h)
   :Rectangular(l,w,h)
{}
RectangularPrism::RectangularPrism(double l)
   : Rectangular(l)
{}


class Cube : public RectangularPrism
{
public:
   Cube(double l);
   static const std::string solid_name;
   std::string name() const { return solid_name; }

   double volume() const { return (length * length * length); }
   double surface_area() const { return (6 * pow(length, 2)); }
};

const std::string Cube::solid_name = "cube";

Cube::Cube(double l)
   : RectangularPrism(l)
{}

std::ostream& operator<<(std::ostream& out, GeometricSolid* solid)
{
   std::cout << std::left << std::setw(20) << solid->name()
      << std::setw(15) << solid->surface_area() << std::setw(12) << solid->volume()
      << std::endl;
   return out;
}

int main()
{
   std::ifstream in_file;
   in_file.open(INPUT_FILE);
   if (!in_file)
   {
      std::cerr << "The file " << INPUT_FILE << " did not open!" << std::endl;
      exit(1);
   }

   GeometricSolid* geo_ptr = nullptr;
   std::string buffer;
   double length, width, height, radius;
   std::size_t space_pos;

   std::cout << std::setprecision(4) << std::fixed;

   while (!in_file.eof())
   {
      getline(in_file, buffer);
      if (in_file.eof()) break;

      if (buffer.find("cy") != std::string::npos)
      {
         buffer = buffer.substr(3);
         radius = std::stod(buffer.substr(0, buffer.rfind(' ')));
         height = std::stod(buffer.substr(buffer.rfind(' ')));
         geo_ptr = new Cylinder(radius, height);
         std::cout << geo_ptr;
         delete geo_ptr;
         geo_ptr = nullptr;
      }
      if (buffer.find("sp") != std::string::npos)
      {
         buffer = buffer.substr(3);
         radius = std::stod(buffer.substr(0));
         geo_ptr = new Sphere(radius);
         std::cout << geo_ptr;
         delete geo_ptr;
         geo_ptr = nullptr;
      }
      if (buffer.find("cu") != std::string::npos)
      {
         buffer = buffer.substr(3);
         length = std::stod(buffer);
         geo_ptr = new Cube(length);
         std::cout << geo_ptr;
         delete geo_ptr;
         geo_ptr = nullptr;
      }
      if (buffer.find("re") != std::string::npos)
      {
         buffer = buffer.substr(3);
         height = stod(buffer.substr(buffer.rfind(' ')));
         buffer = buffer.substr(0, buffer.rfind(' '));
         buffer = buffer.substr(0, buffer.find_last_not_of(' ') + 1);
         width = stod(buffer.substr(buffer.rfind(' ')));
         length = stod(buffer.substr(0, buffer.rfind(' ')));
         geo_ptr = new RectangularPrism(length, width, height);
         std::cout << geo_ptr;
         delete geo_ptr;
         geo_ptr = nullptr;
      }
      buffer.clear();
   }
   in_file.close();
   return 0;
}