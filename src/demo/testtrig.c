/*
 * TESTTRIG.C
 *
 * Test to verify release v3.09-1 has fixed floating point
 * Trigonometry routines.
 *
 * Compile using
 *
 * 	c -o -lf testtrig.c
 *
 * From a USENET newsgroup post to comp.os.cpm on 2013-09-02 by "Ed"
 *
 * "LIBF.LIB supplied with the freeware Hitech-C 3.09 release
 *  produces inaccurate trig results.  I found that by simply
 *  recompiling the library with the existing source files from
 *  FLOAT.HUF, it fixed the problem.  Absolutely no changes
 *  to the sources were required.
 *
 *  Below is a comparison of results between the original and
 *  rebuilt library.
 *
 * ---
 *
 * (using original LIBF.LIB)
 *
 *   n  LN             EXP            SIN            COS            ATAN
 *  01  0.000000e+00   2.703595e+00   8.502954e-01   5.339794e-01   7.800306e-01
 *  02  6.931469e-01   7.309311e+00   9.107645e-01  -4.232263e-01   1.116727e+00
 *  03  1.098605e+00   1.976185e+01   1.411983e-01  -9.956650e-01   1.257505e+00
 *  04  1.386294e+00   5.342758e+01  -7.673132e-01  -6.481950e-01   1.333912e+00
 *  05  1.609434e+00   1.444486e+02  -9.609912e-01   2.909977e-01   1.381350e+00
 *  06  1.791752e+00   3.905289e+02  -2.795844e-01   9.680709e-01   1.413529e+00
 *  07  1.945900e+00   1.055842e+03   6.572353e-01   7.495101e-01   1.436745e+00
 *  08  2.079441e+00   2.854568e+03   9.921404e-01  -1.529755e-01   1.454266e+00
 *  09  2.197222e+00   7.717445e+03   4.124018e-01  -9.213704e-01   1.467951e+00
 *  10  2.302581e+00   2.086538e+04  -5.440205e-01  -8.359161e-01   1.478932e+00
 *  11  2.397890e+00   5.641094e+04  -1.003614e+00   1.190640e-02   1.487935e+00
 *  12  2.484899e+00   1.525148e+05  -5.370088e-01   8.565310e-01   1.495450e+00
 *  13  2.564940e+00   4.123360e+05   4.199748e-01   9.057026e-01   1.501817e+00
 *  14  2.639047e+00   1.114781e+06   9.952080e-01   1.294013e-01   1.507279e+00
 *  15  2.708037e+00   3.013969e+06   6.509256e-01  -7.748882e-01   1.512017e+00
 *  16  2.772588e+00   8.148225e+06  -2.875695e-01  -9.574937e-01   1.516165e+00
 *  17  2.833212e+00   2.202966e+07  -9.671226e-01  -2.681288e-01   1.519827e+00
 *  18  2.890369e+00   5.955735e+07  -7.518865e-01   6.661855e-01   1.523084e+00
 *  19  2.944436e+00   1.610253e+08   1.494345e-01   9.902740e-01   1.525998e+00
 * 
 * 
 * (using rebuilt LIBF.LIB)
 * 
 *   n  LN             EXP            SIN            COS            ATAN
 *  01  0.000000e+00   2.718280e+00   8.414706e-01   5.403037e-01   7.853970e-01
 *  02  6.931469e-01   7.389050e+00   9.092973e-01  -4.161461e-01   1.107148e+00
 *  03  1.098612e+00   2.008552e+01   1.411217e-01  -9.899922e-01   1.249045e+00
 *  04  1.386294e+00   5.459808e+01  -7.568023e-01  -6.536445e-01   1.325817e+00
 *  05  1.609438e+00   1.484130e+02  -9.589242e-01   2.836605e-01   1.373400e+00
 *  06  1.791759e+00   4.034281e+02  -2.794159e-01   9.601696e-01   1.405647e+00
 *  07  1.945910e+00   1.096632e+03   6.569859e-01   7.539025e-01   1.428899e+00
 *  08  2.079441e+00   2.980951e+03   9.893581e-01  -1.454975e-01   1.446441e+00
 *  09  2.197224e+00   8.103068e+03   4.121197e-01  -9.111288e-01   1.460139e+00
 *  10  2.302584e+00   2.202640e+04  -5.440195e-01  -8.390731e-01   1.471127e+00
 *  11  2.397894e+00   5.987400e+04  -9.999901e-01   4.422163e-03   1.480136e+00
 *  12  2.484906e+00   1.627543e+05  -5.365736e-01   8.438515e-01   1.487654e+00
 *  13  2.564949e+00   4.424121e+05   4.201658e-01   9.074482e-01   1.494024e+00
 *  14  2.639056e+00   1.202602e+06   9.906070e-01   1.367416e-01   1.499488e+00
 *  15  2.708049e+00   3.269002e+06   6.502892e-01  -7.596840e-01   1.504228e+00
 *  16  2.772588e+00   8.886073e+06  -2.879012e-01  -9.576598e-01   1.508377e+00
 *  17  2.833213e+00   2.415486e+07  -9.613965e-01  -2.751657e-01   1.512040e+00
 *  18  2.890371e+00   6.565973e+07  -7.509890e-01   6.603144e-01   1.515297e+00
 *  19  2.944438e+00   1.784813e+08   1.498741e-01   9.887048e-01   1.518213e+00
 *  "
 */

#include <math.h>

float a, b, c, d, e, f, g;
int i;

int main() {
	a = 1.0;
	printf(
			"\n  n  LN             EXP            SIN            COS            ATAN");
	for (i = 1; i < 20; i++) {
		b = log(a);
		c = exp(a);
		d = sin(a);
		e = cos(a);
		f = atan(a);

		printf("\n%3.2d", i);
		printf("%14.6e ", b);
		printf("%14.6e ", c);
		printf("%14.6e ", d);
		printf("%14.6e ", e);
		printf("%14.6e ", f);

		a = a + 1.0;
	}
	printf("\n");
	return 0;
}