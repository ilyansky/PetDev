#include "grep.h"

// Grep without flags
void grep_without_flags(char* argv[], int files_amount,
                        const int files_indices[]) {
  // grep pattern 1.txt
  if (files_amount == 1) one_file_case(argv, files_indices, 'd', 0);
  // grep pattern 1.txt 2.txt
  else if (files_amount > 1)
    several_files_case(argv, files_amount, files_indices, 'd', 0);
}

// Grep with 1 flag
// grep -flag pattern 1.txt / 1.txt 2.txt
void grep_with_one_flag(int argc, char* argv[], struct Flags flag,
                        int files_amount, int files_indices[]) {
  if (flag.e)
    e_flag(argc, argv, files_amount, files_indices);
  else if (flag.i)
    i_flag(argv, files_amount, files_indices);
  else if (flag.v)
    v_flag(argv, files_amount, files_indices);
  else if (flag.c)
    c_flag(argv, files_amount, files_indices);
  else if (flag.l)
    l_flag(argv, files_amount, files_indices);
  else if (flag.n)
    n_flag(argv, files_amount, files_indices);
  else if (flag.h)
    h_flag(argv, files_amount, files_indices);
  else if (flag.s)
    s_flag(argv, files_amount, files_indices);
  else if (flag.f)
    f_flag(argv, files_amount, files_indices);
  else if (flag.o)
    o_flag(argv, files_amount, files_indices);
}

// Flag funcs
void e_flag(int argc, char* argv[], int files_amount,
            const int files_indices[]) {
  int patterns_indices[300];
  int patterns_amount = find_patterns_indices(argc, argv, patterns_indices);
  many_patterns_case(argv, files_amount, files_indices, patterns_indices,
                     patterns_amount, NULL, 'e');
}

void i_flag(char* argv[], int files_amount, int files_indices[]) {
  if (files_amount == 1)
    one_file_case(argv, files_indices, 'i', 1);
  else if (files_amount > 1)
    several_files_case(argv, files_amount, files_indices, 'i', 1);
}

void v_flag(char* argv[], int files_amount, int files_indices[]) {
  if (files_amount == 1)
    one_file_case(argv, files_indices, 'v', 1);
  else if (files_amount > 1)
    several_files_case(argv, files_amount, files_indices, 'v', 1);
}

void c_flag(char* argv[], int files_amount, int files_indices[]) {
  if (files_amount == 1) {
    int matches = collect_info(argv[files_indices[0]], argv[2], 'c');
    if (matches != -1) printf("%d\n", matches);
  } else if (files_amount > 1) {
    for (int i = 0; i < files_amount; i++) {
      int matches = collect_info(argv[files_indices[i]], argv[2], 'c');
      if (matches != -1) printf("%s:%d\n", argv[files_indices[i]], matches);
    }
  }
}

void l_flag(char* argv[], int files_amount, int files_indices[]) {
  for (int i = 0; i < files_amount; i++) {
    int l_indic = collect_info(argv[files_indices[i]], argv[2], 'l');
    if (l_indic == 1) printf("%s\n", argv[files_indices[i]]);
  }
}

void n_flag(char* argv[], int files_amount, int files_indices[]) {
  if (files_amount == 1) {
    one_file_case(argv, files_indices, 'n', 1);
  } else if (files_amount > 1) {
    several_files_case(argv, files_amount, files_indices, 'n', 1);
  }
}

void h_flag(char* argv[], int files_amount, int files_indices[]) {
  for (int i = 0; i < files_amount; i++) {
    FILE* file = fopen(argv[files_indices[i]], "r");
    if (is_file_null(file, argv[files_indices[i]])) continue;
    char line[2000] = "";
    while (fgets(line, 2000, file)) {
      int res = find_match(line, argv[2], 'd');
      if (res == 1) printf("%s", line);
      end_back_slash_n(line, res);
    }
    fclose(file);
  }
}

void s_flag(char* argv[], int files_amount, int files_indices[]) {
  if (files_amount == 1)
    one_file_case(argv, files_indices, 's', 1);
  else if (files_amount > 1)
    several_files_case(argv, files_amount, files_indices, 's', 1);
}

// grep -f p.txt 1.txt 2.txt 3.txt
void f_flag(char* argv[], int files_amount, int files_indices[]) {
  char patterns[LINES][LEN];
  int patterns_amount = find_patterns(patterns, argv[2]);
  if (patterns_amount != -1) {
    many_patterns_case(argv, files_amount, files_indices, NULL, patterns_amount,
                       patterns, 'f');
  }
}

