#include <stdio.h>
#include <stdlib.h>
#include "lnum.h"

void check_main_functions()
{
	printf("-------------------------------------------\n");
	printf("check_main_functions\n\n");

	bigInt num1 = ln_create("1234567890123415451523412344524352353452345");
	bigInt num2 = ln_create("0");
	bigInt num3 = ln_toBig(0);
	bigInt num4 = ln_create("-1234567890123415451523412344524352353452345");
	bigInt num5 = ln_toBig(-12344312);
	bigInt num6 = ln_toBig(12344312);

	ln_print(num1); printf("\n"); //1234567890123415451523412344524352353452345
	ln_print(num2); printf("\n"); //0
	ln_print(num3); printf("\n"); //0
	ln_print(num4); printf("\n"); //-1234567890123415451523412344524352353452345
	ln_print(num5); printf("\n"); //-12344312
	ln_print(num6); printf("\n\n"); //12344312

	ln_cpy(num2, num1);
	ln_cpy(num4, num3);
	ln_cpy(num5, num6);

	ln_print(num1); printf("\n"); //1234567890123415451523412344524352353452345
	ln_print(num2); printf("\n"); //1234567890123415451523412344524352353452345
	ln_print(num3); printf("\n"); //0
	ln_print(num4); printf("\n"); //0
	ln_print(num5); printf("\n"); //12344312
	ln_print(num6); printf("\n\n"); //12344312

	ln_free(num1); ln_free(num2); ln_free(num3);
	ln_free(num4); ln_free(num5); ln_free(num6);

	printf("-------------------------------------------\n");
}

void check_addition_poz_plus_poz()
{
	printf("-------------------------------------------\n");
	printf("check_addition_poz_plus_poz\n\n");

	bigInt num1 = ln_create("111111111222222222333333333");
	bigInt num2 = ln_create("333333333444444444555555555");
	bigInt num3 = ln_create("999999999999999999999999999");
	bigInt num4 = ln_create("111111111222222222");
	bigInt num5 = ln_create("999999999999999999");
	bigInt num6 = ln_create("1");
	bigInt num7 = ln_create("111111111222222222323333332");
	bigInt num8 = ln_create("1000000000000000000");

	bigInt ans1 = ln_op(num1, '+', num2);
	bigInt ans2 = ln_op(num3, '+', num2);
	bigInt ans3 = ln_op(num1, '+', num4);
	bigInt ans4 = ln_op(num1, '+', num5);
	bigInt ans5 = ln_op(num5, '+', num6);

	printf("ans1 = "); ln_print(ans1); printf("\n"); //444444444666666666888888888
	printf("ans2 = "); ln_print(ans2); printf("\n"); //1333333333444444444555555554
	printf("ans3 = "); ln_print(ans3); printf("\n"); //111111111333333333555555555
	printf("ans4 = "); ln_print(ans4); printf("\n"); //1111111111222222222333333332
	printf("ans5 = "); ln_print(ans5); printf("\n"); //1000000000000000000

	ln_free(num1); ln_free(num2); ln_free(num3); ln_free(num4);
	ln_free(num5); ln_free(num6); ln_free(num7); ln_free(num8);
	ln_free(ans1); ln_free(ans2); ln_free(ans3); ln_free(ans4);
	ln_free(ans5);

	printf("-------------------------------------------\n\n");
}

void check_addition_poz_plus_neg()
{
	printf("-------------------------------------------\n");
	printf("check_addition_poz_plus_neg\n\n");

	bigInt num1 = ln_create("111111111222222222333333333");
	bigInt num2 = ln_create("-333333333444444444555555555");
	bigInt num3 = ln_create("999999999999999999999999999");
	bigInt num4 = ln_create("-111111111222222222");
	bigInt num5 = ln_create("999999999999999999");
	bigInt num6 = ln_create("1");
	bigInt num7 = ln_create("-111111111222222222323333332");
	bigInt num8 = ln_create("-1000000000000000000");

	bigInt ans1 = ln_op(num1, '+', num2);
	bigInt ans2 = ln_op(num1, '+', num7);
	bigInt ans3 = ln_op(num4, '+', num1);
	bigInt ans4 = ln_op(num2, '+', num5);
	bigInt ans5 = ln_op(num6, '+', num8);

	printf("ans1 = "); ln_print(ans1); printf("\n"); //-222222222222222222222222222
	printf("ans2 = "); ln_print(ans2); printf("\n"); //10000001
	printf("ans3 = "); ln_print(ans3); printf("\n"); //111111111111111111111111111
	printf("ans4 = "); ln_print(ans4); printf("\n"); //-333333332444444444555555556
	printf("ans5 = "); ln_print(ans5); printf("\n"); //-999999999999999999

	ln_free(num1); ln_free(num2); ln_free(num3); ln_free(num4);
	ln_free(num5); ln_free(num6); ln_free(num7); ln_free(num8);
	ln_free(ans1); ln_free(ans2); ln_free(ans3); ln_free(ans4);
	ln_free(ans5);

	printf("-------------------------------------------\n\n");
}

