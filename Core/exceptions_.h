#pragma once

#include <exception>

class WordRingsException : public std::exception
{
public:
    char const* what() const { return " word rings "; };
};

class IllegalInterfaceParaException : public std::exception
{
public:
    char const* what() const { return " illegal interface parameters "; };
};