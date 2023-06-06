#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>
#define ENCRYPT 1
#define DECRYPT 0

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

  if(!EVP_EncryptUpdate(&ctx, outbuf, &outlen, intext, 32)){
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

  size_t len = 0;
  char* line = (char*)malloc(1024);
  ssize_t read;
  int word_i = 0;
  while ((read = getline(&line, &len, word_list)) != -1) {
      unsigned char key[17];
      char key2[17];
      for(int i=0;i<16;i++){
        if(i<(int)(read)-1){
          key2[i] = key[i] = line[i];
        } else {
          key2[i] = key[i] = '#';
        }
      }
      key2[16] = key[16] = 0;       
      unsigned char* ans = do_crypt(ciphertext, key, iv, DECRYPT);
      if(ans){
        char check_ans[22];
        for(int i=0; i< 21;i++){
          check_ans[i] = ans[i];
        }      
        check_ans[21] = 0;
        if(strcmp(check_ans, "This is a top secret.") == 0){
          printf("%s\n", key2);
        }
      } 
  }
  return 0;
}
