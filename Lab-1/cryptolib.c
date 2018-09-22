/*	Import section	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*	Func section	*/

int dectobin(unsigned long long int value)
{
	if (value < 2)
		return value;
	else
		return (dectobin(value / 2) * 10 + value % 2);
}

void expmod_func(unsigned long long int base, unsigned long long int exponent, unsigned long long int module)
{	
	int cnt = 0;
	unsigned long long int bin_exp = dectobin(exponent);
	unsigned long long int bin_res[100];
	int res_arr[100];
	while (bin_exp > 0)
	{
		bin_res[cnt] = bin_exp % 10;
		bin_exp /= 10;

		if (cnt == 0)
			res_arr[cnt] = base;
		else
			res_arr[cnt] = res_arr[cnt - 1] * res_arr[cnt - 1];
		res_arr[cnt] %= module;
		cnt++;
	}

	int result = 1;
	for (int i = 0; i < cnt; i++)
	{
		res_arr[i] = pow(res_arr[i], bin_res[i]);
		result *= res_arr[i];
	}
	printf("FEM's result:\t%lld\n", result % module);
}

void euclid(unsigned long long int a, unsigned long long int b, unsigned long long int *res)
{
	long int U[2] = {1, 0};
	long int V[2] = {0, 1};
	long int T[2];
	long int buff;
	double q = a / b;

	while (b > 0)
	{
		T[0] = U[0] - q * U[1];
		T[1] = V[0] - q * V[1];

		U[0] = U[1];
		V[0] = V[1];

		U[1] = T[0];
		V[1] = T[1];

		buff = a % b;
		a = b;
		b = buff;
	}

	res[0] = U[0];
	res[1] = V[0];
	res[2] = a;
}

/*	Main section	*/

int main(int argc, char const *argv[])
{
	if (argc < 4) {
		fprintf(stderr, "Not enough arguments for FEM func!\n");
		return EXIT_FAILURE;
	} else if (argc < 6) {
		fprintf(stderr, "Not enough arguments for GEA func!\n");
		return EXIT_FAILURE;
	}

	unsigned long long int base = atoi(argv[1]);
	unsigned long long int exponent = atoi(argv[2]);
	unsigned long long int module = atoi(argv[3]);
	unsigned long long int euclid_a = atoi(argv[4]);
	unsigned long long int euclid_b = atoi(argv[5]);
	unsigned long long int euclid_res[2];

	expmod_func(base, exponent, module);
	euclid(euclid_a, euclid_b, euclid_res);
	printf("GEA's result:\t%lld, %lld and their GCD: %lld\n", euclid_res[0], euclid_res[1], euclid_res[2]);

	return EXIT_SUCCESS;
}
