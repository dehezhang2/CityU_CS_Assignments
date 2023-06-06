#include <stdio.h>
#include <openssl/bn.h>
#define NBITS 256
void printBN(char *msg, BIGNUM * a)
{
	/* Use BN_bn2hex(a) for hex string
	* Use BN_bn2dec(a) for decimal string */
	char * number_str = BN_bn2hex(a);
	printf("%s %s\n", msg, number_str);
	OPENSSL_free(number_str);
}

int main ()
{
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *one = BN_new();
	BIGNUM *p = BN_new();
	BIGNUM *q = BN_new();
	BIGNUM *n = BN_new();
	BIGNUM *phi_p = BN_new();
	BIGNUM *phi_q = BN_new();
	BIGNUM *phi_n = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *res = BN_new();

	// Initialization
	BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
	BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
	BN_hex2bn(&one, "1");
	BN_hex2bn(&e, "0D88C3");

	BN_mul(n, p, q, ctx);
	printBN("n = ", n);

	// Calculate phi
	BN_sub(phi_p, p, one);
	BN_sub(phi_q, q, one);
	BN_mul(phi_n, phi_p, phi_q, ctx);

	// res = e^{-1} (mod phi_n)
	BN_mod_inverse(res, e, phi_n, ctx);
	printBN("e  = e^{-1} (mod phi_n) = ", res);
	return 0;
}
