
#pragma once
#include<list>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//全局变量，用于保存输入输出文件
extern ifstream infile;
extern ofstream outfile;

//资源控制块
struct RCB {
	string rname = "Ri";    //资源名称
	int initial = 0;    //资源数量
	int status = 0;    //资源状态
	list<int> waitList;    //等待资源的进程列表
};

//资源 
struct resource {
	int rid = -1;    //资源ID
	int used = 0;    //是否被占用
	int waitNum = 0;    //等待该资源的进程数
};

//进程控制块
struct PCB {
	string pname = " ";    //进程名
	string  state = "ready";    //进程状态
	int id = -1;    //进程id
	int parent = -1;    //父进程
	int children = -1;    //子进程
	int previous = -1;    //该进程的前一个进程
	int next = -1;    //该进程的后一个进程
	int priority = -1;    //进程优先级
	resource resource[4];    //进程资源
};