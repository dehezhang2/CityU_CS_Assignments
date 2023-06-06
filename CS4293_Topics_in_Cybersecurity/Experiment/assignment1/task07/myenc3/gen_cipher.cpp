#include <string.h>
#include <stdio.h>

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
	FILE* cipher_text = fopen("./cipher.bin", "wb");
	char ciphertext[32];
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
  	fwrite(ciphertext, 1, 32, cipher_text);
	return 0;
}