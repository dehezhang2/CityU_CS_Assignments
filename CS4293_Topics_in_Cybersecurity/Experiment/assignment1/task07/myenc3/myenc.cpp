#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#define ENCRYPT 1
#define DECRYPT 0
unsigned char* do_crypt( unsigned char* key, unsigned char* iv, int do_encrypt){
   /* Allow enough space in output buffer for additional block */
    FILE* in = fopen("./cipher.bin", "rb");
   unsigned char* ans = (unsigned char*) malloc(40) ;
   memset(ans, 0, 40);
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
   printf("haha1\n");
   for(;;){
       printf("haha2\n");
       inlen = fread(inbuf, 1, 1024, in);
          printf("haha3\n");
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
   fclose(in);
   // free(in);
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

  size_t len = 0;
  char* line = (char*)malloc(1024);
  ssize_t read;
  int word_i = 0;
  while ((read = getline(&line, &len, word_list)) != -1) {
      unsigned char key[17];
      char key2[17];
      // printf("read: %d, line: %s",read, line);
      for(int i=0;i<16;i++){
        if(i<(int)(read)-1){
          key2[i] = key[i] = line[i];
        } else {
          key2[i] = key[i] = '#';
        }
      }
      key2[16] = key[16] = 0;       
      printf("%s\n", key2);   
      unsigned char* ans = do_crypt(key, iv, DECRYPT);

      if(ans!=NULL){
        // printf("haha\n");
        if(strcmp(key2,"Syracuse########")==0){
          std::cout << ans << std::endl;
        }
        
      } 
      free(ans);
      // printf("hh\n");
      
  }
  // unsigned char key[] = "Syracuse########";
  // unsigned char* fuck = do_crypt(key, iv, DECRYPT);
  // if(fuck) printf("%s\n", do_crypt( key, iv, DECRYPT));
  // fuck = do_crypt(key, iv, DECRYPT);
  // if(fuck) printf("%s\n", do_crypt( key, iv, DECRYPT));
  // fuck = do_crypt(key, iv, DECRYPT);
  // if(fuck) printf("%s\n", do_crypt( key, iv, DECRYPT));
  // fuck = do_crypt(key, iv, DECRYPT);
  // if(fuck) printf("%s\n", do_crypt( key, iv, DECRYPT));



printf("hhh");

  
  return 0;
}
