#pragma once
#include "ProcessResourceManage.hpp"

using namespace std;

void testShell()
{
	string command, line, name;    //command用于读取命令，line用于从文件中按行读取,name用于申请资源时保存资源名
	int priority, unit;    //priority是创建进程时进程的优先级，unit是要申请或释放的资源数量
	ProcessResourceManage prm;    //实例化资源控制器
	//不断从文件中按行读取，直到读到文件末尾
	while (getline(infile, line)) {
		istringstream linestream(line);    //将读取到的一行转换为字符串流

		//读取到的行不为空且长度大于二
		if (!line.empty() && line.length() >= 2) {

			linestream >> command;    //从读入的一行中得到命令

			//初始化命令
			if (command == "init") {
				prm.init();
				cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
				outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
			}
			//创建进程命令
			else if (command == "cr") {
				linestream >> name >> priority;
				if (prm.search(name) != -1) {
					cout << "error (duplicate name)." << endl;
					outfile << "error (duplicate name)." << endl;
				}
				else if (priority > 2 || priority <= 0) {
					cout << "error" << endl;
				}
				else {
					prm.create(name, priority);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
				}
			}
			//撤销进程命令
			else if (command == "de") {
				linestream >> name;
				int t = prm.search(name);
				if (t == -1) {
					cout << "error (process not existed)." << endl;
					outfile << "error (process not existed)." << endl;
				}
				else {
					prm.destroy(t);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
				}
			}
			//请求资源命令
			else if (command == "req") {
				linestream >> name >> unit;
				if (name == "R1" && unit == 1) {
					prm.request(0, unit);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
				}
				else if (name == "R2" && (0 < unit && unit <= 2)) {
					prm.request(1, unit);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
				}
				else if (name == "R3" && (0 < unit && unit <= 3)) {
					prm.request(2, unit);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
				}
				else if (name == "R4" && (0 < unit && unit <= 4)) {
					prm.request(3, unit);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
				}
				else {
					cout << "error (invalid request)." << endl;
					outfile << "error (invalid request)." << endl;
				}
			}
			//释放资源命令
			else if (command == "rel") {
				linestream >> name >> unit;
				if (name == "R1" && unit == 1) {
					if (prm.pcb[prm.currentRunning].resource[0].used >= unit) {
						prm.release(0, unit);
						cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
						outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
					}
					else {
						cout << "error (release exceed actual R1 units)." << endl;
						outfile << "error (release exceed actual R1 units)." << endl;
					}
				}
				else if (name == "R2" && (0 < unit && unit <= 2)) {
					if (prm.pcb[prm.currentRunning].resource[1].used >= unit) {
						prm.release(1, unit);
						cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
						outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
					}
					else {
						cout << "error (release exceed actual R2 units)" << endl;
						outfile << "error (release exceed actual R2 units)" << endl;
					}
				}
				else if (name == "R3" && (0 < unit && unit <= 3)) {
					if (prm.pcb[prm.currentRunning].resource[2].used >= unit) {
						prm.release(2, unit);
						cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
						outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
					}
					else {
						cout << "error (release exceed actual R3 units)." << endl;
						outfile << "error (release exceed actual R3 units)." << endl;
					}
				}
				else if (name == "R4" && (0 < unit && unit <= 4)) {
					if (prm.pcb[prm.currentRunning].resource[3].used >= unit) {
						prm.release(3, unit);
						cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
						outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
					}
					else {
						cout << "error (release exceed actual R4 units)." << endl;
						outfile << "error (release exceed actual R4 units)." << endl;
					}
				}
				else {
					cout << "error (invalid release)." << endl;
					outfile << "error (invalid release)." << endl;
				}

			}
			//定时中断命令
			else if (command == "to") {
				prm.timeout();
				cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
				outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running." << endl;
			}
			//列出所有进程命令
			else if (command == "lp"){
			    prm.processList();
            }
			//列出所有资源命令
			else if (command == "lr"){
			    prm.resourceList();
            }
			//列出指定进程信息命令
			else if (command == "pi"){
			    linestream >> name;
				prm.processInfo(name);
            }
			//出现了无效的命令
			else {
				cout << "error command." << endl;
				outfile << "error command." << endl;
			}
		}
		//读取到了无效行
		else {
			cout << endl;
			outfile << endl;
		}
	}

	cout << "end" << endl;    //处理完成，输出end

}