void check_addition_neg_plus_neg()
{
	printf("-------------------------------------------\n");
	printf("check_addition_neg_plus_neg\n\n");

	bigInt num1 = ln_create("-111111111222222222333333333");
	bigInt num2 = ln_create("-333333333444444444555555555");
	bigInt num3 = ln_create("-999999999999999999999999999");
	bigInt num4 = ln_create("-111111111222222222");
	bigInt num5 = ln_create("-999999999999999999");
	bigInt num6 = ln_create("-1");

	bigInt ans1 = ln_op(num1, '+', num2);
	bigInt ans2 = ln_op(num3, '+', num2);
	bigInt ans3 = ln_op(num1, '+', num4);
	bigInt ans4 = ln_op(num1, '+', num5);
	bigInt ans5 = ln_op(num5, '+', num6);

	printf("ans1 = "); ln_print(ans1); printf("\n"); //-444444444666666666888888888
	printf("ans2 = "); ln_print(ans2); printf("\n"); //-1333333333444444444555555554
	printf("ans3 = "); ln_print(ans3); printf("\n"); //-111111111333333333555555555
	printf("ans4 = "); ln_print(ans4); printf("\n"); //-111111111222222222333333332
	printf("ans5 = "); ln_print(ans5); printf("\n"); //-1000000000000000000

	ln_free(num1); ln_free(num2); ln_free(num3); ln_free(num4);
	ln_free(num5); ln_free(num6);
	ln_free(ans1); ln_free(ans2); ln_free(ans3); ln_free(ans4);
	ln_free(ans5);

	printf("-------------------------------------------\n\n");
}

void check_subvision_poz_minus_poz()
{
	printf("-------------------------------------------\n");
	printf("check_subvision_poz_minus_poz\n\n");

	bigInt num1 = ln_create("111111111222222222333333333");
	bigInt num2 = ln_create("333333333444444444555555555");
	bigInt num3 = ln_create("999999999999999999999999999");
	bigInt num4 = ln_create("111111111222222222");
	bigInt num5 = ln_create("999999999999999999");
	bigInt num6 = ln_create("1");
	bigInt num7 = ln_create("111111111222222222323333332");
	bigInt num8 = ln_create("1000000000000000000");

	bigInt ans1 = ln_op(num1, '-', num2);
	bigInt ans2 = ln_op(num1, '-', num7);
	bigInt ans3 = ln_op(num4, '-', num1);
	bigInt ans4 = ln_op(num1, '-', num5);
	bigInt ans5 = ln_op(num8, '-', num5);

	printf("ans1 = "); ln_print(ans1); printf("\n"); //-222222222222222222222222222
	printf("ans2 = "); ln_print(ans2); printf("\n"); //10000001
	printf("ans3 = "); ln_print(ans3); printf("\n"); //-111111111111111111111111111
	printf("ans4 = "); ln_print(ans4); printf("\n"); //-111111110222222222333333334
	printf("ans5 = "); ln_print(ans5); printf("\n"); //1

	ln_free(num1); ln_free(num2); ln_free(num3); ln_free(num4);
	ln_free(num5); ln_free(num6); ln_free(num7); ln_free(num8);
	ln_free(ans1); ln_free(ans2); ln_free(ans3); ln_free(ans4);
	ln_free(ans5);

	printf("-------------------------------------------\n");
}

void check_subvision_poz_minus_neg()
{
	printf("-------------------------------------------\n");
	printf("check_subvision_poz_minus_neg\n\n");

	bigInt num1 = ln_create("111111111222222222333333333");
	bigInt num2 = ln_create("-333333333444444444555555555");
	bigInt num3 = ln_create("999999999999999999999999999");
	bigInt num4 = ln_create("-111111111222222222");
	bigInt num5 = ln_create("999999999999999999");
	bigInt num6 = ln_create("-1");
	bigInt num7 = ln_create("111111111222222222323333332");
	bigInt num8 = ln_create("1000000000000000000");

	bigInt ans1 = ln_op(num1, '-', num2); 
	bigInt ans2 = ln_op(num3, '-', num2);
	bigInt ans3 = ln_op(num1, '-', num4);
	bigInt ans4 = ln_op(num5, '-', num4);
	bigInt ans5 = ln_op(num5, '-', num6);

	printf("ans1 = "); ln_print(ans1); printf("\n"); //444444444666666666888888888
	printf("ans2 = "); ln_print(ans2); printf("\n"); //1333333333444444444555555554
	printf("ans3 = "); ln_print(ans3); printf("\n"); //111111111333333333555555555
	printf("ans4 = "); ln_print(ans4); printf("\n"); //1111111111222222221
	printf("ans5 = "); ln_print(ans5); printf("\n"); //1000000000000000000

	ln_free(num1); ln_free(num2); ln_free(num3); ln_free(num4);
	ln_free(num5); ln_free(num6); ln_free(num7); ln_free(num8);
	ln_free(ans1); ln_free(ans2); ln_free(ans3); ln_free(ans4);
	ln_free(ans5);

	printf("-------------------------------------------\n");
}

