#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

#include "def.h"
#include "node.h"
#include "Solver.h"

Solver::Solver(char* words[], int len, char* result[], char head, char tail, bool enable_loop, int tag)
{
    m_words = words;
    m_len = len;
    m_result = result;
    m_head = (head >= 'A' && head <= 'Z') ? head - 'A' + 'a' : head;
    m_tail = (tail >= 'A' && tail <= 'Z') ? tail - 'A' + 'a' : tail;
    m_enable_loop = enable_loop;
    m_tag = tag;

    m_currentOptLen = 0;
    m_currentTempLen = 0;

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

Solver::~Solver()
{
    int size = 0;
    for (int i = 0; i < charNum; ++i)
    {
        size = m_firstDic[i].size();
        for (int j = 0; j < size; ++j)
        {
            delete m_firstDic[i][j];
        }
    }
    delete []m_firstDic;
    delete []m_lastDic;
    delete m_currentOpt;
    delete m_currentTemp;
}

/*
    apple
    part['a']['e'] = 1
*/

bool Solver::isRepeat(const char * const newstr)
{
    int index = (newstr[0] >= 'A' && newstr[0] <= 'Z') ? newstr[0] - 'A' : newstr[0] - 'a';
    for (int i = 0; i < m_firstDic[index].size(); ++i)
    {
        if (_strcmpi(m_firstDic[index][i]->getWord(), newstr) == 0)
        {
            return true;
        }
    }
    return false;
}

/*
    ��������ַ�ָ������ת��Ϊ����Ķ��󣬲�������Ӧ��������
*/
void Solver::fillInTable()
{
    Node *temp;
    int firstIndex = -1;
    int lastIndex = -1;
    for (int i = 0; i < m_len; ++i)
    {
        if (isRepeat(m_words[i]))
        {
            continue;
        }
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
void Solver::alphaSort()
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
void Solver::fillInOrder(int beginIndex, int &loopBegin)
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
void Solver::dynamicAlgorithm(int loopBegin, int beginIndex, int endIndex, Node* &prevNodeNow)
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
int Solver::gen_chain()
{
    using std::vector;

    Node *prevNodeNow = nullptr;

    vector<Node*> retVec;

    int beginIndex = (m_head == '\0') ? -1 : m_head - 'a';
    int endIndex = (m_tail == '\0') ? -1 : m_tail - 'a';
    int loopBegin = 0;

    fillInTable();  // ���ݴ�����ַ�ָ�����鹹����Ӧ�Ķ��󣬲���������firstDic��lastDic������

    if (!m_enable_loop)
    {
        // �����ɻ����������Ҫ���ǿ��ܳ��ֻ�
        alphaSort();
        fillInOrder(beginIndex, loopBegin);
        //std::cout << "loopBegin = " << loopBegin << std::endl;
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
        int retSize = retVec.size();
        if (retSize < 2)
        {
            return 0;
        }
        for (int i = 0; i < retSize; ++i)
        {
            int length = retVec[i]->getLength();
            m_result[i] = new char[length + 1];
            strcpy_s(m_result[i], length + 1, retVec[i]->getWord());
            //m_result[i] = retVec[i]->getWord();
        }
        return retSize;
    }
    else
    {
        // $TODO
        m_currentOpt = new std::vector<Node*>;
        m_currentTemp = new std::vector<Node*>;
        int maxLengthNow = 0;
        //ָ����ͷ��ĸ
        if (m_head != '\0')
        {
            for (int i = 0; i < m_firstDic[beginIndex].size(); ++i)
            {
                m_currentTempLen = 0;
                m_currentTemp->clear();
                recursion(m_firstDic[beginIndex][i]);
                m_firstDic[beginIndex][i]->changeIsUsed();
            }
        }
        //ûָ��
        else
        {
            for (int i = 0; i < charNum; ++i)
            {
                for (int j = 0; j < m_firstDic[i].size(); ++j)
                {
                    m_currentTempLen = 0;
                    m_currentTemp->clear();
                    recursion(m_firstDic[i][j]);
                    m_firstDic[i][j]->changeIsUsed();
                    //std::cout << "--\n";
                }
            }
        }
        /*
        ��vector�е�����ȡ������result��
        */
        int retSize = m_currentOpt->size();
        if (retSize < 2)
        {
            return 0;
        }
        for (int i = 0; i < retSize; ++i)
        {
            int length = (*m_currentOpt)[i]->getLength();
            m_result[i] = new char[length + 1];
            strcpy_s(m_result[i], length + 1, (*m_currentOpt)[i]->getWord());
        }
        return retSize;
    }
    return 0;
}

void Solver::recursion(Node *rootWord)
{
    int flag = 0;

    rootWord->changeIsUsed();
    m_currentTemp->push_back(rootWord);

    if (m_tag == 1)
    {
        m_currentTempLen += rootWord->getLength();
    }
    else
    {
        m_currentTempLen++;
    }


    int tempIndex = rootWord->getLastChar() - 'a';
    Node* nextNode = nullptr;

    for (int i = 0; i < m_firstDic[tempIndex].size(); ++i)
    {
        nextNode = m_firstDic[tempIndex][i];
        if (!nextNode->getIsUsed() && (m_currentOptLen < m_currentTempLen + nextNode->getMaxLength() || nextNode->getMaxLength() == 0))
        {
            flag = 1;
            recursion(nextNode);
            nextNode->changeIsUsed();
        }
    }
    if (m_tail != '\0')
    {
        if (rootWord->getLastChar() == m_tail)
        {
            if (m_currentTempLen > (*m_currentTemp)[0]->getMaxLength())
            {
                (*m_currentTemp)[0]->setMaxLength(m_currentTempLen);
            }
            if (m_currentTempLen > m_currentOptLen)
            {
                m_currentOptLen = m_currentTempLen;
                delete m_currentOpt;
                m_currentOpt = new std::vector<Node*>;
                *m_currentOpt = *m_currentTemp;
            }
        }
    }
    else
    {
        if (flag == 0 && m_currentTempLen > (*m_currentTemp)[0]->getMaxLength())
        {
            (*m_currentTemp)[0]->setMaxLength(m_currentTempLen);
        }
        if (flag == 0 && m_currentTempLen > m_currentOptLen)
        {
            m_currentOptLen = m_currentTempLen;
            delete m_currentOpt;
            m_currentOpt = new std::vector<Node*>;
            *m_currentOpt = *m_currentTemp;
        }
    }
    m_currentTemp->pop_back();
    if (m_tag == 1)
    {
        m_currentTempLen -= rootWord->getLength();
    }
    else
    {
        m_currentTempLen--;
    }
}