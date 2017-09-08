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
    static bool dumpvars = false;

    token[0] = strtok(buf, DELIMITER);  // This is the firs token
    if (token[0]) {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++){
        token[n] = strtok(0, DELIMITER);
        if (!token[n]) break; // No more tokens
      }
    }
    // Now look for signals, modules, transitions, etc. in the tokens
    for (int i = 0; i < n; i++) {
      if (strcmp("module",token[i]) == 0) {
        // Top Module
        top->id_name.first = "";
        top->id_name.second = token[i+1];
        top->type = MODULE;
        top->width = 0;
        top->total_sw = 0;
      }
      if (strcmp("$var",token[i]) == 0 && strcmp("wire",token[i+1]) == 0) {
        // Wires
        element temp;
        temp.id_name.first = token[i+3];
        temp.id_name.second = token[i+4];
        temp.type = WIRE;
        temp.width = 1; // TODO: Deal with buses...
        temp.total_sw = 0;
        top->sub_elements.push_back(temp);
      }
      if (strcmp("$dumpvars",token[i]) == 0) {
        // Init values on following lines
        dumpvars = true;
      } else if (dumpvars == true && (strcmp("$end",token[i]) == 0)) {
        // Init values ended
        dumpvars = false;
      } else if (dumpvars == true) {
        // Everything between $dumpvars and $end is <value><id>
        char* temp_str = (char*)token[i]+1;
        vector<element>::iterator it = find_if(top->sub_elements.begin(), top->sub_elements.end(), find_id(temp_str));
        it->total_sw++;
        cout << "Wire: " << it->id_name.second << " SW: " << it->total_sw << endl;
      }
    }
  }
}

Vcd_loader::~Vcd_loader(){
  vcd_file.close();
}
