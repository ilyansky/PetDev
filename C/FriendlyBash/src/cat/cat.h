#ifndef CAT_H
#define CAT_H

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Flags {
  int s;
  int e;
  int t;
  int b;
  int n;
  int E;
  int T;
  int v;
};

// Main func
void cat(char filename[], struct Flags flag);

// Sup funcs
int find_last_flag_ind(int amount, char *args[]);
int flags_decompose(char *args[], int last_flag_ind, struct Flags *flag);
int check_flag_correct(char option[]);
void flag_detector(struct Flags *flag, char option[]);

// Test funcs
void test_cat_utility();
void counter(int compare, int *suc, int *fail);
void command_launcher(char custom_com[], char com[]);

// Flags
int s_f(char line[], int *streak_null_lines);
void e_f(char line[]);
void v_f(char sym, char temp[]);
void t_f(char line[]);
void b_f(char line[], int *not_empty_counter, int *pre_not_empty_counter,
         struct Flags flag);
void n_f(int *counter);

void E_f(char line[]);
void T_f(char line[]);

#endif