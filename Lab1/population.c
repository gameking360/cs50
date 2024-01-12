#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void){

int population = 0, finalPopulation = 0, backup;
int anos = 0;
do{
    population = get_int("Start size: ");

}while(population < 9);

do{
    finalPopulation = get_int("End size: ");
}while(finalPopulation < population);

while(population < finalPopulation){
    backup = population;
    population += round((population/3));
    population -= round((backup/4));
    anos++;

}



printf("Years: %i",anos);

}
