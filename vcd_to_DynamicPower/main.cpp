#include <iostream>
#include <iomanip>
#include <string>
#include "hdr/vcd_loader.h"
#include "hdr/dynamic_power.h"

using namespace std;

#define BOLD_ON   "\e[1m"
#define BOLD_OFF  "\e[0m"

int main(int argc, char *argv[]) {
  element top;
  float freq = 0;
  float vdd  = 0;
  float cl   = 0;

  if (argc < 3) {
    // ./psw vcd_files/pif2wb_dump.vcd 300 1.2 100
    cout << "Usage: psw <vcd_file_name> <freq in MHz> <vdd> <load capacitance in pF>" << endl;
    return 1;
  }
  freq = strtof(argv[2], NULL);
  vdd = strtof(argv[3], NULL);
  cl = strtof(argv[4], NULL);

  cout << freq << " " << vdd << " " << cl << " " << endl;
  Vcd_loader * loader = new Vcd_loader(argv[1], &top);
  Psw * power = new Psw(&top, freq, vdd, cl);

  cout << endl << BOLD_ON << "--> VCD FILE PARSER <--" << BOLD_OFF << endl;
  cout << "Authors: Guilherme Korol & Matheus Storck" << endl << endl;

  loader->load();
  power->calculate();

  // NOTE: Signals that appear in more than one module will only be counted once
  // during dynamic energy calculations. However, they will appear under all
  // modules which instantiate them. Eg. clock and reset signal.

  cout << endl << "Top module " << BOLD_ON << top.id_name.second << BOLD_OFF <<
    " Total of " << BOLD_ON << top.total_signals << BOLD_OFF << " signals" << " :" << endl;
  for(vector<element>::iterator it = top.sub_elements.begin() ; it != top.sub_elements.end(); it++) {
    cout << "|__ Name: " << setw(20) << left << it->id_name.second << setw(8) << left << "From module: " << it->parent_module <<
      " ID: " << setw(3) << left << it->id_name.first << " PSW: " << setw(11) << left << it->psw << " W" << endl;
      if (!it->sub_elements.empty()) {
        cout << " |__ Sub-module " << BOLD_ON << it->id_name.second << BOLD_OFF <<
          " Total of " << BOLD_ON << it->total_signals << BOLD_OFF << " signals" <<" :" << endl;
        for (vector<element>::iterator it_ = it->sub_elements.begin() ; it_ != it->sub_elements.end(); it_++) {
          cout << " |__ Name: " << setw(20) << left << it_->id_name.second << setw(8) << left << "From module: " << it_->parent_module <<
            " ID: " << setw(3) << left << it_->id_name.first << " PSW: " << setw(11) << left << it_->psw << " W" << endl;
        }
      }
  }

  cout << endl << "Top module " << BOLD_ON << top.id_name.second << BOLD_OFF << " total PSW: " << top.psw << " W" << endl;
  cout << endl;
  return 0;
}
