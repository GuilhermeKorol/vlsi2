#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "vcd_loader.h"

#define FREQ 300  // [MHz]
#define VDD  1.2  // [V]
#define CL   50   // [pF]

class Psw {
public:
  Psw(element* e, float f = VDD, float v = VDD, float c = CL);
  void calculate();
  ~Psw();
private:
  element* top;
  int max_sw;
  int sim_time;
  float f;
  float v;
  float c;

  void find_max_sw();
};
