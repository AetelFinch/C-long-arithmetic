#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lnum.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define IN_ABS(a) ((a) < 0 ? (-a) : (a))
#define IS_FALSE(a) ((a) ? 0 : 1)

#define BASE 1000000000
#define LEN_DIGIT 9
#define MAX_LLD 9223372036854775807
#define ERROR_SIZE -9223372036854775807

typedef struct lnum_s
{
	unsigned long long *number;
	int length;
	int sign;
}lnum;

int isNumberIncorrect(char *num)
{
	if (num[0] != '-' && (num[0] < '0' || num[0] > '9'))
		return 1;

	int len = strlen(num);

	for (int i = 1; i < len; ++i)
		if (num[i] < '0' || num[i] > '9')
			return 1;

	return 0;
}

int getLengthOfLnum(char *num)
{
	int len = strlen(num);
	if (num[0] == '-')
		--len;

	int lenOfLongNum = len / LEN_DIGIT;
	if (len - lenOfLongNum * LEN_DIGIT != 0)
		++lenOfLongNum;

	return lenOfLongNum;
}

int getSignFromStr(char *num)
{
	return (num[0] == '-' ? -1 : 1);
}

void convertToLnumFromStr(unsigned long long *Lnum, char *num)
{
	int len = strlen(num);
	int end = 0;

	if (num[0] == '-')
		++end;

	unsigned long long digitOfLnum = 0;
	int posDigit = 0;
	int digitInDigitLnum = 0;
	int mult = 1;

	for (int i = len - 1; i >= end; --i)
	{
		digitOfLnum += (num[i] - '0') * mult;
		++digitInDigitLnum;
		mult *= 10;

		if (digitInDigitLnum == LEN_DIGIT)
		{
			Lnum[posDigit] = digitOfLnum;
			digitInDigitLnum = 0;
			digitOfLnum = 0;
			mult = 1;
			++posDigit;
		}
	}

	if (digitInDigitLnum != 0)
		Lnum[posDigit] = digitOfLnum;
}

bigInt ln_create(char *num)
{
	if (isNumberIncorrect(num))
		return NULL;

	bigInt self = (bigInt)malloc(sizeof *self);

	self->length = getLengthOfLnum(num);
	self->sign = getSignFromStr(num);

	self->number = (unsigned long long*)malloc(sizeof(unsigned long long) * self->length);

	convertToLnumFromStr(self->number, num);
	
	return self;
}

void ln_free(bigInt self)
{
	free(self->number);
	free(&(self->length));
	free(&(self->sign));
	free(self);
}

void ln_cpy(bigInt numTo, bigInt numFrom)
{
	numTo->sign = numFrom->sign;
	numTo->length = numFrom->length;
	numTo->number = (unsigned long long*)realloc(numTo->number, sizeof(unsigned long long) * numTo->length);
	numTo->number = (unsigned long long*)memcpy(numTo->number, numFrom->number, sizeof(unsigned long long) * numTo->length);
}

bigInt ln_abs(bigInt self)
{
	bigInt absolute = (bigInt)malloc(sizeof *absolute);
	ln_cpy(absolute, self);
	absolute->sign = 1;
	return absolute;
}

int ln_sign(bigInt self)
{
	return self->sign;
}

int getLenOfLLD(long long num)
{
	if (num == 0)
		return 1;
	num = IN_ABS(num);

	int counter = 0;
	for (; num > 0; num /= BASE, ++counter);
	return counter;
}

int getSignFromLLD(long long num)
{
	return (num < 0 ? -1 : 1);
}

void convertToLnumFromLLD(unsigned long long *Lnum, long long num, int len)
{
	num = IN_ABS(num);

	for (int i = 0; i < len; ++i)
	{
		Lnum[i] = num % BASE;
		num /= BASE;
	}
}

bigInt ln_toBig(long long num)
{
	bigInt self = (bigInt)malloc(sizeof(lnum));

	self->length = getLenOfLLD(num);
	self->sign = getSignFromLLD(num);

	self->number = (unsigned long long*)malloc(sizeof(unsigned long long) * self->length);
	convertToLnumFromLLD(self->number, num, self->length);

	return self;
}

void ln_print(bigInt self)
{
	if (self->length == 1 && self->number[0] == 0)
	{
		printf("0");
		return;
	}

	if (self->sign == -1)
		printf("-");

	printf("%llu", self->number[self->length - 1]);
	for (int i = self->length - 2; i >= 0; --i)
	{
		printf("%0.9llu", self->number[i]);
	}
}

