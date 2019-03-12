#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

#include "commenFuncs.h"
#include "node.h"
#include "def.h"
#include "core.h"

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

    getopt(argc, argv, tag, headCh, endCh, isRing, filename);

    getFileInput(filename);
    /*
    for (int i = 0; i < wordIndex; ++i)
    {
        cout << wordlist[i] << endl;
    }
    */
    char **result = new char*[wordIndex];
    int maxLength = 0;

    if (tag == 0)
    {
        maxLength = Core::gen_chain_word(wordlist, wordIndex, result, headCh, endCh, isRing);
        for (int i = 0; i < maxLength; ++i)
        {
            cout << result[i] << endl;
        }
    }
    else
    {
        maxLength = Core::gen_chain_char(wordlist, wordIndex, result, headCh, endCh, isRing);
        for (int i = 0; i < maxLength; ++i)
        {
            cout << result[i] << endl;
        }
    }
    std::ofstream out = std::ofstream(outputFile);
    for (int i = 0; i < maxLength; ++i)
    {
        out << result[i] << endl;
    }
    out.close();

    return 0;
}