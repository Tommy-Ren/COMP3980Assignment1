#include "../include/file_transformer.h"
#include <ctype.h>
#include <string.h>

// Transformation functions
char upper_filter(char c)
{
    return (char)toupper((unsigned char)c);
}

char lower_filter(char c)
{
    return (char)tolower((unsigned char)c);
}

char null_filter(char c)
{
    return c;
}

// Function to get the filter function based on the input string
filter_func get_filter_function(const char *filter_name)
{
    if(strcmp(filter_name, "upper") == 0)
    {
        return upper_filter;
    }
    if(strcmp(filter_name, "lower") == 0)
    {
        return lower_filter;
    }
    if(strcmp(filter_name, "null") == 0)
    {
        return null_filter;
    }
    return NULL;
}
