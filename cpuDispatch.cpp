#include <iostream>
#include <typeinfo.h>
#include <queue>	//调用STL中的优先队列
using namespace std;
 
//定义一个PCB进程类
class PCB
{
public:
	char name[10];//进程的名字
	float runtime;//该进程的运行时间
	float priority;//该进程的优先级
	char state;//该进程的状态
	PCB* next;//指向下个进程的指针
	void print()const//输出进程的信息
	{
		cout<<"(name="<<name<<",runtime="<<runtime<<",state="<<state<<",priority="<<priority<<")"<<endl;
	}
};

//优先队列的优先准则类
class PCBSortCriterion
{
public:
	bool operator()(const PCB & p1,const PCB & p2)const//仿函数确定优先准则，从大到小
	{
		return (p1.priority < p2.priority);
	}
};
 
int main()
{
	int number;//进程数
	cout<<"请输入你要建立的进程数:"<<endl;
	cin>>number;
	PCB* pcb=new PCB[number];//一个PCB的数组用来保存就绪进程
	PCB* p1=new PCB[number];//一个PCB的数组用来保存已经结束的进程
	int n=0, //进程执行的次数
		m=0;//完成进程的个数

	cout<<endl;

	PCB p;//一个PCB型的变量，用来保存队首元素
	int i;
        
	for( i=0 ;i<=number-1;i++)//建立进程信息
	{
		cout<<"请输入pcb["<<i<<"]的信息!"<<endl;
		cout<<"以(name(char[10]),runtime(float),state(初始为R),priority(float))格式输入:"<<endl;
		cin>>pcb[i].name;
		cin>>pcb[i].runtime;
		cin>>pcb[i].state;
		cin>>pcb[i].priority;
		cout<<endl;
	}
      
      
	typedef priority_queue<PCB,vector<PCB> ,PCBSortCriterion> pQueue;//以PCBSortCriterion为优先准则的优先队列
	pQueue q,// 优先队列pQueue的一个对象，对这个队列进行主操作
		temp;//优先队列pQueue的一个对象，是q的一个拷贝对象，作为实现打印输出//的一个中间变量

	for(int j=0;j<=number-1;j++)//将进程入队建立优先队列
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

	//输出进程控制块的初始状态信息
	cout<<"进程控制块的初始状态信息为:"<<endl;
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

	while(!q.empty())//对进程进行调度
	{
		cout<<"第"<<++n<<"次运行";
		p=q.top();
		cout<<q.top().name<<"!"<<endl;
		p.runtime-=1;//要求运行时间-1
		p.priority-=1;//优先数-1
		q.pop();
		if(p.runtime>0)//表明该进程还未执行完 ，继续入队进行操作
		{
			q.push(p);
		}
		else 
		{//表明该进程已经执行完，设置其状态为E，并将其保存到p1中
			p.state='E';
			p1[m++]=p;
		}
			
		cout<<"运行后的状态为:"<<endl;//打印出运行后的进程状态
		temp=q;//拷贝输出队列
		while(!temp.empty())
		{
			p=temp.top();
			p.print();
			temp.pop();
		}
		if(m>0)//输出完成的进程的信息
			for( i=0;i<=m-1;i++)
				p1[i].print();
			cout<<endl;
			cout<<endl;
	}
	cout<<"恭喜你！你的进程已经调度完毕！"<<endl;
	system("pause");
	return 0;
}