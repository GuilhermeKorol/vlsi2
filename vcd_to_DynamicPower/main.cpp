#include <iostream>
#include "hdr/vcd_loader.h"

using namespace std;

int main(int argc, char *argv[]) {
  element top;
  Vcd_loader * loader = new Vcd_loader("vcd_files/foo.vcd", &top);

  cout << "Size of sub_elements of Top: " << top.sub_elements.size() << endl;

  for(vector<element>::iterator it = top.sub_elements.begin() ; it != top.sub_elements.end(); it++) {
    cout << "Element name: " << it->id_name.second << endl;
  }
}
