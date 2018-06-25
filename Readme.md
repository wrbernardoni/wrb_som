# WRB_SOM
A C++ self organizing map library by William Bernardoni

All aspects of this code are free to use for any purpose, commercial or not, and you are free to modify it as you want. Credit would be nice, but I'm not gonna sue anyone over this code.

## How to use
Get either the code archive (*wrb_som.a*) or the source code (*wrb_som.h* and *wrb_som.cpp*) and place it into your codebase where it belongs.  
  
Create a wrb_SOM object like so:  
***wrb_SOM manifold(2,100,3,0.0,1.0);***  
This creates a 2-dimensional manifold in a 3-dimensional space with a resolution of 100 (meaning 100^2 or 10,000 nodes) with each node initialized to have an image between 0.0 and 1.0 in each dimension.  
  
Train it by passing in a vector\<double\*\> of your training data, where each double\* is an array of doubles in your output dimension's dimension; also pass in the number of iterations you want it to train for.  
***manifold.train(data, iterations);***  
  
Afterwards you can get the output of the manifold in a given coordinants by passing in coordinants (on the unit cube i.e. all coords between 0 and 1), and it will output the generated map's image at that point.  
***double\* m_out = manifold.out(coords);***


