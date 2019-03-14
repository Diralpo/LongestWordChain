#pragma once

#include <exception>

class IllegalParametersException : public std::exception
{
public:
    const char* what() { return " illegal parameters ";  };
};

class FileNotExitException : public std::exception
{
public:
    const char* what() { return " input text file does not exist "; };
};
