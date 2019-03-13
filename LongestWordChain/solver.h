#pragma once

#ifndef SOLVER_H_
#define SOLVER_H_

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
    char m_head;
    char m_tail;
    bool m_enable_loop;
    int m_tag;
    int m_partOrderRelation[charNum][charNum];
    int m_alphaOrder[charNum];
    int m_alphaInDegree[charNum];

    int m_currentOptLen;
    int m_currentTempLen;

    std::vector<Node*> *m_firstDic;
    std::vector<Node*> *m_lastDic;
    std::vector<Node*> m_sortedWords;
    std::vector<Node*> *m_currentOpt;
    std::vector<Node*> *m_currentTemp;


    void fillInTable();
    void alphaSort();
    void fillInOrder(int beginIndex, int &loopBegin);
    void dynamicAlgorithm(int loopBegin, int beginIndex, int endIndex, Node* &prevNodeNow);
    void recursion(Node *);
    bool isRepeat(const char const *);
    int gen_chain();

public:
    Solver(char* words[], int len, char* result[], char head, char tail, bool enable_loop, int tag);
    ~Solver();
    friend int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
    friend int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的
};

#endif