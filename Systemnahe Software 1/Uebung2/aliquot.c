#include <stdio.h>
#include <time.h>

// determines if a is a divisor of b
_Bool isDivisor(int a, int b){
  return (b % a == 0);
}

// randomly chooses divisor for a given number
int generateNumber(int number){
  int count = 0; // counts how many divisors exist for the given number
  for (int i = 1; i < number; ++i){
    if (number % i == 0){
      count++;
    }
  }
  
  srand(time(NULL));
  int index = rand() % count + 1; // chooses one divisor randomly
  
  count = 0;
  for (int i = 1; i < number; ++i){
    if (number % i == 0){
      count++;
    }
    if (count == index){
      return i; // return the divisor with the chosen index
    }
  }
  return -1; // should never be here (since every number has at least one divisor)
}

int main(){
  srand(time(NULL));
  int number = rand() % 50 +10;
  printf("*** Aliquot Game ***\n");

  while (number != 0){
    printf("Number: %d\nYou:", number);
    int input = 0;
    scanf("%d", &input);
    if (input >= number || input <= 0){
      printf("Out of range!\n");
      continue;
    }
    if(!isDivisor(input, number)){
      printf("No proper divisor!\n");
      continue;
    }
    number -= input;
    if (number == 1){
      printf("You win!\n");
      break;
    }
    printf("Number: %d\n", number);
    int botNumber = generateNumber(number);
    printf("Bot: %d\n", botNumber);
    number -= botNumber;
    if (number == 1){
      printf("You lose!\n");
      break;
    }
  }
  return 0;
}