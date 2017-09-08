#include "hdr/dynamic_power.h"

bool cmp(const element& e, const element& f)
{
  return e.total_sw < f.total_sw;
}

Psw::Psw(element* e) : top(e) {
  if (top->sim_time > 0 && !top->sub_elements.empty()) {
  } else {
    cout << "Top module not valid!" << endl;
  }
}

void Psw::calculate() {
  find_max_sw();
  sim_time = top->sim_time;   // Top gives the total simulation time
  cout << "Sim time: " << sim_time << endl;
  cout << "Max SW: " << max_sw << endl;

}

void Psw::find_max_sw() {
  vector<element>::iterator it = std::max_element(top->sub_elements.begin(),top->sub_elements.end(),cmp);
  max_sw = it->total_sw;
}

Psw::~Psw() {

}
