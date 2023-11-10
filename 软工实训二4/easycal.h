#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
#pragma once
map<string, int> op_mapping;    // 运算符优先级映射表
string ops = "+-*/()";      // 包含所有运算符的字符串,方便find
string ch = "+-*/";
// 检测合法性
int check(string s) {
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[0] == '-') {      // 用户输入不合法字符
            cout << "ERROR >> 操作数应为正数" << endl << endl;       // 给用户友好提示
            return 0;       // 有括号就返回0
        }
        if (isdigit(s[i])==0 && s[i]!='+' && s[i]!='-'&& s[i] != '*' && s[i] != '/'&& s[i]!=' ' && s[i] != '.'&& s[i] != '('&& s[i] != ')') {      // 用户输入不合法字符
            cout << "ERROR >> 输入的表达式不合法，请再次输入" << endl << endl;       // 给用户友好提示
            return 0;       // 有括号就返回0
        }
    }
    for (unsigned int i = 0; i < s.size()-1; i++) {
        if (ch.find(s[i])!=-1 && ch.find(s[i+1])!=-1) {      // 用户输入表达式不合法
            cout << "ERROR >> 输入的表达式不合法，请检查操作符" << endl << endl;       // 给用户友好提示
            return 0;       // 有括号就返回0
        }
    }
    return 1;       // 整体没有括号就返回1
}
// 删除空格
void eatspace(string &s) {
    int count = 0;
    for (unsigned int i = 0; i < s.size(); i++) {        // 删除操作
        if (s[i] != ' ') {      // 如果不是空格，则可以留下
            s[count] = s[i];        // 覆盖掉空格
            count++;        // 统计非空格的字符个数
        }
    }
    s = s.substr(0, count);
}
// 将string转换成double
double toDouble(string str)
{
    double target;
    stringstream sstream;   // 这里利用了辅助变量sstream，可以把string类型转化为double
    sstream << str;     // 字符串存入
    sstream >> target;      // 变成数字
    return target;
}
// 将string转换成double
double toDouble2(string str)
{
    double target = 0;
    int i = 0;
    while (isdigit(str[i])) {//对整数部分的转换
        target = target * 10 + str[i] - 48; //将字符转化为数字
        i++;
    }
    if (str[i] == '.') {//对小数部分的转换
        i++;
        double target2 = 0;//记录小数部分
        double j = 10.0;
        while (isdigit(str[i])) {
            target2 = target2 + (double(str[i]) - 48) / j;//将字符转化为小数
            i++;
            j *= 10;//小数点后面越来越小（逐渐小10倍）
        }
        target += target2;//整数部分加上小数部分
    }
    return target;
}

// 初始化操作符优先级映射表
void init_mapping(map<string, int>& mapping)
{
    mapping["+"] = 0;       // +的优先级设为0
    mapping["-"] = 0;       // -的优先级和+一样，两个操作符对应的值都是0
    mapping["*"] = 1;       // *的优先级设为1
    mapping["/"] = 1;       // /的优先级和*一样，两个操作符对应的值都是1
    mapping["("] = 2;       // (的优先级设为2
    mapping[")"] = 2;       // )的优先级和(一样，两个操作符对应的值都是2
}
// 将中缀表达式转化为后缀表达式
vector<string> toPostfix(string formula)
{
    vector<string> result;      // 字符串结果栈，用于存入最后的后缀表达式
    vector<string> op_stack;        // 操作符栈，存储和比较操作符优先级
    string cur_num, cur_op;     // 辅助变量，用于存储当前读入的数字字符与操作符

    int flag = 0;
    if (formula[formula.size() - 1] == ')')     //判断最后是否以 ) 为结尾
        flag = 1;

    for (unsigned int i = 0; i < formula.size(); ++i)
    {
        if (ops.find(formula[i]) == ops.npos)   // 扫描到的是操作数,即没有找到'+-'
            cur_num += formula[i];      // 将该数字字符存入cur_num

        else    // 扫描到的是操作符，现将累加的操作数字符串加入
        {
            if (!cur_num.empty())// 将遇到操作符之前累计的数字字符串存入
            {
                result.push_back(cur_num);  // 将数字对应的字符串入栈
                cur_num.clear();    // 清空这个辅助变量字符串
            }

            cur_op = formula[i];    // 存储当前操作符

            // 操作符的入栈分两种情况
            if (op_stack.empty())           // 栈为空，直接入栈
                op_stack.push_back(cur_op);
            else if (cur_op == "(")         // 当前操作数为左括号，直接入栈
                op_stack.push_back(cur_op);
            else if (cur_op == ")")         // 当前操作数为右括号，则需要将op_stack中直到左括号前的所有的元素弹出
            {
                while (op_stack.back() != "(")
                {
                    result.push_back(op_stack.back());//变成后缀表达式了
                    op_stack.pop_back();
                }
                op_stack.pop_back();        // 将 ( 弹出
            }
            else if (op_stack.back() == "(")          // 在当前操作符不是括号的情况下，如果栈顶元素为左括号，则直接入栈
                op_stack.push_back(cur_op);
            else if (op_mapping[cur_op] > op_mapping[op_stack.back()])        // 在当前操作符和栈顶元素为+-*/的情况下，若当前操作符优先级大于栈顶元素，直接入栈
                op_stack.push_back(cur_op);
            else        // 另一种情况就是当前操作符的优先级低于或等于栈顶元素
            {
                while (op_stack.back() != "(" && op_mapping[op_stack.back()] >= op_mapping[cur_op] )
                {
                    result.push_back(op_stack.back());//转后缀表达式
                    op_stack.pop_back();    // 弹出栈顶元素

                    // 若栈已空，则直接返回
                    if (op_stack.empty())
                        break;
                }
                op_stack.push_back(cur_op);     // 在符合要求的操作符弹出后，当前操作符入栈
            }
        }
    }

    if(flag==0)
        result.push_back(cur_num);      // 若表达式结尾时数字，最后一个数字组成的字符串入栈

    // 最后op_stack可能还会有剩余元素，全部弹出
    while (!op_stack.empty())
    {
        result.push_back(op_stack.back());
        op_stack.pop_back();
    }

    return result;      // 返回后缀表达式
}
//运算后缀表达式
double calculatePostfix(vector<string>& postfix)
{
    vector<double> result;
    for (unsigned int i = 0; i < postfix.size(); ++i)
    {
        if (ops.find(postfix[i]) == ops.npos)        // 扫描到操作数，直接压入栈中
            result.push_back(toDouble2(postfix[i]));     // 压栈前调用函数转换为double
        else       // 扫描到操作符
        {
            double num1 = result.back();
            result.pop_back();
            double num2 = result.back();
            result.pop_back();
            double op_res;

            // 分类讨论，计算num2 op num1
            if (postfix[i] == "+")
                op_res = num2 + num1;
            else if (postfix[i] == "-")
                op_res = num2 - num1;
            else if (postfix[i] == "*")
                op_res = num2 * num1;
            else if (postfix[i] == "/")
            {
                // 判断除数是否为0
                if (num1 == 0)
                {
                    cout << "ERROR: /0" << endl;
                    return 0.0;
                }

                op_res = num2 / num1;
            }
            
            result.push_back(op_res);   // 将所的结果重新压入栈中
        }
    }
    if (result.size() == 1)     // 返回栈顶元素，在正常情况下只剩下一个元素
        return result.back();   // 最终的计算结果
}
// 整合的函数
double cal(string& infix)   
{
    vector<string> postfix = toPostfix(infix);  // 先把前缀表达式变后缀表达式
    return calculatePostfix(postfix);       // 计算后缀表达式并返回结果
}


