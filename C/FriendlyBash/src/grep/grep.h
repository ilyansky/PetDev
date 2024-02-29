#ifndef GREP_H
#define GREP_H

#define LINES 1000
#define LEN 1000

// #include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

// Grep without flags
void grep_without_flags(char* argv[], int files_amount,
                        const int files_indices[]);

// Grep with 1 flag
void grep_with_one_flag(int argc, char* argv[], struct Flags flag,
                        int files_amount, int files_indices[]);

// Flag funcs
void e_flag(int argc, char* argv[], int files_amount,
            const int files_indices[]);

void i_flag(char* argv[], int files_amount, int files_indices[]);

void v_flag(char* argv[], int files_amount, int files_indices[]);

void c_flag(char* argv[], int files_amount, int files_indices[]);

void l_flag(char* argv[], int files_amount, int files_indices[]);

void n_flag(char* argv[], int files_amount, int files_indices[]);

void h_flag(char* argv[], int files_amount, int files_indices[]);

void s_flag(char* argv[], int files_amount, int files_indices[]);

void f_flag(char* argv[], int files_amount, int files_indices[]);

void o_flag(char* argv[], int files_amount, int files_indices[]);

// Sup funcs
void many_patterns_case(char* argv[], int files_amount,
                        const int files_indices[], int patterns_indices[],
                        int patterns_amount, char patterns[][LEN], char opt);

int is_backslash_pattern(char patterns[][LEN], int patterns_amount);

int find_patterns(char patterns[][LEN], char filename[]);  // for f flag

int collect_info(char filename[], char pattern[], char opt);  // for cl

void one_file_case(char* argv[], const int files_indices[], char opt,
                   int is_flag);  // for eivn

void several_files_case(char* argv[], int files_amount,
                        const int files_indices[], char opt,
                        int is_flag);  // for eivn

int find_patterns_indices(int argc, char* argv[],
                          int patterns_indices[]);  // for flag e

int find_match(char line[], char pattern[], char opt);
int flag_detect(int argc, char* argv[], struct Flags* flag, int* flags_amount);
int count_files(int argc, char* argv[], int* files_indices, int flags_amount,
                struct Flags flag);
void print_usage();
int is_file_null(FILE* file, char filename[]);
void end_back_slash_n(char line[], int res);

#endif
