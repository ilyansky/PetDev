#include "s21_math.h"

// 1 ABS
int s21_abs(int x) { return (x >= 0) ? x : -x; }

// 2 ASIN
long double s21_asin(double x) {
  long double asinus = 0;
  if (x < -1.0 || x > 1.0 || S21_IS_NAN(x)) {
    asinus = S21_NAN;
  } else {
    asinus = s21_atan(x / (s21_sqrt(1 - x * x)));
  }

  return asinus;
}

// 3 ACOS
long double s21_acos(double x) {
  long double acosinus = 0;
  if (x >= 0 && x <= 1) {
    acosinus = s21_atan(s21_sqrt(1 - x * x) / x);
  } else if (x >= -1 && x < 0) {
    acosinus = S21_PI + s21_atan(s21_sqrt(1 - x * x) / x);
  } else {
    acosinus = S21_NAN;
  }

  return acosinus;
}

// 4 ATAN
long double s21_atan(double x) {
  long double atang = 0;
  if (S21_IS_NAN(x))
    atang = S21_NAN;
  else if (x == NEG_INF)
    atang = -1.570796;
  else if (x == POS_INF)
    atang = 1.570796;
  else if (-1 < x && x < 1) {
    for (register int i = 0; i < 1000; i++)
      atang += s21_pow_int(-1, i) * s21_pow_int(x, 1 + (2 * i)) / (1 + (2 * i));
  } else {
    for (register int i = 0; i < 1000; i++)
      atang +=
          s21_pow_int(-1, i) * s21_pow_int(x, -1 - (2 * i)) / (1 + (2 * i));
    atang = S21_PI * s21_sqrt(x * x) / (2 * x) - atang;
  }
  return atang;
}

// 5 CEIL
long double s21_ceil(double x) {
  long double res = 0;
  if (S21_IS_NAN(x) || S21_IS_INF(x) || x == (int)x)
    res = x;
  else if (x >= 0)
    res = (long double)((int)(x + 1));
  else if (x < 0 && x > -1.0)
    res = -(long double)((int)(x));
  else
    res = (long double)((int)(x));

  return res;
}

// 6 COS
long double s21_cos(double x) {
  long double cosinus = 1;
  if (S21_IS_INF(x) || S21_IS_NAN(x))
    cosinus = S21_NAN;
  else {
    long double x_res = s21_fmod(x, 2 * S21_PI);
    long double next_term = 1;
    int n = 1;
    while (s21_fabs((double)next_term) > 1e-16) {
      next_term *= (-1) * x_res * x_res / ((2 * n - 1) * (2 * n));
      cosinus += next_term;
      n++;
    }
  }
  return cosinus;
}

// 7 EXP
long double s21_exp(double x) {
  long double res = 1;
  if (x == POS_INF || S21_IS_NAN(x))
    res = x;
  else if (x <= -15)
    res = 0;
  else {
    long double term = 1;
    long double i = 1;
    while (s21_fabs(term) > S21_EPS) {
      term *= x / i;
      i++;
      res += term;
      if (res > __LDBL_MAX__) {
        res = POS_INF;
        break;
      }
    }
  }
  return res;
}

// 8 FABS
long double s21_fabs(double x) {
  long double res = 0;
  if (S21_IS_INF(x))
    res = POS_INF;
  else if (S21_IS_NAN(x))
    res = x;
  else
    res = (x >= 0.000000) ? (long double)x : (long double)(-x);

  return res;
}

// 9 FLOOR
long double s21_floor(double x) {
  long double res = 0;
  if (S21_IS_INF(x) || S21_IS_NAN(x) || x == DBL_MAX)
    res = x;
  else if (x >= 0)
    res = (long double)((int)x);
  else if (x < 0 && x != (int)x)
    res = (long double)((int)(x - 1));
  else
    res = x;
  return res;
}

