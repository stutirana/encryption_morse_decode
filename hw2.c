// Stuti Rana
// 85039361

#include "../include/hw2.h"
#include "helpers2.h"

// Part 1  Functions to implement
void createSecretKey(char* keyphrase, char* keyArray) {
	
	char * available=(char*)malloc(27*sizeof(char));
	//char * available = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i = 0;
	char cap=*keyphrase;
	char* firstel = available;
	int val;
	init_ABCs(available);
	if (keyArray ==NULL || keyphrase==NULL){
		return;
	}else if(*keyphrase== 0){
		init_ZYX(keyArray);
	}else{
		int count = 0;

		while(*keyphrase){
			cap=*keyphrase;
			val =notin(cap, available);
			if(97<=*keyphrase && *keyphrase<123){//is it lower

				cap = *keyphrase-32;
				val =notin(cap, available);
				if(val==0){//check if it is in the available ones
					*keyArray++ = cap;//out the value in keyArray and iterate
					
					remove_char(available,cap);//remove the character you just added from available	
					
				}
			}else if(65<=*keyphrase && *keyphrase<=90 && val==0){
				
				char c = *keyphrase;
				*keyArray++ = c;
				
				remove_char(available,c);
				
			}
			keyphrase++;
		}
		
		while(*available){
			*keyArray++ = *available++;//add the rest of the alphabet to keyArray
		}
		*keyArray='\0';
	}
	free(firstel);
}

char morseToKey(char* mcmsg, char* FMCtoKey, char* key) {
	char match =-1;
	char * encryptchar = (char*)malloc(3*sizeof(char));
	init(encryptchar,3);
	int i = 0;
	if (mcmsg ==NULL || FMCtoKey==NULL || key==NULL){
		return match;
	}
	while(i<26){
		getchars(FMCtoKey,i,encryptchar);

		if(ismatch(encryptchar,mcmsg)==0){
			key+=i;

			match = *key;
			break;
		}
		i++;
	}
	
	free(encryptchar);
	return match;
}


// Part 2 Functions to implement

void mapping_tPrinter(void* val_ref) {
	mapping_t* mp;
	mp = (mapping_t*)val_ref;
	//mp =val_ref;
	if(val_ref!=NULL){
		fprintf(stderr, "%c: %s", mp->ASCII,mp->sequence);
	}
}

int mapping_tComparator(void* lhs, void* rhs) {
	mapping_t* mpl;
	mpl = (mapping_t*)lhs;
	//mpl =lhs;
	mapping_t* mpr;
	mpr = (mapping_t*)rhs;
	//mpr =rhs;
	if(lhs==NULL || rhs == NULL){
		return 0;
	} else if(mpl->ASCII<mpr->ASCII){
		return -1;
	}else if (mpl->ASCII>mpr->ASCII){
		return 1;
	}else{
		return 0;
	}
}

void mapping_tDeleter(void* val_ref) {
	
	if(val_ref!=NULL){
		mapping_t* mp;
		mp = (mapping_t*)val_ref;
		mp =val_ref;
		free(mp->sequence);
		free(val_ref);

	}
}

void DestroyList(list_t* list) {
	node_t* nodes=NULL;
	if(list!=NULL){
		nodes= list->head;

	}
	
	while(nodes!=NULL){
		node_t * pnext = nodes->next;
		mapping_tDeleter(nodes->data);
		free(nodes);
		nodes  = pnext;
	}
	free(list);
}

mapping_t* CreateMapping(char* line) {

	
	mapping_t * lcadd = malloc(sizeof(mapping_t));
	lcadd->ASCII  = *line;
	
	line+=2;
	int s = slen(line)-1;

	char * sq=(char*)malloc(s*sizeof(char));

	init(sq,s);

	lcadd->sequence = sq;
	while(*line){
		if(*line!=10){
			*sq++= *line++;
		}else{
			break;
		}
	}
	sq='\0';

	return lcadd;
}

