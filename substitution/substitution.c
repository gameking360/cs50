#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

bool Check(string);
string Encrypt(string,string);

const string minAlfabet = "abcdefghijklmnopqrstuvwxyz";

int main(int argc,string argv[]){

    if(argc != 2){
        printf("Erro\n");
        return 1;
    }

    if(Check(argv[1]) == false){
        printf("Use ./substitution key");
        return 1;
    }


    string text = get_string("plaintext: ");
    string encrypt = Encrypt(text,argv[1]);

    printf("ciphertext: %s\n",encrypt);
}


bool Check(string key){

    if(strlen(key) != 26){
        return false;
    }

    for(int x = 0, s = strlen(key);x < s; x++ ){

        if((key[x] < 65 || key[x] > 90) && (key[x] < 97 || key[x] > 122 )){
            return false;
        }

        for(int y = x + 1, z = strlen(key); y < z; y++ ){
            if(key[x] == key[y]){
                return false;
            }
        }
    }

    return true;
}


string Encrypt(string text, string key) {
    for (int x = 0, y = strlen(text); x < y; x++) {
        if (isupper(text[x])) {
            int index = text[x] - 'A';
            text[x] = isupper(key[index]) ? key[index] : toupper(key[index]);
        } else if (islower(text[x])) {
            int index = text[x] - 'a';
            text[x] = islower(key[index]) ? key[index] : tolower(key[index]);
        }
    }

    return text;
}
