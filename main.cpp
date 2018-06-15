#include <iostream>
#include <fstream>
#include <random>
#include <string>

#include "wrb_som.h"

#define XPIX "1000"
#define YPIX "1000"

#define RES 50
#define TI 10000
#define SAMPLE 50 

using namespace std;

int main()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0.0, 1.0);

  wrb_SOM som(2,RES,3);
  //som.setOutDistanceMetric(cosSim);

  vector<double*> trainingData;

  for(int i = 0; i < SAMPLE; i++)
  {
    double* d = new double[3];
    double l = dis(gen);
    d[0] = l;
    d[1] = l;
    d[2] = l;
    cout << d[0] << ":" << d[1] << ":" << d[2] << endl;
    trainingData.push_back(d);
  }

  cout << endl << "Training\n";
  som.train(trainingData, TI);
  cout << " -- Complete\nWriting Picture.\n";

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
      double* coord = new double[2];
      coord[0] = (double) x / (double) atoi(XPIX);
      coord[1] = (double) y / (double) atoi(YPIX);
      double* d = som.out(coord);
      delete coord;

      pGreen = d[1] * 1024;
      pRed = d[0] * 1024;
      pBlue = d[2] * 1024;
      out << pRed << " " << pGreen << " " << pBlue << " ";
    }
    out << endl;
  } 
  out.close();
}


