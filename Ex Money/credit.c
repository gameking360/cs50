#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

bool Validator(char[]);
char* Transform(long);
int CalculateResult(char[]);
void CardCompany(char[]);

long numCard = 0;

int main(void){


do{
numCard = get_long("What is your card number?\n");
}while(numCard <= 100);


char *numero = Transform(numCard);

bool t = Validator(numero);

if(t){
   CardCompany(numero);

}
else printf("INVALID\n");
}


bool Validator(char numbers[]){


    int resultado = CalculateResult(numbers);
    if(resultado%10 == 0 && strlen(numbers) >= 13 && strlen(numbers) <= 16){
        return true;
    }


    return false;
}

char* Transform(long num){

    int size = snprintf(NULL,0,"%ld",num) + 1;

    char *numArray = (char *)malloc(size);

    snprintf(numArray,size,"%ld",num);

    return numArray;
}

int CalculateResult(char num[]){

bool time = true;
int total = 0;

    for(int x = strlen(num) - 1; x >= 0; x--){

    if(!time){
            time = !time;
            int digit = (num[x] - '0') * 2;
            if(digit >= 10){
                total += digit/10;
                total += digit%10;
            }
            else{
                total += digit;
            }
        }

else if(time){
       time = !time;
    total += num[x] - '0';

}


    }

    return total;
}

void CardCompany(char nums[]){

    int num1 = nums[0] - '0';
    int num2 = nums[1] - '0';

    if(num1 == 4){
        printf("VISA\n");
    }

    else if((num1 == 3) && ((num2 == 4) || (num2 == 7))){
        printf("AMEX\n");
    }
    else if((num1 == 5) && ((num2 >= 1) && (num2 <= 5))) printf("MASTERCARD\n");

    else{
        printf("INVALID\n");
    }
}
