#include <cstring> 
#include <iostream>
using namespace std;
 
#define M 5 //总进程数 
#define N 3 //总资源数 
#define FALSE 0
#define TRUE 1

//M个进程对N类资源最大资源需求量 
int MAX[M][N]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}}; 
//系统可用资源数 
int AVAILABLE[N]={10,5,7}; 
//M个进程已经得到N类资源的资源量 
int ALLOCATION[M][N]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}}; 
//M个进程还需要N类资源的资源量 
int NEED[M][N]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}}; 
int Request[N]={0,0,0}; 


int main(void)
{
	int i=0,j=0; 
	char flag='Y'; 
	void showdata(); 
	void changdata(int); 
	void rstordata(int); 
	int chkerr(int); 

	showdata(); 
	while(flag=='Y'||flag=='y') 
	{
		i=-1; 
		while(i<0||i>=M)
		{
			cout<<" 请输入需申请资源的进程号（从0到"<<M-1<<"，否则重输入!）:"; 
			cin>>i; 
			if(i<0||i>=M)cout<<" 输入的进程号不存在，重新输入!"<<endl; 
		}
		cout<<" 请输入进程"<<i<<"申请的资源数"<<endl; 
		for(j=0;j<N;j++) 
		{
			cout<<" 资源"<<j<<": "; 
			cin>>Request[j]; 
			if(Request[j]>NEED[i][j])
			{
				cout<<" 进程"<<i<<"申请的资源数大于进程"<<i<<"还需要"<<j<<"类资源的资源量!"; 
				cout<<"申请不合理，出错!请重新选择!"<<endl<<endl; 
				flag='N'; 
				break; 
			}
			else
			{
				if(Request[j]>AVAILABLE[j]) 
				{ 
					cout<<" 进程"<<i<<"申请的资源数大于系统可用"<<j<<"类资源的资源量!"; 
					cout<<"申请不合理，出错!请重新选择!"<<endl<<endl; 
					flag='N'; 
					break; 
				}
			}
		}
		if(flag=='Y'||flag=='y')
		{
			changdata(i); 
			if(chkerr(i)) 
			{
				rstordata(i); 
				showdata();
			}
			else
				showdata(); 
		}
		else
			showdata(); 
		cout<<endl; 
		cout<<" 是否继续银行家算法演示,按'Y'或'y'键继续,按'N'或'n'键退出演示: "; 
		cin>>flag; 
	}
}


void showdata() 
{ 
	int i,j; 
	cout<<" 系统可用的资源数为:"<<endl<<endl; 
	cout<<" "; 
	for (j=0;j<N;j++)cout<<" 资源"<<j<<": "<<AVAILABLE[j]; 
	cout<<endl; 
	// cout<<endl; 
	// cout<<" 各进程资源的最大需求量:"<<endl<<endl; 
	// for (i=0;i<M;i++) 
	// { 
	// cout<<"进程"<<i<<":"; 
	// for (j=0;j<N;j++)cout<<" 资源"<<j<<": "<<MAX[i][j]; 
	// cout<<endl; 
	// } 
	cout<<endl; 
	cout<<" 各进程还需要的资源量:"<<endl<<endl; 
	for(i=0;i<M;i++) 
	{
		cout<<"进程"<<i<<":"; 
		for(j=0;j<N;j++)cout<<" 资源"<<j<<": "<<NEED[i][j]; 
		cout<<endl; 
	}
	cout<<endl; 
	cout<<" 各进程已经得到的资源量: "<<endl<<endl; 
	for(i=0;i<M;i++) 
	{
		cout<<"进程"<<i<<":"; 
		for(j=0;j<N;j++)cout<<" 资源"<<j<<": "<<ALLOCATION[i][j]; 
		cout<<endl; 
	} 
	cout<<endl; 
}

void changdata(int k)
{ 
	int j; 
	for (j=0;j<N;j++) 
	{ 
		AVAILABLE[j]=AVAILABLE[j]-Request[j]; 
		ALLOCATION[k][j]=ALLOCATION[k][j]+Request[j]; 
		NEED[k][j]=NEED[k][j]-Request[j]; 
	} 

}

void rstordata(int k) 
{ 
	int j; 
	for (j=0;j<N;j++) 
	{ 
		AVAILABLE[j]=AVAILABLE[j]+Request[j]; 
		ALLOCATION[k][j]=ALLOCATION[k][j]-Request[j]; 
		NEED[k][j]=NEED[k][j]+Request[j]; 
	} 
}

int chkerr(int s) 
{ 
	int WORK,FINISH[M],temp[M]; 
	int i,j,k=0; 
	for(i=0;i<M;i++)FINISH[i]=FALSE; 
	for(j=0;j<N;j++) 
	{
		WORK=AVAILABLE[j]; 
		i=s; 
		while(i<M) 
		{
			if(FINISH[i]==FALSE&&NEED[i][j]<=WORK)
			{
				WORK=WORK+ALLOCATION[i][j]; 
				FINISH[i]=TRUE; 
				temp[k]=i; 
				k++;
				i=0;
			}
			else
			{
				i++;
			}
		}
		for(i=0;i<M;i++) 
			if(FINISH[i]==FALSE) 
			{
				cout<<endl; 
				cout<<" 系统不安全!!! 本次资源申请不成功!!!"<<endl; 
				cout<<endl;
				return 1;
			}
	}
	cout<<endl; 
	cout<<" 经安全性检查，系统安全，本次分配成功。"<<endl; 
	cout<<endl; 
	cout<<" 本次安全序列："; 
	for(i=0;i<M;i++)cout<<"进程"<<temp[i]<<"->"; 
	cout<<endl<<endl;
	return 0; 
}
