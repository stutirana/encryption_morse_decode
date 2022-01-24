#include "../include/helpers2.h"
#include "../include/hw2.h"
#include "../include/hw2_ec.h"
#include "../include/constants2.h"
int main(int argc, char* argv[]) {
    char* keyphrase = NULL;
    char* mapping_file = NULL;
    char* output_file = NULL;
    int mode_flag = -1;    // 0 for encrypt, 1 for decrypt
    int had_output = 0;
    int had_morse_file=0;
    FILE * out=NULL;
    // Use basic getopt to parse flags and respective arguments
    int c;
    while ((c = getopt(argc, argv, "hk:m:O:ED")) >= 0) {
        switch (c) {
            case 'h':
                fprintf(stdout,USAGE_MSG);
            case 'k':
                keyphrase = optarg;
                break;
            case 'm':
                had_morse_file=1;
                mapping_file = optarg;
                
                break;
            case 'O':

                had_output=1;
                output_file = optarg;
                break;
            case 'E':
                mode_flag = 0;
                break;
            case 'D':
                mode_flag = 1;
                break;
            default:

                fprintf(stderr, USAGE_MSG);

                if(output_file==NULL){
                    
                    return 2 ;
                }
                
                
                return EXIT_FAILURE;
        }
    }
   
    
    
    if (output_file!=NULL){//something was passed
        out = fopen(output_file,"w");
        
        if(out==NULL){
            return 1;//error with opening
        }
    }
    if(mapping_file!=NULL){
        FILE * map = fopen(mapping_file,"r");
        if(map ==NULL){
            return 1;//error with opening
        }
        fclose(map);
    }


    
    
   

    list_t* LL;
    if(mapping_file!=NULL){
        LL = GenerateFMCMappings(mapping_file);
    }else{
        LL = GenerateDefaultMorseMappings();
    }
    if(output_file==NULL){
        encrypt(LL,DEFAULT_FMC2KEY,keyphrase,stdout);
    }else{
        
        encrypt(LL,DEFAULT_FMC2KEY,keyphrase,out);
    }
    if(mapping_file!=NULL){
        DestroyList(LL);
    }else{
        DestroyDefaultMorseMappings(LL);
    }

  

    
    return 0;
}
