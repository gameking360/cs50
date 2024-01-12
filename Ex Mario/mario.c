#include <stdio.h>
#include <cs50.h>

void Less();
void More();
void Scanner(int);


int main(void){

//Less();

More();
}




void Less(void){
    int flors = 0;
     int max;

    do{
    flors = get_int("How many floors are?\n");
     max = flors;
    }while(flors < 1 || flors > 8);


    for(int i = 1;i <= max; i++){

flors--;
for(int counter = 0; counter < flors; counter++){
    printf(" ");

}
        Scanner(i);
        printf("\n");

    }
}

void More(void){

    int Max = 0;

    do{
        Max = get_int("How many floats are?");
    }while(Max < 1 || Max > 8);

    for(int x = 1; x <= Max; x++){

        for(int z = 0; z < Max - x; z++){
            printf(" ");
        }

        Scanner(x);
        printf("  ");
        Scanner(x);
        printf("\n");
    }

}

void Scanner(int n){
for(int x = 1; x <= n;x++){
            printf("#");
        }

}