void o_flag(char* argv[], int files_amount, int files_indices[]) {
  if (files_amount == 1) {
    FILE* file = fopen(argv[files_indices[0]], "r");
    if (is_file_null(file, argv[files_indices[0]])) return;
    char line[2000] = "";
    int count = 0;
    while (fgets(line, 2000, file)) {
      const char* position = line;
      while ((position = strstr(position, argv[2])) != NULL) {
        count++;
        position += strlen(argv[2]);
      }
    }
    for (int i = 0; i < count; i++) {
      printf("%s", argv[2]);
      end_back_slash_n(argv[2], 1);
    }
    fclose(file);
  } else if (files_amount > 1) {
    for (int i = 0; i < files_amount; i++) {
      FILE* file = fopen(argv[files_indices[i]], "r");
      if (is_file_null(file, argv[files_indices[i]])) continue;
      char line[2000] = "";
      int count = 0;
      while (fgets(line, 2000, file)) {
        const char* position = line;
        while ((position = strstr(position, argv[2])) != NULL) {
          count++;
          position += strlen(argv[2]);
        }
      }
      for (int j = 0; j < count; j++) {
        printf("%s:%s", argv[files_indices[i]], argv[2]);
        end_back_slash_n(argv[2], 1);
      }
      fclose(file);
    }
  }
}

// Sup funcs
void many_patterns_case(char* argv[], int files_amount,
                        const int files_indices[], int patterns_indices[],
                        int patterns_amount, char patterns[][LEN], char opt) {
  if (files_amount == 1) {
    FILE* file = fopen(argv[files_indices[0]], "r");
    if (is_file_null(file, argv[files_indices[0]])) return;
    char line[2000] = "";
    while (fgets(line, 2000, file)) {
      if (opt == 'f' && is_backslash_pattern(patterns, patterns_amount)) {
        printf("%s", line);
        end_back_slash_n(line, 1);
        continue;
      }
      int res = 0;
      for (int i = 0; i < patterns_amount; i++) {
        if (opt == 'e')
          res = find_match(line, argv[patterns_indices[i]], 'd');
        else if (opt == 'f')
          res = find_match(line, patterns[i], 'd');

        if (res == 1) {
          printf("%s", line);
          break;
        }
      }
      end_back_slash_n(line, res);
    }
    fclose(file);
    // for many files
  } else if (files_amount > 1) {
    for (int i = 0; i < files_amount; i++) {
      FILE* file = fopen(argv[files_indices[i]], "r");
      if (is_file_null(file, argv[files_indices[i]])) continue;
      char line[2000] = "";
      while (fgets(line, 2000, file)) {
        if (opt == 'f' && is_backslash_pattern(patterns, patterns_amount)) {
          printf("%s:%s", argv[files_indices[i]], line);
          end_back_slash_n(line, 1);
          continue;
        }
        int res = 0;
        for (int j = 0; j < patterns_amount; j++) {
          if (opt == 'e')
            res = find_match(line, argv[patterns_indices[j]], 'd');
          else if (opt == 'f')
            res = find_match(line, patterns[j], 'd');

          if (res == 1) {
            printf("%s:%s", argv[files_indices[i]], line);
            break;
          }
        }
        end_back_slash_n(line, res);
      }
      fclose(file);
    }
  }
}

int is_backslash_pattern(char patterns[][LEN], int patterns_amount) {
  for (int i = 0; i < patterns_amount; i++) {
    if (strcmp(patterns[i], "\n") == 0) return 1;
  }
  return 0;
}

int find_patterns(char patterns[][LEN], char filename[]) {
  int i = 0;
  FILE* file = fopen(filename, "r");
  if (is_file_null(file, filename)) return -1;
  while (fgets(patterns[i], LEN, file)) {
    if (patterns[i][strlen(patterns[i]) - 1] == '\n' &&
        strcmp(patterns[i], "\n") != 0)
      patterns[i][strlen(patterns[i]) - 1] = '\0';
    i++;
    if (i >= LINES) break;
  }
  fclose(file);
  return i;
}

int collect_info(char filename[], char pattern[], char opt) {
  int l_indic = 0;
  int c_counter = 0;
  FILE* file = fopen(filename, "r");
  if (is_file_null(file, filename)) return -1;
  char line[2000] = "";
  while (fgets(line, 2000, file)) {
    int res = find_match(line, pattern, 'd');
    if (res == 1) {
      if (opt == 'c')
        c_counter++;
      else if (opt == 'l') {
        l_indic = 1;
        break;
      }
    }
  }
  fclose(file);

  if (opt == 'c')
    return c_counter;
  else if (opt == 'l')
    return l_indic;
  else
    return -1;
}

