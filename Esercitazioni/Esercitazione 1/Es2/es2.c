/*
1. Scrivere un programma in linguaggio C che riceve su riga di comando il nome di un
   file. Utilizzando le funzioni di I/O a basso livello,in un ciclo infinito:
	•  Legge dallo standard input una stringa S
	•  Scrive nel file la variabile intera (senza convertirla in stringa)
	   contenente la lunghezza della stringa S
	•  Scrive nel file la stringa S
	•  Il programma termina quando l’utente digita la stringa “fine”

2. Scrivere un programma che riceve su riga di comando il nome del file generato
   dall’esercizio appena descritto. Per ogni stringa S contenuta nel file:
	•  Visualizza la lunghezza di S su standard output
	•  Visualizza la stringa S su standard input
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_SIZE 50
#define BUF_SIZE 512

int main(int argc,char *argv[]){
	char *s=malloc(sizeof(char)*MAX_SIZE);
	char *c=malloc(sizeof(char)*MAX_SIZE);
	char *x=(char*)malloc(sizeof(char)*BUF_SIZE);
	int *a=malloc(sizeof(int));
	int fd,scelta=0,dim_tot=0,pos_dim_num=0,dim_char=0,pos_dim_char=0,n=0,i=0,j=0;
	ssize_t r;
	char buf[BUF_SIZE];
		//FORM
			write(1,"\t\t┌───────────────────────────┐\n\t\t│ FABIANO ESPOSITO N86/2052 │\n\t\t└───────────────────────────┘\n",strlen("\t\t┌───────────────────────────┐\n\t\t│ FABIANO ESPOSITO N86/2052 │\n\t\t└───────────────────────────┘\n"));
	write(1,"MENU\n1. OPEN FILE IN WRITE\n2. OPEN FILE IN READ\nscelta: ",strlen("MENU\n1. OPEN FILE IN WRITE\n2. OPEN FILE IN READ\nscelta: "));
		scanf("%d",&scelta);
			// read();
	switch(scelta){
		case 1:
			write(1,"-> 1. OPEN FILE IN WRITE <-\n",strlen("-> 1. OPEN FILE IN WRITE <-\n"));
			if(s==NULL){
				perror("Error malloc");
				return -1;
			}
			fd=open("file.txt",O_WRONLY|O_CREAT);
			if(fd==-1) {
				perror("Error file");
				return -1;
			}
			write(1,"file.txt CREATED\n",strlen("file.txt CREATED\n"));
			do{
				write(1,"Inserire una stringa (fine per interrompere): ",strlen("Inserire una stringa (fine per interrompere): "));
				r=read(STDIN_FILENO,c,MAX_SIZE);
				*a=(int) r;
				*a=*a-1;
				sprintf(s,"%d",*a);
				write(1,s,strlen(s));
				write(1,c,*a);
				write(fd,s,strlen(s));
				write(fd,c,*a);
				write(1,"\n",strlen("\n"));
				if(r==-1){
					perror("errore: stringa di lunghezza -1\n");
					return -1;
				}
				if(strncmp(c,"fine\0",strlen("fine\0"))==0){
					close(fd);
					return 0;
				}
				free(s);
				free(c);
			}while(strncmp(c,"fine\0",strlen("fine\0"))!=0);
		break;

		case 2:
			write(1,"-> 2. OPEN FILE IN READ IN <-\n",strlen("-> 2. OPEN FILE IN READ IN<-\n"));
			fd=open("file.txt",O_RDONLY|O_CREAT);
			if(fd==-1){
				perror("Error file");
				return -1;
			}else{
				write(1,"\nfile.txt OPENED in READ IN and in WRITE OUT\n",strlen("\nfile.txt OPENED in READ IN and in WRITE OUT\n"));
				r=read(fd,buf,BUF_SIZE);
				if(r==-1){
					perror("Error read");
				return -1;
				}
				*a=(int) r;
				dim_tot=*a;
				sprintf(s,"%d",dim_tot);
				write(STDOUT_FILENO,"len-tot: ",strlen("len-tot: "));
				write(STDOUT_FILENO,s,strlen(s));
				write(STDOUT_FILENO,"\n",strlen("\n"));
				buf[BUF_SIZE]=read(fd,s,sizeof(char));
				write(1,"string: ",strlen("string: "));
				write(STDOUT_FILENO,buf,strlen(buf));
				write(STDOUT_FILENO,"\n\n",strlen("\n\n"));
				pos_dim_num=dim_tot-dim_tot;
				pos_dim_char=(dim_char+1)-dim_char;
				do{
					sprintf(s,"%d",pos_dim_num);
					write(STDOUT_FILENO,"pos-dim-num: ",strlen("pos-dim-num: "));
					write(STDOUT_FILENO,s,strlen(s));
					write(STDOUT_FILENO,"\n",strlen("\n"));
					sprintf(s,"%d",pos_dim_char);
					write(STDOUT_FILENO,"pos-dim-char: ",strlen("pos-dim-char: "));
					write(STDOUT_FILENO,s,strlen(s));
					write(STDOUT_FILENO,"\n",strlen("\n"));
					write(1,"len-char: ",strlen("len-char: ")); 
					sprintf(s,"%c",buf[pos_dim_num]);
					write(STDOUT_FILENO,s,strlen(s));
					write(STDOUT_FILENO,"\n",strlen("\n"));
					write(STDOUT_FILENO,"string: ",strlen("string: "));
					dim_char=atoi(buf);
					write(STDOUT_FILENO,"[",strlen("["));
					sprintf(s,"%d",pos_dim_char);
					write(STDOUT_FILENO,s,strlen(s));
					write(STDOUT_FILENO,"]",strlen("]"));
					for(i=pos_dim_char;i<dim_char+pos_dim_char;i++){
						sprintf(s,"%c",buf[i]);
						write(STDOUT_FILENO,s,strlen(s));
					}
					write(STDOUT_FILENO,"[",strlen("["));
					sprintf(s,"%d",dim_char+pos_dim_char);
					write(STDOUT_FILENO,s,strlen(s));
					write(STDOUT_FILENO,"]",strlen("]"));
					write(STDOUT_FILENO,"\n\n",strlen("\n\n"));
					pos_dim_num=pos_dim_num+dim_char+1;
					pos_dim_char=pos_dim_num+1;
				}while(pos_dim_char<=dim_tot);
				close(fd);
				bzero(c,strlen(c));
				bzero(s,strlen(s));
			}
		break;
	}
	return 0;
}