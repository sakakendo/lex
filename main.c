
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tools.h"

//generic
//connect(char*,char*);
//connect(char*,char);
//connect(char*,char*,char*)
/*
enum RESERVED{Auto,Break,Case,Char,Const,Countinue,Default,
	Do,Double,Else,Enum,Extern,Float,For,Goto,If,Int,Long,Register,
	Return,Short,Signed,Sizeof,Static,Struct,Switch,
	Typedef,Union,Unsigned,Void,Volatile,While,RESERVED_END};
	*/
//operation list
//char *ope[]={"+","-","*","/",";"};

//Max len of value name
#define valSize 16

//memory -> m
#define MEM_SIZE 128
int mem[MEM_SIZE]={};
int memCnt;		//defined number's count

struct memInfo{
	char name[128];
	int pointer;
	int size;
}mInfo[128];

//char mlist[128][128];

//my string function
char *chrSlice(char *str,int first,int end){

}

char **strSlice(char **str,int first,int end){

}

int searchLexed(char *str,int n){
	//search next found <*str> in lexed
	for(int i=n;i<lexLen;i++){
		if(strcmp(str,lexed[i])==0){
			debug1("%s is found in lexed %d",str,i);
			return i;
		}
	}
	return -1;
}

int reservedCheck(char *str){
	for(int i=0;i<RESERVED_END;i++){
		if(strcmp(str,reserved[i])==0){
//			debug1("reserved %s",nToReserved(i));
			return i;
		}
	}
	return -1;
}
int attribute(char *c){
	int res;
	res=reservedCheck(c);
	return res;
}

void printParse(){
	for(int i=0;i<parseLen;i++){
		debug1("%d: %s",i,parsed[i]);
	}
}

int searchVal(char *name){
	for(int i=0;i<memCnt;i++){
		if(strcmp(mInfo[i].name,name)==0){
			debug1("pos=%d",i);
			return i;
		}
	}
	return -1;
}

void addVal(char *name){
	//memcpy
	strcpy(mInfo[memCnt].name,name);
	debug1("%s %s",mInfo[memCnt].name,name);
	memCnt++;
}

void inputVal(char *name,int value){
	int pval=searchVal(name);
	mem[pval]=value;
}

void outputVal(char *name){
	int pval=searchVal(name);
	int val=mem[pval];
	debug1("val %d",val);
	return val;
}


int printVal(){
	for(int i=0;i<memCnt;i++){
		debug1("%s,%d",mInfo[i].name,mem[i]);
	}
}

void decVal(char *exp,char *type){
	//TypeSpecifier VarDeclarator ";"
	/*
	   char str[128][valSize];
	   remove(exp,type);
	   str=token(exp,",");
	   */

	debug1("type %s :%s",type,exp);
	addVal("aa");
}


void parse(){
	enum STATE{DEC_VAL=3,DEC_FUNC,EXP,NONE};
	int attr,state,lastState,ptype;
	int ppos=0;
	debug2("state i lexed[i]");
	for(int lpos=0;lpos<lexLen;lpos++){
		attr=attribute(lexed[lpos]);
		if(attr==Int){
			state=DEC_VAL;
			ptype=lpos;
			//save type for decVal()
		}else if(attr==End){
			state=NONE;
		}

		if(state==DEC_VAL){
			connect(parsed[ppos],lexed[lpos]);
		}else{
			if(lastState==DEC_VAL){
				connect(parsed[ppos],lexed[lpos]);
				decVal(parsed[ppos],lexed[ptype]);
				ppos++;
			}
		}
		lastState=state;
		debug1("%3d %-3d %-3d %3s",attr,state,lpos,lexed[lpos]);
	}
	parseLen=ppos;
	printParse();
}
void decFunc(char *exp){

}

void load(char *fname,char *prog){
	FILE *fp;
	char buf[128];
	if ((fp=fopen(fname,"r"))==NULL){
		printf("file can't open");
		exit(EXIT_FAILURE);
	}else{
		printf("file open success");
	}
	while(fgets(buf,80,fp)){
		connect(prog,buf);
	}
	debug1("program \n%s",prog);

}

int main(int argc,char **argv){
	char prog[128];
	debug2(argv[1]);
	load(argv[1],prog);
	lex(prog);
	parse();
	printVal();
	inputVal("aa",3);
	outputVal("aa");
	printVal();
//	calc(argv[1]);
    return 0;
}
