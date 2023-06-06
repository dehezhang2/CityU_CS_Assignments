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
	BIGNUM *n = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *M = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *C = BN_new();
	BIGNUM *M_prime = BN_new();

	// Initialization
	BN_hex2bn(&n, "E103ABD94892E3E74AFD724BF28E78366D9676BCCC70118BD0AA1968DBB143D1");
	BN_hex2bn(&e, "0D88C3");
	BN_hex2bn(&M, "4120746f702073656372657421");
	BN_hex2bn(&d, "3587A24598E5F2A21DB007D89D18CC50ABA5075BA19A33890FE7C28A9B496AEB");

	// C = M^e mod n
	BN_mod_exp(C, M, e, n, ctx);
	printBN("Encrypted M^e mod n = ", C);
	BN_mod_exp(M_prime, C, d, n, ctx);
	printBN("Decrypted C^d mod n = ", M_prime);
	return 0;
}
