#include "main.h"

int main() {
    Longlong *pa = malloc(sizeof(Longlong) * 3);
    ll_assign_long(pa, -1);
    //ll_assign_long(pa+1, 2);
    ll_add1(pa + 2, pa, 2);
    ll_sub1(pa + 2, pa + 2, 3);
	free(pa);
	return 0;
}