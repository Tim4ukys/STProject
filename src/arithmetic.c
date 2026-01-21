#include "arithmetic.h"
#include <memory.h>

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


