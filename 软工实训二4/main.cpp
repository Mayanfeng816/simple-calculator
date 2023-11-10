#include"cal.h"
int main()
{
    double result;
    init_mapping(op_mapping);       // ³õÊ¼»¯Ó³Éä±í
    string infix;
    cin >> infix;
    cout << eval(infix);
    return 0;
}
