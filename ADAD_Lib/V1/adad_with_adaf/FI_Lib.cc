#include <stdio.h>
#include <string>
#include "FI_Lib.h"


static FI_Lib fi_lib("settings.txt");

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