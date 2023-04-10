#include <userio.h>

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

void parseParameters(const char *, const Str *, const char **);