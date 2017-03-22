
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//debug functions
#ifdef __DEBUG__
//#pragma message("debug mode")
#define debug()			printf("%s(%d)\n",__func__,__LINE__)
#define debug1(fmt, ...) do{ printf("%s(%d):" fmt, __func__, __LINE__, __VA_ARGS__),printf("\n");}while(0)
#define debug2(arg) 	do { printf("%s(%d):", __func__, __LINE__), printf("%s\n",arg); } while (0)
//color debugger
#define printd(...) printf("%s",__VA_ARGS__)
#define printb(str)	printf("\x1b[30m%s",str); //black 
#define printr(str)	printf("\x1b[31m%s",str); //red
#define printy(str)	printf("\x1b[33m%s",str); //yellow
//#define printb(str)	printf("\x1b[34m%s",str); //blue
#define print_default(str)	printf("\x1b[39m%s",str); ///default
#elif
#pragma message("release mode")
#define printd(str) pass()
#endif //__DEBUG__

//generic
//connect(char*,char*);
//connect(char*,char);
//connect(char*,char*,char*)
enum CLASS{CHAR,NUM,OPE,SPECIAL};

//reserved list
char *reserved[]={"int","if"};
enum RESERVED{INT,IF,RESERVED_END};

#define MEM_SIZE 128
int mem[MEM_SIZE]={};

int lexLen;
char lexed[128][128]={"int","hello","world"};

void initArray(char p[],int n){
	for(int i=0;i<n;i++){
		p[i]=0;
	}
}

int ischar(char c){
	if(65<=c && c<= 90) return 1;
	else if(97<=c && c<=122) return 1;
	else if(95==c ) return 1;
	else return 0;
}

int isspecial(char c){
	// \n,\t
	if(c=='\n' || c=='\t') return 1;
	else return 0;
}

char* escapeSpecial(char c){
	if(c=='\n'){
//		debug2("\\n");
		return "\\n";
	}else if(c=='\t'){
//		debug2("\\t");
		return "\\t";
	}
	debug1("unknown special character :%c",c);
	return "\0";

}

int class(char c){
	if(ischar(c)) return CHAR;
	else if(isdigit(c)) return NUM;
	else if(isspecial(c)) return SPECIAL;
	else return OPE;
}

void connect(char a[],char b[]){
	int lenSum=(int)strlen(a)+(int)strlen(b);
	for(int i=(int)strlen(a),j=0;i<lenSum;i++,j++){
		a[i]=b[j];
	}
	a[lenSum]='\0';
}

char *nToReserved(int n){
	if(n==INT) return "int";
	else if (n==IF) return "if";
	debug1("unknown number:%d",n);
	return "\0";
}

int reservedCheck(char *str){
	for(int i=0;i<RESERVED_END;i++){
		if(strcmp(str,reserved[i])==0){
			debug1("reserved %s",nToReserved(i));
		}
	}
	return 0;
}
void pass(){
}

int lex(char *exp){
	int c0,c1=0,cnt=0;
	char c[16]={};
	char cbuf[128]={};
	char nbuf[128]={};
	for(;*exp;exp++){
		c[0]=*exp;
		c1=class(*exp);
		if(c1==NUM){
			connect(nbuf,c);
		}else if(c0==NUM){
//			debug1("int  %-5s ",nbuf);
			strcpy(lexed[cnt++],nbuf);
			initArray(nbuf,128);
		}
		if(c1==CHAR){
			connect(cbuf,c);
		}else if(c0==CHAR){
//			debug1("char %-5s ",cbuf);
			strcpy(lexed[cnt++],cbuf);
			initArray(cbuf,128);
		}
		if (c1==SPECIAL){
//			debug1("spec %-5s ",escapeSpecial(*c));
			strcpy(lexed[cnt++],escapeSpecial(*c));
		}
		if(c1==OPE){
//			debug1("ope  %-5s ",c);
			strcpy(lexed[cnt++],c);
		}
		c0=c1;
	}
	lexLen=cnt;
	return 0;
}

void printLexed(){
//	for(int i=0;lexed[i][0]!=NULL;i++){
	for(int i=0;i<lexLen;i++){
		debug1("%d: %s",i,lexed[i]);
	}
}

int searchLexed(char *str){
	for(int i=0;i<lexLen;i++){
		if(strcmp(str,lexed[i])==0){
			debug1("str is found in lexed %d",i);
		}
	}
	return 0;
}

void findNum(char *exp,int *n){
	int i;
	char tmp[128];
	do{
		if (isdigit(*exp)){
			tmp[i++]=*exp;
		}else{
			*n=atoi(tmp);
			n++;
			i=0;
			initArray(tmp,128);
		}
	}while(*(++exp));
	*n=atoi(tmp);
}

int calc(char *exp){
	//input exp
	// str(<int> <ope> <int>)
	int n[2],i,result;
	char ope[128],tmp[128];
	debug();
	debug2(exp);
	while(*(exp)){
		if (isdigit(*exp)){
			tmp[i++]=*exp;
		}else{
			n[0]=atoi(tmp);
			i=0;
			tmp[0]='\0';
			ope[0]=*exp;
			ope[1]='\0';
		}
		exp++;
	}
	tmp[i]='\0';
	n[1]=atoi(tmp);
	if(*ope=='+'){
		result=n[0]+n[1];
	}else if(*ope=='-'){
		debug2("ope : -");
	}
	debug1("n[0] ope n[1]=result:%d%c%d=%d",n[0],*ope,n[1],result);
	return 0;
}

void parse(){
	printLexed();
	searchLexed("int");
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
//	calc(argv[1]);
    return 0;
}