int isEqual(bigInt num1, bigInt num2)
{
	if (num1->length != num2->length)
		return 0;

	for (int i = 0; i < num1->length; ++i)
		if (num1->number[i] != num2->number[i])
			return 0;
	return 1;
}

int isNonEqual(bigInt num1, bigInt num2)
{
	return IS_FALSE(isEqual(num1, num2));
}

int isGreater(bigInt num1, bigInt num2)
{
	if (num1->sign < num2->sign)
		return 0;
	else if (num1->sign > num2->sign)
		return 1;

	if (num1->length < num2->length && num1->sign > 0)
		return 0;
	else if (num1->length > num2->length && num1->sign > 0)
		return 1;
	else if (num1->length > num2->length && num1->sign < 0)
		return 0;
	else if (num1->length < num2->length && num1->sign < 0)
		return 1;

	for (int i = num1->length - 1; i >= 0; --i)
	{
		if (num1->number[i] < num2->number[i])
			return 0;
		else if (num1->number[i] > num2->number[i])
			return 1;
	}
	return 0;
}

int isLess(bigInt num1, bigInt num2)
{
	if (num1->sign < num2->sign)
		return 1;
	else if (num1->sign > num2->sign)
		return 0;

	if (num1->length < num2->length && num1->sign > 0)
		return 1;
	else if (num1->length > num2->length && num1->sign > 0)
		return 0;
	else if (num1->length > num2->length && num1->sign < 0)
		return 1;
	else if (num1->length < num2->length && num1->sign < 0)
		return 0;

	for (int i = num1->length - 1; i >= 0; --i)
	{
		if (num1->number[i] < num2->number[i])
			return 1;
		else if (num1->number[i] > num2->number[i])
			return 0;
	}
	return 0;
}

int isGreaterOrSame(bigInt num1, bigInt num2)
{
	return IS_FALSE(isLess(num1, num2));
}

int isLessOrSame(bigInt num1, bigInt num2)
{
	return IS_FALSE(isGreater(num1, num2));
}

int ln_cmp(bigInt num1, char oper, bigInt num2)
{
	switch (oper)
	{
		case '>':
			return isGreater(num1, num2);
		case '<':
			return isLess(num1, num2);
		case '=':
			return isEqual(num1, num2);
		case '!':
			return isNonEqual(num1, num2);
		case ')':
			return isGreaterOrSame(num1, num2);
		case '(':
			return isLessOrSame(num1, num2);
	}
}

int isGreaterInt(bigInt num1, long long inum)
{
	bigInt num2 = ln_toBig(inum);
	return isGreater(num1, num2);
}

int isLessInt(bigInt num1, long long inum)
{
	bigInt num2 = ln_toBig(inum);
	return isLess(num1, num2);
}

int isEqualInt(bigInt num1, long long inum)
{
	bigInt num2 = ln_toBig(inum);
	return isEqual(num1, num2);
}

int isNonEqualInt(bigInt num1, long long inum)
{
	bigInt num2 = ln_toBig(inum);
	return isNonEqual(num1, num2);
}

int isGreaterOrSameInt(bigInt num1, long long inum)
{
	bigInt num2 = ln_toBig(inum);
	return isGreaterOrSame(num1, num2);
}

int isLessOrSameInt(bigInt num1, long long inum)
{
	bigInt num2 = ln_toBig(inum);
	return isLessOrSame(num1, num2);
}

int in_cmp(bigInt num1, char oper, long long num2)
{
	switch (oper)
	{
		case '>':
			return isGreaterInt(num1, num2);
		case '<':
			return isLessInt(num1, num2);
		case '=':
			return isEqualInt(num1, num2);
		case '!':
			return isNonEqualInt(num1, num2);
		case ')':
			return isGreaterOrSameInt(num1, num2);
		case '(':
			return isLessOrSameInt(num1, num2);
	}
}

long long ln_fromBig(bigInt self)
{
	if (in_cmp(self, '>', MAX_LLD))
	{
		return ERROR_SIZE;
	}
	else if (in_cmp(self, '(', MAX_LLD))
	{
		long long ans = 0;
		long long multiplicator = 1;
		for (int i = 0; i < self->length; ++i)
		{
			ans += self->number[i] * multiplicator;
			multiplicator *= BASE;
		}
		return ans * self->sign;
	}
}

void poz_plus_poz(bigInt num1, bigInt num2, bigInt ans)
{
	int minLen = num2->length;
	long long bufRes = 0;

	int i;
	for (i = 0; i < minLen; ++i)
	{
		bufRes += num1->number[i] + num2->number[i];
		ans->number[i] = bufRes % BASE;
		bufRes /= BASE;
	}

	for (; i < num1->length; ++i)
	{
		bufRes += num1->number[i];
		ans->number[i] = bufRes % BASE;
		bufRes /= BASE;
	}

	if (bufRes != 0)
	{
		ans->number[i] += bufRes;
	}
}

