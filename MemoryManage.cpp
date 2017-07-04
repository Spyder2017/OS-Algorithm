#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct  
{
	int a[8][8];      /*存放位示图信息的二维数组*/
	int spare_block;      /*剩余空闲块数*/
}Bit_Figure;

typedef struct Page_List
{
	int page_number;  /*页号*/
	int block_number;   /*块号*/
}DataType;

typedef struct Node
{
	char name[10];     /*作业名*/
	int block_amount;    /*块数*/
	DataType *page_list;   /*存放作业数组的首地址*/
	struct Node *next;
}Assignment;

void ListInitiate(Assignment * *head)  /*链表中存入的是已占用主存的所有的作业*/
{
	if((*head=(Assignment *)malloc(sizeof(Assignment)))==NULL)
		exit(1);
	(*head)->next=NULL;
}

void Initiate(Bit_Figure *bit_figure)  /*位示图初始化*/
{
	int i,j;//,n,m;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			bit_figure->a[i][j]=0;
/*		printf("请依次输入初始化的目标:\n");
		printf("请输入初始化的内存个数:");
		scanf("%d",&n);
		for(i=0;i<n;i++)
		{
			scanf("%d",&m);
			bit_figure->a[m/8][m%8] = 1;
		}
		bit_figure->spare_block = 64 - n;
*/  
		bit_figure->a[0][0]=1;
		bit_figure->a[0][1]=1;
		bit_figure->a[0][4]=1;
		bit_figure->a[0][5]=1;
		bit_figure->a[0][6]=1;
		bit_figure->a[1][1]=1;
		bit_figure->a[1][3]=1;
		bit_figure->a[1][5]=1;
		bit_figure->a[3][0]=1;
		bit_figure->a[3][7]=1;
		bit_figure->spare_block=54;
		printf("位示图初始化完成!\n\n");
} 

void show_bit_figure(Bit_Figure *bit_figure)  /*位示图显示*/
{
	int i,j;
	printf("当前位示图显示如下:\n");
	printf("--------------------------------------\n");
	printf("   ");
	for(i=0;i<8;i++)
		printf("%d  ",i);
	printf("\n");
	for(i=0;i<8;i++)
	{
		printf("%d  ",i);
		for(j=0;j<8;j++)
			printf("%d  ",bit_figure->a[i][j]);
		printf("\n");
	}  
	printf("--------------------------------------\n\n");
	printf("当前空闲块数为:%d\n\n",bit_figure->spare_block);
}


int distribute(Assignment *head,Bit_Figure *bit_figure)    /*建立作业*/
{
	int i,j,k;
	Assignment *temp,*p=head->next;
	Assignment *q=(Assignment *)malloc(sizeof(Assignment));
	temp=p;
	printf("请输入作业名:");
	scanf("%s",q->name);
	printf("\n");
	getchar();
	printf("请输入作业所需的主存块数:");
	scanf("%d",&q->block_amount);
	q->page_list=(DataType *)malloc((q->block_amount)*sizeof(DataType));
	if((q->block_amount) > (bit_figure->spare_block))
	{
		printf("\n");
		printf("所需主存块数超过剩余主存块数,所以无法进行分配!\n\n");
		return 0;
	}
	for(k=0;k<q->block_amount;k++)
	{
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			{
				if(bit_figure->a[i][j]==0)
					break;
			}
			if(bit_figure->a[i][j]==0)
			{
				q->page_list[k].block_number=i*8+j;
				q->page_list[k].page_number=k; 
				bit_figure->spare_block--;   
				bit_figure->a[i][j]=1;
				break;
			}
		}
	}
	while(p!=NULL)
	{
		temp=p;
		p=p->next;
	}
	if(head->next==NULL)
	{
		head->next=q;
		q->next=NULL;
	}
	else
	{
		temp->next=q;
		q->next=NULL;
	}
	printf("\n\n");
	printf("作业名:%s\n",q->name);
	printf("  页号    块号\n");
	for(i=0;i<q->block_amount;i++)
		printf("   %d    %d\n",q->page_list[i].page_number,q->page_list[i].block_number);                        
	printf("\n");
	return 1;
}

int recycle_store(Assignment *head,Bit_Figure *bit_figure)  /*回收作业*/
{
	int m,n=0;
	int BiaoJi=0;   /*判断是否存在该作业,0表示没有,1表示存在*/
	char name1[10];
	Assignment *p=head->next;
	Assignment *q,*temp,*p1;
	q=head;
	temp=head->next;
	p1=temp;
	if(head->next==NULL)
	{
		printf("没有作业占用主存,所以没有可以回收的作业!\n");
		return 0;
	}
	printf("请输入要回收作业的名字:");
	scanf("%s",name1);
	while(p!=NULL)
	{
		if(!strcmp(p->name,name1))
		{
			if(p->next != NULL)
			{
				printf("mmm%s",p->next->name);
			}
			/*
			if(p->next->next != NULL)
			{
				printf("%s",p->next->next->name);
			}
			*/
			int i,j,k;
			for(k=0;k<p->block_amount;k++)
			{
				i=p->page_list[k].block_number/8;
				j=p->page_list[k].block_number%8;
				bit_figure->a[i][j]=0;
				bit_figure->spare_block++;
				BiaoJi=1;
			}
			printf("作业归还的块号有:");
			for(m=0;m<p->block_amount;m++)
				printf("%d   ",p->page_list[m].block_number);
			printf("\n\n");
			break;
		}
		p=p->next;
	}
	while(temp!=NULL)
	{
		if(!strcmp(temp->name,name1) && n==0)
		{         
			if(q==head)  /*判断删除点是否是存入链表的第一个作业*/
				head->next=temp->next;
			if(temp->next==NULL)   /*判断删除点是否是存入链表的最后一个作业*/
				p1->next=NULL;
			if(temp->next!=NULL)     /*判断删除点是否是链表中间的一个作业*/
				p1->next=temp->next;
			n++;
		}
		p1=temp;
		temp=temp->next;
		q=q->next;
	}
	if(BiaoJi==0)
		printf("主存中没有该作业!\n");
	return 1;
}

void main()
{
	int m;
	char ch;
	Assignment *head;
	Bit_Figure bit_figure;
	ListInitiate(&head);
	while(1)
	{
		printf("\n\t***************************************************************");
		printf("\n\n\t                    分页式存储管理系统               ");
		printf("\n\n\t***************************************************************");
		printf("\n\n\t\t请选择功能菜单选项： ");
		printf("\n\n\t\t\t\t1.位示图初始化：");
		printf("\n\n\t\t\t\t2.显示当前位示图： ");
		printf("\n\n\t\t\t\t3.主存分配：");
		printf("\n\n\t\t\t\t4.主存回收：");
		printf("\n\n\t\t\t\t5.退出!");
		printf("\n\n");
		printf("\t\t请选择(1-5): ");
		scanf("%d",&m);
		switch(m)
		{
		case 1:  
			Initiate(&bit_figure);
			break;
		case 2:  
			show_bit_figure(&bit_figure);
			break;
		case 3:
			distribute(head,&bit_figure);
			show_bit_figure(&bit_figure);
			break;
		case 4:
			recycle_store(head,&bit_figure);
			show_bit_figure(&bit_figure);
			break;
		case 5:
			exit(0);
		default:
			break;
		}
		getchar();
		printf("是否继续(Y/N):");
		scanf("%c",&ch);
		if(ch!='Y'&&ch!='y')
			break;
	}
}
