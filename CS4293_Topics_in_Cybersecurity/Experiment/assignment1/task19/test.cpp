#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

#define llong long long 
#define ENCRYPT 1
#define DECRYPT 0
#define TEXTLEN 16
#define KEYSIZE 16

unsigned char* do_crypt( unsigned char* intext, unsigned char* key, 
                         unsigned char* iv, int do_encrypt
){
   unsigned char* ans = (unsigned char*) malloc(1024) ;
   memset(ans, 0, 1024);
   unsigned char outbuf[1024];
   int outlen, tmplen;

   EVP_CIPHER_CTX ctx;

   /* Don't set key or IV right away; we want to check lengths */
   EVP_CIPHER_CTX_init(&ctx);
   EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, NULL, NULL,
           do_encrypt);
   OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == 16);
   OPENSSL_assert(EVP_CIPHER_CTX_iv_length(&ctx) == 16);
   /* Now we can set key and IV */
   EVP_CipherInit_ex(&ctx, NULL, NULL, key, iv, do_encrypt);

  if(!EVP_EncryptUpdate(&ctx, outbuf, &outlen, intext, TEXTLEN)){
    /* Error */
    return 0;
  }

  if(!EVP_EncryptFinal_ex(&ctx, outbuf + outlen, &tmplen)){
    /* Error */
    return 0;
  }
  outlen += tmplen;
  EVP_CIPHER_CTX_cleanup(&ctx);
  memcpy(ans, outbuf, outlen);
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

  // Convert hex cipher text into string
  unsigned char plaintext[TEXTLEN];
  const char* tmp = "255044462d312e350a25d0d4c5d80a34";
  int length = strlen(tmp);
  char buf = 0;
  for(int i = 0; i < length; i++){
    if(i % 2 != 0){
      plaintext[i/2] = hex_to_ascii(buf, tmp[i]);
    }else{
      buf = tmp[i];
    }
  }

  unsigned char ciphertext[TEXTLEN];
  const char* tmp1 = "d06bf9d0dab8e8ef880660d2af65aa82";
  length = strlen(tmp1);
  buf = 0;
  for(int i = 0; i < length; i++){
    if(i % 2 != 0){
      ciphertext[i/2] = hex_to_ascii(buf, tmp1[i]);
    }else{
      buf = tmp1[i];
    }
  }

  unsigned char iv[16];
  const char* tmp2 = "09080706050403020100A2B2C2D2E2F2";
  length = strlen(tmp2);
  buf = 0;
  for(int i = 0; i < length; i++){ 
    if(i % 2 != 0){
      iv[i/2] = hex_to_ascii(buf, tmp2[i]);
    }else{
      buf = tmp2[i];
    }
  }

  llong start = 1524013689L, end = 1524020889L;

  for(llong i = start; i <= end; i++){
    srand(i);

    unsigned char key[17];
    char key2[17];
    for (int j = 0; j< KEYSIZE; j++){
       key2[j] = key[j] = rand()%256;
    }
    key2[16] = key[16] = 0;
    unsigned char* ans = do_crypt(ciphertext, key, iv, DECRYPT);
    if(ans){
      int same = 1;
      char check[16];
      for(int j=0;j<TEXTLEN;j++){
        check[j] = ans[j];
        if(ans[j] != plaintext[j] ){
          same = 0;
          break;
        } else {
          // printf("Same %d", j);
        }
      }
      if(same){
        printf("Time: %lld, key: %s", i, key2);
      }
    } 
        
  }

  return 0;
}
