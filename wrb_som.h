#ifndef WRB_SOM
#define WRB_SOM

#include <vector>

struct wrb_SOM_node
{
  double *image; 
};

double eulerianDist(double *a, double *b, int dim);
double cosSim(double *a, double *b, int dim);
double monDecreasingEuler(double *a, double *b, int dim, int ts, int mTs);


class wrb_SOM
{
private:
  bool inited;
  int m_dim, o_dim, res;
  wrb_SOM_node *map;
  double (*dMetric)(double *a, double *b, int dim);
  double (*nMetric)(double *a, double *b, int dim, int, int);
  double (*distDivisor)(int ts, int maxTs);

  int mapIndex(int*);
  void inverseMapIndex(int, int*);
public:
  wrb_SOM();
  wrb_SOM(int map_dim, int resolution, int out_dim);

  void init(int map_dim, int resolution, int out_dim);

  double* out(double*);
  double train(std::vector<double*> trainingSet, int numIterations);

  inline wrb_SOM_node* getMap() { return map; };
  inline bool isInited() { return inited; };

  inline void setOutDistanceMetric(double (*f)(double*,double*,int)) { dMetric = f; };
  inline void setNeighborhoodDistanceMetric(double (*f)(double*,double*,int, int, int)) { nMetric = f; };

};

#endif


