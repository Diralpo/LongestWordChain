#pragma once

#include <exception>

class FormEnglishWordRingsException : public std::exception
{
public:
    char const* what() const { return " word rings "; };
};