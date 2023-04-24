#ifndef _MYHEADER_H3
#define _MYHEADER_H3

void getUsrIpt(const char *);
void printSysMsg(const char *);

typedef enum
{
    BooleanChr,
    SpaceChr,
    LnBrkChr,
    NumChr,
    KorChr,
    AlphChr,
    SpecialChr,
    NotChr
} Chr;
Chr chrType(const char *);

typedef enum
{
    BooleanStr,
    SpaceStr,
    NonLnBrkStr,
    OneLnStr,
    LnBrkStr,
    PureStr,
    SpecialStr,
    DateStr,
    NotStr
} Str;
Str strType(const char *);

int stepStr(const char *, int, Str, char *);
int dateCmpr(const char *, const char *);

#endif