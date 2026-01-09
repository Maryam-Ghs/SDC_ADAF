#ifndef FI_LIB_H
#define FI_LIB_H

#include <fstream>
#include <string>
#include <stdexcept>
#include <setjmp.h>
#include <map>
#include "adad.h"
#include "adaf.h"

extern std::map<std::string, int> fault_strings;
extern std::map<int, double>      fault_probs;
extern std::map<int, int>         fault_counts;
extern std::map<int, int>         run_counts;
extern int                        num_sdc, num_core, last_id, verbose,current_trial, num_trials;

class FI_Lib {
public:
    unsigned int SEED{};
    int FI_id{};
    double probability{};
    int cycle{};
    bool List;

    explicit FI_Lib(const std::string& input_path)
        : input_file_path(input_path)
    {
        load_from_file();
    }

    ~FI_Lib() {
        save_to_file();
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
        std::map<std::string, int>::iterator it0;
        std::map<int, int>::iterator it1;
        std::map<int, int>::iterator it2;

        printf("Fault Locations:\n\tid\tdescription\n");
        for (it0 = fault_strings.begin(); it0 != fault_strings.end(); it0++) {
          printf("\t%d\t%s\n", it0->second, it0->first.c_str());
        }
        printf("Run Counts:\n");
          for (it1 = run_counts.begin(); it1 != run_counts.end(); it1++) {
          printf("\t%d\t%d\n", it1->first, it1->second);
        }
        printf("Fault Counts:\n");
          for (it2 = fault_counts.begin(); it2 != fault_counts.end(); it2++) {
          printf("\t%d\t%d\n", it2->first, it2->second);
        }
        return;
      }

      std::map<int, double>::iterator it1;
      std::map<int, int>::iterator it2;

      printf("Injection Fault_Probs:\n\tid\tprob\n");
      for (it1 = fault_probs.begin(); it1 != fault_probs.end(); it1++) {
        printf("\t%d\t%g\n", it1->first, it1->second);
      }

      printf("Fault Counts:\n");
      for (it2 = fault_counts.begin(); it2 != fault_counts.end(); it2++) {
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

extern int coredump(int index, int lb, int ub);

#endif /* FI_LIB_H */