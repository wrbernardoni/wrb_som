#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <time.h>

#include "wrb_som.h"

#define XPIX "1000"
#define YPIX "1000"

#define RES 100
#define TI 3000
#define T_SAVE 300
#define SAMPLE 5000 
#define MAX_INTENSITY 255

using namespace std;

int main()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0.0, 1.0);

  wrb_SOM som(2,RES,3, 0.0, 1.0);
  //som.setOutDistanceMetric(cosSim);

  time_t timer;
  time(&timer);

  vector<double*> trainingData;

  for(int i = 0; i < SAMPLE; i++)
  {
    double* d = new double[3];
    d[0] = dis(gen);
    d[1] = 0;//dis(gen);
    d[2] = dis(gen);
    cout << d[0] << ":" << d[1] << ":" << d[2] << endl;
    trainingData.push_back(d);
  }

  ofstream out;
  out.open("out/im000.ppm");
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

  double sumSeconds = 0.0;

  cout << endl << "Training\n";
  for (int i = 0; i < T_SAVE; i++)
  { 
    som.train(trainingData, i * (TI/T_SAVE), TI/T_SAVE, TI);
    time_t currentTime;
    time(&currentTime);
    double seconds = difftime(currentTime, timer);
    sumSeconds += seconds;
    int secondsRem = (int)((T_SAVE - i) * (sumSeconds / (i+1)));
    int minRem = secondsRem / 60;
    secondsRem -= minRem * 60;
    time(&timer);
    cout << "Batch [" << (i+1) << "/" << T_SAVE << "] -- Time Remaining:" << minRem << ":" << secondsRem << "\n";

    ofstream out;
    string s = to_string(i+1);
    if (s.size() < 2)
      s = "00" + s;
    if (s.size() < 3)
      s = "0" + s;
    out.open("out/im" + s + ".ppm");
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


