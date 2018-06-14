#include "wrb_som.h"

void wrb_SOM::init(int map_dim, int resolution[], int out_dim)
{
  m_dim = map_dim;
  o_dim = out_dim;

  res = new int[m_dim];
  for (int i = 0; i < m_dim; i++)
  {
    res[i] = resolution[i];
  }

}

