#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int number(void){
    srand(time(NULL));
    return rand() % 3;
}

void win(void){
    printf("You win\n");
}

void lose(void){
    printf("You lose\n");
}

void tie(void){
    printf("Tie\n");
}

int main(void){
    int hand;
    printf("Chose number:\n 1. Rock\n 2. Paper\n 3. Scissors\n");
    scanf(">%d\n", &hand);
    int ans = number() - hand;
    switch (ans)
    {
    case -2:
        lose();
        break;
    case -1:
        win();
        break;
    case 0: 
        tie();
        break;
    case 1:
        lose();
        break;
    case 2:
        win();
        break;
    default:
        printf("Wrong input\n");
        break;
    }        
    return 0;
}