void poz_minus_poz(bigInt num1, bigInt num2, bigInt ans)
{
	int minLen = num2->length;
	long long bufRes = 0;
	
	int i;
	for (i = 0; i < minLen; ++i)
	{
		long long signedBuffer = num1->number[i] - num2->number[i] - bufRes;
		bufRes = 0;

		if (signedBuffer < 0)
		{
			ans->number[i] = BASE + signedBuffer;
			bufRes = 1;
		}
		else
		{
			ans->number[i] = signedBuffer;
		}
	}

	for (; i < num1->length; ++i)
	{
		long long signedBuffer = num1->number[i] - bufRes;
		bufRes = 0;

		if (signedBuffer < 0)
		{
			ans->number[i] = BASE + signedBuffer;
			bufRes = 1;
		}
		else
		{
			ans->number[i] = signedBuffer;
		}
	}
}

void ln_resize(bigInt self)
{
	int posLastDigit = 0;
	for (int i = 0; i < self->length; ++i)
			if (self->number[i] != 0)
				posLastDigit = i;

	if (posLastDigit + 1 < self->length)
	{
		self->number = (unsigned long long*)realloc(self->number, sizeof(unsigned long long) * (posLastDigit + 1));
		self->length = posLastDigit + 1;
	}
}

void getMaxMinLnum(bigInt num1, bigInt num2, bigInt *max, bigInt *min)
{
	if (num1->length > num2->length)
	{
		*max = num1;
		*min = num2;
	}
	else if (num1->length == num2->length)
	{
		for (int i = num1->length - 1; i >= 0; --i)
		{
			if (num1->number[i] > num2->number[i])
			{
				*max = num1;
				*min = num2;
				break;
			}
			else if (num1->number[i] < num2->number[i])
			{
				*max = num2;
				*min = num1;
				break;
			}
		}
		*max = num2;
		*min = num1;
	}
	else
	{
		*max = num2;
		*min = num1;
	}
}

bigInt ln_add(bigInt num1, bigInt num2)
{
	bigInt ans = (bigInt)malloc(sizeof *ans);

	ans->length = MAX(num1->length, num2->length) + 1;
	ans->number = (unsigned long long*)calloc(sizeof(unsigned long long), ans->length);

	bigInt min, *max;
	getMaxMinLnum(num1, num2, &max, &min);

	if (max->sign == 1 && min->sign == 1)
	{
		poz_plus_poz(max, min, ans);
		ans->sign = 1;
	}
	else if (max->sign == 1 && min->sign == -1)
	{
		poz_minus_poz(max, min, ans);
		ans->sign = 1;
	}
	else if (max->sign == -1 && min->sign == 1)
	{
		poz_minus_poz(max, min, ans);
		ans->sign = -1;
	}
	else if (max->sign == -1 && min->sign == -1)
	{
		poz_plus_poz(max, min, ans);
		ans->sign = -1;
	}
	ln_resize(ans);

	return ans;
}

bigInt ln_sub(bigInt num1, bigInt num2)
{
	bigInt ans = (bigInt)malloc(sizeof *ans);

	ans->length = MAX(num1->length, num2->length) + 1;
	ans->number = (unsigned long long*)calloc(sizeof(unsigned long long), ans->length);

	bigInt min, *max;
	getMaxMinLnum(num1, num2, &max, &min);

	if (max->sign == 1 && min->sign == 1)
	{
		poz_minus_poz(max, min, ans);
		if (max == num1)
			ans->sign = 1;
		else
			ans->sign = -1;
	}
	else if (max->sign == 1 && min->sign == -1)
	{
		poz_plus_poz(max, min, ans);
		if (max == num1)
			ans->sign = 1;
		else
			ans->sign = -1;
	}
	else if (max->sign == -1 && min->sign == 1)
	{
		poz_plus_poz(max, min, ans);
		if (max == num1)
			ans->sign = -1;
		else
			ans->sign = 1;
	}
	else if (max->sign == -1 && min->sign == -1)
	{
		poz_minus_poz(max, min, ans);
		if (max == num1)
			ans->sign = -1;
		else
			ans->sign = 1;
	}
	ln_resize(ans);

	return ans;
}

