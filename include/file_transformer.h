// Last update: 2024-09-20
#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

typedef char (*filter_func)(char);

filter_func get_filter_function(const char *filter_name);
char        upper_filter(char c);
char        lower_filter(char c);
char        null_filter(char c);

#endif    // TRANSFORMATIONS_H
