#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "vcd_loader.h"

#define VDD  1.2  // V
#define CL   50   // [pF]
#define FREQ 300   // [MHz]

class Psw {
public:
  Psw(element* e);
  void calculate();
  ~Psw();
private:
  element* top;
  int max_sw;
  int sim_time;

  void find_max_sw();
};
