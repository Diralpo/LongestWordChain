#include "pch.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

#include "def.h"
#include "node.h"
#include "core.h"

Core::Core(char* words[], int len, char* result[], char head, char tail, bool enable_loop, int tag)
{
    m_words = words;
    m_len = len;
    m_result = result;
    m_head = head;
    m_tail = tail;
    m_enable_loop = enable_loop;
    m_tag = tag;

    for (int i = 0; i < charNum; ++i)
    {
        m_alphaOrder[i] = 0;
        m_alphaInDegree[i] = 0;
        for (int j = 0; j < charNum; ++j)
        {
            m_partOrderRelation[i][j] = 0;
            m_partOrderRelation[j][i] = 0;
        }
    }

    m_firstDic = new std::vector<Node*>[charNum];
    m_lastDic = new std::vector<Node*>[charNum];
}

Core::~Core()
{

}

/*
    apple
    part['a']['e'] = 1
*/

/*
    ��������ַ�ָ������ת��Ϊ����Ķ��󣬲�������Ӧ��������
*/
void Core::fillInTable()
{
    Node *temp;
    int firstIndex = -1;
    int lastIndex = -1;
    for (int i = 0; i < m_len; ++i)
    {
        temp = new Node(m_words[i]);
        firstIndex = temp->getFirstChar() - 'a';
        lastIndex = temp->getLastChar() - 'a';
        if (firstIndex == lastIndex)
        {
            m_firstDic[firstIndex].insert(m_firstDic[firstIndex].begin(), temp);
            m_lastDic[lastIndex].insert(m_lastDic[lastIndex].begin(), temp);
        }
        else
        {
            m_firstDic[firstIndex].push_back(temp);
            m_lastDic[lastIndex].push_back(temp);
        }
        if (firstIndex == lastIndex)
        {
            if (!m_enable_loop && m_partOrderRelation[firstIndex][lastIndex] > 0)
            {
                // $TODO
                exit(-1);
            }
            else
            {
                m_partOrderRelation[firstIndex][lastIndex]++;
            }
        }
        else
        {
            if (!m_enable_loop && m_partOrderRelation[firstIndex][lastIndex] < 0)
            {
                // $TODO
                exit(-1);

            }
            else
            {
                if (m_partOrderRelation[firstIndex][lastIndex] == 0)
                {
                    m_alphaInDegree[lastIndex]++;
                }
                m_partOrderRelation[firstIndex][lastIndex] = 1;
                m_partOrderRelation[lastIndex][firstIndex] = -1;
            }
        }
    }
}

/*
    ����ͬ����ĸ����
*/
void Core::alphaSort()
{
    int flag = 0;
    int orderedNum = 0;
    int isOrdered[charNum] = { 0 };
    while (orderedNum < charNum)
    {
        flag = 0;
        for (int i = 0; i < charNum; ++i)
        {
            if (m_alphaInDegree[i] == 0 && isOrdered[i] == 0)
            {
                flag = 1;
                isOrdered[i] = 1;
                m_alphaOrder[orderedNum] = i;
                orderedNum++;
                for (int j = 0; j < charNum; ++j)
                {
                    if (i != j && m_partOrderRelation[i][j] == 1)
                    {
                        m_alphaInDegree[j]--;
                    }
                }
                break;
            }
        }
        if (flag == 0)
        {
            // $TODO
            exit(-1);
        }
    }

}

/*
    �������������ַ���˳������vector��
*/
void Core::fillInOrder(int beginIndex, int loopBegin)
{
    for (int i = 0; i < charNum; ++i)
    {
        if (beginIndex >= 0 && beginIndex == m_alphaOrder[i])
        {
            if (m_firstDic[m_alphaOrder[i]].size() > 0)
            {
                loopBegin = m_sortedWords.size();
            }
            else
            {
                // $TODO
                abort();
            }
        }
        for (int j = 0; j < m_firstDic[m_alphaOrder[i]].size(); ++j)
        {
            m_sortedWords.push_back(m_firstDic[m_alphaOrder[i]][j]);
        }
    }
}