void one_file_case(char* argv[], const int files_indices[], char opt,
                   int is_flag) {
  int pat;
  if (is_flag)
    pat = 2;
  else
    pat = 1;

  FILE* file = fopen(argv[files_indices[0]], "r");
  if (opt == 's' && file == NULL)
    return;
  else if (opt != 's' && is_file_null(file, argv[files_indices[0]]))
    return;

  char line[2000] = "";
  int line_number = 0;
  while (fgets(line, 2000, file)) {
    line_number++;
    int res = find_match(line, argv[pat], opt);
    if (res == 1 && opt != 'n')
      printf("%s", line);
    else if (res == 1 && opt == 'n')
      printf("%d:%s", line_number, line);
    end_back_slash_n(line, res);
  }
  fclose(file);
}

void several_files_case(char* argv[], int files_amount,
                        const int files_indices[], char opt, int is_flag) {
  int pat;
  if (is_flag)
    pat = 2;
  else
    pat = 1;

  for (int i = 0; i < files_amount; i++) {
    FILE* file = fopen(argv[files_indices[i]], "r");
    if (opt == 's' && file == NULL)
      continue;
    else if (opt != 's' && is_file_null(file, argv[files_indices[i]]))
      continue;
    char line[2000] = "";
    int line_number = 0;
    while (fgets(line, 2000, file)) {
      line_number++;
      int res = find_match(line, argv[pat], opt);
      if (res == 1 && opt != 'n')
        printf("%s:%s", argv[files_indices[i]], line);
      else if (res == 1 && opt == 'n')
        printf("%s:%d:%s", argv[files_indices[i]], line_number, line);

      end_back_slash_n(line, res);
    }
    fclose(file);
  }
}

int find_match(char line[], char pattern[], char opt) {
  regex_t regex;
  int reti = -2;
  int match = 0;

  if (opt == 'i')
    reti = regcomp(&regex, pattern, REG_ICASE);
  else  // other options
    reti = regcomp(&regex, pattern, 0);

  if (reti) {
    printf("Compilation error\n");
    return -1;
  }

  reti = regexec(&regex, line, 0, NULL, 0);
  if (opt == 'v') {
    if (reti == REG_NOMATCH) match = 1;
  } else {
    if (reti == 0) match = 1;
  }
  regfree(&regex);

  return match;
}

int find_patterns_indices(int argc, char* argv[], int patterns_indices[]) {
  // for e flag
  int index = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
      patterns_indices[index] = i + 1;
      index++;
    }
  }
  return index;
}

int flag_detect(int argc, char* argv[], struct Flags* flag, int* flags_amount) {
  int invalid_option = 0;
  int option;
  while ((option = getopt(argc, argv, "eivclnhsfo")) != -1) {
    switch (option) {
      case 'e':
        flag->e = 1;
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'o':
        flag->o = 1;
        break;
      case 'f':
        flag->f = 1;
        break;
      case '?':
        invalid_option = 1;
        break;
      default:
        break;
    }
  }
  *flags_amount = flag->e + flag->i + flag->v + flag->c + flag->l + flag->n +
                  flag->h + flag->s + flag->f + flag->o;

  return invalid_option;
}

int count_files(int argc, char* argv[], int* files_indices, int flags_amount,
                struct Flags flag) {
  int amount = 0;

  if (flags_amount == 0) {
    for (int i = 2; i < argc; i++) {
      files_indices[amount] = i;
      amount++;
    }
  } else if (flag.e) {
    int first_file_ind = 0;
    for (int i = 3; i < argc; i++) {
      if (strcmp(argv[i - 2], "-e") == 0 && strcmp(argv[i], "-e") != 0) {
        first_file_ind = i;
        break;
      }
    }
    for (int i = first_file_ind; i < argc; i++) {
      files_indices[amount] = i;
      amount++;
    }
  } else {
    for (int i = 3; i < argc; i++) {
      files_indices[amount] = i;
      amount++;
    }
  }
  return amount;
}

void print_usage() {
  fprintf(stderr,
          "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for "
          "more "
          "information.\n");
}

int is_file_null(FILE* file, char filename[]) {
  int res = 0;
  if (file == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory\n", filename);
    res = 1;
  }
  return res;
}

void end_back_slash_n(char line[], int res) {
  if (strchr(line, '\n') == NULL && res == 1) printf("\n");
}