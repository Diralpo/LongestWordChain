#pragma once


#include <vector>

#include "def.h"
#include "node.h"



extern __declspec(dllexport) int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // ������൥��������
extern __declspec(dllexport) int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // ���������ĸ������


