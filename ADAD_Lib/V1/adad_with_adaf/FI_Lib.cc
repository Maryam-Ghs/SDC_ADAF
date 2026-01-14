#include <stdio.h>
#include <string>
#include "FI_Lib.h"

FI_Lib fi_lib("settings.txt");

int coredump(int index, int lb, int ub) {
  return 1;
  // if (verbose) printf("run %4d/%4d had an indexing fault %d not in %d-%d\n", current_trial, num_trials, index, lb, ub);
  // ++num_core;
  // ++current_trial;
  // // are we at the end?
  // if (current_trial >= num_trials) finalize();
  // // no, so we jump back into the loop
  // longjmp(JumpBuffer, 1);
}

int get_location_id(const char *OP) {
    return fi_lib.get_location_id(OP);
}
int get_faulty_integer(int id, int value) {
    return fi_lib.get_faulty_integer(id, value);
}
int get_faulty_boolean(int id, int value) {
    return fi_lib.get_faulty_boolean(id, value);
}
float get_faulty_float(int id, float value) {
    return fi_lib.get_faulty_float(id, value);
}
double get_faulty_double(int id, double value) {
    return fi_lib.get_faulty_double(id, value);
}
