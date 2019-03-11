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

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // 计算最多单词数量的
{
    using std::vector;
    using std::cout;
    using std::endl;

    int maxLengthNow = 0;
    Node *prevNodeNow = nullptr;
    Node* nodeNow = nullptr;
    int lengthNow = 0;
    int alphaOrder[charNum];

    int beginIndex = (head == '\0') ? -1 : ((head <= 'Z' && head >= 'A') ? head - 'A' : head - 'a');
    int endIndex = (tail == '\0') ? -1 : ((tail <= 'Z' && tail >= 'A') ? tail - 'A' : tail - 'a');
    int loopBegin = 0;

    initPartOrder();

    vector<Node*> firstDic[charNum];
    vector<Node*> lastDic[charNum];
    vector<Node*> sortedWords;

    fillInTable(words, len, firstDic, lastDic, enable_loop);

    if (!enable_loop) 
    {
        alphaSort(alphaOrder);
        for (int i = 0; i < charNum; ++i)
        {
            if (head != '0' && beginIndex == alphaOrder[i])
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

        for (int i = loopBegin; i < len; ++i)
        {
            nodeNow = sortedWords[i];
            for (int j = loopBegin; j < i; ++j)
            {
                if (sortedWords[j]->getLastChar() == nodeNow->getFirstChar() && sortedWords[j]->getMaxLength() > 0)
                {
                    lengthNow = sortedWords[j]->getMaxLength() + 1;
                    if (lengthNow > nodeNow->getMaxLength())
                    {
                        nodeNow->setMaxLength(lengthNow);
                        nodeNow->setPreNode(sortedWords[j]);
                    }
                }
            }
            if (head != '\0')
            {
                if (beginIndex == nodeNow->getFirstChar() - 'a' && nodeNow->getMaxLength() < 1)
                {
                    nodeNow->setMaxLength(1);
                }
            }
            else
            {
                if (nodeNow->getMaxLength() < 1)
                {
                    nodeNow->setMaxLength(1);
                }
            }

            if (tail != '\0')
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
        vector<Node*> retVec;
        while (prevNodeNow != nullptr)
        {
            retVec.insert(retVec.begin(), prevNodeNow);
            prevNodeNow = prevNodeNow->getPreNode();
        }
        for (int i = 0; i < retVec.size(); ++i)
        {
            result[i] = retVec[i]->getWord();
        }
        return retVec.size();
    }
    else
    {

    }

    return 0;
}

int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // 计算最多字母数量的
{
    using std::vector;
    using std::cout;
    using std::endl;

    int maxLengthNow = 0;
    Node *prevNodeNow = nullptr;
    Node* nodeNow = nullptr;
    int lengthNow = 0;
    int alphaOrder[charNum];

    int beginIndex = (head == '\0') ? -1 : ((head <= 'Z' && head >= 'A') ? head - 'A' : head - 'a');
    int endIndex = (tail == '\0') ? -1 : ((tail <= 'Z' && tail >= 'A') ? tail - 'A' : tail - 'a');
    int loopBegin = 0;

    initPartOrder();

    vector<Node*> firstDic[charNum];
    vector<Node*> lastDic[charNum];
    vector<Node*> sortedWords;

    fillInTable(words, len, firstDic, lastDic, enable_loop);

    if (!enable_loop)
    {
        alphaSort(alphaOrder);
        for (int i = 0; i < charNum; ++i)
        {
            if (head != '0' && beginIndex == alphaOrder[i])
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

        for (int i = loopBegin; i < len; ++i)
        {
            nodeNow = sortedWords[i];
            for (int j = loopBegin; j < i; ++j)
            {
                if (sortedWords[j]->getLastChar() == nodeNow->getFirstChar() && sortedWords[j]->getMaxLength() > 0)
                {
                    lengthNow = sortedWords[j]->getMaxLength() + nodeNow->getLength();
                    if (lengthNow > nodeNow->getMaxLength())
                    {
                        nodeNow->setMaxLength(lengthNow);
                        nodeNow->setPreNode(sortedWords[j]);
                    }
                }
            }
            if (head != '\0')
            {
                if (beginIndex == nodeNow->getFirstChar() - 'a' && nodeNow->getMaxLength() < nodeNow->getLength())
                {
                    nodeNow->setMaxLength(nodeNow->getLength());
                }
            }
            else
            {
                if (nodeNow->getMaxLength() < nodeNow->getLength())
                {
                    nodeNow->setMaxLength(nodeNow->getLength());
                }
            }

            if (tail != '\0')
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
        vector<Node*> retVec;
        while (prevNodeNow != nullptr)
        {
            retVec.insert(retVec.begin(), prevNodeNow);
            prevNodeNow = prevNodeNow->getPreNode();
        }
        for (int i = 0; i < retVec.size(); ++i)
        {
            result[i] = retVec[i]->getWord();
        }
        return retVec.size();
    }
    else
    {

    }

    return 0;
}