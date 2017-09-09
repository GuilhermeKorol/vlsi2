#include "hdr/dynamic_power.h"

bool cmp(const element& e, const element& f)
{
  return e.total_sw < f.total_sw;
}

Psw::Psw(element* e, float f/*= VDD*/, float v/*= VDD*/, float c/*= CL*/) :
        top(e), f(f), v(v), c(c) { }

void Psw::calculate() {
  find_max_sw();
  sim_time = top->sim_time;            // Top gives is the total simulation time
  cout << "Simulation time: " << sim_time << endl;
  cout << "Max number of SW: " << max_sw << endl;
  // With the maximum number of transistions, we can estimate Esw
  // Esw(x) = x.total_sw / max_sw

  // Walk through all elements calculating their Dynamic Energy
  for(vector<element>::iterator it = top->sub_elements.begin(); it != top->sub_elements.end(); it++) {
    if (!it->sub_elements.empty()) {
      float temp_psw = 0;
      for(vector<element>::iterator it_ = it->sub_elements.begin(); it_ != it->sub_elements.end(); it_++) {
        float esw = it_->total_sw / max_sw;
        it_->psw += (0.5*(v*v)) * (f*1000000) * (c*0.000000000001) * esw;
        it_->psw += it_->psw;
        temp_psw += it_->psw;
      }
      it->psw += temp_psw;
     }
     float esw = it->total_sw / max_sw;
     it->psw += (0.5*(v*v)) * (f*1000000) * (c*0.000000000001) * esw;
     top->psw += it->psw;
    }
}

void Psw::find_max_sw() {
  vector<element>::iterator it = std::max_element(top->sub_elements.begin(),top->sub_elements.end(),cmp);
  max_sw = it->total_sw;
}

Psw::~Psw() {

}
