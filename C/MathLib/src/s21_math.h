#ifndef S21_MATH_H
#define S21_MATH_H

#define S21_PI 3.14159265358979323846264338327
#define TO_RAD S21_PI / 180
#define TOL 0.000001
#define POS_INF (1.0 / 0.0)
#define NEG_INF (-1.0 / 0.0)
#define S21_NAN (0.0 / 0.0)
#define S21_EPS 1e-9
#define S21_IS_NAN(x) (x != x)
#define S21_IS_INF(x) (x == POS_INF || x == NEG_INF)
#define S21_EXP 2.7182818284590452

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int s21_abs(int x);                            // 1
long double s21_asin(double x);                // 2
long double s21_acos(double x);                // 3
long double s21_atan(double x);                // 4
long double s21_ceil(double x);                // 5
long double s21_cos(double x);                 // 6
long double s21_exp(double x);                 // 7
long double s21_fabs(double x);                // 8
long double s21_floor(double x);               // 9
long double s21_fmod(double x, double y);      // 10
long double s21_log(double x);                 // 11
long double s21_pow(double base, double exp);  // 12
long double s21_sin(double x);                 // 13
long double s21_sqrt(double x);                // 14
long double s21_tan(double x);                 // 15

// Sup funcs
int s21_factorial(int x);
double s21_fmax(double start, double x);
int s21_pow_check(double base, double exp);
long double s21_pow_int(double base, long long exp);

#endif
