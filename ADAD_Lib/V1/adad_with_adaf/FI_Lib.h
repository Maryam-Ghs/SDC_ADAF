#ifndef FI_LIB_H
#define FI_LIB_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <setjmp.h>
#include <map>
#include <execinfo.h>
#include "adad.h"
#include "adaf.h"



class FI_Lib {
public:
    unsigned int SEED{};
    int FI_id{};
    double probability{};
    int cycle{};
    bool List;

    std::map<std::string, int> fault_strings;
    std::map<int, double>      fault_probs;
    std::map<int, int>         fault_counts;
    std::map<int, int>         run_counts;
    int                        num_sdc, num_core, last_id, verbose,current_trial, num_trials;

    explicit FI_Lib(const std::string& input_path)
        : input_file_path(input_path)
    {
        load_from_file();
    }

    ~FI_Lib() {
        save_to_file();
    }

    int get_location_id(const char *OP) {
      int    id;
      const int depth = 4;
      void	*p[depth];
      char **q;
      backtrace(p, depth);
      q = backtrace_symbols(p, depth);
      std::string S = OP + std::string("\t") + std::string(q[depth - 1]);
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

    double get_faulty_double(int id, double value) {
      int f, g;
      union two {
        int   i;
        double f;
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
      f = random() % 64;
      // put a 1 there
      g = 1 << f;
      // xor it on the result
      x.f = value;
      x.i = x.i ^ g;
      return x.f;
    }

private:
    std::string input_file_path;

    void load_from_file() {
        std::ifstream file(input_file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open input file: " + input_file_path);
        }

        file >> SEED >> FI_id >> probability >> cycle >> List;
        if (file.fail()) {
            throw std::runtime_error("Error reading input file");
        }
    }

    void finalize() const{
      if (List) {
        std::cout << fault_strings.size() << std::endl;

        printf("Fault Locations:\n\tid\tdescription\n");
        for (auto it0 = fault_strings.begin(); it0 != fault_strings.end(); it0++) {
          printf("\t%d\t%s\n", it0->second, it0->first.c_str());
        }
        printf("Run Counts:\n");
          for (auto it1 = run_counts.begin(); it1 != run_counts.end(); it1++) {
          printf("\t%d\t%d\n", it1->first, it1->second);
        }
        printf("Fault Counts:\n");
          for (auto it2 = fault_counts.begin(); it2 != fault_counts.end(); it2++) {
          printf("\t%d\t%d\n", it2->first, it2->second);
        }
        return;
      }

      printf("Injection Fault_Probs:\n\tid\tprob\n");
      for (auto it1 = fault_probs.begin(); it1 != fault_probs.end(); it1++) {
        printf("\t%d\t%g\n", it1->first, it1->second);
      }

      printf("Fault Counts:\n");
      for (auto it2 = fault_counts.begin(); it2 != fault_counts.end(); it2++) {
        printf("\t%d\t%d\n", it2->first, it2->second);
      }
      return;
    }

    void save_to_file() const {
        std::string out_path = make_out_path(input_file_path);
        std::ofstream file(out_path);
        if (!file.is_open()) {
            // IMPORTANT: destructors must NOT throw
            return;
        }

        file << SEED << "\n"
             << FI_id << "\n"
             << probability << "\n"
             << cycle << "\n";

        finalize();
    }

    static std::string make_out_path(const std::string& in) {
        auto pos = in.find_last_of('.');
        if (pos == std::string::npos) {
            return in + "_out";  // no extension
        }
        return in.substr(0, pos) + "_out" + in.substr(pos);
    }


};


extern FI_Lib fi_lib;

int get_location_id(const char *OP);
int get_faulty_integer(int id, int value);
int get_faulty_boolean(int id, int value);
float get_faulty_float(int id, float value);
double get_faulty_double(int id, double value);


int coredump(int index, int lb, int ub);

#endif /* FI_LIB_H */
