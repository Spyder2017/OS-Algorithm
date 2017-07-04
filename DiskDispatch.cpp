#include <cstdio> 
#include <iostream> 
#include <cstring> 
#include <cmath> 
using namespace std;

const int MAXQUEUE=200; //������������ 


//�ṹ�嶨�� 

typedef struct node{ 
	int go; 
	int visited; 
}qu; 

qu queue[MAXQUEUE]; 
int quantity; 

int start; //���忪ʼʱ��ͷ����λ�� 

//��ʼ������ 
void initial() 
{ 
	int i; 
	
	for(i=0;i<MAXQUEUE;i++){ 
		queue[i].go=-1; 
		queue[i].visited=0; 
	} 
	
	start=53;//��ͷ�ĳ�ʼλ�� 

} 

//����ŵ����� 
void readData() 
{ 
	FILE *fp; 
	char fname[20]; 
	int temp,i; 
	
	cout<<"������ŵ������ļ���:"; 
	strcpy(fname,"7hard.txt"); 
	cin>>fname; 
	
	if((fp=fopen(fname,"r"))==NULL){ 
		cout<<"����,�ļ��򲻿�,�����ļ���:)"<<endl; 
	} 
	else{ 
		while(!feof(fp)){ 
			fscanf(fp,"%d ",&temp); 
			queue[quantity].go=temp; 
			quantity++; 
		} 
		cout<<endl<<"---------------------------------------------"<<endl; 
		cout<<"������Ĵŵ�����:"; 
		for(i=0;i<quantity;i++){ 
			cout<<queue[i].go<<" "; 
		} 
		cout<<endl<<"������Ϊ:"<<quantity<<endl; 
	} 
} 

//FIFO�㷨 
void FIFO() 
{ 
	int i; 
	int total=0; 
	int current; 
	
	cout<<endl<<"---------------------------------------------"<<endl; 
	cout<<"FIFO�㷨�ķ��ʴŵ���˳����:"; 
	
	current=start; 
	for(i=0;i<quantity;i++){ 
		cout<<queue[i].go<<" "; 
		total+=abs(queue[i].go-current); 
		current=queue[i].go; 
	} 
	cout<<endl<<"��ͷ�ƹ���������:"<<total; 
} 

//���Ѱ�����ȵ����㷨
void shortest() 
{ 
	int i,j,p; 
	int total=0; 
	int current; 
	
	cout<<endl<<"---------------------------------------------"<<endl; 
	cout<<"���Ѱ�����ȵ����㷨�ķ��ʴŵ���˳����:"; 
	
	current=start; 
	for(i=0;i<quantity;i++){ 
		p=0; 
		while(queue[p].visited!=0){ 
			p++; 
		} 
		for(j=p;j<quantity;j++){ 
			if((queue[j].visited==0)&&(abs(current-queue[p].go)>abs(current-queue[j].go))){ 
				p=j; 
			} 
		} 
		cout<<queue[p].go<<" "; 
		total+=abs(queue[p].go-current); 
		queue[p].visited=1; 
		current=queue[p].go; 
	} 
	cout<<endl<<"��ͷ�ƹ���������:"<<total; 
} 

//�����㷨
void elevator() 
{ 
	int i,j,p,flag; 
	int total=0; 
	int current; 
	
	cout<<endl<<"---------------------------------------------"<<endl; 
	cout<<"���ݵ����㷨"<<endl; 
	
	//��ͷ��ʼ���� 

	cout<<"��ͷ��ʼ����ķ��ʴŵ���˳����:"; 
	
	current=start; 
	for(i=0;i<quantity;i++){ 
		flag=1000; 
		p=-1; 
		for(j=0;j<quantity;j++){ 
			if((queue[j].visited==0)&&(queue[j].go>=current)){ 
				if(abs(queue[j].go-current)<flag){ 
					p=j; 
					flag=abs(queue[j].go-current); 
				} 
			} 
		} 
		if(p!=-1){ 
			cout<<queue[p].go<<" "; 
			total+=abs(queue[p].go-current); 
			current=queue[p].go; 
			queue[p].visited=1; 
		} 
		else{ 
			for(j=0;j<quantity;j++){ 
				if((queue[j].visited==0)&&(queue[j].go<current)){ 
					if(abs(queue[j].go-current)<flag){ 
						p=j; 
						flag=abs(queue[j].go-current); 
					} 
				} 
			} 
			cout<<queue[p].go<<" "; 
			total+=abs(queue[p].go-current); 
			current=queue[p].go; 
			queue[p].visited=1; 
		} 
	} 
	cout<<endl<<"��ͷ�ƹ���������:"<<total<<endl; 
	
	//��ͷ��ʼ���� 

	for(i=0;i<quantity;i++){ 
		queue[i].visited=0; 
	} 
	total=0; 
	
	cout<<"��ͷ��ʼ����ķ��ʴŵ���˳����:"; 
	
	current=start; 
	for(i=0;i<quantity;i++){ 
		flag=1000; 
		p=-1; 
		for(j=0;j<quantity;j++){ 
			if((queue[j].visited==0)&&(queue[j].go<=current)){ 
				if(abs(queue[j].go-current)<flag){ 
					p=j; 
					flag=abs(queue[j].go-current); 
				} 
			} 
		} 
		if(p!=-1){ 
			cout<<queue[p].go<<" "; 
			total+=abs(queue[p].go-current); 
			current=queue[p].go; 
			queue[p].visited=1; 
		} 
		else{ 
			for(j=0;j<quantity;j++){ 
				if((queue[j].visited==0)&&(queue[j].go>current)){ 
					if(abs(queue[j].go-current)<flag){ 
						p=j; 
						flag=abs(queue[j].go-current); 
					} 
				} 
			} 
			cout<<queue[p].go<<" "; 
			total+=abs(queue[p].go-current); 
			current=queue[p].go; 
			queue[p].visited=1; 
		} 
	} 
	cout<<endl<<"��ͷ�ƹ���������:"<<total; 
	
} 

void version() 
{ 
	cout<<endl<<endl; 
	
	cout<<" ��������������������������������������������������"<<endl; 
	cout<<" �������� ��     ���̵����㷨ϵͳ �� ��������    ��"<<endl; 
	cout<<" ��������������������������������������������������"<<endl; 
	
	cout<<endl<<endl; 
} 


int main(void) 
{ 
	int i; 
	
	version(); 
	initial(); 
	
	readData(); 
	
	FIFO(); 
	
	shortest(); 
	
	for(i=0;i<quantity;i++){ 
		queue[i].visited=0; 
	} 
	
	elevator(); 
} 