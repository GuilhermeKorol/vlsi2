#include <iostream>
#include "hdr/vcd_loader.h"
#include "hdr/dynamic_power.h"

using namespace std;

int main(int argc, char *argv[]) {
  element top;
  Vcd_loader * loader = new Vcd_loader("vcd_files/pif2wb_dump.vcd", &top);
  Psw * power = new Psw(&top);

  loader->load();
  power->calculate();

  for(vector<element>::iterator it = top.sub_elements.begin() ; it != top.sub_elements.end(); it++) {
    cout << "Name: " << it->id_name.second << " ID: " << it->id_name.first << " SW Activity: " << it->total_sw << endl;
  }

}
