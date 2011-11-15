#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* compile with:

gcc -std=gnu99 -o soupsum soupsum.c -lm

*/

 /**********************************************************************
 * Typical implementation of a final state machine with a lookup table *
 ***********************************************************************/
 
 /* States. */
#define  S0			0 
#define  S1			1 
#define  S2			2 
#define  S3			3 
#define  S4			4 
#define  S5			5 
#define  S6			6
#define  S7			7 
#define  TRASH			8

/* Possible inputs    */
#define  DIGIT			0 
#define  SIGN			1 
#define  DOT			2 
#define  EXP			3
#define  INVALID		4

int lookupTable[5][8] = 
{
/*S0	S1	S2	S3	S4	S5	S6	S7	*/
{S2,	S2,	S2,	S4,	S4,	S7,	S7,	S7},	/* DIGIT */
{S1,	TRASH,	TRASH,	TRASH,	TRASH,	S6,	TRASH,	TRASH},	/* SIGN */
{S3,	S3,	S4,	TRASH,	TRASH,	TRASH,	TRASH,	TRASH},	/* DOT */
{TRASH,	TRASH,	S5,	TRASH,	S5,	TRASH,	TRASH,	TRASH},	/* EXP */
{TRASH,	TRASH,	TRASH,	TRASH,	TRASH,	TRASH,	TRASH,	TRASH},	/* INVALID */
};

/* Candidates for a struct:*/
int sign = 1;  // sign of the whole expression (either 1 or -1)
int expSign = 1; // sign of the number after E/e (either 1 or -1)
int expNumber = 0; // number after E/e
int preDecimal = 0; // integer value of the whole expression
double postDecimal = 0.0; // decimal places of the whole expression ( btw. 0 and 0.9999...)
int countDecimalPlaces = 0; // amount of decimal places

/* Determines the kind of input*/
int determineInput(int ascii){
  if (ascii >= '0' && ascii <= '9')
    return DIGIT;
  else if (ascii == '+' || ascii == '-')
    return SIGN;
  else if (ascii == '.')
    return DOT;
  else if (ascii == 'e' || ascii == 'E')
    return EXP;
  return INVALID; // else
}

/*evaluates the actual char by adjusting the fields of the number-struct */
void evaluate(int ascii, int state){
  switch(state){
    case S1:;
      sign = ascii=='+'?1:-1;
      break;    
    case S2:;
      preDecimal = preDecimal * 10 + (ascii - '0');
      break;  
    case S4:;
      if(ascii != '.'){
	postDecimal = postDecimal + (double)(ascii - '0') * exp10(--countDecimalPlaces);
      }
      break;   
    case S6:;
      expSign = ascii=='+'?1:-1;
      break;  
    case S7:;
      expNumber = expNumber * 10 + (ascii - '0');
      break;  
    default:
      return;
  }
}

int main(){
  printf("Type in:\n");
  int input;
  int currentState = S0;
  double sum = 0.0;
  while ((input = getchar()) != EOF){
    currentState = lookupTable[determineInput(input)][currentState];
    if ( currentState == TRASH){
      sum = sum + sign * (preDecimal + postDecimal) * exp10(expSign * expNumber);
      currentState = S0;
      /* setting the fields of the number-struct to it's initial values */
      sign = 1;
      expSign = 1;
      expNumber = 0;
      preDecimal = 0;
      postDecimal = 0.0;
      countDecimalPlaces = 0;
    }
    else{
      evaluate(input, currentState);
    }
  }
  printf("\n%.4f\n", sum);
  return 0;
}
