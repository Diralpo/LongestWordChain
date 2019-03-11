// LongestWordChain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>

#include "node.h"

Node::Node(char *word) 
{
    m_word = word;
    m_length = std::strlen(word);
    m_firstCh = word[0];
    m_firstCh = (m_firstCh >= 'a' && m_firstCh <= 'z')? m_firstCh : m_firstCh - 'A' + 'a';
    m_lastCh = word[m_length - 1];
    m_lastCh = (m_lastCh >= 'a' && m_lastCh <= 'z') ? m_lastCh : m_lastCh - 'A' + 'a';
    m_isUsed = false;
    m_maxLength = 0;
    m_preNode = nullptr;
}

Node::~Node()
{
    delete m_word;
}

int Node::getLength() 
{
    return m_length;
}

char Node::getFirstChar()
{
    return m_firstCh;
}

char Node::getLastChar()
{
    return m_lastCh;
}

char *Node::getWord()
{
    return m_word;
}

bool Node::getIsUsed()
{
    return m_isUsed;
}

void Node::changeIsUsed() 
{
    m_isUsed = !m_isUsed;
}

int Node::getMaxLength()
{
    return m_maxLength;
}
void Node::setMaxLength(int length) 
{
    m_maxLength = length;
}
Node *Node::getPreNode()
{
    return m_preNode;
}

void Node::setPreNode(Node *preNode)
{
    m_preNode = preNode;
}

std::ostream &operator<<(std::ostream &os, Node &node)
{
    os << node.m_word;
    return os;
}
