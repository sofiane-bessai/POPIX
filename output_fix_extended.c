#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main() {
	int32_t __register1__;
	int32_t __register2__;
	int32_t __register3__;
	int32_t __register4__;
	int32_t __register5__;
	int16_t res;
	int16_t tmp_fix_5;
	int16_t tmp_fix_4;
	int16_t tmp_fix_2;
	int16_t tmp_fix_3;
	int16_t t1;
	int16_t tmp_fix_1;
	int16_t T;
	int16_t v;
	int8_t u;
	u = 10;
	v = 1000;
	T = 20;
	__register1__ = (int32_t) 10 * T; // <3, 5> = <-1, 5> * <4, 5>
	__register1__ = __register1__ << 4; // -5 -> -1
	tmp_fix_1 = (int32_t) __register1__;

	__register1__ = 1326 << 1; // -1 -> 0
	__register2__ = tmp_fix_1 << 1; // -1 -> 0
	t1 = __register1__ + __register2__; // <8, 9> = <8, 10> + <3, 5>

	__register1__ = (int32_t) -1 * t1; // <8, 8> = <0, 8> * <8, 8>
	__register1__ = __register1__ << 7; // -6 -> 1
	tmp_fix_2 = (int32_t) __register1__;

	__register1__ = t1 << 1; // 0 -> 1
	__register2__ = u << 1; // 0 -> 1
	tmp_fix_3 = __register1__ + __register2__; // <8, 8> = <8, 9> + <3, 4>

	__register1__ = (int32_t) tmp_fix_2 * v; // <18, 8> = <8, 8> * <9, 8>
	__register1__ = __register1__ << 8; // 3 -> 11
	tmp_fix_4 = (int32_t) __register1__;

	__register1__ = (int32_t) tmp_fix_3 * tmp_fix_3; // <16, 8> = <8, 8> * <8, 8>
	__register1__ = __register1__ << 7; // 2 -> 9
	tmp_fix_5 = (int32_t) __register1__;

	__register1__ = tmp_fix_4 >> 17; // 11 -> -6
	__register2__ = tmp_fix_5 >> 15; // 9 -> -6
	res = (int) ( __register1__ * ( 1 << -6 ) ) / __register2__; // <1, 8> = <18, 8> / <16, 8>


	return 0;
}