void multiplication(bigInt num1, bigInt num2, bigInt ans)
{
	int len1 = num1->length;
	int len2 = num2->length;

	long long bufRes;
	int i, j;

	for (i = 0; i < len1; ++i)
	{
		bufRes = 0;
		for (j = 0; j < len2; ++j)
		{
			ans->number[i + j] = ans->number[i + j] + bufRes + num1->number[i] * num2->number[j];
			bufRes = ans->number[i + j] / BASE;
			ans->number[i + j] %= BASE;
		}
		ans->number[i + j] = bufRes;
	}
}

bigInt ln_mul(bigInt num1, bigInt num2)
{
	bigInt ans = (bigInt)malloc(sizeof *ans);

	ans->length = num1->length + num2->length;
	ans->number = (unsigned long long*)calloc(sizeof(unsigned long long), ans->length);

	bigInt min, *max;
	getMaxMinLnum(num1, num2, &max, &min);

	multiplication(max, min, ans);
	ans->sign = num1->sign * num2->sign;

	ln_resize(ans);

	return ans;
}

void division(bigInt num1, bigInt num2, bigInt ans)
{
	// will be added
}

bigInt ln_div(bigInt num1, bigInt num2)
{
	bigInt ans;

	if (ln_cmp(ln_abs(num1), '<', ln_abs(num2)))
	{
		ans = ln_create("0");
		return ans;
	}
	else if (ln_cmp(ln_abs(num1), '=', ln_abs(num2)))
	{
		ans = ln_create("1");
		ans->sign = num1->sign * num2->sign;
		return ans;
	}
	else if (in_cmp(ln_abs(num2), '=', 0))
	{
		return NULL;
	}
	else if (in_cmp(ln_abs(num2), '=', 1))
	{
		ans = (bigInt)malloc(sizeof *ans);
		ln_cpy(ans, num1);
		return ans;
	}

	ans = (bigInt)malloc(sizeof *ans);

	ans->length = num1->length;
	ans->number = (unsigned long long*)calloc(sizeof(unsigned long long), ans->length);

	division(num1, num2, ans);

	return ans;
}

void modulo(bigInt num1, bigInt num2, bigInt ans)
{
	// will be added
}

bigInt ln_mod(bigInt num1, bigInt num2)
{
	bigInt ans;

	if (ln_cmp(ln_abs(num1), '<', ln_abs(num2)))
	{
		ln_cpy(ans, num1);
		return ans;
	}
	else if (ln_cmp(ln_abs(num1), '=', ln_abs(num2)) || in_cmp(ln_abs(num2), '=', 1))
	{
		ans = ln_create("0");
		return ans;
	}
	else if (in_cmp(ln_abs(num2), '=', 0))
	{
		return NULL;
	}

	ans = (bigInt)malloc(sizeof *ans);

	ans->length = num1->length;
	ans->number = (unsigned long long*)calloc(sizeof(unsigned long long), ans->length);

	modulo(num1, num2, ans);

	return ans;
}

bigInt ln_op(bigInt num1, char oper, bigInt num2)
{
	switch (oper)
	{
		case '+':
			return ln_add(num1, num2);
		case '-':
			return ln_sub(num1, num2);
		case '*':
		 	return ln_mul(num1, num2);
		case '/':
			return ln_div(num1, num2); 
		case '%':
			return ln_mod(num1, num2);
	}
}

bigInt in_op(bigInt num1, char oper, long long num)
{
	bigInt num2 = ln_toBig(num);
	ln_op(num1, oper, num2);
}

// void exponentiation(bigInt num1, int pow, bigInt ans)
// {
// 	while (pow)
// 	{
// 		if (pow & 1)
// 		{
// 			bigInt buf = ln_op(ans, '*', num1);
// 			ln_free(ans);
// 			ln_cpy(ans, buf);
// 			ln_free(buf);
// 		}
// 		bigInt buf = ln_op(num1, '*', num1);
// 		ln_free(num1);
// 		ln_cpy(num1, buf);
// 		ln_free(buf);
// 		pow >>= 1;
// 	}
// }

// bigInt ipow(long long num, int pow)
// {
// 	bigInt ans, *num1;
// 	num1 = ln_toBig(num);

// 	if (pow < 0)
// 	{
// 		return NULL;
// 	}
// 	else if (pow == 0)
// 	{
// 		ans = ln_create("1");
// 		return ans;
// 	}
// 	else if (pow == 1)
// 	{
// 		ln_cpy(ans, num1);
// 		return ans;
// 	}
// 	else if (pow > 2000000)
// 	{
// 		return NULL;
// 	}

// 	ans = ln_create("1");

// 	exponentiation(num1, pow, ans);

// 	return ans;
// }

