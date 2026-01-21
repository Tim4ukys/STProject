#include "main.h"

int main() {
    Longlong* pa = malloc(sizeof(Longlong));
    ll_assign_long(pa, INT32_MAX);
    ll_shiftleft(pa, 32);
    ll_negate(pa);
    ll_ushiftright(pa, 32);
	free(pa);
	return 0;
}