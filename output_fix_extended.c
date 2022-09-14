#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main() {
	clock_t begin_dtime = clock();
	clock_t end_dtime;
	double exec_time;
	int32_t __register1__;
	int32_t __register2__;
	int32_t __register3__;
	int32_t __register4__;
	int32_t __register5__;
	int8_t res;
	int32_t tmp_fix_6;
	int32_t tmp_fix_5;
	int32_t s_lat1;
	int32_t lat1;
	int32_t lat2;
	int32_t tmp_fix_4;
	int32_t tmp_fix_1;
	int32_t c_lat1;
	int32_t tmp_fix_3;
	int32_t c_lat2;
	int32_t lon2;
	int32_t lon1;
	int32_t dLon;
	int32_t s_dLon;
	int32_t s_lat2;
	int32_t c_dLon;
	int32_t tmp_fix_2;
	lat1 = 1677722;
	lat2 = 6291456;
	lon1 = 1;
	lon2 = -3277;
	__register1__ = lon2 << 1; // -22 -> -21
	__register2__ = lon1 << 1; // -22 -> -21
	dLon = __register1__ - __register2__; // <0, 22> = <-4, 19> - <0, 23>

/* FPGen_Sin Begin */

	__register1__ = (int32_t) lat1 * lat1; // <-3, 13> = <-2, 22> * <-2, 22>
	__register1__ = __register1__ << 31; // -46 -> -15
	__register3__ = (int32_t) __register1__;

	__register1__ = __register3__ >> 28; // 16 -> -12
	__register2__ = 1536 >> 20; // 8 -> -12
	__register4__ = (int) ( __register1__ * ( 1 << -12 ) ) / __register2__; // <0, 13> = <-3, 13> / <2, 3>

	__register1__ = 1024 >> 21; // 10 -> -11
	__register2__ = __register4__ >> 11; // 0 -> -11
	__register5__ = __register1__ - __register2__; // <1, 13> = <0, 1> - <0, 0>

	__register1__ = (int32_t) lat1 * __register5__; // <0, 13> = <-2, 22> * <1, 13>
	__register1__ = __register1__ >> 1; // -11 -> -12
	s_lat1 = (int32_t) __register1__;

/* FPGen_Sin End */

/* FPGen_Cos Begin */

	__register1__ = (int32_t) lat1 * lat1; // <-3, 15> = <-2, 24> * <-2, 24>
	__register1__ = __register1__ << 33; // -50 -> -17
	__register3__ = (int32_t) __register1__;

	__register1__ = (int32_t) __register3__ * 64; // <-4, 15> = <-3, 15> * <-2, -2>
	__register1__ = __register1__ >> 44; // 26 -> -18
	__register4__ = (int32_t) __register1__;

	__register1__ = 1024 >> 23; // 10 -> -13
	__register2__ = __register4__ >> 32; // 19 -> -13
	c_lat1 = __register1__ - __register2__; // <1, 15> = <0, 1> - <-4, 15>

/* FPGen_Cos End */

/* FPGen_Sin Begin */

	__register1__ = (int32_t) lat2 * lat2; // <-1, 15> = <-1, 24> * <-1, 24>
	__register1__ = __register1__ << 33; // -48 -> -15
	__register3__ = (int32_t) __register1__;

	__register1__ = __register3__ >> 30; // 16 -> -14
	__register2__ = 1536 >> 22; // 8 -> -14
	__register4__ = (int) ( __register1__ * ( 1 << -14 ) ) / __register2__; // <0, 15> = <-1, 15> / <2, 3>

	__register1__ = 1024 >> 23; // 10 -> -13
	__register2__ = __register4__ >> 13; // 0 -> -13
	__register5__ = __register1__ - __register2__; // <1, 15> = <0, 1> - <0, 0>

	__register1__ = (int32_t) lat2 * __register5__; // <1, 15> = <-1, 24> * <1, 15>
	__register1__ = __register1__ >> 3; // -10 -> -13
	s_lat2 = (int32_t) __register1__;

/* FPGen_Sin End */

/* FPGen_Cos Begin */

	__register1__ = (int32_t) lat2 * lat2; // <-1, 13> = <-1, 22> * <-1, 22>
	__register1__ = __register1__ << 31; // -44 -> -13
	__register3__ = (int32_t) __register1__;

	__register1__ = (int32_t) __register3__ * 64; // <-2, 13> = <-1, 13> * <-2, -2>
	__register1__ = __register1__ >> 36; // 22 -> -14
	__register4__ = (int32_t) __register1__;

	__register1__ = 1024 >> 21; // 10 -> -11
	__register2__ = __register4__ >> 26; // 15 -> -11
	c_lat2 = __register1__ - __register2__; // <1, 13> = <0, 1> - <-2, 13>

