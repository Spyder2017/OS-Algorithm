#include<iostream>
#include<string>
using namespace std;
#define N 10

class I_O_Table		//����I/O��
{
public:
	string  Name;		//������
	int	Cylinder_Num;	//�����
	int Track_Num;		//�ŵ���
	int Physic_Rec;		//�����¼��
	int sign;			//��־λ���Ƿ�ѡ��
	I_O_Table(){		//I/O������ʼ��
		Name=' ';
		Cylinder_Num=-1;
		Track_Num=-1;
		Physic_Rec=-1;
	}

	void Insert(string Na,int C,int T,int P)	//I/O��ǼǺ���
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

	cout<<"�������������";
	cin>>Na;
	cout<<"�����������(0-199)��";
	cin>>C;
    cout<<"������ŵ���(0-19)��";
	cin>>T;
	cout<<"�����������¼��(0-7)��";
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
		cout<<"��ǰ�����ڵȴ�����!"<<endl;
	else
	{
		/*
		for(;j<N;j++)
			if(list[j].sign==1)
				same=list[j].Cylinder_Num;
		for(int k=0;k<N;k++)
			if(list[k].Cylinder_Num==same&&k!=j)
				return;		//��ת��
		*/
		if(dir=="up")	//������
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
	string dir="up";					//�趨��������
	float n;
	int temp=0;
	char choice;
	pt[0].Insert("P0",0,0,0);    //��ʼ����ǰ����
	pt[1].Insert("P1",100,1,1); 
	pt[2].Insert("P2",20,2,2);

	do
	{
	cout<<"������[0,1]�����һ�������: "<<endl;

	cin>>n;
	if(0<=n&&n<=0.5)
		Required(pt);//��������
	else if(0.5<n&&n<=1)
		Control(pt,dir,temp);//��������
	else
		cout<<"�������"<<endl;


	for(int i=0;i<N;i++)
		if(pt[i].sign==1)
		{	
			cout<<"ѡ�еĽ��̣�"<<endl;
			cout<<"������\t\t�����\t\t�����¼��\t����"<<endl;
			temp=pt[i].Cylinder_Num;
			cout<<pt[i].Name<<"\t\t"<<pt[i].Cylinder_Num<<"\t\t"<<pt[i].Physic_Rec<<"\t\t"<<dir<<endl;
			pt[i].clear();
		}

	cout<<"����I/O��"<<endl;
	cout<<"������\t\t�����\t\t�ŵ���\t\t�����¼��"<<endl;
	for(i=0;i<N;i++)
		if(pt[i].Cylinder_Num!=-1&&pt[i].sign!=1)
			pt[i].display(); 

	cout<<"�Ƿ����?(Y/N)"<<endl;
	getchar();
	cin>>choice;
	
	}while(choice=='Y'||choice=='y');

	system("pause");

}
