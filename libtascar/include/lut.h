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
    void loadgains(std::string gainFile,float az_s,float el_s,int u3D);
    float* get_entry(float az,float el);
    int getChannels();

  
  private:
    int use3D =-1;
    float az_spacing = -1;
    float el_spacing = -1;
    float az_spacing_rad = -1;
    float el_spacing_rad = -1;
    int azentries=0;
    int elentries=0;
    int nKernels = -1;
    int nDirections = -1;

    float*** firstTable; //2D array of pointers to second table arrays
    float** secondTable; //2D array of gains
    
    void setupTables();
    float* findNearestEntry(float az,float el,float** directions);
    float distance(float az1,float el1,float az2,float el2);

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
