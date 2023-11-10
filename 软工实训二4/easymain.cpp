#include"easycal.h"
int main()
{
    init_mapping(op_mapping);       // 初始化映射表
    string infix;

	cout << "Welcome to your friendly calculator," << endl;
	cout << "Enter an expression, or an empty line to quit." << endl;

	while (true) {	// 无限循环

		getline(cin, infix);

		eatspace(infix);	// 调用去空格函数

		if (infix.empty())	// 直到输入的字符串是空，退出循环
		{
			cout << "NOTICE >> calculator exited." << endl;
			return 0;
		}
			
		if (check(infix))	// 调用check检查函数，在合法情况下输出计算结果，否则给出提示
			cout << "       =" << cal(infix) << endl << endl;	// 输出结果
	}

	return 0;
}
