#include <stdio.h>
#include <cs50.h>
#include <math.h>

void Easy();

int main(void){

Easy();

}

void Easy(void){

float total = 0;
int coins = 0;

while(total <= 0){
    total = get_float("How many is the change?\n");
}

total = round(total*100);

while(total >= 25){
total -= 25;
coins++;
}
while(total >= 10){
    total-= 10;
    coins++;
}
while(total >= 5){
    total -= 5;
    coins++;
}
while(total != 0){
    total -=1;
    coins++;
}

printf("%i",coins);
printf("\n");
}
