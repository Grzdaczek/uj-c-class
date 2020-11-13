#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
// #include <string.h>

#define ERR_INV_COEFF 0x01
#define ERR_MSC_ISNT_ONE 0x02
#define IT_MAX 1e5
#define DELTA_MIN 5e-9

typedef _Complex long double complexl;

int fail(int code) {
	printf("\nerror code: %#04x - ", code);
	switch (code)
	{
		case ERR_INV_COEFF: printf("invalid coefficient\n"); break;
		case ERR_MSC_ISNT_ONE: printf("highest must be equal to 1\n"); break;
		default: break;
	}
	return code;
}

complexl tap (complexl z, char *label) {
	printf("%s = %Le + %Lei\n", label, creall(z), cimagl(z));
	return z;
}

int main(int argc, char *argv[]) {

	unsigned int i = 0;
	unsigned int aLen = 0;
	unsigned int xLen = 0;
	complexl *aArr = malloc((argc-1) * sizeof(complexl));
	complexl *xArr = malloc((argc-2) * sizeof(complexl));

	for (i = 1; i < argc; i++) {
		double a;
		if (sscanf(argv[i] ,"%lf", &a) != 1 || isinf(a) || isnan(a)) return fail(ERR_INV_COEFF);
		aArr[i-1] = a + 0*I;
		aLen = i;
		printf("a%d = '%s' -> %Lf\n", i-1, argv[i], creall(aArr[i-1]));//, cimagl(aArr[i-1]));
	}

	unsigned int n = aLen - 1;
	double radius = powl(cabsl(aArr[0]/aArr[n]), 1.0/n);

	printf("radius = %f\n", radius);

	if (aArr[n] != 1) return fail(ERR_MSC_ISNT_ONE);
	for (i = 0; i < n; i++) {
		double phi = i*3.14/n;
		xArr[i] = radius*cosl(phi) + radius*sinl(phi)*I;
		xArr[i] = xArr[i];
		xLen = i + 1;
		// tap(xArr[i], "x");
	}
	
	long double deltaMax = 0;
	for (i = 0; i < IT_MAX; i++) {
		
		complexl *xArrBuff = malloc((argc-2) * sizeof(complexl));
		int j;
		deltaMax = 0;
		for (j = 0; j < xLen; j++) {
			complexl num = 0 + 0*I;
			complexl denom = 1 + 0*I;
			int k;
			for (k = 0; k < aLen; k++) num += aArr[k] * cpowl(xArr[j], k);
			for (k = 0; k < xLen; k++) if(k != j) denom *= xArr[j]-xArr[k];
			complexl delta = num / denom;
			xArrBuff[j] = xArr[j] - delta;
			long double deltaAbs = cabsl(delta);
			if (deltaAbs > deltaMax) deltaMax = deltaAbs;
		}

		free(xArr);
		xArr = xArrBuff;
		// for (j = 0; j < xLen; j++) tap(xArr[j], "x");
		printf("i: %d\t | d: %Le\n", i, deltaMax);
		if (deltaMax < DELTA_MIN) break;	
	}

	printf("i: %d\t | d: %Le\n", i, deltaMax);
	for (i = 0; i < xLen; i++) printf("%.*Lf  %.*Lfi \t| %Le  %Lei\n", 4, creall(xArr[i]), 4, cimagl(xArr[i]), creall(xArr[i]), cimagl(xArr[i]));
		
	return 0;

}


// 2432902008176640000 -8752948036761600000 13803759753640704000 -12870931245150988800 8037811822645051776 -3599979517947607200 1206647803780373360 -311333643161390640 63030812099294896 -10142299865511450 1307535010540395 -135585182899530 11310276995381 -756111184500 40171771630 -1672280820 53327946 -1256850 20615 -210 1 