enum CLASS{CHAR,NUM,OPE,SPECIAL,RIGHT,LEFT,SQUARE_RIGHT,SQUARE_LEFT};

//reserved list
char *reserved[]={"base","int","if","+","-","*","/",";","\\n"};
enum RESERVED{RESERVED_BASE,Int,If,Sum,Sub,Multi,Div,End,NewLine,RESERVED_END,UNRESERVED,NUMBER,OPERATION,PAREN,BRACE};

int lexLen;
char lexed[128][128]={"int","hello","world"};

int parseLen;
char parsed[128][128]={};

//infomation function
#define Info()			printf("%s(%d)\n",__func__,__LINE__)
#define Info1(fmt, ...) do{ printf("%s(%d):" fmt, __func__, __LINE__, __VA_ARGS__),printf("\n");}while(0)
#define Info2(arg) 	do { printf("%s(%d):", __func__, __LINE__), printf("%s\n",arg); } while (0)

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
#elif __RELEASE__
#pragma message("release mode")
#define printd(str) pass()
#endif //__DEBUG__
void pass(){
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
	else if(c=='(') return RIGHT;
	else if(c==')') return LEFT;
	else if(c=='{') return SQUARE_LEFT;
	else if(c=='}') return SQUARE_RIGHT;
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
	if(n==Int) return "int";
	else if (n==If) return "if";
	debug1("unknown number:%d",n);
	return "\0";
}


int lex(char *exp){
	int c0,c1=0,cnt=0;
	int brackets=0,brackets0=0,SquBra=0,SquBra0=0,Squote,Dquote;
	char c[16]={};
	char cbuf[128]={};
	char nbuf[128]={};
	char bbuf[128]={};
	char sbuf[128]={};
	for(;*exp;exp++){
		c[0]=*exp;
		c1=class(*exp);
		if(c1==RIGHT){
			brackets++;
//			debug1("%d",brackets);
		}else if(c1==LEFT){
			brackets--;	
//			debug1("%d",brackets);
		}
		if(c1==SQUARE_RIGHT){
			SquBra--;
//			debug1("%d",SquBra);
		}else if(c1==SQUARE_LEFT){
			SquBra++;	
//			debug1("%d",SquBra);
		}
		if(brackets>=1){
			connect(bbuf,c);
//			debug1("%d %s",brackets,bbuf);
		}else if(SquBra>=1){
			connect(sbuf,c);
//			debug1("%d %s",SquBra,sbuf);
		}else{
			if(c1==NUM){
				connect(nbuf,c);
			}else if(c0==NUM){
//				debug1("int  %-5s ",nbuf);
				strcpy(lexed[cnt++],nbuf);
				initArray(nbuf,128);
			}
			if(c1==CHAR){
				connect(cbuf,c);
			}else if(c0==CHAR){
//				debug1("char %-5s ",cbuf);
				strcpy(lexed[cnt++],cbuf);
				initArray(cbuf,128);
			}
			if (c1==SPECIAL){
//				debug1("spec %-5s ",escapeSpecial(*c));
//				strcpy(lexed[cnt++],escapeSpecial(*c));
			}
			if(c1==OPE){
//				debug1("ope  %-5s ",c);
				strcpy(lexed[cnt++],c);
			}	
			if(brackets0>=1){
				connect(bbuf,c);
//				debug1("brack %-5s ",bbuf);
				strcpy(lexed[cnt++],bbuf);
				initArray(bbuf,128);
			}
			if(SquBra0>=1){
				connect(sbuf,c);
//				debug1("SquBra %-5s",sbuf);
				strcpy(lexed[cnt++],sbuf);
				initArray(sbuf,128);
			}
		}
		c0=c1;
		brackets0=brackets;
		SquBra0=SquBra;
	}
	lexLen=cnt;
//	printLexed();
	return 0;
}

void printLexed(){
//	for(int i=0;lexed[i][0]!=NULL;i++){
	for(int i=0;i<lexLen;i++){
		debug1("%d: %s",i,lexed[i]);
	}
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
void load(char *fname,char *prog){
	FILE *fp;
	char buf[128];
	if ((fp=fopen(fname,"r"))==NULL){
//		printf("file can't open");
//		Info2("file can't read %s",fname);
		exit(EXIT_FAILURE);
	}else{
//		Info2("file open success %s",fname);
	}
	while(fgets(buf,80,fp)){
		connect(prog,buf);
	}
	debug1("program \n%s",prog);
	fclose(fp);
}

void setWrite(char *fname,char *prog){
	FILE *fp;
	int progl,wl;
	progl=strlen(prog);
	debug1("prog len %d",progl);
	fp=fopen(fname,"w");
	if(fp==NULL){
		Info1("can't write %s",fname);
		exit(EXIT_FAILURE);
	}else{
		Info1("file open success %s",fname);
	}
	wl=fprintf(fp,prog);
	if(progl=wl){
		Info2("prog write success");
	}else {
		Info2("prog write failed");
	}
}
