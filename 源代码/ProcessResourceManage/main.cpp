
#include"DataStructure.hpp"
#include "ProcessResourceManage.hpp"
#include "TestShell.hpp"
#include <cstdlib>
using namespace std;

//输入输出的文件
ifstream infile;
ofstream outfile;

int main(int argc, char *argv[]) {
	//有一个命令行参数，-h
	if (argc == 2)
	{
		if (strcmp(argv[1], "-h") == 0)
		{

			exit(0);
		}
		else
		{
			cout << "不支持的参数选项：." << argv[1] << ",请重新输入！." << endl;

			exit(0);
		}
	}
	//有两个命令行参数，分别是输入输出文件
	else if (argc == 3)
	{
		infile.open(argv[1]);
		outfile.open(argv[2], ios::out);
		//判断文件是否打开成功，如果没有打开说明输入的文件名有误
		if (!infile.is_open())
		{
			cout << "输入文件." << argv[1] << "不存在，请检查文件名是否正确！." << endl;
		}
	}
	//如果没有命令行参数，默认输入输出文件
	else if (argc == 1)
	{
		infile.open("input.txt");
		outfile.open("output.txt", ios::out);
	}
	//其他情况出错
	else
	{

		exit(0);
	}

	testShell();    //调用testShell函数执行文件中的命令

	//关闭打开的文件，退出程序
	infile.close();
	outfile.close();
	system("pause");
	return 0;
}