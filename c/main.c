
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include "inc/tools.h"

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

//my string function
/*
char *chrSlice(char *str,int first,int end){
	char tmp[end-first];
	for(int i=first,j=0;i<end;i++,j++){
		tmp[j]=str[i];
	}
	tmp[end-first]='\0';
	initArray(str,end);
	strcpy(tmp,str);
	return str;
}
char **strSlice(char **str,int first,int end){
	char tmp[end-first+128][valSize];
	for(int i=first,j=0;i<end;i++,j++){
		strcpy(tmp[j],str[i]);
	}
}
*/

void printParse(){
	for(int i=0;i<parseLen;i++){
		debug1("%d: %s",i,parsed[i]);
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
	}else if(c[0]=='('){
		debug2("paren");
		return PAREN;
	}else if(c[0]=='{'){
		debug2("brace");
		return BRACE;
	}else{
		debug2("unreserved");
		return UNRESERVED;
	}
	return -1;
}

void parse(){
	enum parseState{ValiableDeclaration,Assignment,IfState,None};
	char stack[128];
	int attr,state=None;
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
			if(attr==PAREN){
				debug1("if cond %s",stack);
			}else if(attr==BRACE){
				debug1("if state%s",stack);
				initArray(stack,128);
				state=None;
			}
			debug();
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

void llvmStart(char *prog){
	char *str={"\
		@.str = private unnamed_addr constant [12 x i8] c\"hello world\\00\", align 1\n \
		define i32 @main() #0 {\n \
		%1 = alloca i32, align 4\n \
		store i32 0, i32* %1, align 4\n \
		%2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str, i32 0, i32 0))\n \
	"};

	connect(prog,"\n");
	connect(prog,str);
}
void llvmEnd(char *prog){
	char *str={"\
		ret i32 0\n \
		}	\n \
		declare i32 @printf(i8*, ...) #1	\n \
	"};
	connect(prog,str);
}

int lpos=0;
char lstr[128];

void laddstr(const char *str,int len){
	static int n;
	char tmp[128];
	sprintf(tmp,"@.str.%d = private unnamed_addr constant [%d x i8] c\"%s\\00\", align 1\n",n,len,str);
	connect(lstr,tmp);
//  debug1("@.str.%d = private unnamed_addr constant [%d x i8] c\"%s\\00\", align 1",n,len,str);
  n++;
}
void llvmstr(){
	printf(lstr);
}
void lprint(const char *fmt, ...)
{
  va_list list;
  int len;
  char str[128];
  va_start(list, fmt);
  vsprintf(str,fmt,list);
  len=strlen(str)+1;
  laddstr(str,len);
  debug1("%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([%d  x i8], [%d x i8]* @.str, i32 0, i32 0)\n"
			,lpos,len,len);
  va_end(list);
}
void lout(){
	char lcode[1024]={";hello"};
	llvmstr(lcode);
	llvmStart(lcode);
	llvmEnd(lcode);
	setWrite(lcode,"llvm.ll");

}

void pre(char *fname){
	FILE *fp,*fout;
	char *fname1="aaaa";
	char buf[80];
	debug();
	if((fp=fopen(fname,"r"))==NULL){
		debug2("%s open failed",fname);
		exit(0);
	}else{
		debug2("%s open succeed",fname);
	}
	if((fout=fopen(fname1,"w"))==NULL){
		Info1("%s open failed",fname1);
	}else{
		Info1("%s open succeed",fname1);
	}
	while(fgets(buf,80,fp)){
		Info1("%s",buf);
	}
	fclose(fp);
	fclose(fout);

}

int main(int argc,char **argv){
	char prog[128];
	pre(prog);
/*
	lprint("hello world %d",10);
	lprint("hello %d",10);
	lout();
*/
//	printfl("hello %d",33);
//	debug1("llvm code \n %s",lcode);
//	setWrite("llvm.ll",llvm);
//	calc(argv[1]);
//	reservedCheck("a");
    return 0;
}

