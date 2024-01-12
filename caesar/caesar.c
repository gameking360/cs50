#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string Criptgraf(int,string);

int main(int argc,string argv[]){



if(argc > 2 || argc == 1){
    printf("Erro\n");
    return 1;
}

for(int x = 0; argv[1][x] != '\0';x++){
    if(!isdigit(argv[1][x])){
        printf("Use ./caesar key");
        return 1;
    }
}

string s = get_string("plaintext: ");
string criptografada = Criptgraf( atoi(argv[1]), s);

printf("ciphertext: %s\n",criptografada);
return 0;
}


string Criptgraf(int p,string text){

    for(int i = 0, n = strlen(text); i < n; i++){
        int count = p;

        if((text[i] >= 65 && text[i] < 91) || (text[i] < 123 && text[i] >= 97)){

            while(count != 0){
                    text[i]++;
                if(text[i] == 91){
                    text[i] = 65;
                }
                else if(text[i] == 123) text[i] = 97;

            count--;
        }

        }

    }
return text;
}
