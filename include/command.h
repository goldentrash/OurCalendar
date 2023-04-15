#include <userio.h>

#ifndef _MYHEADER_H1
#define _MYHEADER_H1

typedef enum
{
    Help,
    Add,
    Del,
    Search,
    Quit,
    Unknown
} Cmd;

Cmd cmdType(const char *);

void help(const char *);
void add(const char *);
void del(const char *);
void search(const char *);

#endif
