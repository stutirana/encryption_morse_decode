// Define all helper functions for hw2 in this file
#include "../include/helpers2.h"

int notin(char c,char* key){

	int there = 1;// 1 is false
	
	while(*key){// we want to go trhgouh the entire line for each character
		
		if(*key!= c){
			key++;
		}else{
			
			there = 0;
			break;
		}
		
	}
	
	return there;
}

void remove_char(char *line, char c){
	// hopefully this chages the actually line
	if(*line ==0){
		return;
	}
	char * write=line ;
	while(*line){// we want to go through the entire line for each character

		if(*line!= c){
			*write++ =*line++;
		}else{
			line++;
		}
		
	}
	*write= '\0';
}

void init(char * str, int max) {
	int i;
	for(i =0; i<max;i++){
		*str++ = ' ';
	}
	return;

}
void init_ABCs(char * str) {
	int i;
	char first = 'A';
	for(i =0; i<26;i++){
		*str++ = first;
		first++;
	}
	str = '\0';
	return;

}
void init_ZYX(char * str) {
	int i;
	char first = 'Z';
	for(i =0; i<26;i++){
		*str++ = first;
		first--;
	}
	
	return; 
}

void getchars(char * FMCtoKey,int i,char * encryptchar){
	int starting = i*3;
	int count = 0;
	FMCtoKey+=starting;
	while (count<3){
		
		*encryptchar++=*FMCtoKey++;
		count++;
	}
}

int ismatch(char * encryptchar, char * mcmsg){
	int m = 0;//true is match
	int size =0;
	while (size<3){
		if(*mcmsg=='\0' ||*mcmsg == 32){
			m =-1;
			break;
		}
		if(*encryptchar != *mcmsg){
			m = -1;//nope wrong
			break;
		}
		
		encryptchar++;
		mcmsg++;
		size++;
	}
	return m;
}

int slen(char *line){
	if(*line ==0){
		return 0;
	}
	int count = 0;
	while(*line){
		line++;
		count++;
	}
	return count;
}

