#include <stdio.h>
#include "utils.h"

size_t min(size_t num1, size_t num2)
{
    if (num1 < num2) return num1;
    return num2;
}