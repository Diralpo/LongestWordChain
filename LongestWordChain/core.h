#pragma once

#ifndef CORE_H_
#define CORE_H_

#include <vector>

#include "def.h"
#include "node.h"

class Core 
{
public:
    static int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // ������൥��������
    static int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // ���������ĸ������
};

#endif