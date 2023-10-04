#include "expl.h"
#include<iostream>
#include<fstream>
using namespace std;
ExpL::ExpL()
{
    this->str="";
    this->token="";
    this->pos=0;
    this->endStr="";
    ReadKeyWords();
}

void ExpL::ReadKeyWords(){
    string filePath = ":/data/keyWords.txt";
    fstream inputFile;
    inputFile.open(filePath, ios::in);
    if (!inputFile) {
        cout << "该文件不存在" << endl;
        return;
    }
    string line = "";
    int i = 0;
    while (getline(inputFile, line)) {
        keyWords[i] = line;
        i++;
    }

}

string ExpL::ChangSyn() {
    switch (syn){
    case IDENTIFIER:
        return "标识符";
    case KEYWORD:
        return "关键词";
    case NUMBER:
        return "数";
    case STRING:
        return "字符串";
    case CHAR:
        return "字符";
    case ANNOTATION:
        return "注释";
    case SPECIALSYMBOL:
        return "特殊符号";
    case OPERATORSYMBOL:
        return "运算符";
    default:
        return "";
    }
}

bool ExpL::IsLetter(char ch)   //判断是否为字母
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        return true;
    }
    else {
        return false;
    }
}

bool ExpL::IsDigit(char ch) { //判断是否为数字
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    else {
        return false;
    }
}

bool ExpL::IsOperator() { //判断是否为运算符
    token = "";//清空当前字符串
    switch (str[pos]) {
    case'+':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '+' || str[pos] == '=') {
            token += str[pos];
            pos++;
        }
        return true;
    case'-':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '-' || str[pos] == '=') {
            token += str[pos];
            pos++;
        }
    case'*':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '=') {
            token += str[pos];
            pos++;
        }
        return true;
    case'/':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '=') {
            token += str[pos];
            pos++;
        }
        return true;
    case'%':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '=') {
            token += str[pos];
            pos++;
        }
        return true;
    case'=':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '=') {
            token += str[pos];
            pos++;
        }
        return true;
    case'!':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '=') {
            token += str[pos];
            pos++;
        }
        return true;
    case'>':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '=') {
            token += str[pos];
            pos++;
            return true;
        }
        if (str[pos] == '<') {
            token += str[pos];
            pos++;
        }
        if (str[pos] == '=') {
            token += str[pos];
            pos++;
        }
        return true;
    case'<':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '=') {
            token += str[pos];
            pos++;
            return true;
        }
        if (str[pos] == '<') {
            token += str[pos];
            pos++;
        }
        if (str[pos] == '=') {
            token += str[pos];
            pos++;
        }
        return true;
    case'&':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '&'||str[pos]=='=') {
            token += str[pos];
            pos++;
        }
        return true;
    case'|':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '|') {
            token += str[pos];
            pos++;
        }
        return true;
    case'^':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        if (str[pos] == '=') {
            token += str[pos];
            pos++;
        }
        return true;
    case'~':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos++;
        return true;
    case':':
        syn = OPERATORSYMBOL;
        token = str[pos];
        pos += 2;
        token += ':';
        return true;
    default:
        return false;
    }
}

