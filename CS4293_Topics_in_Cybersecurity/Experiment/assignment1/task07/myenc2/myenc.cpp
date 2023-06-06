#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>
#define ENCRYPT 1
#define DECRYPT 0

int do_crypt(FILE *in, FILE *out, 
  unsigned char* iv, int do_encrypt){
  unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
  int inlen, outlen;
  EVP_CIPHER_CTX ctx;

  EVP_CIPHER_CTX_init(&ctx);
  EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, NULL, NULL,
                do_encrypt);
  OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == 16);
  OPENSSL_assert(EVP_CIPHER_CTX_iv_length(&ctx) == 16);
  /* Now we can set key and IV */
  unsigned char key[] = "Syracuse########";
  EVP_CipherInit_ex(&ctx, NULL, NULL, key, iv, do_encrypt);
  for(;;){
    inlen = fread(inbuf, 1, 1024, in);
    if(inlen <= 0) break;
    if(!EVP_CipherUpdate(&ctx, outbuf, &outlen, inbuf, inlen)){
      /* Error */
      printf("haha1\n");
      EVP_CIPHER_CTX_cleanup(&ctx);
      return 0;
    }
    fwrite(outbuf, 1, outlen, out);
  }
  if(!EVP_CipherFinal_ex(&ctx, outbuf, &outlen)){
    /* Error */
    printf("haha2\n");
    EVP_CIPHER_CTX_cleanup(&ctx);
    return 0;
  }
  fwrite(outbuf, 1, outlen, out);
  EVP_CIPHER_CTX_cleanup(&ctx);
  return 1;
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
	FILE* word_list = fopen("./assignment1-words.txt", "rb");
  FILE* in = fopen("./cipher.bin", "rb");
  FILE* out = fopen("./myenc.txt", "wb");
  
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

  // Test iv
  // for(int i=0;i<16;i++){
  //   printf("%d ", iv[i]);
  // }
  // printf("\n");

  // Try one by one
  size_t len = 0;
  char* line = (char*)malloc(1024);
  ssize_t read;
  int word_i = 0;
  while ((read = getline(&line, &len, word_list)) != -1) {
      unsigned char key[17];
      printf("read: %d, line: %s",read, line);
      for(int i=0;i<16;i++){
        if(i<(int)(read)-1){
          key[i] = line[i];
        } else {
          key[i] = '#';
        }
      }
      key[16] = 0;
                
      // printf("%s\n", key); 
      // printf("%d\n", do_crypt(in, out, key, iv, DECRYPT));
      if(do_crypt(in, out, iv, DECRYPT)){
        FILE* check = fopen("./myenc.txt", "rb");
        char inbuf[1024];
        int inlen = fread(inbuf, 1, 1024, check);
        printf("%d\n", inlen);
        if(inlen==16){
          printf("key: %s, decrypt:%s\n", key, inbuf);
        }
      }
  }
	return 0;
}