void check_subvision_neg_minus_neg()
{
	printf("-------------------------------------------\n");
	printf("check_subvision_neg_minus_neg\n\n");

	bigInt num1 = ln_create("-111111111222222222333333333");
	bigInt num2 = ln_create("-333333333444444444555555555");
	bigInt num3 = ln_create("-999999999999999999999999999");
	bigInt num4 = ln_create("-111111111222222222");
	bigInt num5 = ln_create("-999999999999999999");
	bigInt num6 = ln_create("-1");
	bigInt num7 = ln_create("-111111111222222222323333332");
	bigInt num8 = ln_create("-1000000000000000000");

	bigInt ans1 = ln_op(num1, '-', num2); 
	bigInt ans2 = ln_op(num1, '-', num7);
	bigInt ans3 = ln_op(num1, '-', num4);
	bigInt ans4 = ln_op(num5, '-', num1);
	bigInt ans5 = ln_op(num8, '-', num6);

	printf("ans1 = "); ln_print(ans1); printf("\n"); //222222222222222222222222222
	printf("ans2 = "); ln_print(ans2); printf("\n"); //-10000001
	printf("ans3 = "); ln_print(ans3); printf("\n"); //-111111111111111111111111111
	printf("ans4 = "); ln_print(ans4); printf("\n"); //111111110222222222333333334
	printf("ans5 = "); ln_print(ans5); printf("\n"); //-999999999999999999

	ln_free(num1); ln_free(num2); ln_free(num3); ln_free(num4);
	ln_free(num5); ln_free(num6); ln_free(num7); ln_free(num8);
	ln_free(ans1); ln_free(ans2); ln_free(ans3); ln_free(ans4);
	ln_free(ans5);

	printf("-------------------------------------------\n");
}

void check_multiplication()
{
	printf("-------------------------------------------\n");
	printf("check_multiplication\n\n");

	bigInt num1 = ln_create("111111111222222222333333333");
	bigInt num2 = ln_create("-333333333444444444555555555");
	bigInt num3 = ln_create("999999999999999999999999999");
	bigInt num4 = ln_create("0");
	bigInt num5 = ln_create("-999999999999999999");
	bigInt num6 = ln_create("-1");
	bigInt num7 = ln_create("18");
	bigInt num8 = ln_create("-5");

	bigInt ans1 = ln_op(num2, '*', num3); 
	bigInt ans2 = ln_op(num5, '*', num3);
	bigInt ans3 = ln_op(num7, '*', num8);
	bigInt ans4 = ln_op(num6, '*', num8);
	bigInt ans5 = ln_op(num4, '*', num6);

	printf("ans1 = "); ln_print(ans1); printf("\n"); //-333333333444444444555555554666666666555555555444444445
	printf("ans2 = "); ln_print(ans2); printf("\n"); //-999999999999999998999999999000000000000000001
	printf("ans3 = "); ln_print(ans3); printf("\n"); //-90
	printf("ans4 = "); ln_print(ans4); printf("\n"); //5
	printf("ans5 = "); ln_print(ans5); printf("\n"); //0

	ln_free(num1); ln_free(num2); ln_free(num3); ln_free(num4);
	ln_free(num5); ln_free(num6); ln_free(num7); ln_free(num8);
	ln_free(ans1); ln_free(ans2); ln_free(ans3); ln_free(ans4);
	ln_free(ans5);

	printf("-------------------------------------------\n");
}

void check_transform_from_lnum()
{
	printf("-------------------------------------------\n");
	printf("check_transform_from_lnum\n\n");

	bigInt num1 = ln_create("11111135656456111222222222");
	bigInt num2 = ln_create("-333333333444444444");
	bigInt num3 = ln_create("9999999999");
	bigInt num4 = ln_create("0");
	bigInt num5 = ln_create("-999999999999");
	bigInt num6 = ln_create("-1");
	bigInt num7 = ln_create("18");
	bigInt num8 = ln_create("-5");

	printf("num1 = %lld\n", ln_fromBig(num1));
	printf("num2 = %lld\n", ln_fromBig(num2));
	printf("num3 = %lld\n", ln_fromBig(num3));
	printf("num4 = %lld\n", ln_fromBig(num4));
	printf("num5 = %lld\n", ln_fromBig(num5));
	printf("num6 = %lld\n", ln_fromBig(num6));
	printf("num7 = %lld\n", ln_fromBig(num7));
	printf("num8 = %lld\n", ln_fromBig(num8));

	ln_free(num1); ln_free(num2); ln_free(num3); ln_free(num4);
	ln_free(num5); ln_free(num6); ln_free(num7); ln_free(num8);

	printf("-------------------------------------------\n");
}

int main()
{
	//test main functions
	//============================================================================
	
	check_main_functions();
	check_transform_from_lnum();

	//============================================================================


	//test arithmetic functions
	//============================================================================

	//addition
	check_addition_poz_plus_poz();
	check_addition_poz_plus_neg();
	check_addition_neg_plus_neg();

	//subtraction
	check_subvision_poz_minus_poz();
	check_subvision_poz_minus_neg();
	check_subvision_neg_minus_neg();

	//multiplication
	check_multiplication();

	//============================================================================

	return 0;
}