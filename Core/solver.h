#pragma once

#include <vector>

#include "def.h"
#include "node.h"
#include "core.h"

class Solver
{
private:
    char **m_words;
    int m_len;
    char **m_result;
    char m_head;  // 首字母约束
    char m_tail;  // 尾字母约束
    bool m_enable_loop;  // 是否能够成环
    int m_tag;  // 标记是解决最大单词数还是最大字母数
    int m_partOrderRelation[charNum][charNum];  // 不同字母间的关系
    int m_alphaOrder[charNum];  // 当不能成环时不同字母的先后顺序
    int m_alphaInDegree[charNum];  // 将字母视为一个节点时字母的入度
    int m_currentOptLen;  // 当前最优解的长度
    int m_currentTempLen;  // 当前遍历解的长度

    std::vector<Node*> *m_firstDic; // 首字母节点集
    std::vector<Node*> *m_lastDic;  // 尾字母节点集
    std::vector<Node*> m_sortedWords;  // 存储拓扑排序后的单词顺序
    std::vector<Node*> *m_currentOpt;  // 成环的情况下，当前最优路径
    std::vector<Node*> *m_currentTemp;  // 不成环的情况下，当前遍历的路径

    void fillInTable(); // 将传入的字符指针数组转换为定义的对象，并填入相应的数组中
    void alphaSort();  // 将一个字母视为一个节点，给不同的字母排序
    void fillInOrder(int beginIndex, int &loopBegin);  // 将拓扑排序后的字符串顺序填入vector中
    void dynamicAlgorithm(int loopBegin, int beginIndex, int endIndex, Node* &prevNodeNow);  // 动态规划解决无环图的最长路径问题
    void recursion(Node *);  // 递归实现有环图的最长路径问题
    bool isRepeat(const char * const);  // 读入输入时检查是否已读入一个重复的单词
    int gen_chain();  // Core调用的函数

    Solver(char* words[], int len, char* result[], char head, char tail, bool enable_loop, int tag);
    ~Solver();
    
public:
    
    friend int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
    friend int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的
};
