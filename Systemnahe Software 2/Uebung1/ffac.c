#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

//#define MAXPRIM ULLONG_MAX
#define MAXPRIM 32

void addFactor(unsigned long int *factors, int *count, unsigned long int newFactor) {
    factors[*count] = newFactor;    
    factors = realloc(factors, (++(*count) + 1)*sizeof(unsigned long int));
    if (factors == NULL) {
      printf("couldnt allocate memory");
      exit(0);
    }
}

void factorize(unsigned long int n) {
  unsigned long int stop = n / 2;
  _Bool thereAreFactors = false;
  unsigned long int lastFactor = 0;
  printf("%lu:\t", n);
  
  unsigned long int * factors = malloc(sizeof(unsigned long int));
  int count = 0;
  
  if ( (n % 2) == 0 ){
    addFactor(factors, &count, 2);
    thereAreFactors = true;
    n /= 2;
  }
  
  for (unsigned long int i = 3; i <= stop; i+=2) {
    
    if ( (n % i) == 0 ){
      n /= i;
      thereAreFactors = true;
      if (lastFactor != i) {
	addFactor(factors, &count, i);
	lastFactor = i;
      }
      i = 1;
    }
  }
  
  /* n is a prime already*/
  if (!thereAreFactors){
    addFactor(factors, &count, n);
  }
  for (int i = 0; i < count; ++i)
    printf("%lu\t",factors[i]);
  printf("\n");
}

int main(int argc, char *argv[] ) {
  if (argc < 2) {
    printf("Usage: %s NUMBER1 [NUMBER2 ...]\n", argv[0]);
    exit(1);
  }
  
  pid_t pid;

  
  for (int i = 1; i < argc; ++i) {
    pid = fork();
    if (pid == -1) {
      perror("unable to fork"); exit(1);
    }
    if (pid == 0) {    
      unsigned long int n = strtoul(argv[i], NULL, 10);  
      factorize(n);
    exit(0);
    }
  }
  
 return 0;
}