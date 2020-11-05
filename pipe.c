#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define READ  0
#define WRITE 1


char instruction(char * array[],int number){
	char * cmd[256]= {};
        char word[256] ="";
        char savedWords[256][256] = {};
	char *str = array[number];
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
	//printf("%s\n",cmd[2]);
	return cmd;
}

int main(int argc, char *argv[]) {
 // printf("%s",argv[1]);
  pid_t pid;
  int   fd[2];

///////////////////////////
	//array de direcciones de palabras.
	char * cmd[256]= {};
	//palabra en un instante del ciclo.
        char word[256] ="";
	//array de valores de palabras.
        char savedWords[256][256] = {};
	//texto que recibe.
        char *str = argv[1];
	//contador de las palabras anadidas.
        int index = 0;

	//Recorre la palabra y cuando vea un espacio, anade la direccion a la palabra en el array cmd.
        for(int i = 0;i<strlen(str);++i){
		//Si hay un espacio o es el final del texto.
                if(str[i]==' ' || strlen(str)-1 == i){
			//Cuando llega al final introduce la palabra final.
                        if(strlen(str)-1 == i){
                                strncat(word,&str[i],1);
                        }
			//copia la palabra actual en el array de valor de palabras.
                        strcpy(savedWords[index],word);
			//asigna la direccion del valor en la posicion dada.
                        cmd[index] = &savedWords[index];
                        index++;
                        //printf("Meti la palabra %s\n", word);
			//reinicia la pabra.
                        memset(word,0,strlen(word));
                }else{	//concatena las letras para formar una palabra.
                        strncat(word,&str[i],1);
                }
        }
	//inserta null en la ultima posicion.
        cmd[index] = NULL;
///////////////////

///////////////////////////
        //array de direcciones de palabras.
        char * cmd1[256]= {};
        //palabra en un instante del ciclo.
        char word1[256] ="";
        //array de valores de palabras.
        char savedWords1[256][256] = {};
        //texto que recibe.
        char *str1 = argv[2];
        //contador de las palabras anadidas.
        int index1 = 0;

        //Recorre la palabra y cuando vea un espacio, anade la direccion a la palabra en el array cmd.
        for(int i = 0;i<strlen(str1);++i){
                //Si hay un espacio o es el final del texto.
        	if(str1[i]==' ' || strlen(str1)-1 == i){
			//Cuando llega al final introduce la palabra final.
                	if(strlen(str1)-1 == i){
                        	strncat(word1,&str1[i],1);
                        }
                     	//copia la palabra actual en el array de valor de palabras.
	                strcpy(savedWords1[index1],word1);
        	        //asigna la direccion del valor en la posicion dada.
                	cmd1[index1] = &savedWords1[index1];
                        index1++;
                        //printf("Meti la palabra %s\n", word);
                        //reinicia la pabra.
                        memset(word1,0,strlen(word1));
                }else{  //concatena las letras para formar una palabra.
                        strncat(word1,&str1[i],1);
                }
        }
        //inserta null en la ultima posicion.
        cmd1[index1] = NULL;

//////////////////////////




  //char * word1[]= {"wc", "-l",NULL};
  //char * word2[]= {"cat", "p4.c",NULL};
  //char * palabra1 = instruction(argv,1);

  if (pipe(fd) == -1) {
	perror("Creating pipe");
	exit(EXIT_FAILURE);
  }

  switch(pid = fork()) {

  case 0:
	// The child process will execute wc.
	// Close the pipe write descriptor.
	close(fd[WRITE]);
	// Redirect STDIN to read from the pipe.
	dup2(fd[READ], STDIN_FILENO);
	// Execute wc
	execvp(cmd1[0],cmd1);

  case -1:
	perror("fork() failed)");
	exit(EXIT_FAILURE);

  default:
	// The parent process will execute ls.
	// Close the pipe read descriptor.
	close(fd[READ]);
	// Redirect STDOUT to write to the pipe.
	dup2(fd[WRITE], STDOUT_FILENO);
	// Execute ls -l
	execvp(cmd[0],cmd);
  }
}

