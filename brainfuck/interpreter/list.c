#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Log printf("%d %s ",__LINE__,__func__); printf

struct list{
  char *name;
  struct list *prev;
  struct list *next;
  int pos;
  int type;
};

struct vlist{
  char *name;
  struct list *prev;
  struct list *next;
  int pos;  //memory address
  int type; //scope,value,reserved
};

struct flist{
  char *name;
  struct list *prev;
  struct list *next;
  int pos;
};
void addList(struct list *head,char *s/*, mode (like func,value,scope)*/){
  struct list *next,*now=head;
  next=(struct list*)malloc(sizeof(struct list *));
  next->name=(char *)malloc(sizeof(char)*sizeof(s));
  char *name=(char *)malloc(sizeof(char)*(sizeof(s)+sizeof("__VAL__")));
  sprintf(name,"__VAL__%s",s);
  next->name=name;
  next->next=NULL;

  while(now->next!=NULL){
    if( !strcmp(now->name,name) ){
      Log ("%s has already defined\n",now->name);
    }else{
      Log ("not defined\n");
    }
//    Log ("%s\n",now->name);
    now=now->next;
  }
  now->next=next;
}

void printListAll(struct list *now){
  Log ("\n");
  do{
    printf("%s ",now->name);
    if(now->next==NULL){
      break;
    }else{
      now=now->next;
    }
  }while(1);
}
//resreved
// __HEAD__
// __FUNC__ :scope
// __VAL__  :valiable

struct list* initList(){
  struct list *tmp;
  tmp=(struct list*)malloc(sizeof(struct list));
  tmp->name=(char *)malloc(sizeof(char)*sizeof("__HEAD__"));
  tmp->name="__HEAD__";
  tmp->next=NULL;
  tmp->prev=NULL;
}

int main(){
  struct list *first;//,*next,*now;
  struct list *value=initList();
  addList(value,"firstval");
  addList(value,"firstval");
  printListAll(value);

}
