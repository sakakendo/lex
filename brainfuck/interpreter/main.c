#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __DEBUG__
#include "mystr.h"
#include "labelList.h"
//#include "tools.h"

enum TAG{UNCHAR=-1,CHAR};

int main(int argc,char **argv){
	int mptr=0,pptr=0;
	int memory[3000];
	char program[3000],tmp[128];
	char c;
	//name management
	int lastc=UNCHAR,laststr,namel=0;
	char name[100];
	struct list *lhead=initLabel();
	//,*vhead,*fhead;

	do{
		printf("mptr:%d pptr:%d\n",mptr,pptr);
		if(program[pptr]=='\0'){
			printf("input program\n>>> ");
			fgets(tmp,128,stdin);
			connect(program+pptr,tmp);
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
		}else{
			printf("unknown command %c\n",c);
		}
		if( ('a'<=c && c<='z') || ('A'<=c && c<='Z') ){
			name[namel]=c;
			printf("name :%s\n",name);
//			connect(*(name+namel),*c);
			lastc=CHAR;
			namel++;
		}else{
			if(lastc==CHAR){
				printf("name :%s",name);
				addLabel(lhead,name,pptr);

			}else if(lastc==UNCHAR){

			}
			lastc=UNCHAR;
			for(int i=0;name[i];i++) name[i]='\0';
			namel=0;
		}
		pptr++;
//		printLabelAll(lhead);
	}while(1);
}
