#include "receivermod.h"
#include "lut.h"

class lut_t : public TASCAR::receivermod_base_t {
public:
  class data_t : public TASCAR::receivermod_base_t::data_t {
  public:
    data_t(uint32_t order);
    // ambisonic weights:
    float* B;
  };
  lut_t(tsccfg::node_t xmlsrc);
  ~lut_t();
  void add_pointsource(const TASCAR::pos_t& prel, double width, const TASCAR::wave_t& chunk, std::vector<TASCAR::wave_t>& output, receivermod_base_t::data_t*);
  void add_diffuse_sound_field(const TASCAR::amb1wave_t& chunk, std::vector<TASCAR::wave_t>& output, receivermod_base_t::data_t*);
  
  void configure() { n_channels = channels; TASCAR::receivermod_base_t::configure();};
  receivermod_base_t::data_t* create_state_data(double srate,uint32_t fragsize) const;
  uint32_t channels;
  lut LUT;
  float* B;
  float* deltaB;
};

lut_t::data_t::data_t(uint32_t channels )
{
  B = new float[channels]();
}

lut_t::lut_t(tsccfg::node_t xmlsrc)
  : TASCAR::receivermod_base_t(xmlsrc)
{
  std::string gainFile;
  GET_ATTRIBUTE(gainFile,"","gainFile");
  LUT.loadgains(gainFile);
  channels = LUT.getChannels();
  deltaB = new float[channels]();
}

lut_t::~lut_t()
{

  //delete deltaB;
}

void lut_t::add_pointsource(const TASCAR::pos_t& prel, double width, const TASCAR::wave_t& chunk, std::vector<TASCAR::wave_t>& output, receivermod_base_t::data_t* sd)
{
  data_t* state(dynamic_cast<data_t*>(sd));
  if( !state )
    throw TASCAR::ErrMsg("Invalid data type.");
  float az(prel.azim());
  float el(prel.elev());

  B = LUT.get_entry(az,el);

  // calculate incremental weights:
  for(uint32_t acn=0;acn<channels;++acn)
    deltaB[acn] = (B[acn] - state->B[acn])*t_inc;

  // apply weights:
  for(uint32_t t=0;t<chunk.size();++t)
    for(uint32_t acn=0;acn<channels;++acn)
      output[acn][t] += (state->B[acn] += deltaB[acn]) * chunk[t];
  


  // copy final values to avoid rounding errors:
  for(uint32_t acn=0;acn<channels;++acn)
    state->B[acn] = B[acn];

}

void lut_t::add_diffuse_sound_field(const TASCAR::amb1wave_t& chunk, std::vector<TASCAR::wave_t>& output, receivermod_base_t::data_t* sd)
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

TASCAR::receivermod_base_t::data_t* lut_t::create_state_data(double srate, uint32_t fragsize) const
{
  return new data_t(channels);
}

REGISTER_RECEIVERMOD(lut_t);

/*
 * Local Variables:
 * mode: c++
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * compile-command: "make -C .."
 * End:
 */
