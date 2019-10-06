//
// Created by hyjcrydby on 2019/10/5.
//leetcode:20 155 232 844
#include <stack>
#include <map>
#include <string>
#include <set>
#include <cctype>
#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

//有效的括号 20
bool isValid(string s) {
    if (s == "") return true;
    if (s.empty()) return false;
    if (s.size() == 1) return false;

    stack<char> st;

    map<char, char> map{{'(', ')'},
                        {'[', ']'},
                        {'{', '}'}};

    for (auto &c : s) {
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else if (!st.empty() && map[st.top()] == c) {
            st.pop();
        } else {
            return false;
        }

    }
    return st.empty();
}

// 155 最小栈，不可以只拿一个变量存储最小值，因为同一最小值的个数可为多个
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        m_stValue.push(x);
        if (m_stMin.empty() || m_stMin.top() >= x) {
            m_stMin.push(x);
        }
    }

    void pop() {
        int value = m_stValue.top();
        m_stValue.pop();
        if (value == m_stMin.top()) {
            m_stMin.pop();
        }
    }

    int top() {
        return m_stValue.top();
    }

    int getMin() {
        return m_stMin.top();
    }

private:
    stack<int> m_stValue;
    stack<int> m_stMin;
};

//232 用栈实现队列
class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {

    }

    /** Push element x to the back of queue. */
    void push(int x) {
        m_stIn.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        //if (m_stIn.empty() && m_stOut.empty()) return -1;


        if (m_stOut.empty()) {
            while (!m_stIn.empty()) {
                m_stOut.push(m_stIn.top());
                m_stIn.pop();
            }

        }

        int value = m_stOut.top();
        m_stOut.pop();
        return value;
    }

    /** Get the front element. */
    int peek() {
        if (m_stOut.empty()) {
            while (!m_stIn.empty()) {
                m_stOut.push(m_stIn.top());
                m_stIn.pop();
            }

        }

        return m_stOut.top();

    }

    /** Returns whether the queue is empty. */
    bool empty() {
        if (m_stIn.empty() && m_stOut.empty()) {
            return true;
        }
        return false;
    }

private:
    stack<int> m_stIn;
    stack<int> m_stOut;
};

//844 比较含退格的字符串
bool backspaceCompare(string S, string T) {

    stack<char> stS;
    stack<char> stT;

    for (const auto &v: S) {
        if (v == '#') {
            if (!stS.empty()) {
                stS.pop();
            }
        } else {
            stS.push(v);
        }

    }

    for (const auto &v: T) {
        if (v == '#') {
            if (!stT.empty()) {
                stT.pop();
            }
        } else {
            stT.push(v);
        }

    }

    return stT == stS;
}



//150 逆波兰表达式求值
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack <int> values;
        for(auto& str : tokens){
            if(str == "*" ||str == "/" ||str == "+" ||str == "-")
                resolve(values,str);
            else
                values.push(atoi(str.c_str())); //string to int
        }
        return values.top();
    }
    void resolve(stack <int>& num_stack,string operation)
    {
        int obj1,obj2;

        obj2 = num_stack.top();
        num_stack.pop();
        obj1 = num_stack.top();
        num_stack.pop();

        num_stack.push(calc(obj1,obj2,operation));
    }
    int calc(int obj1,int obj2,string operation)
    {
        switch(operation[0])
        {
            case '+':
                obj1 = obj1 + obj2;
                break;
            case '-':
                obj1 = obj1 - obj2;
                break;
            case '*':
                obj1 = obj1 * obj2;
                break;
            case '/':
                obj1 = obj1 / obj2;
                break;
        }
        return obj1;
    }
};

//中缀表达式转逆波兰表达式
class solution {
    std::vector<string> infixExpression2RBN(const vector<string> &tokens) {
        stack<string> stOp;
        set<string> setOperator = {"+", "-", "*", "/", "(", ")"};

        std::vector<string> result;
        for (const auto &c: tokens) {
            if (setOperator.find(c) != setOperator.end()) {
                //栈空 入栈 //左括号 入栈
                if (stOp.empty() || c == "(") {
                    stOp.push(c);
                    continue;
                }
                if (c == ")") {
                    while (!stOp.empty() && stOp.top() != "(") {
                        result.push_back(stOp.top());
                        stOp.pop();
                    }
                    stOp.pop(); //"("弹出去
                    continue;
                }
                //比较优先及,栈顶为左括号，直接入栈
                if (stOp.top() == "(") {
                    stOp.push(c);
                    continue;
                }
                //优先级高入栈,优先级低，栈顶元素出栈到表示，直到栈空或者该元素优先级较高
                //优先级低
                while (!stOp.empty() && !IsHighPriority(c, stOp.top())) {
                    result.push_back(stOp.top());
                    stOp.pop();
                }
                //优先级高
                stOp.push(c);

            } else {
                //操作数情况，直接输出表达式
                result.push_back(c);
            }

        }

        //清理栈内其他元素
        while (!stOp.empty()) {
            result.push_back(stOp.top());
            stOp.pop();
        }
        return result;
    }
    bool IsHighPriority(const string &a, const string &b) {
        std::map<string, int> priorityTable = {
                {"+", 1},
                {"-", 1},
                {"*", 2},
                {"/", 2},
        };
        if (priorityTable[a] == priorityTable[b]) {
            return false;
        }

        if (priorityTable[a] < priorityTable[b]) {
            return false;
        }

        if (priorityTable[a] > priorityTable[b]) {
            return true;
        }
        return true;
    }
};





