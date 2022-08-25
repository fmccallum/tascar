/*
 * This file is part of the TASCAR software, see <http://tascar.org/>
 *
 * Copyright (c) 2019 Giso Grimm
 * Copyright (c) 2020 Giso Grimm
 * Copyright (c) 2021 Giso Grimm
 */
/*
 * TASCAR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, version 3 of the License.
 *
 * TASCAR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHATABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License, version 3 for more details.
 *
 * You should have received a copy of the GNU General Public License,
 * Version 3 along with TASCAR. If not, see <http://www.gnu.org/licenses/>.
 */

#include "lut.h"

lut::lut()
{

}



void lut::setupTables()
{
  if(!use3D) {
    elentries = 1;
    firstTable = new float**[1];
    firstTable[0] = new float* [azentries] {};
  } else {
    firstTable = new float**[elentries];
    for(int i =0; i< elentries;i++){
      firstTable[i] = new float* [azentries] {};
    }
  }
  secondTable = new float*[nDirections];
  for(int i = 0; i < nDirections; i++) {
    secondTable[i] = new float[nKernels]{};
  }

}

float lut::distance(float az1, float el1, float az2, float el2)
{
  return 1 - (sin(el1) * sin(el2) * cos(az1 - az2) + cos(el1) * cos(el2));
}

float* lut::findNearestEntry(float az, float el, float** directions)
{

  int bestIndex = 0;
  float bestDist = distance(az, el, directions[0][0], directions[0][1]);
  for(int i = 1; i < nDirections; i++) {
    float dist = distance(az, el, directions[i][0], directions[i][1]);
    if(dist < bestDist) {
      bestDist = dist;
      bestIndex = i;
    }
  }

  return secondTable[bestIndex];
}



void lut::loadgains(std::string gainFile,float az_s,float el_s,int u3D)
{
  use3D = u3D;
  az_spacing = az_s;
  az_spacing_rad = DEG2RADf* az_spacing;
  azentries = (int)360 / az_spacing;

  if (use3D == 0){
    el_spacing = 360;
    elentries =1;
  }
  else{
    el_spacing = el_s;
    elentries =(int)180/el_spacing;
  }
  el_spacing_rad = DEG2RADf*el_spacing;


  


  std::ifstream source;
  source.open(gainFile, std::ios_base::in);
  if(!source) {
    throw TASCAR::ErrMsg("No file found");
  }
  std::string line;

  // Assumes that metadata is in first 4 lines of file
  for(int i = 0; i < 2; i++) {
    std::getline(source, line);
    std::istringstream in(line);
    std::string name;
    in >> name;
    if(name == "nKernels") {
      in >> nKernels;
    } else if(name == "nDirections") {
      in >> nDirections;
    }
  }
  //check that all settings are valid
  if(use3D == -1 || az_spacing <= 0 || nKernels <= 0 || nDirections <= 0) {
    throw TASCAR::ErrMsg("Please fix header in gains file");
  }

  // create LUTs
  setupTables();

  // create table to store directions from file
  float** directions = new float*[nDirections];
  //tdirections = directions;
  for(int i = 0; i < nDirections; i++) {
    directions[i] = new float[2]{};
  }
  int nDir = 0;
  // go through each line in file, if line starts with float: fill in table with new entry
  for(; std::getline(source, line);) {
    std::istringstream in(line);
    std::string check;
    in >> check;
    bool isFloat = true;
    try {
      float az = std::stof(check);
      (void) az; //otherwise get a set but not used warning for az
    }
    catch(std::exception& ia) {
      isFloat = false;
    }
    if(isFloat) {
      directions[nDir][0] = std::stof(check);
      in >> directions[nDir][1];
      for(int i = 0; i < nKernels; i++) {
        in >> secondTable[nDir][i];
      }
      nDir++;
    }
  }
  if(nDir < nDirections) {
    throw TASCAR::ErrMsg("Less directions than specified");
  }

  // now fill in first table with nearest input direction
  for(int azn = 0; azn < azentries; azn++) {
    float az = azn *az_spacing * DEG2RADf - TASCAR_PIf;
    for(int eln = 0; eln < elentries; eln++) {
      // TASCAR puts horizontal plane at el = 0, but gain file uses el =
      // 90deg, making zero index equal to horizontal plane
      float el = DEG2RADf * ((1-use3D)*90 + eln * el_spacing); 

      firstTable[eln][azn] = findNearestEntry(az, el, directions);
    }
  }

  // delete directions;
}

int lut::getChannels()
{
  return nKernels;
}

float* lut::get_entry(float az, float el)
{

  //az should be in range -pi to pi, and el shouold be -pi/2 to pi/2
  /*if(az<-TASCAR_PIf){
    if(az<-TASCAR_2PIf){
      throw TASCAR::ErrMsg("Source at angle less than expected range");
    }
    az = az+TASCAR_2PIf;
  }
  else if( az>TASCAR_2PIf)
    throw TASCAR::ErrMsg("at angle greater than expected range");


  if( el <-TASCAR_PI2f){
    if(az<-TASCAR_PIf){
      throw TASCAR::ErrMsg("el at angle less than expected");
    }
    //temporarily
    el = -TASCAR_PI2f;
  }
  else if( el > TASCAR_PI2f){
    throw TASCAR::ErrMsg("el at angle greater than expected");
  }*/



  int az_index = (int)(0.5 + (az + TASCAR_PIf) / az_spacing_rad);
  int el_index =(int)(0.5 + (el + TASCAR_PI2f) / el_spacing_rad);

  if(az_index == azentries) {
    az_index = 0;
  }

  return firstTable[el_index][az_index];
}

lut::~lut()
{
  // delete firstTable;
  // delete secondTable;
}




/*
 * Local Variables:
 * mode: c++
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * compile-command: "make -C .."
 * End:
 */
