#include "receivermod.h"
#include "lut.h"

class lutnull_t : public TASCAR::receivermod_base_t {
public:
  class data_t : public TASCAR::receivermod_base_t::data_t {
  public:
    data_t(uint32_t order);
    // ambisonic weights:
    float* B;
  };
  lutnull_t(tsccfg::node_t xmlsrc);
  ~lutnull_t();
  void add_pointsource(const TASCAR::pos_t& prel, double width, const TASCAR::wave_t& chunk, std::vector<TASCAR::wave_t>& output, receivermod_base_t::data_t*);
  void add_diffuse_sound_field(const TASCAR::amb1wave_t& chunk, std::vector<TASCAR::wave_t>& output, receivermod_base_t::data_t*);
  
  void configure() { n_channels = channels; TASCAR::receivermod_base_t::configure();};
  receivermod_base_t::data_t* create_state_data(double srate,uint32_t fragsize) const;
  uint32_t channels;
  lut LUT;
  float* B;
  float* deltaB;
  float az_spacing;
  float el_spacing;
  int use3D=1;
};

lutnull_t::data_t::data_t(uint32_t channels )
{
  B = new float[channels]();
}

lutnull_t::lutnull_t(tsccfg::node_t xmlsrc)
  : TASCAR::receivermod_base_t(xmlsrc)
{
  std::string gainFile;
  GET_ATTRIBUTE(gainFile,"","gainFile");
  GET_ATTRIBUTE(az_spacing,"","az_spacing");
  GET_ATTRIBUTE(el_spacing,"","el_spacing");
  GET_ATTRIBUTE(use3D,"","use3D");
  LUT.loadgains(gainFile,az_spacing,el_spacing,use3D);
  channels = LUT.getChannels();
  deltaB = new float[channels]();
}

lutnull_t::~lutnull_t()
{

  //delete deltaB;
}

void lutnull_t::add_pointsource(const TASCAR::pos_t& prel, double width, const TASCAR::wave_t& chunk, std::vector<TASCAR::wave_t>& output, receivermod_base_t::data_t* sd)
{


}

void lutnull_t::add_diffuse_sound_field(const TASCAR::amb1wave_t& chunk, std::vector<TASCAR::wave_t>& output, receivermod_base_t::data_t* sd)
{
  if( output.size() ){
    output[0].add( chunk.w(), sqrtf(2.0f) );
    if( output.size() > 3 ){
      output[1].add( chunk.y() );
      output[2].add( chunk.z() );
      output[3].add( chunk.x() );
    }
  }
}

TASCAR::receivermod_base_t::data_t* lutnull_t::create_state_data(double srate, uint32_t fragsize) const
{
  return new data_t(channels);
}

REGISTER_RECEIVERMOD(lutnull_t);

/*
 * Local Variables:
 * mode: c++
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * compile-command: "make -C .."
 * End:
 */
