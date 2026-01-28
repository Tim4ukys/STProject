#include "arithmetic.h"
#include <memory.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define HI_W(x) (x >> 16)
#define LO_W(x) (x & 0xffff)
#define MSb(x)  (x >> 31)

void ll_assign_longlong(Longlong* pll, uint64_t x) {
    if (!pll)
        return;

    pll->lo = x & UINT32_MAX;
    pll->hi = x >> 32;
}

void ll_assign(Longlong* pll, Longlong* pll2) {
    if (!pll || !pll2)
        return;

    memcpy(pll, pll2, sizeof(Longlong));
}

void ll_assign_long(Longlong* pl, int32_t x) {
    if (!pl)
        return;

    pl->hi = (x >> 31) ? -1 : 0;
    pl->lo = x;
}

void ll_inc(Longlong* pl) {
    if (!pl)
        return;
    
    if (!++pl->lo)
        pl->hi++;
}

void ll_dec(Longlong* pl) {
    if (!pl)
        return;

    if (!pl->lo) {
        if (!pl->hi)
            pl->lo--;
        pl->hi--;
    } else {
        pl->lo--;
    }
}

void ll_negate(Longlong* pl) {
    if (!pl)
        return;

    pl->hi = ~pl->hi;
    pl->lo = ~pl->lo;
    ll_inc(pl);
}

void ll_abs(Longlong* pl) {
    if (!pl)
        return;

    if (ll_sign(pl) == -1)
        ll_negate(pl);
}

void ll_shiftleft(Longlong* pl, int8_t n) {
    if (!pl || !n)
        return;
    else if (n < 0)
        return ll_shiftright(pl, -n);

    //pl->hi = ((pl->hi << n) & (((1 << (32 - n + 1)) - 1) << n)) | (pl->lo >> (32 - n));
    if (n >= 64) {
        pl->lo = 0;
        pl->hi = 0;
    } else if (n < 32) {
        pl->hi = (pl->hi << n) | (pl->lo >> (32 - n));
        pl->lo <<= n;
    } else {
        pl->hi = pl->lo << (32 - n);
        pl->lo = 0;
    }
}

void ll_shiftright(Longlong* pl, int8_t n) {
    if (!pl || !n)
        return;
    else if (n < 0)
        return ll_shiftleft(pl, -n);

    if (n >= 64) {
        pl->hi = 0;
        pl->lo = 0;
    }
    else if (n < 32) {
        pl->lo = (pl->lo >> n) | (pl->hi << (32 - n));
        pl->hi >>= n;
    } else {
        pl->lo = pl->hi >> (32 - n);
        pl->hi = 0;
    }
}

int ll_sign(Longlong* pl) {
    if (!pl || !(pl->hi || pl->lo))
        return 0;

    return (pl->hi >> 31) ? -1 : 1;
}

void ll_ushiftright(Longlong* pl, int8_t n) {
    if (!pl || !n)
        return;
    else if (n < 0)
        return ll_shiftleft(pl, -n);

    const int sign = ll_sign(pl);
    ll_shiftright(pl, n);
    if (sign < 0) {
        if (n < 32) {
            pl->hi |= (((1 << n) - 1) << (32 - n));   
        } else if (n < 64) {
            pl->hi = -1;
            n -= 32;
            pl->lo |= (((1 << n) - 1) << (32 - n));
        } else {
            pl->hi = -1;
            pl->lo = -1;
        }
    }
}

int ll_eq(Longlong* px, Longlong* py) {
    if (!px || !py) 
        return LL_FAIL;
    return px->hi == py->hi && px->lo == py->lo;
}

int ll_neq(Longlong* px, Longlong* py) {
    if (!px || !py) 
        return LL_FAIL;
    return px->hi != py->hi && px->lo != py->lo;
}

int ll_lt(Longlong* px, Longlong* py) {
    if (!px || !py) 
        return LL_FAIL;
    return px->hi < py->hi || (px->hi == py->hi && px->lo < py->lo);
}

int ll_gt(Longlong* px, Longlong* py) {
    if (!px || !py) 
        return LL_FAIL;
    return px->hi > py->hi || (px->hi == py->hi && px->lo > py->lo);
}

int ll_le(Longlong* px, Longlong* py) {
    if (!px || !py)
        return LL_FAIL;
    return px->hi <= py->hi || (px->hi == py->hi && px->lo <= py->lo);
}

int ll_ge(Longlong* px, Longlong* py) {
    if (!px || !py)
        return LL_FAIL;
    return px->hi >= py->hi || (px->hi == py->hi && px->lo >= py->lo);
}


void ll_and(Longlong* pres, const Longlong* px, const Longlong* py) {
    pres->hi = px->hi & py->hi;
    pres->lo = px->lo & py->lo;
}

void ll_or(Longlong* pres, const Longlong* px, const Longlong* py) {
    pres->hi = px->hi | py->hi;
    pres->lo = px->lo | py->lo;
}

void ll_xor(Longlong* pres, const Longlong* px, const Longlong* py) {
    pres->hi = px->hi ^ py->hi;
    pres->lo = px->lo ^ py->lo;
}


