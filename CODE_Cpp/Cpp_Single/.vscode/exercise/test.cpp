#include <iostream>
#include <stdlib.h>
using namespace std;
typedef int elem;

class Node 
{
	public:
		elem data;
		Node *next;
};
void InitList(Node *&h)
{
	h=(Node*)malloc(sizeof(Node));
    // cout << 'a';
    // cout << sizeof(Node);
	h->next=NULL;
}
void CreateList(Node *&h,elem a[],int n)
{
	Node *s,*r;
	h=(Node*)malloc(sizeof(Node));
    r=h;
    for(int i=0;i<n;i++)
    {
     s=(Node*)malloc(sizeof(Node));
     s->data=a[i];
     r->next=s; 
     r=s;  
    }
    r->next=NULL;
}
int Length(Node *&h)
{
   int n=0;
   Node *p=h;
   while (p->next!=NULL)    // 
   {
       n++;
       p=p->next;
   }
   return (n);
}
void Order(Node *h)
{
    int len = Length(h);
    Node *p=h->next,*r=p->next;
    int i=0,j=0;
    elem temp;
    for(i=len-1;i>0;i--)
    {
        p=h->next;
        r=p->next;
        for(j=0;j<i;j++)
        {
            if(p->data>r->data)
            {
                temp=p->data;
                p->data=r->data;
                r->data=temp;
            }
            p=p->next;
            r=r->next;
        }
    }
}
void Display(Node *&h)
{
    Node *p=h->next;
    while(p!=NULL)
    {
        cout<<p->data;
        p=p->next;
    }
    cout<<endl;
}
void Union(Node *la,Node *lb,Node *&le)
{
    Node *s,*r,*pa=la->next,*pb=lb->next;
    le=(Node*)malloc(sizeof(Node));
    r=le;
    while(pa!=NULL&&pb!=NULL)
    {
      if(pa->data<pb->data)
      {
          s=(Node*)malloc(sizeof(Node));
          s->data=pa->data;
          r->next=s;
          r=s;
          pa=pa->next;
      }
      else if(pa->data==pb->data)
      {
          s=(Node*)malloc(sizeof(Node));
          s->data=pb->data;
          r->next=s;
          r=s;
          pb=pb->next;
          pa=pa->next;
      }
      else
      {
         s=(Node*)malloc(sizeof(Node));
         s->data=pb->data;
         r->next=s;
         r=s;
         pb=pb->next;
      }
      while(pa!=NULL)
      {
        s=(Node*)malloc(sizeof(Node));
        s->data=pa->data;
        r->next=s;
        r=s;
        pb=pb->next;  
      }
      while(pb!=NULL)
      {
        s=(Node*)malloc(sizeof(Node));
        s->data=pb->data;
        r->next=s;
        r=s;
        pb=pb->next;  
      }
      r->next=NULL;
    }
}
void Cross(Node *la,Node *lb,Node *&lc)
{
    Node *s,*r,*pa=la->next,*pb=lb=lb->next;
    lc=(Node*)malloc(sizeof(Node));
    r=lc;
    while(pa!=NULL)
    {
        pb=lb->next;
        while(pa!=NULL)
        {
            if(pa->data==pb->data)
            {
                s=(Node*)malloc(sizeof(Node));
                s->data=pa->data;
                r->next=s;
                r=s;
                break;
            }
            pb=pb->next;
        }
        pa=pa->next;
    }
    r->next=NULL;
}
void Sub(Node *la,Node *lb,Node *&lc)
{
	Node *s,*r,*pa=la->next,*pb=lb->next;
	lc=(Node*)malloc(sizeof(Node));
	r=lc;
	while(pa!=NULL)
	{
		pb=lb->next;
		bool flag=true;
		while(pb!=NULL)
		{
			if(pa->data==pb->data)
			{
				flag=false;
				break;
			}
			pb=pb->next;
		}
		if(flag)
		{
			s=(Node*)malloc(sizeof(Node));
			s->data=pa->data;
			r->next=s;
			r=s;
		}
		pa=pa->next;
	}
	r->next=NULL;
 } 
 int main()
 {
 	elem a[5]={6,7,3,8,4},b[6]={6,2,1,9,5,7};
 	Node *exp1,*exp2,*_union,*_cross,*_sub1,*_sub2;
	InitList(exp1);
	InitList(exp2);
	CreateList(exp1,a,5);
	CreateList(exp2,b,6);
	Order(exp1);
	Order(exp2);
	cout<<"exp1:";
	Display(exp1);
	cout<<"exp2:";
	Display(exp2);
	Union(exp1,exp2,_union);
	Cross(exp1,exp2,_cross);
	Sub(exp1,exp2,_sub1);
	Sub(exp2,exp1,_sub2);
	cout<<"Union:";
	Display(_union);
	cout<<"Cross:";
	Display(_cross);
	cout<<"Sub1:";
	Display(_sub1);
	cout<<"Sub2:";
	Display(_sub2);
	system("pause");
	return 0;
 }
