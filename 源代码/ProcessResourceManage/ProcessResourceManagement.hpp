/*
 * ProcessResourceManagement.hpp
 *
 * Created on: May 11, 2019
 * Author: Daozhi
 */

#ifndef PROCESS_RESOURCE_MANAGEMENT_HPP
#define PROCESS_RESOURCE_MANAGEMENT_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <list>

using namespace std;

//进程控制块结构体
struct PCB{
    string name = " ";     //进程名
    string type = "ready";    //进程状态

    int pid = -1;    //进程ID
    int parent = -1;    //父进程
    int children = -1;    //子进程ID
    int younger = -1;
    int older = -1;
    int priority = -1;    //进程优先级
    // int CPUState = -1;    //CPU占用情况
    // int memory = -1;    //内存占用情况
    // int openFiles = -1;    //打开文件情况

    resource other_reource[4];
};

//资源结构体
struct resource{
    int rid = -1;    //资源ID
    int used = -1;    //是否被使用
    int waitRequest = 0;    //???? 
};

//资源控制块
struct RCB{
    int rid = -1;    //资源ID
    int initial = 0;    //初始资源总数
    int remaining = 0;    //剩余资源数
    list<int> waitList;    //请求的队列，装进程ID
};

//进程资源控制器
class ProcessResourceManagement{
private:
    RCB RCB1;
    RCB RCB2;
    RCB RCB2;
    RCB RCB2;
};