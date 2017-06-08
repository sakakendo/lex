/*
    list for label

    define label
    call label
*/
#define Log printf("\n%d %s ",__LINE__,__func__); printf

struct list{
  char *name;
  struct list *prev;
  struct list *next;
  int pos;
//  int type;
};

void printLabelAll(struct list *now){
  int cnt=0;
  Log ("\n");
  do{
    printf("%s ",now->name);
    if(now->next==NULL){
      printf("all label cnt:%d\n",cnt);
      break;
    }else{
      now=now->next;
      cnt++;
    }
  }while(1);
}
void addLabel(struct list *head,char *s,int pos){
  struct list *next,*now=head;
  while(now->next!=NULL){
    if( !strcmp(now->name,s) ){
      Log ("%s has already defined\n",now->name);
      return;
    }else{
      Log ("not defined\n");
    }
    now=now->next;
  }

  next=(struct list*)malloc(sizeof(struct list));
  next->name=(char *)malloc(sizeof(s));
  strcpy(next->name,s);
  now->next=next;
//  char *name=(char *)malloc(sizeof(char)*(sizeof(s)));
//  sprintf(name,"__VAL__%s",s);
  next->next=NULL;

  printLabelAll(head);
}

struct list* searchLabel(struct list *head,char *name){
  while(head->next!=NULL){
    if( !strcmp(head->name,name) ){
//      Log ("%s has already defined\n",head->name);
        return head;
    }else{
      Log ("not defined\n");
    }
    head=head->next;
  }
}


struct list* initLabel(){
  struct list *tmp;
  tmp=(struct list*)malloc(sizeof(struct list));
  tmp->name=(char *)malloc(sizeof(char)*sizeof("__HEAD__"));
  tmp->name="__HEAD__";
  tmp->next=NULL;
  tmp->prev=NULL;
}
