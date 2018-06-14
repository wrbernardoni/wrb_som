#ifndef WRB_SOM
#define WRB_SOM

#include <vector>

struct wrb_SOM_node
{
  double map[]; 
};

class wrb_SOM
{
private:
  int m_dim, o_dim, *res;
public:
  void init(int map_dim, int resolution[], int out_dim);
};

#endif


