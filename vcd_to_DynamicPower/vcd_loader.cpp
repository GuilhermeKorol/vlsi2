#include "hdr/vcd_loader.h"

Vcd_loader::Vcd_loader(string fname, element* e) : top(e) {
  vcd_file.open(fname.c_str());
  if (!vcd_file.good()) {
    printf("ERROR opening vcd file\n");
  }
  allocate();
}

void Vcd_loader::allocate() {
  char DELIMITER[] = " ";  // Peek the delimeters here

  while (!vcd_file.eof()) {
    // Get a line from vcd_file
    char buf[MAX_CHARS_PER_LINE];
    vcd_file.getline(buf, MAX_CHARS_PER_LINE);

    int n = 0;

    // Array to store tokens from a line
    const char* token[MAX_TOKENS_PER_LINE] = {};

    token[0] = strtok(buf, DELIMITER);  // This is the firs token
    if (token[0]) {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++){
        token[n] = strtok(0, DELIMITER);
        if (!token[n]) break; // No more tokens
      }
    }
    // Now look for signals, modules, etc. in the tokens
    for (int i = 0; i < n; i++) {
      if (strcmp("module",token[i]) == 0) {
        top->id_name.first = 0; // Module has no ID
        top->id_name.second = token[i+1];
        top->type = MODULE;
        top->width = 0;
        top->total_sw = 0;
        cout << "Top Module: " << top->id_name.second << endl;

      }
      if (strcmp("$var",token[i]) == 0 && strcmp("wire",token[i+1]) == 0) {
        element temp;
        temp.id_name.first = token[i+3][0];
        temp.id_name.second = token[i+4];
        temp.type = WIRE;
        temp.width = 1; // TODO: Deal with buses...
        temp.total_sw = 0;
        top->sub_elements.push_back(temp);
      }
    }
    // if (strcmp("$scope",token[0]) == 0) {
    //   cout << "Top Module:" << token[2] << endl;
    // }
    // if (strcmp("$var",token[0]) == 0 && strcmp("wire",token[1]) == 0) {
    //   cout << "Wire:" << token[4] << endl;
    // }
  }
}

Vcd_loader::~Vcd_loader(){
  vcd_file.close();
}