list_t* GenerateFMCMappings(char* filename) {
	FILE * fptr;
	fptr=fopen(filename,"r");
	
	if(fptr ==NULL){
		
		return NULL;
	}
	
	list_t * LL = CreateList(&mapping_tComparator, &mapping_tPrinter, &mapping_tDeleter);
	
	char * line =NULL;
	size_t len =0;
	ssize_t char_num;

	//get line also reads the number of characte read inludeing the delimiter character but no including the terminating null byte
	char_num = getline(&line,&len,fptr);
	if(char_num==-1){
		return NULL;
	}
	
	while(char_num>-1){
    	if(LL->length == 0){//length is 0
    		mapping_t* mapping1 = CreateMapping(line);
    		InsertInOrder(LL, (void*) mapping1);
    		
    	}
		else if(FindASCII(*line,LL)==NULL ){//no duplicates
			mapping_t* mapping1 = CreateMapping(line);
    		InsertInOrder(LL, (void*) mapping1);
    		
		}else{
			return NULL;
		}
		char_num = getline(&line,&len,fptr);
	}
	if(line){
		free(line);
	}
	fclose(fptr);
	//PrintLinkedList(LL);
	return LL;
}

mapping_t* FindASCII(char token, list_t* list) {
	
	if(list == NULL)
        return NULL;
    
   
    node_t* head = list->head;
	mapping_t* mp;
   
    while(head!=NULL){
    	mp = (mapping_t*)(head->data);
    	if (mp->ASCII == token){
    		return mp;
    	}else{
    		head = head->next;
    	}
    }
	return NULL;
}

int createMorse(list_t* mapping, char **mc_ptr) {
	char* output=NULL;
	char* firstel=NULL;
	char* line =NULL;
	size_t len =0;
	ssize_t char_num;
	char_num = getline(&line,&len,stdin);//get one line at a time
	
	
	if(mapping==NULL){//when mapping is null 
		*mc_ptr = NULL;
		if(line){
			free(line);
		}
		return -1;
	}
	
	if(char_num == -1){//when we get to end of file
		if(line){
			free(line);
		}
		return -1;
	}
	int inspace =0;
	int count = 0;
	while(char_num>-1){
		char* nc = line;
		
		int cnum=0;
		
		char * sq;
		while(1){//go through line //*line is a character in the line
	
			if(*nc == 0){//if end of line
				if(inspace){
					break;
				}
				firstel = realloc(firstel,count*sizeof(char)+1);
				output = firstel+count;
					
				*output++='x';
						
				
				count++;
				inspace = 0;
				break;
			}

			if(*nc != 10 && *nc !=32){//is the character a new line or space
				if(97<=*nc && *nc<123){//is it lower
					*nc-=32;
				}

				sq =FindASCII(*nc,mapping)->sequence;//get sequence of one char
				if(sq==NULL){
					break;
				}
				int s = slen(sq)+1;

				if(count == 0){
					firstel = output;
				}
				
			
				firstel = realloc(firstel,s+count);
				
				output = firstel+count;
				
				
				
				while(*sq){//go through the sequence associated with the *line char
					*output=*sq;
					
					output++;
					sq++;
					count++;
					
				}
				inspace=0;		
				*output++='x';//put x on the end of the char
				count++;
				
				
			}else if(*nc ==32){//replace the space or new line with an x
				
				
				firstel = realloc(firstel,count*sizeof(char)+1);
				output = firstel+count;
				
				*output++='x';
				count++;
				inspace=1;
			}
			
			cnum++;
			nc = line +cnum;
		}
		
		char_num = getline(&line,&len,stdin);
	}
	if(line){
		free(line);
	}
	
	*mc_ptr = firstel;
	
	return 0;
}

// Part 3 Functions to implement
int encrypt(list_t* mapping, char* FMCtoKey , char* phrase, FILE *outstream) {
	//make phrase a morese 
	if(mapping==NULL || FMCtoKey ==NULL || phrase ==NULL){
		return -1;
	}
	
	char * keyArray=(char*)malloc(27*sizeof(char));
	init(keyArray,27);
	createSecretKey(phrase,keyArray);
	int line_num=0;
	char * thingtocode;
	
	int success = createMorse(mapping,&thingtocode);// we get the next line and encode it
	
		
	if(success==-1){//oh mapping was off or something went wrong
		free(thingtocode);
		return -1;
	}
		

	
	char * next, letter;
	int s = slen(thingtocode);
	int i = 0;
		
	while(i<=s){
		next = thingtocode+i;
		
		letter = morseToKey(next,FMCtoKey,keyArray);
			
		
		if(letter!=-1){
			fprintf(outstream, "%c",letter);
			i+=3;
		}else{
			i++;
		}
	}
	

	free(thingtocode);
	
	fclose(outstream);
	free(keyArray);
	
	return 0;
}
