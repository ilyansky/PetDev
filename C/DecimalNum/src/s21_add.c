#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  /* Инициализация слагаемых и нужных переменных */
  s21_decimal val1;
  s21_initDecimal(value_1.bits[3], value_1.bits[2], value_1.bits[1],
                  value_1.bits[0], &val1);

  s21_decimal val2;
  s21_initDecimal(value_2.bits[3], value_2.bits[2], value_2.bits[1],
                  value_2.bits[0], &val2);

  int inMind = 0;    // Единичка в уме
  int overload = 0;  // Флаг переполнения
  int sign1 = (val1.bits[3] & MinusZeroBits) >> 31;  // Знак первого числа
  int sign2 = (val2.bits[3] & MinusZeroBits) >> 31;  // Знак второго числа

  /* Приведение к общему знаменателю */
  int scale1 = (val1.bits[3] >> 16) & Bits3;
  int scale2 = (val2.bits[3] >> 16) & Bits3;

  // У дробной части 1ого числа > знаков
  if (scale1 > scale2) {
    if (!overload) {
      overload = s21_leadToCommonDenominator(&val2, scale1 - scale2);
    }
    // У дробной части 2ого числа > знаков
  } else if (scale1 < scale2) {
    if (!overload) {
      overload = s21_leadToCommonDenominator(&val1, scale2 - scale1);
    }
  }

  /* Проверка на знак - алгоритм суммы или разности? */
  // Операция сложения (в том числе, когда 2 отрицательных числа)
  if (sign1 == sign2) {
    if (!overload) {
      // Складываем 3 инта, один за другим
      s21_sumTwoInts(val1.bits[0], val2.bits[0], &inMind, result, 0);
      s21_sumTwoInts(val1.bits[1], val2.bits[1], &inMind, result, 1);
      s21_sumTwoInts(val1.bits[2], val2.bits[2], &inMind, result, 2);
      result->bits[3] |= val1.bits[3];  // Здесь происходит установка знака

      // Случай переполения
      if (inMind) {
        overload = 1;
      }
    }

    /* Краевые случаи */
    // В случае переполнения заполняем единицами
    if (overload) {
      result->bits[0] = MaxIntMinusOne;
      result->bits[1] = MaxInt;
      result->bits[2] = MaxInt;
      result->bits[3] = val1.bits[3];
    }

    // Операция вычитания (здесь не может быть переполнения)
  } else {
    // Инициализируем начальные значения у большего и меньшего чисел
    s21_decimal greaterModuleVal;
    s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &greaterModuleVal);
    s21_decimal lessModuleVal;
    s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &lessModuleVal);

    // Находим большее по модулю число
    int num = s21_findGreatestVal(val1, val2);

    // |val1| = |val2|
    if (num == 1) {
      s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, result);

      // |val1| > |val2|
    } else if (num == 2) {
      s21_initDecimal(val1.bits[3], val1.bits[2], val1.bits[1], val1.bits[0],
                      &greaterModuleVal);

      s21_initDecimal(val2.bits[3], val2.bits[2], val2.bits[1], val2.bits[0],
                      &lessModuleVal);

      // |val1| < |val2|
    } else if (num == 3) {
      s21_initDecimal(val2.bits[3], val2.bits[2], val2.bits[1], val2.bits[0],
                      &greaterModuleVal);

      s21_initDecimal(val1.bits[3], val1.bits[2], val1.bits[1], val1.bits[0],
                      &lessModuleVal);
    }

    // Последовательно вычитаем инты
    if (!overload) {
      s21_subTwoInts(greaterModuleVal.bits[0], lessModuleVal.bits[0], &inMind,
                     result, 0);
      s21_subTwoInts(greaterModuleVal.bits[1], lessModuleVal.bits[1], &inMind,
                     result, 1);
      s21_subTwoInts(greaterModuleVal.bits[2], lessModuleVal.bits[2], &inMind,
                     result, 2);
      result->bits[3] |= greaterModuleVal.bits[3];
    }
  }

  /* Случай отрицательной бесконечности -INF */
  if (sign1 == sign2 && sign1 == 1 && overload) overload = 2;

  return overload;
}

void s21_sumTwoInts(int num1, int num2, int *inMind, s21_decimal *result,
                    int ind) {
  for (int i = 0; i < 32; i++) {
    int bit1 = num1 & 1;
    int bit2 = num2 & 1;

    // Вычисление суммы битов, операции идут слева направо
    int res = bit1 ^ bit2 ^ *inMind;

    // Присваиваем элементу массива бит, идем с конца
    result->bits[ind] |= (res << i);

    // В любом из случаев в скобках inMind = 1, иначе - 0
    *inMind = (bit1 & bit2) | (bit1 & *inMind) | (bit2 & *inMind);

    num1 >>= 1;
    num2 >>= 1;
  }
}

