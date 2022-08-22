#ifndef LUT_H
#define LUT_H

#include "audiochunks.h"
#include "errorhandling.h"
#include "tscconfig.h"
#include <cmath>
//#include <gsl/gsl_sf.h>
#include <vector>
#include <string>
#include <sstream>
#include<fstream>
#include<iostream>
#include "defs.h"


class lut {
  public:
    lut();
    ~lut();
    void loadgains(std::string gainFile);
    float* get_entry(float az,float inc);
    int getChannels();

  
  private:
    int use3D =-1;
    float spacing = -1;
    float spacing_rad = -1;
    int azentries=0;
    int incentries=0;
    int nKernels = -1;
    int nDirections = -1;

    float*** firstTable; //2D array of pointers to second table arrays
    float** secondTable; //2D array of gains
    
    void setupTables();
    float* findNearestEntry(float az,float inc,float** directions);
    float distance(float az1,float inc1,float az2,float inc2);

};

#endif

/*
 * Local Variables:
 * mode: c++
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * compile-command: "make -C .."
 * End:
 */
