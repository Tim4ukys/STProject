#ifndef __STPROJECT_ARITHMETIC_H__
#define __STPROJECT_ARITHMETIC_H__

#include <stdint.h>

#define LL_FAIL -1

typedef struct {
    uint32_t lo, hi;
} Longlong;

/* присваивает (*pll) <- (*pll2) */
void ll_assign(Longlong* pll, Longlong* pll2);

/* присваивает (*pl1) <- x (32-битное число) */
void ll_assign_long(Longlong* pl, int32_t x);

/* увеличение на 1 */
void ll_inc(Longlong* pl);

/* уменьшение на 1 */
void ll_dec(Longlong* pl);

/* (*pl) = -(*pl) */
void ll_negate(Longlong* pl);

/* (*pl) = |(*pl)| */
void ll_abs(Longlong* pl);

/* сдвиг влево числа (*pl) на n разрядов */
void ll_shiftleft(Longlong* pl, int8_t n);

/* сдвиг вправо числа (*pl) на n разрядов */
void ll_shiftright(Longlong* pl, int8_t n);

/* беззнаковый сдвиг вправо числа (*pl) на n разрядов */
void ll_ushiftright(Longlong* pl, int8_t n);

/* знак числа (-1 если меньше 0, 0 если 0, 1 если больше 0) */
int ll_sign(Longlong* pl);

/* операторы сравнения (возвращают 1, если условие истинно, иначе 0) */
int ll_eq(Longlong* px, Longlong* py);          /* x == y */
int ll_neq(Longlong* px, Longlong* py);         /* x != y */
int ll_lt(Longlong* px, Longlong* py);          /* x < y */
int ll_gt(Longlong* px, Longlong* py);          /* x > y */
int ll_le(Longlong* px, Longlong* py);          /* x <= y */
int ll_ge(Longlong* px, Longlong* py);          /* x >= y */

/* побитовые операторы над x и y (результат в res)  */
void ll_and(Longlong* pres, const Longlong* px, const Longlong* py);
void ll_or(Longlong* pres, const Longlong* px, const Longlong* py);
void ll_xor(Longlong* pres, const Longlong* px, const Longlong* py);

/* сложение */
void ll_add(Longlong* pres, Longlong* px, Longlong* py);
void ll_add1(Longlong* pres, Longlong* px, int32_t y);

/* вычитание */
void ll_sub(Longlong* pres, Longlong* px, Longlong* py);
void ll_sub1(Longlong* pres, Longlong* px, int32_t y);

/* умножение */
void ll_mul(Longlong* pres, Longlong* px, Longlong* py);
void ll_mul1(Longlong* pres, int32_t x, int32_t y);
void ll_umul1(Longlong* pres, uint32_t x, uint32_t y); /* беззнаковое */

/* беззнаковое деление */
void ll_udiv0(Longlong* pres, Longlong* px, int16_t sy);
void ll_udiv1(Longlong* pres, Longlong* px, uint32_t ly);
void ll_udiv(Longlong* pres, Longlong* px, Longlong* py);

/* деление со знаком */
void ll_div1(Longlong* pres, Longlong* px, int32_t ly);
void ll_div(Longlong* pres, Longlong* px, Longlong* py);

#endif