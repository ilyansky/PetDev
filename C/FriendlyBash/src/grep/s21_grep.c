#include "grep.h"

int main(int argc, char *argv[]) {
  struct Flags flag = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int flags_amount = 0;

  if (flag_detect(argc, argv, &flag, &flags_amount) || argc == 1) {
    print_usage();
  } else {
    int files_indices[300];
    int files_amount =
        count_files(argc, argv, files_indices, flags_amount, flag);
    if (flags_amount == 0) {
      grep_without_flags(argv, files_amount, files_indices);
    } else if (flags_amount == 1) {
      grep_with_one_flag(argc, argv, flag, files_amount, files_indices);
    } else {
      grep_with_one_flag(argc, argv, flag, files_amount, files_indices);
    }
  }

  return 0;
}
