#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "tools.h"

char lscript[3000];
char lstr[128];

int lsetup(){

}
void laddstr(char *str,int n){

}
void lprint(const char *fmt, ...)
{
  va_list list;
  int len,lpos=0;
  char str[128];
  va_start(list, fmt);
  vsprintf(str,fmt,list);
  len=strlen(str)+1;
  laddstr(str,len);
  debug1("%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([%d  x i8], [%d x i8]* @.str, i32 0, i32 0)\n"
			,lpos,len,len);
  va_end(list);
}
int loutput(){
	FILE *fp;
	fp=fopen("l","w");
	if(fp==NULL){
		printf("failed to open");
		exit(1);
	}
	fprintf(fp,";test output llvm\n");
	fprintf(fp,lstr);
	fclose(fp);
}

int main(int argc,char **argv){
	int mptr,pptr=0;
	int memory[3000];
	char program[3000],tmp[128];
	char c;
	do{
		c=program[pptr];
		printf("%c",c);
		if(c=='>'){
			mptr++;
		}else if(c=='<'){
			mptr--;
		}else if(c=='+'){
			memory[mptr]++;
		}else if(c=='-'){
			memory[mptr]--;
		}else if(c=='.'){
			printf("\n %d %c\n",memory[mptr],memory[mptr]);
		}else if(c=='['){
		}else if(c==']'){
			if(memory[mptr]!=0){
				while(program[pptr]!='['){
					pptr--;
				}
			}
		}
		pptr++;
	}while(program[pptr]!='\0');
	loutput();
}
