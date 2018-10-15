/*
Scrivere un programma in linguaggio C che,utilizzando le funzioni di I/O a basso livello,
in un ciclo infinito:
	• Legge dallo standard input una stringa S 
	• Visualizza su standard error la stringa S
	• Il programma termina quando l’utente digita la stringa “fine”
Cosa e’ necessario modificare nel codice affinché il programma legga l’input da un file
invece che da standard input?
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 50

int main(int argc, char *argv[]){
	char *s=malloc(sizeof(char)*BUF_SIZE);
	char *c=malloc(sizeof(char)*BUF_SIZE);
	char *x=(char*)malloc(sizeof(char)*BUF_SIZE);
	int *a=malloc(sizeof(int));
	int pf,scelta=0, dim_tot=0, pos_dim_num=0, dim_char=0, pos_dim_char=0, n=0, i=0, j=0;
	ssize_t r;
	char buf[BUF_SIZE];
		//FORM
			write(1,"\t\t┌───────────────────────────┐\n",strlen("\t\t┌───────────────────────────┐\n"));
			write(1,"\t\t│ FABIANO ESPOSITO N86/2052 │\n",strlen("\t\t│ FABIANO ESPOSITO N86/2052 │\n"));
			write(1,"\t\t└───────────────────────────┘\n",strlen("\t\t└───────────────────────────┘\n"));
	do{
		write(1,"Inserire una stringa (fine per interrompere): ",strlen("Inserire una stringa (fine per interrompere): "));
		r=read(STDIN_FILENO,c,BUF_SIZE);
		*a=(int) r;
		*a=*a-1;
		sprintf(s,"%d",*a);
		write(1,c,*a);
		write(1,"\n",strlen("\n"));
		if(r==-1){
			perror("errore: stringa di lunghezza -1\n");
			return -1;
		}
		if(strncmp(c,"fine\0",strlen("fine\0"))==0){
			close(pf);
			return 0;
		}
		free(s);
		free(c);
	}while(strncmp(c,"fine\0",strlen("fine\0"))!=0);	
	return 0;
}