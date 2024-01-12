#include <stdio.h>
#include <cs50.h>
#include<string.h>
#include<math.h>

float DiscoverAbility(string);

int main(void){

string text = get_string("Write a text: ");

int grade = round(DiscoverAbility(text));

if(grade >= 16){
printf("Grade 16+\n");
}
else if(grade <1) printf("Before Grade 1\n");
else printf("Grade %i\n",grade);

}


float DiscoverAbility(string text){
int numLetters = 0, numSentences = 0, numWords = 0;


for(int i = 0, n = strlen(text); i < n; i++ ){

    if(text[i] == 33 || text[i] == 63 || text[i] == 46){
        numSentences++;
        numWords++;
    }
    else if((text[i] == 32 || text[i] == 44) && !(text[i - 1] == 33 || text[i-1] == 63 || text[i - 1] == 46 || text[i - 1] == 44)){
        numWords++;
    }
    else if((text[i] > 96 && text[i] < 123) || (text[i] > 64 && text[i] < 91)) numLetters++;

}
printf("Words: %i\nLetters: %i\nSentences: %i\n",numWords,numLetters,numSentences);

float averageLetters = (numLetters /  (float) numWords) * 100;
float averageWords = (numSentences / (float) numWords) * 100;

float grade = 0.0588 * averageLetters - 0.296 * averageWords - 15.8;
printf("%f\n",grade);

return grade;
}
