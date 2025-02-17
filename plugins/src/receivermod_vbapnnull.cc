/*
 * This file is part of the TASCAR software, see <http://tascar.org/>
 *
 * Copyright (c) 2018 Giso Grimm
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

#include <boost/geometry.hpp>
#include <boost/geometry/multi/geometries/multi_point.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>

#include "errorhandling.h"
#include "scene.h"


BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

namespace bg = boost::geometry;

typedef boost::tuple<double, double> bg_point_t;
typedef bg::model::multi_point<bg_point_t> bg_pointlist_t;

class simplex_t {
public:
  simplex_t() : c1(-1), c2(-1){};
  bool get_gain(const TASCAR::pos_t& p, float& g1, float& g2) const
  {
    g1 = p.x * l11 + p.y * l21;
    g2 = p.x * l12 + p.y * l22;
    if((g1 >= 0.0f) && (g2 >= 0.0f)) {
      float w(sqrtf(g1 * g1 + g2 * g2));
      if(w > 0.0f)
        w = 1.0f / w;
      g1 *= w;
      g2 *= w;
      return true;
    }
    return false;
  };
  uint32_t c1;
  uint32_t c2;
  float l11;
  float l12;
  float l21;
  float l22;
};

class rec_vbapnnull_t : public TASCAR::receivermod_base_speaker_t {
public:
  class data_t : public TASCAR::receivermod_base_t::data_t {
  public:
    data_t(uint32_t channels);
    virtual ~data_t();
    // loudspeaker driving weights:
    float* wp;
    // differential driving weights:
    float* dwp;
    uint32_t prevK1;
    uint32_t prevK2;
  };
  rec_vbapnnull_t(tsccfg::node_t xmlsrc);
  virtual ~rec_vbapnnull_t() {};
  void add_pointsource(const TASCAR::pos_t& prel, double width, const TASCAR::wave_t& chunk, std::vector<TASCAR::wave_t>& output, receivermod_base_t::data_t*);
  receivermod_base_t::data_t* create_state_data(double srate,uint32_t fragsize) const;
  std::vector<simplex_t> simplices;


};

rec_vbapnnull_t::data_t::data_t( uint32_t channels )
{
  wp = new float[channels];
  dwp = new float[channels];
  for(uint32_t k=0;k<channels;++k)
    wp[k] = dwp[k] = 0;

  prevK1 = 0;
  prevK2 = 0;
}

rec_vbapnnull_t::data_t::~data_t()
{
  delete [] wp;
  delete [] dwp;
}

rec_vbapnnull_t::rec_vbapnnull_t(tsccfg::node_t xmlsrc)
  : TASCAR::receivermod_base_speaker_t(xmlsrc)
{
  if( spkpos.size() < 2 )
    throw TASCAR::ErrMsg("At least two loudspeakers are required for 2D-VBAP.");
  // create a boost point list from speaker layout:
  bg_pointlist_t spklist;
  for(uint32_t k=0;k<spkpos.size();++k)
    bg::append(spklist,bg_point_t(spkpos[k].unitvector.x,spkpos[k].unitvector.y));
  // calculate the convex hull:
  bg_pointlist_t hull;
  boost::geometry::convex_hull(spklist, hull);
  if( hull.size() < 2 )
    throw TASCAR::ErrMsg("Invalid convex hull.");
  // identify channel numbers of simplex vertices and store inverted
  // loudspeaker matrices:
  for( uint32_t khull=0;khull<hull.size()-1;++khull){
    simplex_t sim;
    sim.c1 = spklist.size();
    sim.c2 = spklist.size();
    for(uint32_t k=0;k<bg::num_points(spklist);++k)
      if( bg::equals(spklist[k],hull[khull]))
        sim.c1 = k;
    for(uint32_t k=0;k<bg::num_points(spklist);++k)
      if( bg::equals(spklist[k],hull[khull+1]))
        sim.c2 = k;
    if( (sim.c1 >= spklist.size()) || (sim.c2 >= spklist.size()) )
      throw TASCAR::ErrMsg("Simplex vertex not found in speaker list.");
    double l11(spkpos[sim.c1].unitvector.x);
    double l12(spkpos[sim.c1].unitvector.y);
    double l21(spkpos[sim.c2].unitvector.x);
    double l22(spkpos[sim.c2].unitvector.y);
    double det_speaker(l11*l22 - l21*l12);
    if( det_speaker != 0 )
      det_speaker = 1.0/det_speaker;
    sim.l11 = det_speaker*l22;
    sim.l12 = -det_speaker*l12;
    sim.l21 = -det_speaker*l21;
    sim.l22 = det_speaker*l11;
    simplices.push_back(sim);
  }
}

/*
  See receivermod_base_t::add_pointsource() in file receivermod.h for details.
*/
void rec_vbapnnull_t::add_pointsource( const TASCAR::pos_t& prel,
                                  double width,
                                  const TASCAR::wave_t& chunk,
                                  std::vector<TASCAR::wave_t>& output,
                                  receivermod_base_t::data_t* sd)
{
  


}

TASCAR::receivermod_base_t::data_t* rec_vbapnnull_t::create_state_data(double srate,uint32_t fragsize) const
{
  return new data_t(spkpos.size());
}

REGISTER_RECEIVERMOD(rec_vbapnnull_t);

/*
 * Local Variables:
 * mode: c++
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * compile-command: "make -C .."
 * End:
 */
