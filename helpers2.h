#ifndef HELPERS2_H
#define HELPERS2_H
int notin(char c,char* key);
void remove_char(char * line, char c);
void init(char * str,int max);
void init_ABCs(char * str);
void init_ZYX(char * str);
void getchars(char * FMCtoKey,int i,char * encryptchar);
int ismatch(char * encryptchar, char * mcmsg);
int slen(char* line);

#endif