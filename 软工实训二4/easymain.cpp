#include"easycal.h"
int main()
{
    init_mapping(op_mapping);       // ��ʼ��ӳ���
    string infix;

	cout << "Welcome to your friendly calculator," << endl;
	cout << "Enter an expression, or an empty line to quit." << endl;

	while (true) {	// ����ѭ��

		getline(cin, infix);

		eatspace(infix);	// ����ȥ�ո���

		if (infix.empty())	// ֱ��������ַ����ǿգ��˳�ѭ��
		{
			cout << "NOTICE >> calculator exited." << endl;
			return 0;
		}
			
		if (check(infix))	// ����check��麯�����ںϷ��������������������������ʾ
			cout << "       =" << cal(infix) << endl << endl;	// ������
	}

	return 0;
}
