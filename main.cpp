#include <iostream>
#include <fstream>
#include <random>
#include <string>

#include "wrb_som.h"

#define XPIX "1000"
#define YPIX "1000"

#define RES 100
#define TI 100000
#define T_SAVE 100
#define SAMPLE 1000 
#define MAX_INTENSITY 255

using namespace std;

int main()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0.0, 1.0);

  wrb_SOM som(2,RES,3, 0.0, 1.0);
  //som.setOutDistanceMetric(cosSim);

  vector<double*> trainingData;

  for(int i = 0; i < SAMPLE; i++)
  {
    double* d = new double[3];
    d[0] = dis(gen);
    d[1] = dis(gen);
    d[2] = dis(gen);
    cout << d[0] << ":" << d[1] << ":" << d[2] << endl;
    trainingData.push_back(d);
  }

  cout << endl << "Training\n";
  for (int i = 0; i < T_SAVE; i++)
  { 
    som.train(trainingData, i * (TI/T_SAVE), TI/T_SAVE, TI);
    cout << "Batch [" << (i+1) << "/" << T_SAVE << "]\n";

    ofstream out;
    out.open("im.ppm");
    out << "P3 " XPIX " " YPIX " " << to_string(MAX_INTENSITY) << endl;
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

        pGreen = d[1] * MAX_INTENSITY;
        pRed = d[0] * MAX_INTENSITY;
        pBlue = d[2] * MAX_INTENSITY;
        out << pRed << " " << pGreen << " " << pBlue << " ";
      }
      out << endl;
    } 
    out.close();
  }
 
}


