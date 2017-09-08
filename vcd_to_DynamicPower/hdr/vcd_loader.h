#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

// enum vcd_types {event, integer, parameter, real, reg, supply0,
//                 supply1, tri, triand, trior, trireg, tri0,
//                 tri1, wand, wire, wor};
enum vcd_types {MODULE, WIRE};    // Using only both for now

struct element{
  pair<string, string> id_name;
  vcd_types          type;
  int                width;
  double             total_sw;
  vector<element>    sub_elements;
};

struct find_id : unary_function<element, bool> {
  char* id_name;
  find_id(char* id):id_name(id) { }
  int operator()(element const &e) const {
    return !(strcmp(e.id_name.first.c_str(),id_name));
  }
};

class Vcd_loader {
public:
  Vcd_loader(string fname, element* e);
  ~Vcd_loader();

  static const int MAX_CHARS_PER_LINE = 128;    // Pessimistic guess of line size
  static const int MAX_TOKENS_PER_LINE = 10;    // and tokens by line
  // static const char* const DELIMITER = " ";

private:
  ifstream vcd_file;
  element* top;

  void allocate();
};
