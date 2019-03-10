#pragma once

#ifndef NODE_H_
#define NODE_H_

#include <iostream>

class Node
{
private:
    const char *m_word;
    int m_length;
    char m_firstCh;
    char m_lastCh;
    bool m_isUsed;
public:
    Node(const char *word);
    ~Node();
    int getLength();
    char getFirstChar();
    char getLastChar();
    const char *getWord();
    bool getIsUsed();
    void changeIsUsed();
    friend std::ostream &operator<<(std::ostream &os, Node &node);
};

#endif //NODE_H_
