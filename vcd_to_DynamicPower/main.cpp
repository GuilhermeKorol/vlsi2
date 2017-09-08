#include <iostream>
#include <iomanip>
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
    cout << "Name: " << setw(20) << left << it->id_name.second << " ID: " << setw(3) << left <<
      it->id_name.first << " PSW: " << setw(11) << left << it->psw << " W" << endl;
  }
  cout << endl << "Top module " << "\e[1m" << top.id_name.second << "\e[0m" << " total PSW: " << top.psw << " W" << endl;

}
