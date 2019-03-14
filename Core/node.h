#pragma once

#include <iostream>

class Node
{
private:
    char *m_word;
    int m_length;
    char m_firstCh;
    char m_lastCh;
    bool m_isUsed;
    int m_maxLength;
    Node* m_preNode;
public:
    Node(char *word);
    ~Node();
    int getLength();
    char getFirstChar();
    char getLastChar();
    char *getWord();
    bool getIsUsed();
    void changeIsUsed();
    friend std::ostream &operator<<(std::ostream &os, Node &node);
    int getMaxLength();
    void setMaxLength(int length);
    Node *getPreNode();
    void setPreNode(Node *preNode);

};
