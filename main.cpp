#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  ofstream out;
  out.open("im.ppm");
  out << "P3 3 3 255" << endl;
  out << "255 255 255 255 255 255 255 255 255" << endl;
  out << "255 255 255 255 255 255 255 255 255" << endl;
  out << "255 255 255 255 255 255 255 255 255" << endl;
  out.close();
}


