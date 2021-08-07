
#pragma once
#include "DataStructure.hpp"

using namespace std;

//进程资源管理类声明
class ProcessResourceManage {
private:
	list<int> redyList[3];    //用来存储进程的链表

public:
	int currentRunning;    //当前正在运行的进程的id
	RCB rcb[4];    //资源控制块，4个，对应四类资源
	PCB pcb[20];    //进程控制块，20个，即最多同时有20个进程

	ProcessResourceManage();    //构造函数中初始化类中的一些变量
	~ProcessResourceManage();    //析构函数
	void init();    //初始化
	void create(string name, int p);    //创建进程
	int scheduler();    //进程调度
	void destroy(int n);    //进程撤销
	void processList();    //输出所有进程的信息
	void processInfo(string name);    //输出给定进程的信息
	int search(string name);    //根据进程名查找进程的位置

	void request(int n, int unit);    //请求资源
	void release(int n, int unit);    //释放资源
	void resourceList();    //输出所有资源的信息

	void timeout();    //定时中断
};

//构造函数，初始化类中的一些变量
ProcessResourceManage::ProcessResourceManage() {
	//初始化进程控制块的id
	for (int i = 0; i < 20; i++) {
		pcb[i].id = i;
	}

	//初始化0号进程为初始化进程
	pcb[0].pname = "init";
	pcb[0].priority = 0;
	redyList[0].push_back(0);
	currentRunning = 0;

	//初始化资源控制块
	for (int i = 0; i < 4; i++) {
		rcb[i].initial = 1;
		rcb[i].status = 1;
	}
	//设置资源的名字
	rcb[0].rname = "R1";
	rcb[1].rname = "R2";
	rcb[2].rname = "R3";
	rcb[3].rname = "R4";
}

//析构函数
ProcessResourceManage::~ProcessResourceManage() {}

//初始化函数，对应init命令
void ProcessResourceManage::init() {
	//初始化进程控制块中变量的值
	for (int i = 1; i < 20; i++) {
		pcb[i].pname = " ";
		pcb[i].state = "ready";
		pcb[i].parent = -1;
		pcb[i].children = -1;
		pcb[i].next = -1;
		pcb[i].previous = -1;
		pcb[i].priority = -1;
		pcb[i].resource[0].rid = -1;
		pcb[i].resource[1].rid = -1;
		pcb[i].resource[2].rid = -1;
		pcb[i].resource[3].rid = -1;
		pcb[i].resource[0].used = 0;
		pcb[i].resource[1].used = 0;
		pcb[i].resource[2].used = 0;
		pcb[i].resource[3].used = 0;
		pcb[i].resource[0].waitNum = 0;
		pcb[i].resource[1].waitNum = 0;
		pcb[i].resource[2].waitNum = 0;
		pcb[i].resource[3].waitNum = 0;
	}
	currentRunning = 0;    //当前正在执行的进程是init

	//初始化资源控制块
	for (int i = 0; i < 4; i++) {
		rcb[i].initial = i + 1;
		rcb[i].status = i + 1;
		while (!rcb[i].waitList.empty()) {
			rcb[i].waitList.pop_front();
		}
	}

	//初始化进程队列
	for (int i = 0; i < 3; i++) {
		while (!redyList[i].empty()) {
			redyList[i].pop_back();
		}
	}
}

//创建进程
void ProcessResourceManage::create(string name, int p) {
	for (int i = 1; i < 20; i++) {
		//找到一个未分配的进程控制块进行分配
		if (pcb[i].pname == " ") {
			pcb[i].pname = name;   //进程名
			pcb[i].priority = p;    //优先级
			redyList[p].push_back(pcb[i].id);
			pcb[i].parent = currentRunning;    //父进程
			//设置进程控制块中进程的次序关系
			for (int j = 1; j < 20; j++) {
				if (j < i && pcb[j].parent == pcb[i].parent) {
					pcb[j].previous = i;
					pcb[i].next = j;
				}
			}
			break;
		}
	}
	scheduler();    //重新调度
}

//进程调度
int ProcessResourceManage::scheduler() {
	if (!redyList[2].empty()) {
		currentRunning = redyList[2].front();
		pcb[currentRunning].state = "running";
		return redyList[2].front();
	}
	else if (!redyList[1].empty()) {
		currentRunning = redyList[1].front();
		pcb[currentRunning].state = "running";
		return redyList[1].front();
	}
	else {
		currentRunning = 0;
		pcb[currentRunning].state = "running";
		return 0;
	}
}

