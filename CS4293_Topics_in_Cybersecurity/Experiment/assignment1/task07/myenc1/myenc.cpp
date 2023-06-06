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
  // for(int i = 0;i<=255;i++){
  //   char c = i;
  //  // printf("%d ", c);
  //   unsigned char x = 
  //   if(255-(~c)!=i)printf("=================\n");
  // }
	FILE* in = fopen("./plain.txt", "rb");
	FILE* word_list = fopen("./assignment1-words.txt", "rb");

  // Convert hex cipher text into string
  unsigned char ciphertext[32];
  const char* tmp = "764aa26b55a4da654df6b19e4bce00f4ed05e09346fb0e762583cb7da2ac93a2";
  int length = strlen(tmp);
  char buf = 0;
  for(int i = 0; i < length; i++){
    if(i % 2 != 0){
      ciphertext[i/2] = hex_to_ascii(buf, tmp[i]);
    }else{
      buf = tmp[i];
    }
  }
  // ciphertext[length/2] = 0;

  // for(int i=0;i<32;i++){
  //   printf("%d ", ciphertext[i]);
  // }
  // printf("\n");

  unsigned char iv[16];
  const char* tmp2 = "aabbccddeeff00998877665544332211";
  length = strlen(tmp2);
  buf = 0;
  for(int i = 0; i < length; i++){
    if(i % 2 != 0){
      iv[i/2] = hex_to_ascii(buf, tmp2[i]);
    }else{
      buf = tmp2[i];
    }
  }
  // iv[length/2] = 0;

  // for(int i=0;i<16;i++){
  //   printf("%d ", iv[i]);
  // }
  // printf("\n");

  // Try one by one
  size_t len = 0;
  char* line = (char*)malloc(1024);
  ssize_t read;
int zlq = 0;
  while ((read = getline(&line, &len, word_list)) != -1) {

      unsigned char key[17]={0};
      for(int i=0;i<16;i++){
        if(i<int(read)-1){
          key[i] = line[i];
        } else {
          key[i] = '#';
        }
      }

      // printf("%s\n", key);
      const unsigned char* cipher = do_crypt(in, key, iv, ENCRYPT);
  //      for(int i=0;i<32;i++){
  //   printf("%d ", cipher[i]);
  // }
  // printf("\n");
      //printf("key: %s, cipher: %s\n", key, cipher);
      bool res = 1;
int maxI = 0;
      if(cipher==NULL)continue;
      for(int i=0;i<32;i++){
        if(cipher[i]!=ciphertext[i]){
          res = 0;
maxI = maxI>i?maxI:i;
          break;
        }
      }
zlq = zlq>maxI?zlq:maxI;
      if(res){
        printf("Answer key: %s, cipher: %s\n", key, cipher);
        break;
      }
  }
printf("%d\n", zlq);
	return 0;
}
