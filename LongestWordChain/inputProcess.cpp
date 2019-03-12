#include "pch.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

#include "commenFuncs.h"
#include "def.h"
#include "node.h"

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
                exit(-1);
            }
            tag = 0;
            i++;
        }
        else if (strcmp(argv[i], "-c")==0)
        {
            if (tag != -1)
            {
                // $TODO
                exit(-1);
            }
            tag = 1;
            i++;
        }
        else if (strcmp(argv[i], "-h") == 0) 
        {
            if (strlen(argv[i + 1]) != 1)
            {
                // $TODO
                exit(-1);
            }
            if (headCh != '\0')
            {
                // $TODO
                exit(-1);
            }
            headCh = argv[i + 1][0];
            if (isalpha(headCh) == 0)
            {
                // $TODO
                exit(-1);
            }
            i += 2;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            if (strlen(argv[i + 1]) != 1)
            {
                // $TODO
                exit(-1);
            }
            if (endCh != '\0')
            {
                // $TODO
                exit(-1);
            }
            endCh = argv[i + 1][0];
            if (isalpha(endCh) == 0)
            {
                // $TODO
                exit(-1);
            }
            i += 2;
        }
        else if (strcmp(argv[i], "-r") == 0)
        {
            if (isRing)
            {
                // $TODO
                exit(-1);
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
                exit(-1);
            }
        }
    }
    if (tag != 0 && tag != 1)
    {
        // $TODO
        exit(-1);
    }
}

void getFileInput(const std::string &filename)
{
    using std::ifstream;
    ifstream in(filename);

    char temp;
    int tempcnt = 0;
    char tempstr[1000] = {};

    if (!in) 
    {
        // $TODO
        exit(-1);
    }
    while (!in.eof())
    {
        temp = in.get();
        if (isalpha(temp)) 
        {
            //tempstr[tempcnt] = temp;
            tempstr[tempcnt] = (temp >= 'A' && temp <= 'Z') ? (temp - 'A' + 'a') : temp;
            tempcnt++;
        }
        else {
            if (tempcnt > 0)
            {
                tempstr[tempcnt] = '\0';
                //wordlist[wordIndex] = std::string(tempstr);
                wordlist[wordIndex] = new char[tempcnt + 1];
                strcpy(wordlist[wordIndex], tempstr);
                wordIndex++;
                tempcnt = 0;
            }
        }
    }
    in.close();
}
