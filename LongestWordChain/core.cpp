#include "pch.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

#include "def.h"
#include "node.h"
#include "core.h"
#include "solver.h"


int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // ������൥��������
{
    /* 
    using std::cout;
    using std::endl;
    cout << "��൥������" << endl;
    */
    Solver newCore = Solver(words, len, result, head, tail, enable_loop, 0);
    return newCore.gen_chain();
}

int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // ���������ĸ������
{
    /*
    assert(head == 0 || (head <= 'Z' && head >= 'A') || (head <= 'z' && head >= 'a'));
    assert(tail == 0 || (tail <= 'Z' && tail >= 'A') || (tail <= 'z' && tail >= 'a'));
    */
    Solver newCore = Solver(words, len, result, head, tail, enable_loop, 1);
    return newCore.gen_chain();
}

