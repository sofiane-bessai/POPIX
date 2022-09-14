#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main() {
	clock_t begin_dtime = clock();
	clock_t end_dtime;
	double exec_time;
	FIX res;
	FIX tmp_fix_6;
	FIX tmp_fix_5;
	FIX s_lat1;
	FIX lat1;
	FIX lat2;
	FIX tmp_fix_4;
	FIX tmp_fix_1;
	FIX c_lat1;
	FIX tmp_fix_3;
	FIX c_lat2;
	FIX lon2;
	FIX lon1;
	FIX dLon;
	FIX s_dLon;
	FIX s_lat2;
	FIX c_dLon;
	FIX tmp_fix_2;
	lat1 = __float_to_fix__(0.400000, -2, 24);
	lat2 = __float_to_fix__(0.750000, -1, 24);
	lon1 = 1;
	lon2 = __float_to_fix__(-0.100000, -4, 19);
	dLon = ;
	s_lat1 = virtual std::string CallExpression::ToStringFix(int);
	c_lat1 = virtual std::string CallExpression::ToStringFix(int);
	s_lat2 = virtual std::string CallExpression::ToStringFix(int);
	c_lat2 = virtual std::string CallExpression::ToStringFix(int);
	s_dLon = virtual std::string CallExpression::ToStringFix(int);
	c_dLon = virtual std::string CallExpression::ToStringFix(int);
	tmp_fix_1 = ;
	tmp_fix_2 = ;
	tmp_fix_3 = ;
	tmp_fix_4 = ;
	tmp_fix_5 = ;
	tmp_fix_6 = ;
	res = virtual std::string CallExpression::ToStringFix(int);
	printf("%lf\n", res);
	end_dtime = clock();
	exec_time = (double) (end_dtime - begin_dtime) / CLOCKS_PER_SEC;
	exec_time = exec_time * 1000;
	printf("%.3lf\n", exec_time);

	return 0;
}
