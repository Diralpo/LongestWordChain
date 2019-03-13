#include "pch.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

#include "commenFuncs.h"
#include "def.h"
#include "node.h"
#include "exceptions_.h"

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
                throw IllegalParametersException();
            }
            tag = 0;
            i++;
        }
        else if (strcmp(argv[i], "-c")==0)
        {
            if (tag != -1)
            {
                // $TODO
                throw IllegalParametersException();
            }
            tag = 1;
            i++;
        }
        else if (strcmp(argv[i], "-h") == 0) 
        {
            if (strlen(argv[i + 1]) != 1)
            {
                // $TODO
                throw IllegalParametersException();
            }
            if (headCh != '\0')
            {
                // $TODO
                throw IllegalParametersException();
            }
            headCh = argv[i + 1][0];
            if (isalpha(headCh) == 0)
            {
                // $TODO
                throw IllegalParametersException();
            }
            i += 2;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            if (strlen(argv[i + 1]) != 1)
            {
                // $TODO
                throw IllegalParametersException();
            }
            if (endCh != '\0')
            {
                // $TODO
                throw IllegalParametersException();
            }
            endCh = argv[i + 1][0];
            if (isalpha(endCh) == 0)
            {
                // $TODO
                throw IllegalParametersException();
            }
            i += 2;
        }
        else if (strcmp(argv[i], "-r") == 0)
        {
            if (isRing)
            {
                // $TODO
                throw IllegalParametersException();
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
                throw IllegalParametersException();
            }
        }
    }
    if (tag != 0 && tag != 1)
    {
        // $TODO
        throw IllegalParametersException();
    }
}

void getFileInput(const std::string &filename)
{
    using std::ifstream;
    ifstream in(filename);

    char temp;
    int tempcnt = 0;
    std::string readStr;

    if (!in) 
    {
        // $TODO
        throw FileNotExitException();
        //exit(-1);
    }
    while (!in.eof())
    {
        temp = in.get();

        if (isalpha(temp)) 
        {
            readStr += temp;
            tempcnt++;
        }
        else {
            if (tempcnt > 0)
            {
                wordlist[wordIndex] = new char[tempcnt + 1];
                strcpy_s(wordlist[wordIndex], tempcnt + 1, readStr.c_str());
                wordIndex++;
                tempcnt = 0;
                readStr.clear();
            }
        }
    }
    in.close();
}
