#include <userio.h>

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
    char c = chr[0];
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
        return LnBrKChr;
    }
    else if (c & 0x80 != 0) {
        return KorChr;
    }
    else {
        return NotChr;
    }

	
}

// 문자열 유형을 구분
Str strType(const char * str){
  return 1;
}

// source 문자열의 start부터 strType을 읽고 dest에 저장한다.
// 찾은 문자열의 길이를 반환한다.
int stepStr(const char * source, int start, Str strType, const char * dest){

}
