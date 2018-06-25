#ifndef WRB_SOM
#define WRB_SOM

#include <vector>

struct wrb_SOM_node
{
  double *image; 
};

// Different preprogrammed distance metrics
double eulerianDist(double *a, double *b, int dim);
double cosSim(double *a, double *b, int dim);

// Preprogrammed eighbor weighing function
double monDecreasingEuler(double *a, double *b, int dim, int ts, int mTs);


class wrb_SOM
{
private:
  // True if map has been created, false if map is null ptr
  bool inited;

  // m_dim - dimension of the map space
  // o_dim - dimension of the output space
  // res - resolution of the map - # of samples along each dimension
  //   res^m_dim will be the number of nodes total in the map.
  int m_dim, o_dim, res;

  // Actual pointer to the map.
  wrb_SOM_node *map;

  // Function pointers to the different metrics used.
  double (*dMetric)(double *a, double *b, int dim);
  double (*nMetric)(double *a, double *b, int dim, int, int);

  // Functions to convert between n-tuple coords and a single integer coords
  int mapIndex(int*);
  void inverseMapIndex(int, int*);
public:
  // Various constructors
  // Default constructor, does not initialize map at all
  wrb_SOM();

  /* 
    Constructor that also initializes map.
    map_dim - dimensionality of map space
    resolution - resolution of map (# of samples on each dimension)
    out_dim - dimensionality of output space
    min - minimum value in a dimension for random image of map
    max - maximum value in a dimension for random image of map
  */
  wrb_SOM(int map_dim, int resolution, int out_dim, double min = 0.0, double max = 1.0);

  // Initializes map. See above for parameter descriptions.
  void init(int map_dim, int resolution, int out_dim, double min = 0.0, double max = 1.0);

  // Takes in coords on [0,1] in o_dim dimensions and outputs the image of the
  // nearest node to those coords.
  double* out(double*);

  /* 
    Training functions for the network. Takes in a vector of double arrays
    (in the dimensionality of the output space), and the number of iterations
    to run for.
  */
  // Runs for goIt iterations, starting at startIt for the count, maxing out at
  // maxIt
  double train(std::vector<double*> trainingSet, int startIt, int goIt, int maxIt);
  // Runs from startIt iterations until the max
  double train(std::vector<double*> trainingSet, int startIt, int maxIt);
  // Runs numIterations
  double train(std::vector<double*> trainingSet, int numIterations);

  // Returns the full map
  inline wrb_SOM_node* getMap() { return map; };
  // Return true if the map is initialized, false otherwise
  inline bool isInited() { return inited; };

  // Sets the distance metric. Assumes that this functions as a true metric.
  inline void setOutDistanceMetric(double (*f)(double*,double*,int)) { dMetric = f; };

  /*
    Sets the neighborhood weight metric.
    First param is coords of the Best Matching Unit
    Second is coords of node to evaluate
    Third is number of dimensions
    Fourth is current timestep
    Fifth is maximum timestep
    Function should be monotonically decreasing as current timestep approaches
      maximum, and should be on a range of [0,1], outputting 1 if the node 
      is the BMU (or very close) and the current timestep is sufficiently small
    Function should also be monotonically decreasing as distance from BMU to
      current node increases.
  */
  inline void setNeighborhoodDistanceMetric(double (*f)(double*,double*,int, int, int)) { nMetric = f; };

};

#endif


