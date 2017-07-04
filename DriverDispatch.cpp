#include<iostream>
#include<string>
using namespace std;
#define N 10

class I_O_Table		//请求I/O表
{
public:
	string  Name;		//进程名
	int	Cylinder_Num;	//柱面号
	int Track_Num;		//磁道号
	int Physic_Rec;		//物理记录号
	int sign;			//标志位，是否被选中
	I_O_Table(){		//I/O请求表初始化
		Name=' ';
		Cylinder_Num=-1;
		Track_Num=-1;
		Physic_Rec=-1;
	}

	void Insert(string Na,int C,int T,int P)	//I/O表登记函数
	{
		Name=Na;
		Cylinder_Num=C;
		Track_Num=T;
		Physic_Rec=P;
		sign=0;
	}
	
	void clear(){
		Name="NULL";
		Cylinder_Num=-1;
		Track_Num=-1;
		Physic_Rec=-1;
		sign=0;		
	}

	void display(){

		cout<<Name<<"\t\t"<<Cylinder_Num<<"\t\t"<<Track_Num<<"\t\t"<<Physic_Rec<<"\t\t"<<sign<<endl;
	}

};

void Required(I_O_Table *list){
	string Na;
	int C,T,P;

	cout<<"请输入进程名：";
	cin>>Na;
	cout<<"请输入柱面号(0-199)：";
	cin>>C;
    cout<<"请输入磁道号(0-19)：";
	cin>>T;
	cout<<"请输入物理记录号(0-7)：";
	cin>>P;

	for(int i=0;i<N;i++)
		if (list[i].Cylinder_Num==-1)
		{
			list[i].Insert(Na,C,T,P);
			break;
		}
}

void Control(I_O_Table *list,string &dir,int temp)
{

	//int same=-2;		
	int i=0,j=0;
	int m=temp;		//
	for(;i<N;i++)
		if(list[i].Cylinder_Num!=-1)
			break;
	if(i==N)
		cout<<"当前不存在等待进程!"<<endl;
	else
	{
		/*
		for(;j<N;j++)
			if(list[j].sign==1)
				same=list[j].Cylinder_Num;
		for(int k=0;k<N;k++)
			if(list[k].Cylinder_Num==same&&k!=j)
				return;		//旋转臂
		*/
		if(dir=="up")	//往里移
		{
			for(;m<200;m++)
				for(i=0;i<N;i++)
					if(list[i].Cylinder_Num==m)
					{ list[i].sign=1;return; }
			if(m==200)
				dir="down";
		}
		if(dir=="down")
		{
			for(;m>-1;m--)
				for(i=0;i<N;i++)
					if(list[i].Cylinder_Num==m)
					{ list[i].sign=1;return; }
			if(m==-1)
				dir="up";
		}


		
	}

}
void main()
{
	I_O_Table pt[N];
	string dir="up";					//设定方向向里
	float n;
	int temp=0;
	char choice;
	pt[0].Insert("P0",0,0,0);    //初始化当前进程
	pt[1].Insert("P1",100,1,1); 
	pt[2].Insert("P2",20,2,2);

	do
	{
	cout<<"输入在[0,1]区间的一个随机数: "<<endl;

	cin>>n;
	if(0<=n&&n<=0.5)
		Required(pt);//接受请求
	else if(0.5<n&&n<=1)
		Control(pt,dir,temp);//驱动调度
	else
		cout<<"输入错误！"<<endl;


	for(int i=0;i<N;i++)
		if(pt[i].sign==1)
		{	
			cout<<"选中的进程："<<endl;
			cout<<"进程名\t\t柱面号\t\t物理记录号\t方向"<<endl;
			temp=pt[i].Cylinder_Num;
			cout<<pt[i].Name<<"\t\t"<<pt[i].Cylinder_Num<<"\t\t"<<pt[i].Physic_Rec<<"\t\t"<<dir<<endl;
			pt[i].clear();
		}

	cout<<"请求I/O表："<<endl;
	cout<<"进程名\t\t柱面号\t\t磁道号\t\t物理记录号"<<endl;
	for(i=0;i<N;i++)
		if(pt[i].Cylinder_Num!=-1&&pt[i].sign!=1)
			pt[i].display(); 

	cout<<"是否继续?(Y/N)"<<endl;
	getchar();
	cin>>choice;
	
	}while(choice=='Y'||choice=='y');

	system("pause");

}
