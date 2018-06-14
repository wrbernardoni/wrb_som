#ifndef WRB_SOM
#define WRB_SOM

#include <vector>

struct wrb_SOM_node
{
  double *image; 
};

class wrb_SOM
{
private:
  bool inited;
  int m_dim, o_dim, res;
  wrb_SOM_node *map;

  int mapIndex(int*);
public:
  wrb_SOM();
  wrb_SOM(int map_dim, int resolution, int out_dim);

  void init(int map_dim, int resolution, int out_dim);

  double* out(double*);

  //TODO Training function

  inline wrb_SOM_node* getMap() { return map; };
  inline bool isInited() { return inited; };
};

#endif


