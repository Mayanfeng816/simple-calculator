#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
#pragma once
map<string, int> op_mapping;    // ��������ȼ�ӳ���
string ops = "+-*/()";      // ����������������ַ���,����find
string ch = "+-*/";
// ���Ϸ���
int check(string s) {
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[0] == '-') {      // �û����벻�Ϸ��ַ�
            cout << "ERROR >> ������ӦΪ����" << endl << endl;       // ���û��Ѻ���ʾ
            return 0;       // �����žͷ���0
        }
        if (isdigit(s[i])==0 && s[i]!='+' && s[i]!='-'&& s[i] != '*' && s[i] != '/'&& s[i]!=' ' && s[i] != '.'&& s[i] != '('&& s[i] != ')') {      // �û����벻�Ϸ��ַ�
            cout << "ERROR >> ����ı��ʽ���Ϸ������ٴ�����" << endl << endl;       // ���û��Ѻ���ʾ
            return 0;       // �����žͷ���0
        }
    }
    for (unsigned int i = 0; i < s.size()-1; i++) {
        if (ch.find(s[i])!=-1 && ch.find(s[i+1])!=-1) {      // �û�������ʽ���Ϸ�
            cout << "ERROR >> ����ı��ʽ���Ϸ������������" << endl << endl;       // ���û��Ѻ���ʾ
            return 0;       // �����žͷ���0
        }
    }
    return 1;       // ����û�����žͷ���1
}
// ɾ���ո�
void eatspace(string &s) {
    int count = 0;
    for (unsigned int i = 0; i < s.size(); i++) {        // ɾ������
        if (s[i] != ' ') {      // ������ǿո����������
            s[count] = s[i];        // ���ǵ��ո�
            count++;        // ͳ�Ʒǿո���ַ�����
        }
    }
    s = s.substr(0, count);
}
// ��stringת����double
double toDouble(string str)
{
    double target;
    stringstream sstream;   // ���������˸�������sstream�����԰�string����ת��Ϊdouble
    sstream << str;     // �ַ�������
    sstream >> target;      // �������
    return target;
}
// ��stringת����double
double toDouble2(string str)
{
    double target = 0;
    int i = 0;
    while (isdigit(str[i])) {//���������ֵ�ת��
        target = target * 10 + str[i] - 48; //���ַ�ת��Ϊ����
        i++;
    }
    if (str[i] == '.') {//��С�����ֵ�ת��
        i++;
        double target2 = 0;//��¼С������
        double j = 10.0;
        while (isdigit(str[i])) {
            target2 = target2 + (double(str[i]) - 48) / j;//���ַ�ת��ΪС��
            i++;
            j *= 10;//С�������Խ��ԽС����С10����
        }
        target += target2;//�������ּ���С������
    }
    return target;
}