// 10 FMOD
long double s21_fmod(double x, double y) {
  long double res = 0;
  if (S21_IS_INF(x) || S21_IS_NAN(x) || y == 0 || S21_IS_NAN(y) ||
      (x == 1 && y == 0))
    res = S21_NAN;
  else if (s21_fabs(x) < s21_fabs(y))
    res = (long double)x;
  else if (s21_fabs(x) == s21_fabs(y)) {
    res = 0;
    if (x < 0) res = -res;
  } else if (s21_fabs(x) > s21_fabs(y)) {
    long double temp_x = s21_fabs(x);
    long double temp_y = s21_fabs(y);
    int division = (int)(temp_x / temp_y);
    long double near_x = division * temp_y;
    res = temp_x - near_x;
    if (x < 0) res = -res;
  }
  return (long double)res;
}

// 11 LOG
long double s21_log(double x) {
  long double res = 0;
  int ex = 0;
  if (x == NEG_INF || S21_IS_NAN(x) || x < 0)
    res = NAN;
  else if (x == POS_INF)
    return x;
  else if (x == 0)
    return NEG_INF;
  else {
    for (; x >= S21_EXP; x /= S21_EXP, ex++)
      ;

    for (int i = 0; i < 5000; i++) {
      long double temp = res;
      res = temp + 2 * (x - s21_exp(temp)) / (x + s21_exp(temp));
    }
  }

  return (res + ex);
}

// 12 POW
long double s21_pow(double base, double exp) {
  long double res = 0;
  long double copy_base = base;
  int check = s21_pow_check(base, exp);
  if (check == 1)
    res = 1;
  else if (check == 2)
    res = POS_INF;
  else if (check == 3)
    res = S21_NAN;
  else if (copy_base < 0) {
    copy_base = -copy_base;
    res = s21_exp(exp * s21_log(copy_base));
    if (s21_fmod(exp, 2) != 0) {
      res = -res;
    }
  } else {
    res = s21_exp(exp * s21_log(base));
  }

  return res;
}

// 13 SIN
long double s21_sin(double x) {
  return (S21_IS_INF(x) || S21_IS_NAN(x)) ? S21_NAN : s21_cos((S21_PI / 2) - x);
}

// 14 SQRT
long double s21_sqrt(double x) {
  long double left = 0;
  long double right = s21_fmax(1, x);
  long double mid = (left + right) / 2;
  if (x < 0 || S21_IS_NAN(x))
    mid = S21_NAN;
  else if (x == POS_INF)
    mid = x;
  else {
    while ((mid - left) > S21_EPS) {
      if (mid * mid > x)
        right = mid;
      else
        left = mid;

      mid = (left + right) / 2;
    }
  }

  return mid;
}

// 15 TAN - fix 90 and 270 degrees
long double s21_tan(double x) {
  long double res = 0;
  if (S21_IS_INF(x) || S21_IS_NAN(x) || s21_cos(x) == S21_NAN ||
      s21_sin(x) == S21_NAN || s21_cos(0) == 0)
    res = S21_NAN;
  else
    res = s21_sin(x) / s21_cos(x);
  return res;
}

// Sup funcs
int s21_factorial(int x) {
  int res = 0;
  if (x == 0)
    res = 1;
  else if (x > 0)
    res *= x * s21_factorial(x - 1);
  return res;
}

double s21_fmax(double start, double x) { return (x > start) ? x : start; }

int s21_pow_check(double base, double exp) {
  int res = 0;
  if ((base == -1 && S21_IS_INF(exp)) ||
      (base == 1 && (S21_IS_NAN(exp) || S21_IS_INF(exp))) ||
      ((base == 0 || S21_IS_INF(base)) && exp == 0) ||
      (S21_IS_NAN(base) && exp == 0))
    res = 1;
  else if (base == NEG_INF && exp == POS_INF)
    res = 2;  // infinity
  else if (base < 0 && exp != (int)exp && exp != NEG_INF)
    res = 3;  // NAN

  return res;
}

long double s21_pow_int(double base, long long exp) {
  long double res = 1;
  if ((base == 0 && exp == 0) || (base != 0 && exp == 0)) {
    res = 1;
  } else if (base == 0 && exp == 1) {
    res = 0;
  } else if (base == 0 && exp == -1) {
    res = POS_INF;
  } else {
    for (long long i = 0; i < s21_abs(exp); i++) {
      if (exp > 0) {
        res *= base;
      } else if (exp < 0) {
        res /= base;
      }
    }
  }

  return res;
}