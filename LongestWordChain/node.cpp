// LongestWordChain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>

#include "node.h"

Node::Node(const char *word) 
{
    m_word = word;
    m_length = std::strlen(word);
    m_firstCh = word[0];
    m_lastCh = word[m_length - 1];
    m_isUsed = false;
}

Node::~Node(){}

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

const char *Node::getWord()
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

std::ostream &operator<<(std::ostream &os, Node &node)
{
    os << node.m_word;
    return os;
}