/*
��̬�滮
*/
void Core::dynamicAlgorithm(int loopBegin, int beginIndex, int endIndex, Node* &prevNodeNow)
{
    Node *nodeNow = nullptr;  // ��ǰ�����Ľڵ�
    int lengthNow = 0;
    int maxLengthNow = 0;
    for (int i = loopBegin; i < m_len; ++i)
    {
        nodeNow = m_sortedWords[i];
        for (int j = loopBegin; j < i; ++j)
        {
            if (m_sortedWords[j]->getLastChar() == nodeNow->getFirstChar() && m_sortedWords[j]->getMaxLength() > 0)
            {
                if (m_tag == 1)
                {
                    lengthNow = m_sortedWords[j]->getMaxLength() + nodeNow->getLength();
                }
                else
                {
                    lengthNow = m_sortedWords[j]->getMaxLength() + 1;
                }
                if (lengthNow > nodeNow->getMaxLength())
                {
                    nodeNow->setMaxLength(lengthNow);
                    nodeNow->setPreNode(m_sortedWords[j]);
                }
            }
        }
        if (beginIndex >= 0)
        {
            if (m_tag == 1)
            {
                if (beginIndex == nodeNow->getFirstChar() - 'a' && nodeNow->getMaxLength() < nodeNow->getLength())
                {
                    nodeNow->setMaxLength(nodeNow->getLength());
                }
            }
            else
            {
                if (beginIndex == nodeNow->getFirstChar() - 'a' && nodeNow->getMaxLength() < 1)
                {
                    nodeNow->setMaxLength(1);
                }
            }

        }
        else
        {
            if (m_tag == 1)
            {
                if (nodeNow->getMaxLength() < nodeNow->getLength())
                {
                    nodeNow->setMaxLength(nodeNow->getLength());
                }

            }
            else
            {
                if (nodeNow->getMaxLength() < 1)
                {
                    nodeNow->setMaxLength(1);
                }
            }

        }

        if (endIndex >= 0)
        {
            if (endIndex == nodeNow->getLastChar() - 'a' && nodeNow->getMaxLength() > maxLengthNow)
            {
                maxLengthNow = nodeNow->getMaxLength();
                prevNodeNow = nodeNow;
            }
        }
        else
        {
            if (nodeNow->getMaxLength() > maxLengthNow)
            {
                maxLengthNow = nodeNow->getMaxLength();
                prevNodeNow = nodeNow;
            }
        }
    }
}

/*
    ʵ�ʵ��õĺ���
*/
int Core::gen_chain()
{
    using std::vector;

    Node *prevNodeNow = nullptr;

    vector<Node*> retVec;

    int beginIndex = (m_head == '\0') ? -1 : ((m_head <= 'Z' && m_head >= 'A') ? m_head - 'A' : m_head - 'a');
    int endIndex = (m_tail == '\0') ? -1 : ((m_tail <= 'Z' && m_tail >= 'A') ? m_tail - 'A' : m_tail - 'a');
    int loopBegin = 0;

    fillInTable();  // ���ݴ�����ַ�ָ�����鹹����Ӧ�Ķ��󣬲���������firstDic��lastDic������

    if (!m_enable_loop)
    {
        // �����ɻ����������Ҫ���ǿ��ܳ��ֻ�
        alphaSort();
        fillInOrder(beginIndex, loopBegin);
        dynamicAlgorithm(loopBegin, beginIndex, endIndex, prevNodeNow);
        /*
        ���������������vector��
        */
        while (prevNodeNow != nullptr)
        {
            retVec.insert(retVec.begin(), prevNodeNow);
            prevNodeNow = prevNodeNow->getPreNode();
        }
        /*
        ��vector�е�����ȡ������result��
        */
        for (int i = 0; i < retVec.size(); ++i)
        {
            m_result[i] = retVec[i]->getWord();
        }
        return retVec.size();
    }
    else
    {
        // $TODO
    }
    return 0;
}

int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // ������൥��������
{
    using std::cout;
    using std::endl;
    cout << "��൥������" << endl;
    Core newCore = Core(words, len, result, head, tail, enable_loop, 0);
    return newCore.gen_chain();
}

int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // ���������ĸ������
{
    using std::cout;
    using std::endl;
    cout << "�����ĸ����" << endl;
    Core newCore = Core(words, len, result, head, tail, enable_loop, 1);
    return newCore.gen_chain();
}