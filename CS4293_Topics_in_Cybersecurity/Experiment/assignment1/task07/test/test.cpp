#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>
#define ENCRYPT 1
#define DECRYPT 0
const unsigned char* do_crypt(FILE *in, unsigned char* key, unsigned char* iv, int do_encrypt){
   /* Allow enough space in output buffer for additional block */
   unsigned char* ans = (unsigned char*) malloc(1024) ;
   memset(ans, 0, 1024);
   unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
   int inlen, outlen;
   EVP_CIPHER_CTX ctx;
   int totlen=0;
   /* Don't set key or IV right away; we want to check lengths */
   EVP_CIPHER_CTX_init(&ctx);
   EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, NULL, NULL,
           do_encrypt);
   OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == 16);
   OPENSSL_assert(EVP_CIPHER_CTX_iv_length(&ctx) == 16);
   /* Now we can set key and IV */
   EVP_CipherInit_ex(&ctx, NULL, NULL, key, iv, do_encrypt);

   for(;;){
       inlen = fread(inbuf, 1, 1024, in);
       if(inlen <= 0) break;
       if(!EVP_CipherUpdate(&ctx, outbuf, &outlen, inbuf, inlen)){
        /* Error */
           EVP_CIPHER_CTX_cleanup(&ctx);
           return 0;
      }
       // fwrite(outbuf, 1, outlen, out);
      memcpy(ans+totlen, outbuf, outlen);
      totlen+=outlen;
   }
   if(!EVP_CipherFinal_ex(&ctx, outbuf, &outlen)){
       /* Error */
       EVP_CIPHER_CTX_cleanup(&ctx);
       return 0;
   }
   //fwrite(outbuf, 1, outlen, out);
   memcpy(ans+totlen, outbuf, outlen);
   EVP_CIPHER_CTX_cleanup(&ctx);
   return ans;
}



int hex_to_int(char c){
  if(c<='9'&&c>='0'){
    return c-'0' + 0;
  } else {
    return c-'a' + 10;
  }
}

int hex_to_ascii(char c, char d){
  int high = hex_to_int(c) * 16;
  int low = hex_to_int(d);
  return high+low;
}

int main(){
	FILE* in = fopen("./cipher.bin", "rb");
	FILE* word_list = fopen("./assignment1-words.txt", "rb");
  unsigned char key[] = "Syracuse########";
  unsigned char iv[16];
  const char* tmp2 = "aabbccddeeff00998877665544332211";
  int length = strlen(tmp2);
  char buf = 0;
  for(int i = 0; i < length; i++){ 
    if(i % 2 != 0){
      iv[i/2] = hex_to_ascii(buf, tmp2[i]);
    }else{
      buf = tmp2[i];
    }
  }
  printf("%s", do_crypt(in, key, iv, DECRYPT));

	return 0;
}
