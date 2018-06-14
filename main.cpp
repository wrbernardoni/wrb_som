#include <iostream>
#include <fstream>

#define XPIX "100"
#define YPIX "100"

using namespace std;

int main()
{
  ofstream out;
  out.open("im.ppm");
  out << "P3 " << XPIX << " " <<  YPIX << " 255" << endl;
  for (int x = 0; x < atoi(XPIX); x++)
  {
    for (int y = 0; y < atoi(YPIX); y++)
    {
      out << " 100 50 255 ";
    }
    out << endl;
  } 
  out.close();
}


