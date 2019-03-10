#include "pch.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>

#include "commenFuncs.h"
#include "def.h"

/**
    tag :   0-- max number 
            1-- max char
*/
void getopt(int argc, char *argv[], int &tag, char &headCh, char &endCh, bool &isRing, std::string &filename)
{
    using std::strcmp;
    using std::strlen;
    int i = 1;
    while (i < argc)
    {
        if (strcmp(argv[i], "-w")==0)
        {
            if (tag != -1)
            {
                // $TODO
            }
            tag = 0;
            i++;
        }
        else if (strcmp(argv[i], "-c")==0)
        {
            if (tag != -1)
            {
                // $TODO
            }
            tag = 1;
            i++;
        }
        else if (strcmp(argv[i], "-h") == 0) 
        {
            if (strlen(argv[i + 1]) != 1)
            {
                // $TODO
            }
            if (headCh != '\0')
            {
                // $TODO
            }
            headCh = argv[i + 1][0];
            if (isalpha(headCh) == 0)
            {
                // $TODO
            }
            i += 2;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            if (strlen(argv[i + 1]) != 1)
            {
                // $TODO
            }
            if (endCh != '\0')
            {
                // $TODO
            }
            endCh = argv[i + 1][0];
            if (isalpha(endCh) == 0)
            {
                // $TODO
            }
            i += 2;
        }
        else if (strcmp(argv[i], "-r") == 0)
        {
            if (isRing)
            {
                // $TODO
            }
            isRing = true;
            i++;
        }
        else
        {
            if (i == argc - 1)
            {
                filename = std::string(argv[i]);
                break;
            }
            else 
            {
                // $TODO
            }
        }
    }
    if (tag != 0 && tag != 1)
    {
        // $TODO
    }
}

void getFileInput(const std::string &filename)
{
    using std::ifstream;
    ifstream in(filename);
    std::string newStr;

    char temp;
    int tempcnt = 0;
    char tempstr[1000] = {};

    if (!in) 
    {
        // $TODO
    }
    while (!in.eof())
    {
        temp = in.get();
        if (isalpha(temp)) 
        {
            tempstr[tempcnt] = temp;
            tempcnt++;
        }
        else {
            tempstr[tempcnt] = '\0';
            //wordlist[wordIndex] = std::string(tempstr);
            wordlist[wordIndex] = new char[tempcnt + 1];
            strcpy(wordlist[wordIndex], tempstr);
            wordIndex++;
            tempcnt = 0;
        }
    }
    in.close();
}

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // 计算最多单词数量的
{
    for (int i = 0; i < len; i++)
    {
        result[i] = words[i];
    }
    return 0;
}
int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // 计算最多字母数量的
{
    for (int i = 0; i < len; i++)
    {
        result[i] = words[i];
    }
    return 0;
}