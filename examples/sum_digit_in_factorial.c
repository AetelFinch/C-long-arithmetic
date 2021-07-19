#include <stdio.h>
#include <stdlib.h>
#include "..\lnum.h"

bigInt factorial(int num_fact)
{
	bigInt buf = ln_create("1");

	for (int i = 2; i <= num_fact; ++i)
	{
		bigInt x = in_op(buf, '*', i);
		ln_cpy(buf, x);
		ln_free(x);
	}
	return buf;
}

void main(int argc, char **argv)
{
	if (argc == 1)
		return;

	for (int i = 1; i < argc; ++i)
	{
		bigInt fact = factorial(atoi(argv[i]));
		printf("factorial %s = ", argv[i]); ln_print(fact); printf("\n");
		ln_free(fact);
	}
}