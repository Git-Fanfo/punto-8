#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
        char * cmd[256]= {};
        char word[256] ="";
	char savedWords[256][256] = {};
        char *str = argv[1];
        int index = 0;

        for(int i = 0;i<strlen(str);++i){
                if(str[i]==' ' || strlen(str)-1 == i){
			
			if(strlen(str)-1 == i){
				strncat(word,&str[i],1);
			}
			strcpy(savedWords[index],word);
			//savedWords[index] = word;
                        cmd[index] = &savedWords[index]; //&word;
                        index++;
                        printf("Meti la palabra %s\n", word);
			memset(word,0,strlen(word));
                        //strncat(word,&str[i],1);
                }else{
                        strncat(word,&str[i],1); //printf("estoy en un bucle\n");
                }        //strncat(palabra1,&str[i],1);
        }
	cmd[index] = NULL;
        //strncat(palabra1," -lijto",strlen(" -lijto"));
        printf("%s\n", cmd[5]);//str[1]);
 return 0;
}
