#include "hdr/vcd_loader.h"

Vcd_loader::Vcd_loader(string fname, element* e) : top(e) {
  vcd_file.open(fname.c_str());
  if (!vcd_file.good()) {
    printf("ERROR opening vcd file\n");
  }
}

void Vcd_loader::load() {
  char DELIMITER[] = " ";  // Peek the delimeters here

  while (!vcd_file.eof()) {
    // Get a line from vcd_file
    char buf[MAX_CHARS_PER_LINE];
    vcd_file.getline(buf, MAX_CHARS_PER_LINE);

    int n = 0;

    // Array to store tokens from a line
    const char* token[MAX_TOKENS_PER_LINE] = {};
    static bool dumpvars = false;
    static int  last_time = 0;

    token[0] = strtok(buf, DELIMITER);  // This is the firs token
    if (token[0]) {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++){
        token[n] = strtok(0, DELIMITER);
        if (!token[n]) { // No more tokens
          top->sim_time = last_time;
          break;
        }
      }
    }
    // Now look for signals, modules, transitions, etc. in the tokens
    for (int i = 0; i < n; i++) {
      // Load top module
      if (strcmp("module",token[i]) == 0) {
        // Top Module
        top->id_name.first = "";
        top->id_name.second = token[i+1];
        top->type = MODULE;
        top->width = 0;
        top->total_sw = 0;
        top->sim_time = 0;
        top->psw = 0;
      }
      // Load Wire names
      if (strcmp("$var",token[i]) == 0 && strcmp("wire",token[i+1]) == 0) {
        // Wires
        element temp;
        temp.id_name.first = token[i+3];
        temp.id_name.second = token[i+4];
        temp.type = WIRE;
        temp.width = 1; // TODO: Deal with buses...
        temp.total_sw = 0;
        temp.sim_time = 0;
        temp.psw = 0;
        top->sub_elements.push_back(temp);
      }
      char* temp_str = (char*)token[i]; // Help when need to change token pointer
      // Load init values (dumpvars)
      if (strcmp("$dumpvars",token[i]) == 0) {
        // Init values on following lines
        dumpvars = true;
      } else if (dumpvars == true && (strcmp("$end",token[i]) == 0)) {
        // Init values ended
        dumpvars = false;
      } else if (dumpvars == true) {
        // Everything between $dumpvars and $end is <value><id>
        vector<element>::iterator it = find_if(top->sub_elements.begin(), top->sub_elements.end(), find_id(temp_str+1));
        it->total_sw++;
      }
      // Load transitions
      if (temp_str[0] == '#') {
        last_time = atoi(temp_str+1);
      } else if (last_time > 0) {
         vector<element>::iterator it = find_if(top->sub_elements.begin(), top->sub_elements.end(), find_id(temp_str+1));
         it->total_sw++;
      }

    }
  }
}

Vcd_loader::~Vcd_loader(){
  vcd_file.close();
}
