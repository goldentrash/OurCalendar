#include <userio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// 프롬포트에서 입력받은 내용을 ipt에 저장
void getUsrIpt(const char* ipt) {
	scanf("%s", ipt);
}

// msg를 terminal에 출력
void printSysMsg(const char* msg) {
	printf("%s\n", msg);
};

// 문자 유형을 구분 (개행 문자 때문에 배열을 입력으로 받음)
Chr chrType(const char* chr) {
    unsigned char c = chr[0];
    if (c <= 0x7F) {
        if (c >= '0' && c <= '9') {
            return NumChr;
        }
        else if (c >= 'a' && c <= 'z') {
            return AlphChr;
        }
        else if (c >= 'A' && c <= 'Z') {
            return AlphChr;
        }
        else if (c == ' ') {
            return SpaceChr;
        }
        else if (c == '\n') {
            return LnBrkChr;
        }
        else if (c == '.' || c == '-' || c == '/') {
            return SpecialChr;
        }
        else if (c == '\t') {
            return SpaceChr;
        }
        else if (c == '\r') {
            return LnBrkChr;
        }
        else {
            return NotChr;
        }
    }
    else if ((c & 0xE0) == 0xC0) {
        // 2byte UTF-8 
        if ((unsigned char)(chr[1] & 0xC0) != 0x80) {
            return NotChr;
        }
        unsigned char c2 = chr[1];
        if (((c & 0x1F) == 0xE) && ((c2 & 0x20) == 0)) {
            return KorChr;
        }
        else {
            return NotChr;
        }
    }
    else if ((c & 0xF0) == 0xE0) {
        // 3byte UTF-8 
        if ((unsigned char)(chr[1] & 0xC0) != 0x80 ||
            (unsigned char)(chr[2] & 0xC0) != 0x80) {
            return NotChr;
        }
        return KorChr;
    }
    else if ((c & 0xF8) == 0xF0) {
        // 4byte UTF-8 
        if ((unsigned char)(chr[1] & 0xC0) != 0x80 ||
            (unsigned char)(chr[2] & 0xC0) != 0x80 ||
            (unsigned char)(chr[3] & 0xC0) != 0x80) {
            return NotChr;
        }
        return KorChr;
    }
    else {
        return NotChr;
    }
}

// 문자열 유형을 구분
Str strType(const char * str){
  int len = strlen(str);
    if (len == 0 || len > 100) {
        return NotStr;
    }
    int numCount = 0;
    int spaceCount = 0;
    int wordCount = 0;
    int specialCount = 0;
    int lnBrkCount = 0;

    for (int i = 0; i < len; i++) {
    
        Chr cType = chrType(&str[i]);
        switch (cType) {
        case NumChr:
            numCount++;
            break;
        case AlphChr:
            wordCount++;
            break;
        case SpaceChr:
            spaceCount++;
            break;
        case SpecialChr:
            specialCount++;
            break;
        case LnBrkChr:
            lnBrkCount++;
            break;
        case KorChr:
            wordCount++;
            break;
        default:
            break;
        }
       
    }



    if (lnBrkCount == 0)
    {
        return NonLnBrkStr;
    }
    else if (lnBrkCount == 1 && wordCount+specialCount+spaceCount+numCount == len - 1) 
    {
        return OneLnStr;
    }
    else if (wordCount+numCount == len) 
    {
        return PureStr;
    }
    else if (len == spaceCount)
    {
        return SpaceStr;
    }
    else if (lnBrkCount ==1 && spaceCount == len - 1)
    {
        return LnBrkStr;
    }
    else if (wordCount+numCount+specialCount == len)
    {
        return SpecialStr;
    }
    else if (lnBrkCount > 1) 
    {
        return NotStr;
    }
    else if(isDateStr(str))
    {
        return DateStr;
    }
    else if (isBooleanStr(str)) {
        return BooleanStr;
    }
    else {
        return NotStr;
    }
}


// source 문자열의 start부터 strType을 읽고 dest에 저장한다.
// 찾은 문자열의 길이를 반환한다.
int stepStr(const char * source, int start, Str strType, const char * dest){

}

int dateCmpr(const char* date1, const char* date2) {
    int year1, year2, month1, month2, day1, day2;
    char delimiter;

    if (!isDateStr(date1) || !isDateStr(date2)) {
        return -2;  /* 날짜 문자열아님*/
    }

    sscanf(date1, "%d%c%d%c%d", &year1, &delimiter, &month1, &delimiter, &day1);
    sscanf(date2, "%d%c%d%c%d", &year2, &delimiter, &month2, &delimiter, &day2);

    if (year1 < year2) {
        return 1;
    }
    else if (year1 > year2) {
        return -1;
    }
    else {
        if (month1 < month2) {
            return 1;
        }
        else if (month1 > month2) {
            return -1;
        }
        else {
            if (day1 < day2) {
                return 1;
            }
            else if (day1 > day2) {
                return -1;
            }
            else {
                return 0;
            }
        }
    }
}
bool isDateStr(const char* str) {
    int len = strlen(str);
    if (len != 10) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (i == 4 || i == 7) {
            if (str[i] != '-' && str[i] != '.' && str[i] != '/') {
                return false;
            }
        }
        else {
            if (!isdigit(str[i])) {
                return false;
            }
        }
    }
    return true;
}

bool isBooleanStr(const char* str) {
    int len = strlen(str);
    if (len != 1) {  
        return false;
    }
    char c = str[0];
    if (c == 'Y' || c == 'N') { 
        return true;
    }
    return false;
}