/* FPGen_Cos End */

/* FPGen_Sin Begin */

	__register1__ = (int32_t) dLon * dLon; // <1, 13> = <0, 22> * <0, 22>
	__register1__ = __register1__ << 31; // -42 -> -11
	__register3__ = (int32_t) __register1__;

	__register1__ = __register3__ >> 24; // 12 -> -12
	__register2__ = 1536 >> 20; // 8 -> -12
	__register4__ = (int) ( __register1__ * ( 1 << -12 ) ) / __register2__; // <0, 13> = <1, 13> / <2, 3>

	__register1__ = 1024 >> 21; // 10 -> -11
	__register2__ = __register4__ >> 11; // 0 -> -11
	__register5__ = __register1__ - __register2__; // <1, 13> = <0, 1> - <0, 0>

	__register1__ = (int32_t) dLon * __register5__; // <2, 13> = <0, 22> * <1, 13>
	__register1__ = __register1__ >> 1; // -9 -> -10
	s_dLon = (int32_t) __register1__;

/* FPGen_Sin End */

/* FPGen_Cos Begin */

	__register1__ = (int32_t) dLon * dLon; // <1, 13> = <0, 22> * <0, 22>
	__register1__ = __register1__ << 31; // -42 -> -11
	__register3__ = (int32_t) __register1__;

	__register1__ = (int32_t) __register3__ * 64; // <0, 13> = <1, 13> * <-2, -2>
	__register1__ = __register1__ >> 32; // 20 -> -12
	__register4__ = (int32_t) __register1__;

	__register1__ = 1024 >> 21; // 10 -> -11
	__register2__ = __register4__ >> 24; // 13 -> -11
	c_dLon = __register1__ - __register2__; // <1, 13> = <0, 1> - <0, 13>

/* FPGen_Cos End */

	__register1__ = (int32_t) c_lat2 * s_dLon; // <-1, 13> = <-1, 13> * <-1, 13>
	__register1__ = __register1__ << 13; // -26 -> -13
	tmp_fix_1 = (int32_t) __register1__;

	__register1__ = (int32_t) c_lat1 * s_lat2; // <-1, 15> = <-1, 15> * <-1, 15>
	__register1__ = __register1__ << 15; // -30 -> -15
	tmp_fix_2 = (int32_t) __register1__;

	__register1__ = (int32_t) c_lat2 * s_lat1; // <-2, 13> = <-1, 13> * <-2, 13>
	__register1__ = __register1__ << 13; // -27 -> -14
	tmp_fix_3 = (int32_t) __register1__;

	__register1__ = (int32_t) tmp_fix_3 * c_dLon; // <-3, 13> = <-2, 13> * <-2, 13>
	__register1__ = __register1__ << 13; // -28 -> -15
	tmp_fix_4 = (int32_t) __register1__;

	__register1__ = tmp_fix_2 << 1; // -15 -> -14
	__register2__ = tmp_fix_4 << 1; // -15 -> -14
	tmp_fix_5 = __register1__ - __register2__; // <-2, 13> = <-1, 15> - <-3, 13>

	__register1__ = tmp_fix_1 << 1; // -13 -> -12
	__register2__ = tmp_fix_5 << 2; // -14 -> -12
	tmp_fix_6 = (int) ( __register1__ * ( 1 << -12 ) ) / __register2__; // <0, 13> = <-1, 13> / <-2, 13>

/* FPGen_Atan Begin */

	__register1__ = (int32_t) tmp_fix_6 * tmp_fix_6; // <1, 4> = <0, 13> * <0, 13>
	__register1__ = __register1__ << 22; // -24 -> -2
	__register3__ = (int32_t) __register1__;

	__register1__ = tmp_fix_6 << 9; // -12 -> -3
	__register2__ = 1536 >> 12; // 9 -> -3
	__register4__ = (int) ( __register1__ * ( 1 << -3 ) ) / __register2__; // <0, 4> = <0, 13> / <1, 2>

	__register1__ = (int32_t) __register3__ * __register4__; // <2, 4> = <1, 4> * <0, 0>
	__register1__ = __register1__ >> 4; // 3 -> -1
	__register5__ = (int32_t) __register1__;

	__register1__ = tmp_fix_6 << 12; // -12 -> 0
	__register2__ = __register5__ >> 2; // 2 -> 0
	res = __register1__ - __register2__; // <3, 4> = <0, 13> - <2, 4>

/* FPGen_Atan End */

	printf("%lf\n", res);
	end_dtime = clock();
	exec_time = (double) (end_dtime - begin_dtime) / CLOCKS_PER_SEC;
	exec_time = exec_time * 1000;
	printf("%.3lf\n", exec_time);

	return 0;
}
