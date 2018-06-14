#include <iostream>
#include <fstream>

#include "wrb_som.h"

#define XPIX "1000"
#define YPIX "1000"

using namespace std;

int main()
{
  wrb_SOM som(2,1000,5);
  int c;
  cin >> c;

  cout << "Starting -\n";
  for(int i = 0; i < 1000000; i++)
  { 
    double coord[] = {0.75, 1.0};
    double* addr = som.out(coord);
    cout << "["  << i << "]";
    for (int i = 0; i < 5; i++)
    {
      cout << " " << addr[i];
    }
    cout << endl;
  }

  /*
  ofstream out;
  out.open("im.ppm");
  out << "P3 " XPIX " " YPIX " 1024" << endl;
  srand(time(0));
  int pGreen, pRed, pBlue;
  pGreen = pRed = pBlue = 0;
  
  for (int x = 0; x < atoi(XPIX); x++)
  {
    for (int y = 0; y < atoi(YPIX); y++)
    {
      int r = rand() % 6;
      int dG = (r == 0 ? 1 : 0);
      int dR = (r == 1 ? 1 : 0);
      int dB = (r == 2 ? 1 : 0);
      pGreen = (pGreen + dG) % 1024;
      pRed = (pRed + dR) % 1024;
      pBlue = (pBlue + dB) % 1024;
      out << pRed << " " << pGreen << " " << pBlue << " ";
    }
    out << endl;
  } 
  out.close();
  */
}


