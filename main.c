
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
	char str1[end-first];
	for(int i=first,j=0;i<end;i++,j++){
		str1[j]=str[i];
	}
	return str1;
}
char **strSlice(char **str,int first,int end){
	char str1[end-first+128][valSize];
	for(int i=first,j=0;i<end;i++,j++){
		strcpy(str1[j],str[i]);
	}
	return str1;
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

int outputVal(char *name){
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
	char *name={"aa"};
	debug1("type %s :%s",type,exp);
	if(searchVal(name)==-1){
		debug1("valiable %s has been defined yet.",name);
	}else{
		addVal(name);
	}

}
int isNum(char c[]){
	int i=0;
	while(c[i]!='\0'){
//		debug1("%d",c[i]);
		if(48<=c[i] && c[i]<=57) {
			pass();
		}else{
			return -1;
		}
		i++;
	}
	return 1;
}

int reservedCheck(char *str){
	for(int i=RESERVED_BASE;i<RESERVED_END;i++){
		if(strcmp(str,reserved[i])==0){
//			debug1("reserved %d",i);
			return i;
		}
	}
	debug2("unreserved");
	return -1;
}

int attribute(char *c){
	int res;
	res=reservedCheck(c);
	if(isNum(c)!=-1){
//		debug2("number");
		return NUMBER;
	}else if(res){
//		char *reserved[]={"int","if","+","-","*","/",";"};
//		enum RESERVED{Int,If,Sum,Sub,Multi,Div,End,RESERVED_END,UNRESERVED,NUMBER,OPERATION};
//		debug2("reserved");
		return res;
	}else{
		debug2("unreserved");
		return UNRESERVED;
	}
	return -1;
}

void parse(){
	enum parseState{ValiableDeclaration,Assignment,IfState,None};
	char stack[128];
	int attr,state;
	for(int lpos=0;lpos<lexLen;lpos++){
		attr=attribute(lexed[lpos]);
		if(attr!=NewLine)	connect(stack,lexed[lpos]);
		if(state==None){
			debug2("none");
			if(attr==Int){
				debug2("valiable dec");
				state=ValiableDeclaration;
			}else if(attr==IfState){
				debug2("if");
				state=IfState;
			}else if(attr==UNRESERVED){
				debug2("assign");
				state=Assignment;
			}
		}else if(state==ValiableDeclaration){
			if(attr==UNRESERVED){
			}else if(attr==End){
				debug1("state:%dstack:%s ",state,stack);
				initArray(stack,128);
				state=None;
			}
		}else if(state==If){
		
		}else if(state==Assignment){
			if(attr==UNRESERVED){
			}else if(attr==End){
				debug1("stack:%s state:%d",stack,state);
				initArray(stack,128);
				state=None;
			}
		}
		debug1("%10s %-15s %d %d",lexed[lpos],stack,state,attr);
	}

}
void decFunc(char *exp){

}



int main(int argc,char **argv){
	char prog[128];
	debug2(argv[1]);
	load(argv[1],prog);
	lex(prog);
	parse();
//	calc(argv[1]);
//	reservedCheck("a");
    return 0;
}
