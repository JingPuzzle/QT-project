#ifndef EXPL_H
#define EXPL_H
#include<string>

using namespace std;

enum TokenID { ENDING,BLANKSPACE, IDENTIFIER, KEYWORD, NUMBER, STRING, CHAR, ANNOTATION, SPECIALSYMBOL, OPERATORSYMBOL};  //单词的种类

class ExpL
{
public:
    ExpL();
    void ReadKeyWords();    //读取关键字
    string ChangSyn();      //将syn转为中文
    bool IsLetter(char ch); //判断是否为字母
    bool IsDigit(char ch);  //判断是否为数字
    bool IsOperator();  //判断是否为运算符
    void Scan();    //分析单词
    void AssignStr(string sourceCode);  //给源文件字符串赋值
    void beginExpL();   //进行词法分析
    string ExpLResult();    //返回分析结果
private:
    string str="";      //源文件字符串
    string token="";    //token
    TokenID syn;    //字符种类
    int pos;    //扫描到的位置
    const static int keyWordsNum=63;   //关键词个数
    string keyWords[keyWordsNum];   //关键词
    string endStr="";   //分析结果
};

#endif // EXPL_H
