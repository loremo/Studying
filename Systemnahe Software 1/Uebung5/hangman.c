#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#define MAXBUFFLENGTH 255
#define BUFFERELEMENTS 1

void reservoirSampling(char* buffer,  FILE* fp){
	long dataSize = 0;
	char tmp_buffer[MAXBUFFLENGTH];
	tmp_buffer[0] = 'a'; 
	int i = 0;
	for (i; i < BUFFERELEMENTS; ++i){
		fgets(tmp_buffer, MAXBUFFLENGTH, fp);
		for (int j = 0; j < MAXBUFFLENGTH; ++j){
			buffer[i*MAXBUFFLENGTH + j] = tmp_buffer[j];
		}	
	}
	srand(time(NULL));
	while (fgets(tmp_buffer, MAXBUFFLENGTH, fp) != NULL){
		fgets(tmp_buffer, MAXBUFFLENGTH, fp);
		long index = rand() % i;
		if(index < BUFFERELEMENTS){
			for (int j = 0; j < MAXBUFFLENGTH; ++j){
				buffer[index*MAXBUFFLENGTH + j] = tmp_buffer[j];
			}
		}
		++i;
	}
}

int normalizeInput(int input){
  if ( (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') ){
    if (isupper(input)){
      input = tolower(input);
    }
    return input;
  }
  return -1;
}

_Bool checkGameOver(_Bool* alreadyChosen, char* answer, int lives){
  if (lives <= 0){
      printf("\nanswer was: %s\n", answer);
      printf("epic fail!\n");
    return true;
  }
  for (int i = 0; i < answer[i] != '\0'; i++){
    if(normalizeInput(answer[i]) != -1){ // check only letters
      if(alreadyChosen[tolower(answer[i]) - 'a'] == false){
	return false;
      }
    }
  }
  printf("\nanswer: %s\n", answer);
  printf("epic win!\n");
  return true;
}

int main(){
	int lives = 7;
	FILE* fp = fopen("Ulm.hm","r");
	char buffer[MAXBUFFLENGTH * BUFFERELEMENTS]; 
	reservoirSampling(buffer, fp);
	_Bool name = false;
	char answer[42];
	int k = 0;
	
	/*printing the question and saving the answer into an array*/
	for (int i = 0; i < BUFFERELEMENTS; ++i){
		for (int j = 0; buffer[i*MAXBUFFLENGTH + j] != '\n'; ++j){
			if(name == false){
				printf("%c",buffer[i*MAXBUFFLENGTH + j]);
			} else {
			  if (buffer[i*MAXBUFFLENGTH + j] != 0){
			    answer[k++] = buffer[i*MAXBUFFLENGTH + j];
			  }
			}
			if (buffer[i*MAXBUFFLENGTH + j] == '\t')
				name = true;
		}
		printf("\n");
	}
	//printf("answer: %s\n", answer);
	
	/* array of letters that have already been chosen */
	_Bool alreadyChosen[32] = { 0 };
	int input;
	
	
	loop: // goto label
	if (checkGameOver(alreadyChosen, answer, lives))
	  goto gameOver;
	printf("%d\t",lives);
	for (int i = 0; i < 32; ++i){
	  if(alreadyChosen[i] == true){
	    printf("%c", (char)('a' + i)); // print all the letters that have already been chosen 
	  }
	}
	printf("\t\t");
	
	/* printing the word to be guessed */
	for (int i = 0; i < answer[i] != '\0'; i++){
	  if(answer[i] == ' ' || answer[i] == '-' ||answer[i] == '.' || alreadyChosen[tolower(answer[i]) - 'a'] == true){
	    printf("%c", answer[i]);
	  } else {
	      printf("%c", '_');
	  }
	}
	printf("\n");

	while((input = getchar()) != '\n'){
	  if(normalizeInput(input) == -1){ 
	    --lives; // ivalid input
	  }
	  if(alreadyChosen[normalizeInput(input) - 'a'] == true){
	    --lives; // letter already chosen
	  } 
	  for (int i = 0; i < answer[i] != '\0'; i++){
	    if (input == tolower(answer[i])){
	      alreadyChosen[normalizeInput(input) - 'a'] = true; // right choice
	      goto loop;
	    }
	  }
	  alreadyChosen[normalizeInput(input) - 'a'] = true; // wrong choice
	  --lives;
	}
	goto loop;
	
	gameOver:
	fclose(fp);
	return 0;
}
