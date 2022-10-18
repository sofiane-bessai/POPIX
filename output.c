#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main() {
	float res;
	float tmp_fix_5;
	float tmp_fix_4;
	float tmp_fix_2;
	float tmp_fix_3;
	float t1;
	float tmp_fix_1;
	float T;
	float v;
	float u;
	u = 10;
	v = 1000;
	T = 20;
	tmp_fix_1 = 0.60000000 * T;
	t1 = 331.40000000 + tmp_fix_1;
	tmp_fix_2 = -1 * t1;
	tmp_fix_3 = t1 + u;
	tmp_fix_4 = tmp_fix_2 * v;
	tmp_fix_5 = tmp_fix_3 * tmp_fix_3;
	res = tmp_fix_4 / tmp_fix_5;

	return 0;
}
