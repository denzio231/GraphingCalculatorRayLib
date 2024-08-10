#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <functional>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include<map>
#include<cmath>
std::vector<std::string> op_priority = { "+-", "*/", "^" };
std::map<char, std::function<double(double, double)>> op_func = {
{'+', [](double x, double y) { return x + y; }},
{'-', [](double x, double y) { return x - y; }},
{'*', [](double x, double y) { return x * y; }},
{'/', [](double x, double y) { return x / y; }},
{'^', [](double x, double y) { return pow(x, y); }}
};
std::string removeBrackets(std::string evalStr) {
    int c = 0;
    bool flag = false;
    int startidx = 0;
    int endidx = 0;
    int idx = -1;
    bool hasBrackets = false;

    for (char i : evalStr) {
        idx++;
        if (i == ' ') {
            continue;
        } else if (flag) {
            return "";
        } else if (i == '(') {
            if (c == 0) {
                hasBrackets = true;
                startidx = idx;
            }
            c++;
        } else if (i == ')') {
            c--;
        }
        if (c == 0) {
            endidx = idx;
            flag = true;
        }
    }
    if (!hasBrackets) {
        return "";
    }
    std::string buff = evalStr.substr(0, startidx) + evalStr.substr(startidx + 1, evalStr.size() - 1);
    std::string ret = buff.substr(0, endidx - 1) + buff.substr(endidx, buff.size() - 1);
    return ret;
}

std::tuple<std::vector<std::string>, std::vector<char>, bool> splitBy(const std::string& operators, std::string evalStr,int p) {
    std::vector<std::string> splitList;
    std::vector<char> ops;
    std::string buff = "";
    bool flag = false;
    bool noSplitFlag = true;
    bool openBracket = false;

    while (true) {
        std::string buf = removeBrackets(evalStr);
        if (buf.empty()) {
            break;
        } else {
            evalStr = buf;
        }
    }

    for (size_t idx = 0; idx < evalStr.size(); idx++) {
        if (evalStr[idx] == '(') {
            flag=false;
            openBracket = true;
            buff += evalStr[idx];
            continue;
        } else if (evalStr[idx] == ')') {
            buff += evalStr[idx];
            openBracket = false;
            continue;
        }
        if (evalStr[idx] == ' ') {
            continue;
        } else if (!flag) {
            flag = true;
            buff += evalStr[idx];
            continue;
        }
        if (openBracket) {
            buff += evalStr[idx];
            continue;
        }
        if (operators.find(evalStr[idx]) != std::string::npos) {
            splitList.push_back(buff);
            noSplitFlag = false;
            ops.push_back(evalStr[idx]);
            buff = "";
        } else {
            buff += evalStr[idx];
        }
    }
    splitList.push_back(buff);
    return {splitList, ops, noSplitFlag};
}
double eval(std::string evalStr,double x) {

    for (size_t p = 0; p < op_priority.size(); p++) {
        auto [splitList, ops, noSplitFlag] = splitBy(op_priority[p], evalStr,p);
        if (noSplitFlag) {
            continue;
        } else {
            double val = eval(splitList[0],x);
            for (size_t idx = 0; idx < ops.size(); idx++) {
                char op = ops[idx];
                double curr = eval(splitList[idx + 1],x);
                auto func = op_func[op];
                val = func(val, curr);
            }
            return val;
        }
    }
    if(evalStr=="x"){
        return x;
    }
    try {
        return std::stod(evalStr);
    } catch (const std::exception& e) {
        return std::numeric_limits<double>::quiet_NaN();
    }
}