void ll_add(Longlong* pres, Longlong* px, Longlong* py) {
    pres->hi = px->hi;
    pres->lo = px->lo + py->lo;
    __asm {
        jnc of
    }
    pres->hi += 1;
of:
    pres->hi += py->hi;
}

void ll_add1(Longlong* pres, Longlong* px, int32_t y) {
    pres->hi = px->hi;
    pres->lo = px->lo + y;
    __asm {
        jnc of
    }
    pres->hi += 1;
of:
    return;
}

void ll_sub(Longlong* pres, Longlong* px, Longlong* py) {
    pres->hi = px->hi;
    pres->lo = px->lo - py->lo;
    __asm {
        jnc of
    }
    pres->hi -= 1;
of:
    pres->hi -= py->hi;
}

void ll_sub1(Longlong* pres, Longlong* px, int32_t y) {
    pres->hi = px->hi;
    pres->lo = px->lo - y;
    __asm {
        jnc of
    }
    pres->hi -= 1;
of:
    return;
}


void ll_umul1(Longlong* pres, uint32_t x, uint32_t y) {
    ll_assign_long(pres, 0);
    ll_add1(pres, pres, HI_W(x) * HI_W(y));
    ll_shiftleft(pres, 16);
    ll_add1(pres, pres, HI_W(x) * LO_W(y));
    ll_add1(pres, pres, HI_W(y) * LO_W(x));
    ll_shiftleft(pres, 16);
    ll_add1(pres, pres, LO_W(x) * LO_W(y));
}

void ll_mul1(Longlong* pres, int32_t x, int32_t y) {
    ll_umul1(pres, abs(x), abs(y));

    if ((MSb(x) != MSb(y)) != MSb(pres->hi)) {
        if (MSb(pres->hi))
            pres->hi &= INT32_MAX;
        else
            pres->hi |= 1 << 31;
    }
}

void ll_mul(Longlong* pres, Longlong* px, Longlong* py) {
    ll_assign_long(pres, 0);
    Longlong tmp, a, b;
    ll_assign(&a, px);
    ll_assign(&b, py);
    ll_abs(&a);
    ll_abs(&b);

    ll_umul1(&tmp, a.hi, b.lo);
    ll_add(pres, pres, &tmp);
    ll_umul1(&tmp, a.lo, b.hi);
    ll_add(pres, pres, &tmp);
    ll_shiftleft(pres, 32);
    ll_umul1(&tmp, a.lo, b.lo);
    ll_add(pres, pres, &tmp);

    /*if ((MSb(px->hi) != MSb(py->hi)) != MSb(pres->hi))
        pres->hi |= 1 << 31;*/
    if ((MSb(px->hi) != MSb(py->lo)) != MSb(pres->hi)) {
        if (MSb(pres->hi))
            pres->hi &= INT32_MAX;
        else
            pres->hi |= 1 << 31;
    }
}

void ll_udiv0(Longlong* pres, Longlong* px, uint16_t sy) {
    ll_assign_long(pres, 0);
    pres->lo = px->hi / sy;
    ll_shiftleft(pres, 16);
    uint32_t d = ((px->hi % sy) << 16) + HI_W(px->lo);
    ll_add1(pres, pres, d / sy);
    ll_shiftleft(pres, 16);
    d = ((d % sy) << 16) + LO_W(px->lo);
    ll_add1(pres, pres, d / sy);
}

void ll_udiv1(Longlong* pres, Longlong* px, uint32_t ly) {
    ll_assign_long(pres, 0);

    uint16_t x[5];
    memset(x, 0, sizeof(x));
    memcpy(x, px, sizeof(Longlong));
    // D1. нормализация
    while (!(ly >> 31)) {
        ly <<= 1;
        __asm {
            push edi
            mov edi, 4
            shl [x+edi*2], 1

            cum:
            shl [x+edi*2-2], 1
            jnc shot
            inc [x+edi*2]
            shot:
            dec edi
            jnz cum
            pop esi
        }
    }

    for (size_t j = 0; j < 3; j++) {
        // D3. вычисление q 
        uint32_t p = *(uint32_t*)(x + 3 - j);
        uint32_t q = p / LO_W(ly), r = p % LO_W(ly);

        while (q * LO_W(ly) > ((r << 16) + *(x + 2 - j))) {
            r += HI_W(ly);
            q -= 1;
        }

        // D4. Умножить и вычесть
        // y = U4U3U2
        Longlong y, z;
        ll_assign_long(&y, 0);
        memcpy(&y, x + 2 - j, sizeof(uint16_t) * 3);

        // z = q*V1V2
        ll_umul1(&z, q, ly);

        ll_sub(&y, &y, &z);
        
        // D5. Проверка остатка
        while (ll_sign(&y) == -1) {
            // D6. Компенсировать сложение
            ll_add1(&y, &y, ly);
            q--;
        }

        // D4. Присваиваю
        memcpy(x + 2 - j, &y, sizeof(uint16_t)*3);

        ll_shiftleft(pres, 16);
        ll_add1(pres, pres, q);
    }
}
