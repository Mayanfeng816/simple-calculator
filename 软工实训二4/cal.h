#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
#pragma once
map<string, int> op_mapping;    // 运算符优先级映射表
string ops = "+-*/()";                  // 包含所有运算符的字符串，为了通过find方法快速判断目标字符是否为操作符
bool ValueError = false;               // 是否发生数值错误的标记
bool ExpressionError = false;      // 是否发生表达式错误的标记

// 将string转换成double
double toDouble(string str)
{
    double target;
    stringstream sstream;
    sstream << str;
    sstream >> target;
    return target;
}

// 初始化操作符优先级映射表
void init_mapping(map<string, int>& mapping)
{
    mapping["+"] = 0;
    mapping["-"] = 0;
    mapping["*"] = 1;
    mapping["/"] = 1;
    mapping["("] = 2;
    mapping[")"] = 2;
}
// 将中缀表达式转化为后缀表达式
vector<string> toPostfix(string formula)
{
    vector<string> result;
    vector<string> op_stack;
    string cur_num, cur_op;

    for (int i = 0; i < formula.size(); ++i)
    {
        if (ops.find(formula[i]) == ops.npos)   // 扫描到的是操作数,即没有找到'+-*/()'
            cur_num += formula[i];

        else        // 扫描到的是操作符，现将累加的操作数字符串加入
        {
            if (!cur_num.empty())
            {
                result.push_back(cur_num);  //将数字对应的字符串入栈
                cur_num.clear();    //清空这个辅助变量字符串
            }

            cur_op = formula[i];

            if (op_stack.empty())           // 栈为空，直接入栈
                op_stack.push_back(cur_op);
            else if (cur_op == "(")         // 当前操作符为左括号，直接入栈
                op_stack.push_back(cur_op);
            else if (cur_op == ")")         // 当前操作符为右括号，则需要将op_stack中直到左括号前的所有的元素弹出
            {
                while (op_stack.back() != "(")
                {
                    result.push_back(op_stack.back());//变成后缀表达式了
                    op_stack.pop_back();

                    if (op_stack.empty())           // 不合法的表达式会出现这样的情况
                    {
                        ExpressionError = true;
                        result.push_back("0");
                        return result;
                    }
                }
                op_stack.pop_back();        // 将 ( 弹出
            }
            else if (op_stack.back() == "(")          // 在当前操作符不是括号的情况下，如果栈顶元素为左括号，则直接入栈
                op_stack.push_back(cur_op);
            else if (op_mapping[cur_op] > op_mapping[op_stack.back()])        // 在当前操作符和栈顶元素为+-*/的情况下，若当前操作符优先级大于栈顶元素，直接入栈
                op_stack.push_back(cur_op);
            else            // 最后一种情况就是当前操作符的优先级低于或等于栈顶元素优先级时
            {
                while ((op_stack.back() != "(") && (op_mapping[op_stack.back()] >= op_mapping[cur_op]))
                {
                    result.push_back(op_stack.back());//转后缀表达式
                    op_stack.pop_back();

                    // 若栈已空，则直接返回
                    if (op_stack.empty())
                        break;
                }
                op_stack.push_back(cur_op);     // 符合要求的操作符弹出后，当前操作符入栈
            }
        }
    }

    result.push_back(cur_num);//最后一个数字组成的字符串入栈

    // 最后op_stack可能还会有剩余元素，全部弹出
    while (!op_stack.empty())
    {
        result.push_back(op_stack.back());
        op_stack.pop_back();
    }

    return result;
}

double calculatePostfix(vector<string>& postfix)
{
    vector<double> result;
    for (int i = 0; i < postfix.size(); ++i)
    {
        if (ops.find(postfix[i]) == ops.npos)        // 扫描到操作数，直接压入栈中
            result.push_back(toDouble(postfix[i]));
        else               // 扫描到操作符
        {
            // 如果剩余元素的数量小于2，则表达式非法
            if (result.size() < 2)
            {
                ExpressionError = true;
                return 0.0;
            }
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
                // 此处需要判断一下是否分母为0
                if (num1 == 0)
                {
                    ValueError = true;
                    return 0.0;
                }

                op_res = num2 / num1;
            }
            // 将所的结果重新压入栈中
            result.push_back(op_res);
        }
    }
    if (result.size() == 1)     // 返回栈顶元素（如果是合法的表达式，则此时栈中只有一个元素）
        return result.back();
    else            // 不合法的表达式会导致结束时，result中有不止一个元素
    {
        ExpressionError = true;
        return 0.0;
    }
}
double eval(string& infix)
{
    vector<string> postfix = toPostfix(infix);
    return calculatePostfix(postfix);
}

