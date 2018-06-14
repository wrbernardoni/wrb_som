#include <iostream>
#include <fstream>

#define XPIX "100"
#define YPIX "100"

using namespace std;

int main()
{
  ofstream out;
  out.open("im.ppm");
  out << "P3 " XPIX " " YPIX " 255" << endl;
  srand(time(0));
  for (int x = 0; x < atoi(XPIX); x++)
  {
    for (int y = 0; y < atoi(YPIX); y++)
    {
      out << rand() % 255 << " " << rand() % 255 << " " << rand() % 255 << " ";
    }
    out << endl;
  } 
  out.close();
}


