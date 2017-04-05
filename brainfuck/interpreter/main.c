#include <stdio.h>
#include <stdlib.h>

#include "c/string.h"
#include "tools.h"

int main(int argc,char **argv){
	int mptr,pptr=0;
	int memory[3000];
	char program[3000],tmp[128];
	char c;
	do{
		if(program[pptr]=='\0'){
			printf("input program\n>>> ");
			fgets(tmp,128,stdin);
			connect(program,tmp);
		}

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
	}while(1);
}
