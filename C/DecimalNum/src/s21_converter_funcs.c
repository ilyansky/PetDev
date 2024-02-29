#include "s21_decimal.h"

int check_number(float src, int exp) {
  int res = 0;
  if (isinf(src) || isnan(src)) {
    res = 0;
  } else if (exp < -94 || exp > 95)
    res = 0;
  else
    res = 1;
  return res;
}

void s21_setZero(s21_decimal *numDec) {
  numDec->bits[0] = 0;
  numDec->bits[1] = 0;
  numDec->bits[2] = 0;
  numDec->bits[3] = 0;
}

unsigned int s21_GetSign(float src) { return *(unsigned int *)&src >> 31; }

void parse_float(float num, float *new_num, int *scale) {
  char char_float[20] = {'\0'}, char_scale[20] = {'\0'}, char_num[10] = "";
  int j = 0;
  sprintf(char_float, "%e", num);
  for (int i = 0; char_float[i] != 'e'; i++) {
    if (char_float[i] != '.') {
      char_num[j] = char_float[i];
      j++;
    }
  }
  *new_num = atoi(char_num) * pow(10, -6);
  memcpy(char_scale, char_float + j + 3, 2);
  *scale = atoi(char_scale);
}
