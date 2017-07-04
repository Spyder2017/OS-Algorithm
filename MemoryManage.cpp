#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct  
{
	int a[8][8];      /*���λʾͼ��Ϣ�Ķ�ά����*/
	int spare_block;      /*ʣ����п���*/
}Bit_Figure;

typedef struct Page_List
{
	int page_number;  /*ҳ��*/
	int block_number;   /*���*/
}DataType;

typedef struct Node
{
	char name[10];     /*��ҵ��*/
	int block_amount;    /*����*/
	DataType *page_list;   /*�����ҵ������׵�ַ*/
	struct Node *next;
}Assignment;

void ListInitiate(Assignment * *head)  /*�����д��������ռ����������е���ҵ*/
{
	if((*head=(Assignment *)malloc(sizeof(Assignment)))==NULL)
		exit(1);
	(*head)->next=NULL;
}

void Initiate(Bit_Figure *bit_figure)  /*λʾͼ��ʼ��*/
{
	int i,j;//,n,m;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			bit_figure->a[i][j]=0;
/*		printf("�����������ʼ����Ŀ��:\n");
		printf("�������ʼ�����ڴ����:");
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
		printf("λʾͼ��ʼ�����!\n\n");
} 

void show_bit_figure(Bit_Figure *bit_figure)  /*λʾͼ��ʾ*/
{
	int i,j;
	printf("��ǰλʾͼ��ʾ����:\n");
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
	printf("��ǰ���п���Ϊ:%d\n\n",bit_figure->spare_block);
}


int distribute(Assignment *head,Bit_Figure *bit_figure)    /*������ҵ*/
{
	int i,j,k;
	Assignment *temp,*p=head->next;
	Assignment *q=(Assignment *)malloc(sizeof(Assignment));
	temp=p;
	printf("��������ҵ��:");
	scanf("%s",q->name);
	printf("\n");
	getchar();
	printf("��������ҵ������������:");
	scanf("%d",&q->block_amount);
	q->page_list=(DataType *)malloc((q->block_amount)*sizeof(DataType));
	if((q->block_amount) > (bit_figure->spare_block))
	{
		printf("\n");
		printf("���������������ʣ���������,�����޷����з���!\n\n");
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
	printf("��ҵ��:%s\n",q->name);
	printf("  ҳ��    ���\n");
	for(i=0;i<q->block_amount;i++)
		printf("   %d    %d\n",q->page_list[i].page_number,q->page_list[i].block_number);                        
	printf("\n");
	return 1;
}

int recycle_store(Assignment *head,Bit_Figure *bit_figure)  /*������ҵ*/
{
	int m,n=0;
	int BiaoJi=0;   /*�ж��Ƿ���ڸ���ҵ,0��ʾû��,1��ʾ����*/
	char name1[10];
	Assignment *p=head->next;
	Assignment *q,*temp,*p1;
	q=head;
	temp=head->next;
	p1=temp;
	if(head->next==NULL)
	{
		printf("û����ҵռ������,����û�п��Ի��յ���ҵ!\n");
		return 0;
	}
	printf("������Ҫ������ҵ������:");
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
			printf("��ҵ�黹�Ŀ����:");
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
			if(q==head)  /*�ж�ɾ�����Ƿ��Ǵ�������ĵ�һ����ҵ*/
				head->next=temp->next;
			if(temp->next==NULL)   /*�ж�ɾ�����Ƿ��Ǵ�����������һ����ҵ*/
				p1->next=NULL;
			if(temp->next!=NULL)     /*�ж�ɾ�����Ƿ��������м��һ����ҵ*/
				p1->next=temp->next;
			n++;
		}
		p1=temp;
		temp=temp->next;
		q=q->next;
	}
	if(BiaoJi==0)
		printf("������û�и���ҵ!\n");
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
		printf("\n\n\t                    ��ҳʽ�洢����ϵͳ               ");
		printf("\n\n\t***************************************************************");
		printf("\n\n\t\t��ѡ���ܲ˵�ѡ� ");
		printf("\n\n\t\t\t\t1.λʾͼ��ʼ����");
		printf("\n\n\t\t\t\t2.��ʾ��ǰλʾͼ�� ");
		printf("\n\n\t\t\t\t3.������䣺");
		printf("\n\n\t\t\t\t4.������գ�");
		printf("\n\n\t\t\t\t5.�˳�!");
		printf("\n\n");
		printf("\t\t��ѡ��(1-5): ");
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
		printf("�Ƿ����(Y/N):");
		scanf("%c",&ch);
		if(ch!='Y'&&ch!='y')
			break;
	}
}
