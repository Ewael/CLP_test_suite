#pragma once

#include <stdio.h>
#include <string>

FILE* fmap_string(std::string data)
{
    return fmemopen((void *) data.c_str(), data.length(), "r");
}
