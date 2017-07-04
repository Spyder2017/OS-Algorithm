#include <iostream>
#include <typeinfo.h>
#include <queue>	//����STL�е����ȶ���
using namespace std;
 
//����һ��PCB������
class PCB
{
public:
	char name[10];//���̵�����
	float runtime;//�ý��̵�����ʱ��
	float priority;//�ý��̵����ȼ�
	char state;//�ý��̵�״̬
	PCB* next;//ָ���¸����̵�ָ��
	void print()const//������̵���Ϣ
	{
		cout<<"(name="<<name<<",runtime="<<runtime<<",state="<<state<<",priority="<<priority<<")"<<endl;
	}
};

//���ȶ��е�����׼����
class PCBSortCriterion
{
public:
	bool operator()(const PCB & p1,const PCB & p2)const//�º���ȷ������׼�򣬴Ӵ�С
	{
		return (p1.priority < p2.priority);
	}
};
 
int main()
{
	int number;//������
	cout<<"��������Ҫ�����Ľ�����:"<<endl;
	cin>>number;
	PCB* pcb=new PCB[number];//һ��PCB���������������������
	PCB* p1=new PCB[number];//һ��PCB���������������Ѿ������Ľ���
	int n=0, //����ִ�еĴ���
		m=0;//��ɽ��̵ĸ���

	cout<<endl;

	PCB p;//һ��PCB�͵ı����������������Ԫ��
	int i;
        
	for( i=0 ;i<=number-1;i++)//����������Ϣ
	{
		cout<<"������pcb["<<i<<"]����Ϣ!"<<endl;
		cout<<"��(name(char[10]),runtime(float),state(��ʼΪR),priority(float))��ʽ����:"<<endl;
		cin>>pcb[i].name;
		cin>>pcb[i].runtime;
		cin>>pcb[i].state;
		cin>>pcb[i].priority;
		cout<<endl;
	}
      
      
	typedef priority_queue<PCB,vector<PCB> ,PCBSortCriterion> pQueue;//��PCBSortCriterionΪ����׼������ȶ���
	pQueue q,// ���ȶ���pQueue��һ�����󣬶�������н���������
		temp;//���ȶ���pQueue��һ��������q��һ������������Ϊʵ�ִ�ӡ���//��һ���м����

	for(int j=0;j<=number-1;j++)//��������ӽ������ȶ���
	{
		if(pcb[j].runtime>0)
		{
			q.push(pcb[j]);
		}
		else
		{
			p1[m++] = pcb[j];
		}
	}

	//������̿��ƿ�ĳ�ʼ״̬��Ϣ
	cout<<"���̿��ƿ�ĳ�ʼ״̬��ϢΪ:"<<endl;
	temp=q;
	while(!temp.empty())
	{
		p=temp.top();
		for(int i=0;i<m;i++)
		{
			p1[i].print();
			p1[i].state='E';
		}
		p.print();
		temp.pop();
	}
	cout<<endl;

	while(!q.empty())//�Խ��̽��е���
	{
		cout<<"��"<<++n<<"������";
		p=q.top();
		cout<<q.top().name<<"!"<<endl;
		p.runtime-=1;//Ҫ������ʱ��-1
		p.priority-=1;//������-1
		q.pop();
		if(p.runtime>0)//�����ý��̻�δִ���� ��������ӽ��в���
		{
			q.push(p);
		}
		else 
		{//�����ý����Ѿ�ִ���꣬������״̬ΪE�������䱣�浽p1��
			p.state='E';
			p1[m++]=p;
		}
			
		cout<<"���к��״̬Ϊ:"<<endl;//��ӡ�����к�Ľ���״̬
		temp=q;//�����������
		while(!temp.empty())
		{
			p=temp.top();
			p.print();
			temp.pop();
		}
		if(m>0)//�����ɵĽ��̵���Ϣ
			for( i=0;i<=m-1;i++)
				p1[i].print();
			cout<<endl;
			cout<<endl;
	}
	cout<<"��ϲ�㣡��Ľ����Ѿ�������ϣ�"<<endl;
	system("pause");
	return 0;
}