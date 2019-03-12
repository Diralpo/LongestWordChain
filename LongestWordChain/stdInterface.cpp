#include "pch.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

#include "def.h"
#include "node.h"


int partOrderRelation[charNum][charNum];
int alphaInDegree[charNum];

/*
    apple
    part['a']['e'] = 1
*/
void initPartOrder()
{
    for (int i = 0; i < charNum; ++i)
    {
        alphaInDegree[i] = 0;
        for (int j = 0; j <= i; ++j)
        {
            partOrderRelation[i][j] = 0;
            partOrderRelation[j][i] = 0;
        }
    }
}

/*
    ��������ַ�ָ������ת��Ϊ����Ķ��󣬲�������Ӧ��������
*/
void fillInTable(char* words[], int len, std::vector<Node*> firstDic[], std::vector<Node*> lastDic[], bool enable_loop)
{
    Node *temp;
    int firstIndex = -1;
    int lastIndex = -1;
    for (int i = 0; i < len; ++i)
    {
        temp = new Node(words[i]);
        firstIndex = temp->getFirstChar() - 'a';
        lastIndex = temp->getLastChar() - 'a';
        if (firstIndex == lastIndex)
        {
            firstDic[firstIndex].insert(firstDic[firstIndex].begin(), temp);
            lastDic[lastIndex].insert(lastDic[lastIndex].begin(), temp);
        }
        else
        {
            firstDic[firstIndex].push_back(temp);
            lastDic[lastIndex].push_back(temp);
        }
        if (firstIndex == lastIndex)
        {
            if (!enable_loop && partOrderRelation[firstIndex][lastIndex] > 0)
            {
                // $TODO
                exit(-1);
            }
            else
            {
                partOrderRelation[firstIndex][lastIndex]++;
            }
        }
        else
        {
            if (!enable_loop && partOrderRelation[firstIndex][lastIndex] < 0)
            {
                // $TODO
                exit(-1);

            }
            else
            {
                if (partOrderRelation[firstIndex][lastIndex] == 0)
                {
                    alphaInDegree[lastIndex]++;
                }
                partOrderRelation[firstIndex][lastIndex] = 1;
                partOrderRelation[lastIndex][firstIndex] = -1;
            }
        }
    }
}

/*
    ����ͬ����ĸ����
*/
void alphaSort(int alphaOrder[])
{
    int flag = 0;
    int orderedNum = 0;
    int isOrdered[charNum] = { 0 };
    while (orderedNum < charNum)
    {
        flag = 0;
        for (int i = 0; i < charNum; ++i)
        {
            if (alphaInDegree[i] == 0 && isOrdered[i] == 0)
            {
                flag = 1;
                isOrdered[i] = 1;
                alphaOrder[orderedNum] = i;
                orderedNum++;
                for (int j = 0; j < charNum; ++j)
                {
                    if (i != j && partOrderRelation[i][j] == 1)
                    {
                        alphaInDegree[j]--;
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
void fillInOrder(int beginIndex, int *alphaOrder, std::vector<Node*> firstDic[], int loopBegin, std::vector<Node*> &sortedWords)
{
    for (int i = 0; i < charNum; ++i)
    {
        if (beginIndex>=0 && beginIndex == alphaOrder[i])
        {
            if (firstDic[alphaOrder[i]].size() > 0)
            {
                loopBegin = sortedWords.size();
            }
            else
            {
                // $TODO
                abort();
            }
        }
        for (int j = 0; j < firstDic[alphaOrder[i]].size(); ++j)
        {
            sortedWords.push_back(firstDic[alphaOrder[i]][j]);
        }
    }
}

void dynamicAlgorithm(int loopBegin, int len, std::vector<Node*> &sortedWords, int tag, int beginIndex, int endIndex, Node* &prevNodeNow)
{
    /*
    ��̬�滮
    */
    Node *nodeNow = nullptr;
    int lengthNow = 0;
    int maxLengthNow = 0;
    for (int i = loopBegin; i < len; ++i)
    {
        nodeNow = sortedWords[i];
        for (int j = loopBegin; j < i; ++j)
        {
            if (sortedWords[j]->getLastChar() == nodeNow->getFirstChar() && sortedWords[j]->getMaxLength() > 0)
            {
                if (tag == 1)
                {
                    lengthNow = sortedWords[j]->getMaxLength() + nodeNow->getLength();
                }
                else
                {
                    lengthNow = sortedWords[j]->getMaxLength() + 1;
                }
                if (lengthNow > nodeNow->getMaxLength())
                {
                    nodeNow->setMaxLength(lengthNow);
                    nodeNow->setPreNode(sortedWords[j]);
                }
            }
        }
        if (beginIndex >= 0)
        {
            if (tag == 1)
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
            if (tag == 1)
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

int gen_chain(char* words[], int len, char* result[], char head, char tail, bool enable_loop, int tag)
{
    using std::vector;

    Node *prevNodeNow = nullptr;
    vector<Node*> firstDic[charNum];
    vector<Node*> lastDic[charNum];
    vector<Node*> sortedWords;
    vector<Node*> retVec;
    int alphaOrder[charNum];
    int beginIndex = (head == '\0') ? -1 : ((head <= 'Z' && head >= 'A') ? head - 'A' : head - 'a');
    int endIndex = (tail == '\0') ? -1 : ((tail <= 'Z' && tail >= 'A') ? tail - 'A' : tail - 'a');
    int loopBegin = 0;

    initPartOrder(); // ��ʼ��alphaOrder����
    fillInTable(words, len, firstDic, lastDic, enable_loop);  // ���ݴ�����ַ�ָ�����鹹����Ӧ�Ķ��󣬲���������firstDic��lastDic������

    if (!enable_loop)
    {
        // �����ɻ����������Ҫ���ǿ��ܳ��ֻ�
        alphaSort(alphaOrder);
        fillInOrder(beginIndex, alphaOrder, firstDic, loopBegin, sortedWords);
        dynamicAlgorithm(loopBegin, len, sortedWords, tag, beginIndex, endIndex, prevNodeNow);
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
            result[i] = retVec[i]->getWord();
        }
        return retVec.size();
    }
    else
    {
        // $TODO
    }
    return 0;
}

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // ������൥��������
{
    using std::cout;
    using std::endl;

    //cout << "��൥������" << endl;
    return gen_chain(words, len, result, head, tail, enable_loop, 0);
}

int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // ���������ĸ������
{
    using std::cout;
    using std::endl;

    //cout << "�����ĸ����" << endl;
    return gen_chain(words, len, result, head, tail, enable_loop, 1);
}