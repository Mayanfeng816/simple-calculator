#include"cal.h"
int main()
{
    double result;
    init_mapping(op_mapping);       // ��ʼ��ӳ���
    string infix;
    cin >> infix;
    cout << eval(infix);
    return 0;
}
