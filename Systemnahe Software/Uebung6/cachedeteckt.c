#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <limits.h>
#include <unistd.h>

#define MAXSIZE 1000000
#define ITERATIONS (10000000)
#define STEP 10000

struct data {

  struct data* next;
};

void FisherYatesShuffle(int * array, int size){
  srand(time(NULL));
  for (int i = size-1; i > 0 ; i--){  
    int j = rand() % i;
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
  }
}

int main() {
for (int iter = 1; iter < MAXSIZE; iter = iter + STEP){
    int indezes[iter];
    memset( indezes, 0, iter*sizeof(int) );
    struct data dataArray[iter];
    memset( dataArray, 0, iter*sizeof(struct data) );
    for (int i = 0; i < iter; ++i){
      indezes[i] = i;
    }
    FisherYatesShuffle(&indezes, iter);
    for (int i = 0; i < iter; ++i){
      dataArray[i].next = &(dataArray[indezes[i]]);
    }
    
    // CLK_TCK: ticks per second -- is system dependent 
    #ifndef CLK_TCK
    int CLK_TCK = sysconf(_SC_CLK_TCK);
    #endif

    clock_t ticks;
    double nanosecs;
    struct tms timebuf1, timebuf2;

    // initialization for loop 
    struct data* tmp = &(dataArray[0]);
    
    int i = 0;
    times(&timebuf1);
      //********** start time measurment **************
    for (int i = 0; i < (ITERATIONS); ++i){
      tmp = tmp->next;
    }
    
    //********** stop time measurment ****************
    times(&timebuf2);
    // get number of ticks 
    ticks = timebuf2.tms_utime - timebuf1.tms_utime;
    //* convert to human readable unit: nano seconds *
    nanosecs = (double)ticks / CLK_TCK * 1000000000;
    printf(" \" %d\",\t\"%f\"\n", iter, nanosecs, (nanosecs/(double)1000000000));
  }
}
