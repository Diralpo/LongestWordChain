#pragma once

#ifndef COMMEN_FUNCS_H_
#define COMMEN_FUNCS_H_

#include <string>

/**
    tag :   0-- max number
            1-- max char
*/
extern void getopt(int argc, char *argv[], int &tag, char &headCh, char &endCh, bool &isRing, std::string &filename);
extern void getFileInput(const std::string &filename);

/*
extern int gen_chain_word(std::string words[], int len, char* result[], char head, char tail, bool enable_loop);  // ������൥��������
extern int gen_chain_char(std::string words[], int len, char* result[], char head, char tail, bool enable_loop);  // ���������ĸ������
*/
#endif //COMMEN_FUNCS_H_
