#include "wrb_som.h"
#include <random>

wrb_SOM::wrb_SOM()
{
  inited = false;
  m_dim = o_dim = res = 0;
  map = nullptr;
}

wrb_SOM::wrb_SOM(int map_dim, int resolution, int out_dim)
{
  inited = false;
  m_dim = o_dim = res = 0;
  map = nullptr;
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
