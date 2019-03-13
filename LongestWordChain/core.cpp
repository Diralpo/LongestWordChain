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

Core::~Core()
{

}

/*
    apple
    part['a']['e'] = 1
*/

/*
    将传入的字符指针数组转换为定义的对象，并填入相应的数组中
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
    给不同的字母排序
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
    将拓扑排序后的字符串顺序填入vector中
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
动态规划
*/
void Core::dynamicAlgorithm(int loopBegin, int beginIndex, int endIndex, Node* &prevNodeNow)
{
    Node *nodeNow = nullptr;  // 当前遍历的节点
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
    实际调用的函数
*/
int Core::gen_chain()
{
    using std::vector;

    Node *prevNodeNow = nullptr;

    vector<Node*> retVec;

    int beginIndex = (m_head == '\0') ? -1 : ((m_head <= 'Z' && m_head >= 'A') ? m_head - 'A' : m_head - 'a');
    int endIndex = (m_tail == '\0') ? -1 : ((m_tail <= 'Z' && m_tail >= 'A') ? m_tail - 'A' : m_tail - 'a');
    int loopBegin = 0;

    fillInTable();  // 根据传入的字符指针数组构建相应的对象，并将其填入firstDic、lastDic数组中

    if (!m_enable_loop)
    {
        // 不构成环的情况，需要考虑可能出现环
        alphaSort();
        fillInOrder(beginIndex, loopBegin);
        dynamicAlgorithm(loopBegin, beginIndex, endIndex, prevNodeNow);
        /*
        逆序将最长单词链填入vector中
        */
        while (prevNodeNow != nullptr)
        {
            retVec.insert(retVec.begin(), prevNodeNow);
            prevNodeNow = prevNodeNow->getPreNode();
        }
        /*
        将vector中的数据取出填入result中
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
		m_currentOpt = new std::vector<Node*>;
		m_currentTemp = new std::vector<Node*>;
		int maxLengthNow = 0;
		//指定开头字母
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
		//没指定
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
		将vector中的数据取出填入result中
		*/
		for (int i = 0; i < m_currentOpt->size(); ++i)
		{
			m_result[i] = (*m_currentOpt)[i]->getWord();
		}
		return m_currentOpt->size();
    }
    return 0;
}

void Core::recursion(Node *rootWord) 
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
		if (!nextNode->getIsUsed() && (m_currentOptLen < m_currentTempLen + nextNode->getMaxLength() || nextNode->getMaxLength() == 0) )
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
		if(flag == 0 && m_currentTempLen > m_currentOptLen)
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



int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // 计算最多单词数量的
{
    using std::cout;
    using std::endl;
    cout << "最多单词数量" << endl;
    Core newCore = Core(words, len, result, head, tail, enable_loop, 0);
    return newCore.gen_chain();
}

int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // 计算最多字母数量的
{
    using std::cout;
    using std::endl;
    cout << "最多字母数量" << endl;
    Core newCore = Core(words, len, result, head, tail, enable_loop, 1);
    return newCore.gen_chain();
}

