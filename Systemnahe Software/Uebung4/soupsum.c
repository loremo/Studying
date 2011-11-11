#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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

double sum = 0.0;
int sign = 1;  // either 1 or -1
int expSign = 1; // either 1 or -1
int expNumber = 0;
int preDecimal = 0;
double postDecimal = 0.0;
int countDecimalPlaces = 0;

int determineInput(int ascii){
  if (ascii >= '0' && ascii <= '9')
    return DIGIT;
  else if (ascii == '+' || ascii == '-')
    return SIGN;
  else if (ascii == '.')
    return DOT;
  else if (ascii == 'e' || ascii == 'E')
    return EXP;
  return INVALID;
}

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
	//printf(" %d * %f = %f\n",(ascii - '0'), exp10(countDecimalPlaces), (ascii - '0') * exp10(countDecimalPlaces));
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
  printf("Eintippen:\n");
  int a;
  int currentState = S0;
  while ((a = getchar()) != EOF){
    currentState = lookupTable[determineInput(a)][currentState];
    if ( currentState == TRASH){
      sum = sum + sign * (preDecimal + postDecimal) * exp10(expSign * expNumber);
      //printf("number: %f\n", sign * (preDecimal + postDecimal) * exp10(expSign * expNumber));
      currentState = S0;
      sign = 1;
      expSign = 1;
      expNumber = 0;
      preDecimal = 0;
      postDecimal = 0.0;
      countDecimalPlaces = 0;
    }
    else{
      evaluate(a, currentState);
    }
  }
  printf("\n%.4f\n", sum);
  return 0;
}
