#define bigInt lnum*

typedef struct lnum_s lnum;

bigInt ln_create(char *number); //create bigInt

void ln_free(bigInt num); //free bigInt

void ln_print(bigInt num); //print bigInt in stdout

void ln_cpy(bigInt numTo, bigInt numFrom); //copy numFrom to numTo. numTo should be free before copying

bigInt ln_toBig(long long number); //transform long long to bigInt 

long long ln_fromBig(bigInt num); //return long long from bigInt if it possible, otherwise return -9223372036854775807

int ln_sign(bigInt num); // return -1 if bigInt < 0, else 1

bigInt ln_abs(bigInt num); //return an absolute value of bigInt

int ln_len(bigInt num); //return a count of "digits" in num

unsigned long long ln_digit(bigInt num, int i); //return a value of the i-th digit in little-endian

bigInt ln_op(bigInt num1, char oper, bigInt num2);
bigInt in_op(bigInt num1, char oper, long long num2);
	//performs an arithmetic operation with two numbers numbers
	//operations:
	//	+: addition 
	//	-: subtraction 
	//	*: multiplication
	// example: 
	// bigInt a = ln_create("111222333");
	// bigInt b = ln_create("111111111");
	// bigInt res = ln_op(a, '-', b);
	// ln_print(res) -> 111111


int ln_cmp(bigInt num1, char oper, bigInt num2);
int in_cmp(bigInt num1, char oper, long long num2);
	//performs a comparison of two numbers. Return 1 if True, else 0
	//operations:
	// =: is equal
	// !: is not equal
	// >: is greater
	// <: is less
	// ): is greater or equal
	// (: is less or equal
	// example:
	// bigInt a = ln_create("111222333");
	// bigInt b = ln_create("111111111");
	// if(ln_cmp(a, '>', b))
	//     printf("True"); -> True
