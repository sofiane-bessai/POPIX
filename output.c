#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main() {
	clock_t begin_dtime = clock();
	clock_t end_dtime;
	double exec_time;
	float res;
	float tmp_fix_6;
	float tmp_fix_5;
	float s_lat1;
	float lat1;
	float lat2;
	float tmp_fix_4;
	float tmp_fix_1;
	float c_lat1;
	float tmp_fix_3;
	float c_lat2;
	float lon2;
	float lon1;
	float dLon;
	float s_dLon;
	float s_lat2;
	float c_dLon;
	float tmp_fix_2;
	lat1 = 0.40000000;
	lat2 = 0.75000000;
	lon1 = 1;
	lon2 = -0.10000000;
	dLon = lon2 - lon1;
	s_lat1 = sin(lat1);
	c_lat1 = cos(lat1);
	s_lat2 = sin(lat2);
	c_lat2 = cos(lat2);
	s_dLon = sin(dLon);
	c_dLon = cos(dLon);
	tmp_fix_1 = c_lat2 * s_dLon;
	tmp_fix_2 = c_lat1 * s_lat2;
	tmp_fix_3 = c_lat2 * s_lat1;
	tmp_fix_4 = tmp_fix_3 * c_dLon;
	tmp_fix_5 = tmp_fix_2 - tmp_fix_4;
	tmp_fix_6 = tmp_fix_1 / tmp_fix_5;
	res = atan(tmp_fix_6);
	printf("%lf\n", res);
	end_dtime = clock();
	exec_time = (double) (end_dtime - begin_dtime) / CLOCKS_PER_SEC;
	exec_time = exec_time * 1000;
	printf("%.3lf\n", exec_time);

	return 0;
}
