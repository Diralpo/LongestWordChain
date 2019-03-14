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
    char m_head;  // ����ĸԼ��
    char m_tail;  // β��ĸԼ��
    bool m_enable_loop;  // �Ƿ��ܹ��ɻ�
    int m_tag;  // ����ǽ����󵥴������������ĸ��
    int m_partOrderRelation[charNum][charNum];  // ��ͬ��ĸ��Ĺ�ϵ
    int m_alphaOrder[charNum];  // �����ܳɻ�ʱ��ͬ��ĸ���Ⱥ�˳��
    int m_alphaInDegree[charNum];  // ����ĸ��Ϊһ���ڵ�ʱ��ĸ�����
    int m_currentOptLen;  // ��ǰ���Ž�ĳ���
    int m_currentTempLen;  // ��ǰ������ĳ���

    std::vector<Node*> *m_firstDic; // ����ĸ�ڵ㼯
    std::vector<Node*> *m_lastDic;  // β��ĸ�ڵ㼯
    std::vector<Node*> m_sortedWords;  // �洢���������ĵ���˳��
    std::vector<Node*> *m_currentOpt;  // �ɻ�������£���ǰ����·��
    std::vector<Node*> *m_currentTemp;  // ���ɻ�������£���ǰ������·��

    void fillInTable(); // ��������ַ�ָ������ת��Ϊ����Ķ��󣬲�������Ӧ��������
    void alphaSort();  // ��һ����ĸ��Ϊһ���ڵ㣬����ͬ����ĸ����
    void fillInOrder(int beginIndex, int &loopBegin);  // �������������ַ���˳������vector��
    void dynamicAlgorithm(int loopBegin, int beginIndex, int endIndex, Node* &prevNodeNow);  // ��̬�滮����޻�ͼ���·������
    void recursion(Node *);  // �ݹ�ʵ���л�ͼ���·������
    bool isRepeat(const char * const);  // ��������ʱ����Ƿ��Ѷ���һ���ظ��ĵ���
    int gen_chain();  // Core���õĺ���

    Solver(char* words[], int len, char* result[], char head, char tail, bool enable_loop, int tag);
    ~Solver();
    
public:
    
    friend int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // ������൥��������
    friend int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // ���������ĸ������
};
