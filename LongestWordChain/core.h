#pragma once

#ifndef CORE_H_
#define CORE_H_

#include <vector>

#include "def.h"
#include "node.h"

class Core 
{
public:
    static int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
    static int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的
};

#endif