void ExpL::Scan() {   //进行扫描
    if (str[pos] == '\0') { //到了字符串尾
        syn = ENDING;
        return;
    }
    if (str[pos] == ' '||str[pos]=='\n'||str[pos]=='\t') {  //遇到空格或者换行符号或者是缩进符号
        syn = BLANKSPACE;    //空格为1
        pos++;
        return;
    }
    if ((str[pos] == '+' || str[pos] == '-')&&IsDigit(str[pos+1])) {//带正负号的数字
        syn = NUMBER;
        token=str[pos];
        pos++;
        if (str[pos] == '0') {  //如果是16进制的话,x可以读进来
            token += str[pos];
            pos++;
            if (str[pos] == 'x' || str[pos] == 'X') {
                token += str[pos];
                pos++;
            }
        }
        else {
            token += str[pos];
            pos++;
        }
        while (IsDigit(str[pos])) { //读取小数点前面的
            token += str[pos];
            pos++;
        }
        if (str[pos] == '.') {
            token += str[pos];
            pos++;
        }
        while (IsDigit(str[pos])) { //小数点后面的
            token += str[pos];
            pos++;
        }
        if (str[pos] == 'e' ) { //指数部分
            token += str[pos];
            pos++;
            if (str[pos] == '-') {  //带负号
                token += str[pos];
                pos++;
            }
            while (IsDigit(str[pos])) { //小数点后面的
                token += str[pos];
                pos++;
            }
        }
    }
    else if (IsDigit(str[pos])) {    //判断是否为数字
        syn = NUMBER;
        token = "";
        if (str[pos] == '0') {  //如果是16进制的话,x可以读进来
            token += str[pos];
            pos++;
            if (str[pos] == 'x' || str[pos] == 'X') {
                token += str[pos];
                pos++;
            }
        }
        else {
            token += str[pos];
            pos++;
        }
        while (IsDigit(str[pos])) { //读取小数点前面的
            token += str[pos];
            pos++;
        }
        if (str[pos] == '.') {
            token += str[pos];
            pos++;
        }
        while (IsDigit(str[pos])) { //小数点后面的
            token += str[pos];
            pos++;
        }
        if (str[pos] == 'e') { //指数部分
            token += str[pos];
            pos++;
            if (str[pos] == '-') {  //带负号
                token += str[pos];
                pos++;
            }
            while (IsDigit(str[pos])) { //小数点后面的
                token += str[pos];
                pos++;
            }
        }
    }
    else if (IsLetter(str[pos])|| str[pos] == '_') {  //字母或者下划线开头
        token = ""; //清空当前的token
        while (IsDigit(str[pos]) || IsLetter(str[pos])||str[pos]=='_') {   //为数字或者字母
            token += str[pos];
            pos++;
        }

        syn = IDENTIFIER;//标识符

        //判断是否为关键字
        for (int i = 0; i < keyWordsNum; i++) {
            if (token == keyWords[i]) {
                syn = KEYWORD;
            }

        }
    }
    else if (str[pos] == '/'&&(str[pos+1]=='/'|| str[pos + 1] == '*')) {    //注释
        token = str[pos];
        pos++;
        syn = ANNOTATION;
        if (str[pos] == '/') {
            while (str[pos] != '\n') {
                token += str[pos];
                pos++;
            }
        }
        else if(str[pos] == '*') {
            token += str[pos];
            pos++;
            while (str[pos] != '*'||str[pos+1]!='/') {
                token += str[pos];
                pos++;
            }
            token += "*/";
            pos += 2;
        }
    }
    else if (str[pos] == '\'') { //字符
        token = str[pos];
        pos++;
        syn = CHAR;
        token += str[pos];
        pos += 2;
        token += '\'';
    }
    else if (str[pos] == '"') { //字符串
        syn = STRING;
        token = str[pos];
        pos++;
        while (str[pos] != '"') {
            token += str[pos];
            pos++;
        }
        token += '"';
        pos++;
    }
    else if (str[pos] == '<' && isalpha(str[pos + 1])&&token=="include") {    //头文件作为特殊符号
        syn = SPECIALSYMBOL;
        token = str[pos];
        pos++;
        while (str[pos] != '>') {
            token += str[pos];
            pos++;
        }
        token += '>';
        pos++;
    }
    else if (IsOperator()) {    //运算符

    }
    else { //特殊符号
        syn = SPECIALSYMBOL;
        token = str[pos];
        pos++;
    }
}

void ExpL::AssignStr(string sourceCode){    //给源文件字符串赋值
    this->str=sourceCode;
}

void ExpL::beginExpL(){ //进行词法分析
    this->token="";
    this->pos=0;
    this->endStr="";
    do {
        Scan();
        switch (syn) {  //再次判断syn
        case BLANKSPACE:    //遇到空格
            break;
        default:
            if (syn != ENDING) {
                this->endStr.append(token);
                this->endStr.append("\t");
                this->endStr.append(ChangSyn());
                this->endStr.append("\n");
            }
        }
    } while (syn != 0);
}

string ExpL::ExpLResult(){  //返回词法分析的结果
    return this->endStr;
}
