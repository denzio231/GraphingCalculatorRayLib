#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
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

std::tuple<std::vector<std::string>, std::vector<char>, bool> splitBy(const std::string& operators, std::string evalStr) {
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
            flag = true;        
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
    auto [splitList, ops, noSplitFlag] = splitBy("+-", evalStr);
    if (noSplitFlag) {
        auto [splitList2, ops2, noMultFlag] = splitBy("*/", evalStr);

        if (noMultFlag) {
            if(evalStr=="x"){
                return x;
            }
            try {
                return std::stod(evalStr);
            } catch (const std::exception& e) {
                return std::numeric_limits<double>::quiet_NaN();
            }
        } else {
            double val = eval(splitList2[0],x);
            for (size_t idx = 0; idx < ops2.size(); idx++) {
                char op = ops2[idx];
                double curr = eval(splitList2[idx + 1],x);
                if (op == '*') {
                    val *= curr;
                } else if (op == '/') {
                    val /= curr;
                }
            }
            return val;
        }
    } else {
        double sum = eval(splitList[0],x);
        for (size_t idx = 0; idx < ops.size(); idx++) {
            char op = ops[idx];
            double val = eval(splitList[idx + 1],x);
            if (op == '+') {
                sum += val;
            } else if (op == '-') {
                sum -= val;
            }
        }
        return sum;
    }
}