void s21_subTwoInts(int num1, int num2, int *inMind, s21_decimal *result,
                    int ind) {
  for (int i = 0; i < 32; i++) {
    int bit1 = num1 & 1;
    int bit2 = num2 & 1;

    int temp = bit1;  // Сохраняем начальное значение первого бита
    bit1 ^= *inMind;  // Вычитаем единичку в уме, если она есть

    // Вычисление разности битов, операции идут слева направо
    int res = bit1 ^ bit2;

    // Значение inMind на следующей итерации
    if ((!temp && !bit2 && *inMind == 1) || (!temp && bit2 && *inMind == 0) ||
        (!temp && bit2 && *inMind == 1) || (temp && bit2 && *inMind == 1)) {
      *inMind = 1;
    } else {
      *inMind = 0;
    }

    // Присваиваем элементу массива бит, идем с конца
    result->bits[ind] |= (res << i);

    num1 >>= 1;
    num2 >>= 1;
  }
}

int s21_mulNumBy2(s21_decimal *num) {
  int inMind[3] = {0, 0, 0};
  int overload = 0;

  // Если единичка на 31 бите - значение в уме для данного инта = 1
  for (int i = 0; i < 3; i++) {
    if (num->bits[i] & OneAt31) {
      inMind[i] = 1;
    }
  }

  // Сдвиг каждого инта на 1 бит. Если это не нулевой инт - присвоить единичку
  // или нолик нулевому биту инта
  for (int i = 0; i < 3; i++) {
    num->bits[i] <<= 1;
    if (i != 0) {
      num->bits[i] |= inMind[i - 1];
    }
  }

  // Overload case
  if (inMind[2] == 1) {
    overload = 1;
  }

  return overload;
}

int s21_mulNumBy10(s21_decimal *num) {
  int overload = 0;
  int exitFlag = 0;

  // Инициализируем десятку, временную перерменную и результат
  s21_decimal ten;
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, TenBits, &ten);

  s21_decimal temp;
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp);

  s21_decimal res;
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &res);

  int bitsAmount = s21_countBits(*num);
  int bitsCounter = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      bitsCounter++;
      if (num->bits[i] & (1 << j)) {
        // В первый раз, когда трекнется overload - в переменную запишется 1,
        // далее трекать overload не надо
        if (!overload) {
          overload = s21_add(temp, ten, &res);
        }

        if (!overload) {
          // Обновление temp актуальным значением
          temp.bits[0] = res.bits[0];
          temp.bits[1] = res.bits[1];
          temp.bits[2] = res.bits[2];
        }
      }
      // Присваиваем вх. числу результат умножения на 10 на ласт итерации
      if (bitsCounter == bitsAmount) {
        num->bits[0] = temp.bits[0];
        num->bits[1] = temp.bits[1];
        num->bits[2] = temp.bits[2];
        exitFlag = 1;
        break;
      } else {
        // Иначе - обнуляем res
        s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &res);
      }

      // На каждой итерации умножаем десятку на 2, если overload равен 0
      if (!overload) {
        overload = s21_mulNumBy2(&ten);
      }
    }
    if (exitFlag) break;
  }
  return overload;
}

int s21_leadToCommonDenominator(s21_decimal *num, int amount) {
  int overload = 0;

  // Умножение числа на 10 |scale1 - scale2| | ADDME добавить деление на
  // 10
  for (int i = 0; i < amount; i++) {
    if (!overload) {
      overload = s21_mulNumBy10(num);
    }
  }
  if (!overload) {
    int updScale =
        FindScale(num->bits[3]) + amount;  // Расчет обновленного скейла
    // Присвоение обновленного скейла

    num->bits[3] &= MinusZeroBits;  // Обнуляем 3ий инт

    num->bits[3] |= updScale << 16;  // Присваиваем обновленный скейл
  }

  return overload;
}

void s21_initDecimal(int num3, int num2, int num1, int num0, s21_decimal *num) {
  num->bits[3] = num3;
  num->bits[2] = num2;
  num->bits[1] = num1;
  num->bits[0] = num0;
}

// void s21_printDecimalNum(s21_decimal num) {
//   for (int i = 3; i >= 0; i--) {
//     for (int j = 31; j >= 0; j--) {
//       int bit = (num.bits[i] >> j) & 1;
//       printf("%d", bit);
//     }
//     printf(" ");
//   }
// }

int s21_countBits(s21_decimal num) {
  int count = 0;
  int previousIntNotNil = 0;
  int check = 0;

  for (int i = 0; i < 3; i++) {
    while (num.bits[i] > 0) {
      if (i != 0 && previousIntNotNil && !check) {
        count = i * 32;
        check = 1;
      }
      previousIntNotNil = 1;
      count++;
      num.bits[i] >>= 1;
    }
    check = 0;
  }

  return count;
}

int s21_findGreatestVal(s21_decimal val1, s21_decimal val2) {
  int result = 0;

  val1.bits[3] &= ZeroAt31;
  val2.bits[3] &= ZeroAt31;

  if (s21_is_equal(val1, val2)) {
    result = 1;  // Они равны
  } else if (s21_is_greater(val1, val2)) {
    result = 2;  // Первый больше второго по модулю
  } else {
    result = 3;  // Второй больше первого по модулю
  }

  return result;
}
