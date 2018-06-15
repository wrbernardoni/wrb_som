#include "wrb_som.h"
#include <random>

double eulerianDist(double *a, double *b, int dim)
{
  double squaredSum = 0.0;
  for (int i = 0; i < dim; i++)
  {
    squaredSum += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return std::sqrt(squaredSum);
}

double cosSim(double *a, double *b, int dim)
{
  double a_2, b_2, ab;
  a_2 = b_2 = ab = 0;
  for (int i = 0; i < dim; i++)
  {
    ab += a[i] * b[i];
    a_2 += a[i] * a[i];
    b_2 += b[i] * b[i];
  }

  return ab / (std::sqrt(a_2) * std::sqrt(b_2));
}

double monDecreasingEuler(double *a, double *b, int dim, int ts, int maxTs)
{
  double euler = eulerianDist(a, b, dim);
  double tsProg = 1.0 - ((double)ts / (double) maxTs);
  return tsProg * tsProg * std::exp(-euler);
}


wrb_SOM::wrb_SOM()
{
  inited = false;
  m_dim = o_dim = res = 0;
  map = nullptr;
  dMetric = &eulerianDist;
  nMetric = &monDecreasingEuler;
}

wrb_SOM::wrb_SOM(int map_dim, int resolution, int out_dim)
{
  inited = false;
  m_dim = o_dim = res = 0;
  map = nullptr;
  dMetric = &eulerianDist;
  nMetric = &monDecreasingEuler;
  init(map_dim, resolution, out_dim);
}

void wrb_SOM::init(int map_dim, int resolution, int out_dim)
{
  if (inited)
  {
    for (int i = 0; i < std::pow(res, m_dim); i++)
    {
      delete map[i].image;
    }
    delete map;
    inited = false;
  }

  m_dim = map_dim;
  o_dim = out_dim;

  res = resolution;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  int numNodes = std::pow(res, m_dim);
  map = new wrb_SOM_node[numNodes];
  for (int i = 0; i < numNodes; i++)
  {
    wrb_SOM_node* cNode = &map[i];
    cNode->image = new double[o_dim];
    for (int j = 0; j < o_dim; j++)
    {
      cNode->image[j] = dis(gen);
    }
  }

  inited = true;
}

int wrb_SOM::mapIndex(int* nI)
{
  int index = 0;
  for(int i = 0; i < m_dim; i++)
  {
    index += std::pow(res, i) * nI[i];
  }

  return index;
}

void wrb_SOM::inverseMapIndex(int nI, int *out)
{
  for (int i = m_dim - 1; i >= 0; i--)
  {
    out[i] = nI / std::pow(res, i);
    nI -= out[i] * std::pow(res, i);
  }
}

double* wrb_SOM::out(double* coord)
{
  if (!inited)
    return nullptr;

  int* nearestIndex = new int[m_dim];
  for (int i = 0; i < m_dim; i++)
  {
    nearestIndex[i] = (coord[i] * (res - 1) + 0.5);
  }

  int nI = mapIndex(nearestIndex);
  delete nearestIndex;
  return map[nI].image;
}

double wrb_SOM::train(std::vector<double*> trainingSet, int numIterations)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, trainingSet.size());
  int numNodes = std::pow(res, m_dim);
  int* bmuIndex = new int[m_dim];
  int* tmI = new int[m_dim];
  double* bmuDIndex = new double[m_dim];
  double* tempIndex = new double[m_dim];

  for (int t = 0; t < numIterations; t++)
  {
    // Choose random training vector
    double* training = trainingSet[dis(gen)];

    // Find BMU
    double minDist = -1.0; 
    for (int i = 0; i < m_dim; i++)
      bmuIndex[i] = 0;

    for (int i = 0; i < numNodes; i++)
    {
      double dist = dMetric(map[i].image, training, o_dim);
      if (dist < minDist || minDist < 0)
      {
        minDist = dist;
        inverseMapIndex(i, bmuIndex);
      }
    }

    for (int i = 0; i < m_dim; i++)
    {
      bmuDIndex[i] = (double)bmuIndex[i];
    }

    // Modify neighborhood of BMU
    for (int i = 0; i < numNodes; i++)
    {
      inverseMapIndex(i, tmI);
      for (int j = 0; j < m_dim; j++)
        tempIndex[j] = (double)tmI[j];

      double aa = nMetric(bmuDIndex, tempIndex, m_dim, t, numIterations);
      for (int j = 0; j < o_dim; j++)
      {
        map[i].image[j] = map[i].image[j] * (1.0 - aa) + training[j] * (aa);
      }
    }
  }
  delete bmuIndex;
  delete bmuDIndex;
  delete tempIndex;
  delete tmI;

  // Evaluate error of network
  return 0.0;
}
