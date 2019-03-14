#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

#include "commenFuncs.h"
#include "def.h"
#include "exceptions_.h"

#pragma comment(lib, "Core.lib")

extern __declspec(dllimport) int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
extern __declspec(dllimport) int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);


char *wordlist[20000];
int wordIndex = 0;
const char * const outputFile = "solution.txt";

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    int tag = -1;
    char headCh = '\0';
    char endCh = '\0';
    bool isRing = false;
    std::string filename = std::string();
    try 
    {
        getopt(argc, argv, tag, headCh, endCh, isRing, filename);
    }
    catch (IllegalParametersException &illExcept)
    {
        cout << illExcept.what() << endl;
        return -1;
    }
    
    try
    {
        getFileInput(filename);
    }
    catch (FileNotExitException &fileExc)
    {
        cout << fileExc.what() << endl;
    }

    char **result = new char*[wordIndex];
    int maxLength = 0;


    if (tag == 0)
    {
        try 
        {
            maxLength = gen_chain_word(wordlist, wordIndex, result, headCh, endCh, isRing);
        }
        catch (std::exception &excpt)
        {
            cout << excpt.what() << endl;
            exit(-1);
        }
        
        for (int i = 0; i < maxLength; ++i)
        {
            cout << result[i] << endl;
        }
    }
    else
    {
        try
        {
            maxLength = gen_chain_char(wordlist, wordIndex, result, headCh, endCh, isRing);
        }
        catch (std::exception &excpt)
        {
            cout << excpt.what() << endl;
            exit(-1);
        }
        for (int i = 0; i < maxLength; ++i)
        {
            cout << result[i] << endl;
        }
    }
    std::ofstream out = std::ofstream(outputFile);
    for (int i = 0; i < maxLength; ++i)
    {
        out << result[i] << endl;
        delete result[i];
    }
    out.close();
    delete []result;

    return 0;
}