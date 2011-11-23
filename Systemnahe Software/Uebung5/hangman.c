#include <stdio.h>
#define MAXBUFFLENGTH 100
#define BUFFERELEMENTS 1

void reservoirSampling(char* buffer,  FILE* fp){
	long dataSize = 0;
	char tmp_buffer[MAXBUFFLENGTH];
	tmp_buffer[0] = 'a';
	while (tmp_buffer[0] != '\n'){
		++dataSize;	
	}
	fclose(fp);
	fp = fopen("Ulm.hm","r");
	int i = 0;
	for (i; i < BUFFERELEMENTS; ++i){
		fgets(tmp_buffer, MAXBUFFLENGTH, fp);
		printf("inside function: %s",tmp_buffer);
		for (int j = 0; j < MAXBUFFLENGTH; ++j){
			buffer[i*MAXBUFFLENGTH + j] = tmp_buffer[j];
		}	
	}
	for (i; i < dataSize; ++i){
		//to do here
	}
}

int main(){
	FILE* fp = fopen("Ulm.hm","r");
	char buffer[MAXBUFFLENGTH * BUFFERELEMENTS];
	reservoirSampling(buffer, fp);
	for (int i = 0; i < 200; ++i)
		printf("%d.char ist: \t%c\n",i,buffer[i]);
	printf("blubb: %s",buffer);
	fclose(fp);
	return 0;
}