//撤销进程
void ProcessResourceManage::destroy(int n) {
	//先释放进程占用的资源
	for (int i = 0; i < 4; i++) {
		if (pcb[n].resource[i].used != 0) {
			release(i, pcb[n].resource[i].used);
			if (rcb[i].status > rcb[i].initial) {
				cout << "destroy failed: delete resources error" << endl;
			}
			pcb[n].resource[i].rid = -1;
			pcb[n].resource[i].used = 0;
		}
	}
	//如果进程正在运行或处于就绪状态，则从就绪队列删除
	if (pcb[n].state == "ready" or pcb[n].state == "running") {
		int p = pcb[n].priority;
		redyList[p].remove(n);
	}
	//如果进程在阻塞状态，从阻塞队列中删除
	else if ((pcb[n].state).compare("blocked") == 0) {
		for (int i = 0; i < 4; i++) {
			rcb[i].waitList.remove(n);
		}
	}
	//重置删除后pcb对应位置的变量
	for (int i = 0; i < 20; i++) {
		if (pcb[i].parent == n) {
			destroy(pcb[i].id);
		}
		if (pcb[i].id == n) {
			pcb[i].pname = " ";
			pcb[i].state = "ready";
			pcb[i].parent = -1;
			pcb[i].children = -1;
			pcb[i].next = -1;
			pcb[i].previous = -1;
			pcb[i].priority = -1;
			pcb[i].resource[0].rid = -1;
			pcb[i].resource[1].rid = -1;
			pcb[i].resource[2].rid = -1;
			pcb[i].resource[3].rid = -1;
			pcb[i].resource[0].used = 0;
			pcb[i].resource[1].used = 0;
			pcb[i].resource[2].used = 0;
			pcb[i].resource[3].used = 0;
			pcb[i].resource[0].waitNum = 0;
			pcb[i].resource[1].waitNum = 0;
			pcb[i].resource[2].waitNum = 0;
			pcb[i].resource[3].waitNum = 0;
		}
		if (pcb[i].next == n) {
			pcb[i].next = -1;
		}
		if (pcb[i].previous == n) {
			pcb[i].previous = -1;
		}
	}
	scheduler();
}

//显示所有进程
void ProcessResourceManage::processList()
{
	cout << "All processes and their status:" << endl;
	//遍历所有进程控制块，如果名字不为空则打印出对应的信息
	for (int i = 1; i < 20; i++) {
		if (pcb[i].pname != " ") {
			cout << "    " << pcb[i].pname << "  " << pcb[i].state << endl;
		}
	}
}

//输出给定进程的信息
void ProcessResourceManage::processInfo(string name)
{
	int t = search(name);    //先搜索对应的进程
	if (t != -1)    //如果找到则打印进程信息
	{
		cout << "the info of process " << name << " :" << endl;
		cout << "    " << pcb[t].pname << "  " << pcb[t].state << endl;
	}
	else
	{
		cout << "the process does not exist!" << endl;
	}
}

//给定进程名，搜索该进程在PCB中的位置
int ProcessResourceManage::search(string name) {
	//遍历搜索
	for (int i = 0; i < 20; i++) {
		if (name.compare(pcb[i].pname) == 0) {
			return i;
		}
	}
	return -1;
}

//请求资源
void ProcessResourceManage::request(int n, int unit) {
	//如果请求的资源小于剩余资源则分配
	if (rcb[n].status >= unit) {
		rcb[n].status = rcb[n].status - unit;
		pcb[currentRunning].resource[n].rid = n;
		pcb[currentRunning].resource[n].used += unit;
	}
	//资源不够用，阻塞进程
	else {
		pcb[currentRunning].state = "blocked";
		pcb[currentRunning].resource[n].waitNum += unit;
		rcb[n].waitList.push_back(currentRunning);
		redyList[pcb[currentRunning].priority].remove(currentRunning);
	}
	scheduler();
}

//释放资源
void ProcessResourceManage::release(int n, int unit) {
	pcb[currentRunning].resource[n].used -= unit;
	rcb[n].status += unit;
	int temp_pcb = rcb[n].waitList.front();
	while (temp_pcb != 0 && pcb[temp_pcb].resource[n].waitNum <= rcb[n].status) {
		rcb[n].status -= pcb[temp_pcb].resource[n].waitNum;
		rcb[n].waitList.remove(temp_pcb);
		pcb[temp_pcb].state = "ready";
		pcb[temp_pcb].resource[n].used += pcb[temp_pcb].resource[n].waitNum;
		redyList[pcb[temp_pcb].priority].push_back(temp_pcb);
	}
	scheduler();//调度程序
}

//输出所有资源的信息
void ProcessResourceManage::resourceList()
{
	cout << "All resources and their status:" << endl;
	//遍历四种资源，打印出信息
	for (int i = 0; i < 4; i++) {
		cout << "    " << rcb[i].rname << " " << rcb[i].initial << " " << rcb[i].status << endl;
	}
}

//定时中断
void ProcessResourceManage::timeout() {
	//剥夺当前进程的执行，重新调度
	int p = pcb[currentRunning].priority;
	redyList[p].remove(currentRunning);
	pcb[currentRunning].state = "ready";
	redyList[p].push_back(currentRunning);
	scheduler();
}