// ��ʼ�����������ȼ�ӳ���
void init_mapping(map<string, int>& mapping)
{
    mapping["+"] = 0;       // +�����ȼ���Ϊ0
    mapping["-"] = 0;       // -�����ȼ���+һ����������������Ӧ��ֵ����0
    mapping["*"] = 1;       // *�����ȼ���Ϊ1
    mapping["/"] = 1;       // /�����ȼ���*һ����������������Ӧ��ֵ����1
    mapping["("] = 2;       // (�����ȼ���Ϊ2
    mapping[")"] = 2;       // )�����ȼ���(һ����������������Ӧ��ֵ����2
}
// ����׺���ʽת��Ϊ��׺���ʽ
vector<string> toPostfix(string formula)
{
    vector<string> result;      // �ַ������ջ�����ڴ������ĺ�׺���ʽ
    vector<string> op_stack;        // ������ջ���洢�ͱȽϲ��������ȼ�
    string cur_num, cur_op;     // �������������ڴ洢��ǰ����������ַ��������

    int flag = 0;
    if (formula[formula.size() - 1] == ')')     //�ж�����Ƿ��� ) Ϊ��β
        flag = 1;

    for (unsigned int i = 0; i < formula.size(); ++i)
    {
        if (ops.find(formula[i]) == ops.npos)   // ɨ�赽���ǲ�����,��û���ҵ�'+-'
            cur_num += formula[i];      // ���������ַ�����cur_num

        else    // ɨ�赽���ǲ��������ֽ��ۼӵĲ������ַ�������
        {
            if (!cur_num.empty())// ������������֮ǰ�ۼƵ������ַ�������
            {
                result.push_back(cur_num);  // �����ֶ�Ӧ���ַ�����ջ
                cur_num.clear();    // ���������������ַ���
            }

            cur_op = formula[i];    // �洢��ǰ������

            // ����������ջ���������
            if (op_stack.empty())           // ջΪ�գ�ֱ����ջ
                op_stack.push_back(cur_op);
            else if (cur_op == "(")         // ��ǰ������Ϊ�����ţ�ֱ����ջ
                op_stack.push_back(cur_op);
            else if (cur_op == ")")         // ��ǰ������Ϊ�����ţ�����Ҫ��op_stack��ֱ��������ǰ�����е�Ԫ�ص���
            {
                while (op_stack.back() != "(")
                {
                    result.push_back(op_stack.back());//��ɺ�׺���ʽ��
                    op_stack.pop_back();
                }
                op_stack.pop_back();        // �� ( ����
            }
            else if (op_stack.back() == "(")          // �ڵ�ǰ�������������ŵ�����£����ջ��Ԫ��Ϊ�����ţ���ֱ����ջ
                op_stack.push_back(cur_op);
            else if (op_mapping[cur_op] > op_mapping[op_stack.back()])        // �ڵ�ǰ��������ջ��Ԫ��Ϊ+-*/������£�����ǰ���������ȼ�����ջ��Ԫ�أ�ֱ����ջ
                op_stack.push_back(cur_op);
            else        // ��һ��������ǵ�ǰ�����������ȼ����ڻ����ջ��Ԫ��
            {
                while (op_stack.back() != "(" && op_mapping[op_stack.back()] >= op_mapping[cur_op] )
                {
                    result.push_back(op_stack.back());//ת��׺���ʽ
                    op_stack.pop_back();    // ����ջ��Ԫ��

                    // ��ջ�ѿգ���ֱ�ӷ���
                    if (op_stack.empty())
                        break;
                }
                op_stack.push_back(cur_op);     // �ڷ���Ҫ��Ĳ����������󣬵�ǰ��������ջ
            }
        }
    }

    if(flag==0)
        result.push_back(cur_num);      // �����ʽ��βʱ���֣����һ��������ɵ��ַ�����ջ

    // ���op_stack���ܻ�����ʣ��Ԫ�أ�ȫ������
    while (!op_stack.empty())
    {
        result.push_back(op_stack.back());
        op_stack.pop_back();
    }

    return result;      // ���غ�׺���ʽ
}
//�����׺���ʽ
double calculatePostfix(vector<string>& postfix)
{
    vector<double> result;
    for (unsigned int i = 0; i < postfix.size(); ++i)
    {
        if (ops.find(postfix[i]) == ops.npos)        // ɨ�赽��������ֱ��ѹ��ջ��
            result.push_back(toDouble2(postfix[i]));     // ѹջǰ���ú���ת��Ϊdouble
        else       // ɨ�赽������
        {
            double num1 = result.back();
            result.pop_back();
            double num2 = result.back();
            result.pop_back();
            double op_res;

            // �������ۣ�����num2 op num1
            if (postfix[i] == "+")
                op_res = num2 + num1;
            else if (postfix[i] == "-")
                op_res = num2 - num1;
            else if (postfix[i] == "*")
                op_res = num2 * num1;
            else if (postfix[i] == "/")
            {
                // �жϳ����Ƿ�Ϊ0
                if (num1 == 0)
                {
                    cout << "ERROR: /0" << endl;
                    return 0.0;
                }

                op_res = num2 / num1;
            }
            
            result.push_back(op_res);   // �����Ľ������ѹ��ջ��
        }
    }
    if (result.size() == 1)     // ����ջ��Ԫ�أ������������ֻʣ��һ��Ԫ��
        return result.back();   // ���յļ�����
}
// ���ϵĺ���
double cal(string& infix)   
{
    vector<string> postfix = toPostfix(infix);  // �Ȱ�ǰ׺���ʽ���׺���ʽ
    return calculatePostfix(postfix);       // �����׺���ʽ�����ؽ��
}


