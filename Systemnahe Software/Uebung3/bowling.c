#include <stdio.h>
#include <stdbool.h>

void setBit(unsigned long *dataset, unsigned short pos, _Bool value){
   if (value)
      *dataset = *dataset | (1 << pos);
   else
      *dataset = *dataset & ~(1 << pos); 
   return;
}

_Bool getBit(unsigned long dataset, unsigned short pos) {
   return false | ((dataset & (1 << pos)) >> pos);
}

_Bool play(unsigned long *dataset, int pos){
   if(pos < -32 || pos > 32 || pos == 0){
      printf("Invalid pin number.\n");
      return false;
   }
   else if(pos > 0){ // 1 cone chosen
      if(!getBit(*dataset, pos-1)){
         printf("Pin %d is no longer standing.\n", pos);
         return false;
      }
      else{
         setBit(dataset, pos-1, 0);
	 return true;
      }
   }
   else if(pos < 0){ // 2 cones chosen
      if(!getBit(*dataset, -1*pos-1)){ // check if n-th cone is still standing
         printf("Pin %d is no longer standing.\n", -1*pos);
         return false;
      }
      else if(!getBit(*dataset, -1*pos)){ // check if (n+1)-th cone is still standing
         printf("Pin %d is no longer standing.\n", -1*pos+1);
         return false;
      }
      else{
         setBit(dataset, -1*pos-1, 0); // set n-th cone
         setBit(dataset, -1*pos, 0); // set (n+1) cone
         return true;
      }
   }
}

void printKegeln(unsigned long *dataset) {
    for(int i = 1; i <= 32; ++i){
      if(getBit(dataset,i-1)){
	printf("/\\ ");
      } else {
      	printf("   ");
      }
    }
    printf("\n");
    for(int i = 1; i <= 32; ++i){
      if(getBit(dataset,i-1)){
	printf("%02d ",i);
      } else {
      	printf("   ");
      }
    }
    printf("\n");
}

void bot(unsigned long *dataset){
   int kegelnCount = 0; // how many cones are still standing
   for(int i = 0; i < 32; ++i) {
      kegelnCount += getBit(*dataset, i);
   }
   srand(time(NULL));
   int index = rand() % kegelnCount + 1; // choose the index of the cone to be removed
										 //(not the same as the position of the cone in the dataset!
										 // this will be computed in the next step)
   for(int i = 0; i < 32; ++i) {
      if(getBit(*dataset, i)){
	 --index;
	 if(index == 0){
	    index = i + 1; // the position of the cone to be removed in the dataset
	    break;
	 }
      }
   }
   srand(time(NULL));
   if(getBit(*dataset, index)){ // is the (pos+1)-th cone standing?
      if ((rand() % 2) != 0){ // if so, remove 1 or 2 cones?
         play(dataset, index); 
         printf("My Move: %d\n", index);
      }
      else{
	 play(dataset, -1*index);
         printf("My Move: %d\n", -1*index);
      }
   }
   else{ // the (pos+1)-th cone isn't standing, so you can only remove 1 cone.
      play(dataset, index);
      printf("My Move: %d\n", index);
   }
}

int main() {
   srand(time(NULL));
   unsigned long kegeln = 0;
   unsigned anzKegeln = rand() % 22 + 10;
   for (int i = 0 ; i < anzKegeln; ++i){
      setBit(&kegeln, i, 1);
   }
   printf("*** Dawson’s Bowling Game ***\n");
   printKegeln(kegeln);
   printf("Your Move: ");
   int pos = 0;
   while (scanf("%d",&pos) == 1){
      if (!play(&kegeln, pos)){ // invalid input
	     printf("Your Move: "); 
         continue;
      }
      if(kegeln == 0){
         printf("*** You win! ***\n");
         break;
      }
      printKegeln(kegeln);
      bot(&kegeln);
      if(kegeln == 0){
         printf("*** You lose! ***\n");
         break;
      }
      printKegeln(kegeln);
      printf("Your Move: ");
   }
   return 0;
}
