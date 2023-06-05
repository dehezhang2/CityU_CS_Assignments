#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

int main(){

    char *input = NULL ;
    char prompt[] = "Your command:";
    input = readline(prompt);
    printf("%s\n", input);
    return 0;
}

