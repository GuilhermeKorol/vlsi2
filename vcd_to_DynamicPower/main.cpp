#include <iostream>
#include <iomanip>
#include "hdr/vcd_loader.h"
#include "hdr/dynamic_power.h"

using namespace std;

#define BOLD_ON   "\e[1m"
#define BOLD_OFF  "\e[0m"

int main(int argc, char *argv[]) {
  element top;
  Vcd_loader * loader = new Vcd_loader("vcd_files/pif2wb_dump.vcd", &top);
  Psw * power = new Psw(&top);

  cout << endl << BOLD_ON << "--> VCD FILE PARSER <--" << BOLD_OFF << endl;
  cout << "Authors: Guilherme Korol & Matheus Storck" << endl << endl;

  loader->load();
  power->calculate();

  // NOTE: Signals that appear in more than one module will only be counted once
  // during dynamic energy calculations. However they will appear under all
  // modules which instantiate them. Eg. clock and reset signal.

  cout << endl << "Top module " << BOLD_ON << top.id_name.second << BOLD_OFF << " :" << endl;
  for(vector<element>::iterator it = top.sub_elements.begin() ; it != top.sub_elements.end(); it++) {
    cout << "|_ Name: " << setw(20) << left << it->id_name.second << setw(8) << left << "From module: " << it->parent_module <<
      " ID: " << setw(3) << left << it->id_name.first << " PSW: " << setw(11) << left << it->psw << " W" << endl;
      if (!it->sub_elements.empty()) {
        cout << "|_ Sub-module " << BOLD_ON << it->id_name.second << BOLD_OFF << " :" << endl;
        for (vector<element>::iterator it_ = it->sub_elements.begin() ; it_ != it->sub_elements.end(); it_++) {
          cout << "|__ Name: " << setw(20) << left << it_->id_name.second << setw(8) << left << "From module: " << it_->parent_module <<
            " ID: " << setw(3) << left << it_->id_name.first << " PSW: " << setw(11) << left << it_->psw << " W" << endl;
        }
      }
  }

  cout << endl << "Top module " << BOLD_ON << top.id_name.second << BOLD_OFF << " total PSW: " << top.psw << " W" << endl;
  cout << endl;
}
