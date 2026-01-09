#include <stdlib.h>
#include <string>
#include <map>
#include <execinfo.h>

#include "adad.h"
#include "adaf.h"
#include "FI_Lib.h"

 std::map<std::string, int> fault_strings;
 std::map<int, double>      fault_probs;
 std::map<int, int>         fault_counts;
 std::map<int, int>         run_counts;
 int                        num_sdc, num_core, last_id;

extern int                   backtrace(void **buffer, int size);
extern char**                backtrace_symbols(void* const* array, int size);

int get_location_id(const char *OP) {
  int    id;
  void	*p[3];
  char **q;
  backtrace(p, 3);
  q = backtrace_symbols(p, 3);
  std::string S = OP + std::string("\t") + std::string(q[2]);
  free(q);
  if (fault_strings.find(S) == fault_strings.end()) {
    id = 1 + fault_strings.size();
    fault_strings[S] = id;
  } else {
    id = fault_strings[S];
  }
  return id;
}

static double rand01() {
  return random() * 4.656612e-10;
}

int get_faulty_integer(int id, int value) {
  int f, g;
  ++run_counts[id];
  // has the location been marked for fault insertion
  if (fault_probs.find(id) == fault_probs.end()) {
    return value;
  }
  // is the probability sensible (may not be needed)
  if (fault_probs[id] <= 0.0 || fault_probs[id] > 1.0) {
    return value;
  }
  // roll the dice
  if (rand01() > fault_probs[id]) {
    return value;
  }
  // increment the fault count
  ++fault_counts[id];
  // mark this as the last location
  last_id = id;
  // pick a random bit location
  f = random() % 32;
  // put a 1 there
  g = 1 << f;
  // xor it on the result
  value = value ^ g;
  return value;
}

int get_faulty_boolean(int id, int value) {
  ++run_counts[id];
  // has the location been marked for fault insertion
  if (fault_probs.find(id) == fault_probs.end()) {
    return value;
  }
  // is the probability sensible (may not be needed)
  if (fault_probs[id] <= 0.0 || fault_probs[id] > 1.0) {
    return value;
  }
  // roll the dice
  if (rand01() > fault_probs[id]) {
    return value;
  }
  // increment the fault count
  ++fault_counts[id];
  // mark this as the last location
  last_id = id;
  // and reverse the result
  return ! value;
}

float get_faulty_float(int id, float value) {
  int f, g;
  union two {
    int   i;
    float f;
  } x;
  ++run_counts[id];
  // has the location been marked for fault insertion
  if (fault_probs.find(id) == fault_probs.end()) {
    return value;
  }
  // is the probability sensible (may not be needed)
  if (fault_probs[id] <= 0.0 || fault_probs[id] > 1.0) {
    return value;
  }
  // roll the dice
  if (rand01() > fault_probs[id]) {
    return value;
  }
  // increment the fault count
  ++fault_counts[id];
  // mark this as the last location
  last_id = id;
  // pick a random bit location
  f = random() % 32;
  // put a 1 there
  g = 1 << f;
  // xor it on the result
  x.f = value;
  x.i = x.i ^ g;
  return x.f;
}

void coredump(int index, int lb, int ub) {
  if (verbose) printf("run %4d/%4d had an indexing fault %d not in %d-%d\n", current_trial, num_trials, index, lb, ub);
  ++num_core;
  ++current_trial;
  // are we at the end?
  if (current_trial >= num_trials) finalize();
  // no, so we jump back into the loop
  longjmp(JumpBuffer, 1);
}