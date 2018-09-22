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
	printf("My own result %lld\n", result % module);
}

/*	Main section	*/

int main(int argc, char const *argv[])
{
	if (argc < 4) {
		fprintf(stderr, "Not enough arguments\n");
		EXIT_FAILURE;
	}

	unsigned long long int base = atoi(argv[1]);
	unsigned long long int exponent = atoi(argv[2]);
	unsigned long long int module = atoi(argv[3]);

	expmod_func(base, exponent, module);

	return EXIT_SUCCESS;
}
