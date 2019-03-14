#pragma once

#include <exception>

class IllegalParametersException : public std::exception
{
public:
    char const* what() const { return " illegal parameters ";  };
};

class FileNotExitException : public std::exception
{
public:
    char const* what() const { return " input text file does not exist "; };
};
