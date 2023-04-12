#include <task.h>

//char *id가 char배열의 시작 주소값이 맞죠??
typedef struct
{
    char *id;
    char compatable;
    char *startDate;
    char *endDate;
    char *contents;
} Task;

// 일정을 terminal에 출력 (userio/printSysMsg활용)
void printTask(Task  *task, int n){
    for(int i=0;i<n;i++)
    printf("%s/t%c %s~%s\n%s\n",task[i].id,task[i].compatable,task[i].startDate,task[i].endDate,task[i].contents);
};

//일정 배열 받고 해당하는 일정 반환
Task findTask(Task *task, const *number){
    return task[*number];
};

// 일정 생성 (id 자동 생성)
Task mkTask(char compatable, char * startDate, char * endDate, char * contents){
    Task task;
    task.compatable=compatable;
    task.startDate=starDate;
    task.endDate=endDate;
    taxk.contents=contents;
    task.id= PureStr();//순수문자열(한글, 알파벳, 숫자)
    return task;
};


// 동일한 일정인지 확인 (id 기준)
bool isEqualTask(Task a, Task b){ 
    if(strcmp(a.id,b.id)==0)
    return true;
    else
    return false;
};

// 동일한 일정인지 확인 (id 기준), 인자 바꾼 버전
bool isEqualTask(Task a, char *id){ 
    if(strcmp(a.id,id)==0)
    return true;
    else
    return false;
};

//등록된 일정인지 확인 -> 해당 일정이 정말 등록된 일정인지 확인하기 위한 마지막 절차??
bool isEnrolledTask(char * id){
    Task* alltaskarray=readFile();
    for(int i=0;i<readFile();i++){
        if(alltaskarray[i].id=id)
        return true;
    }
    return false;
}

// 일정이 겹치는지 확인
bool isOverlapped(Task a, Task b){
    if(toInteger(a.startDate)>toInteger(b.endDate) || toInteger(a.endDate)<toInteger(b.startDate))
    return true;
    else
    return false;    
}

// 일정 유효 검사, 유효한 일정이 아니면 raise exception
bool taskDiagnosis(Task task){

};

//등록된 모든 일정 반환 -> 승찬이의 readFile()하고 겹치는 것 같습니다
//Task *findAllTasks(){};

//입력한 기간에 시작하는 모든 등록된 일정 반환 
Task *findTasks(char * starDate,char *endDate){
    int n=0;
    Task* alltaskarray=readFile();
    for(int i=0;i<TaskCount();i++){
        if(startDate1=<taskarray[i].startDate=<endtDate)
        n++;
    }
    
    if(n==0)
    return NULL;
    
    Task taskarray[n];

    for(int i=0;i<TaskCount();i++){
        if(startDate1=<alltaskarray[i].startDate=<endtDate)
        taskarry[i]=alltaskarray[i];
    }
    return taskarray;
}

//입력한 기간과 겹치는 등록된 일정을 찾는 함수
Task *findOverlappedTask(char *startDate, char *endDate){

    int n=0;
    Task* alltaskarray=readFile();
    for(int i=0;i<TaskCount();i++){
        if(toInteger(startDate)>toInteger(alltaskarray[i].endDate) || toInteger(endDate)<toInteger(alltaskarray[i].startDate))
        n++;
    }

    if(n==0)
    return NULL;

    Task taskarray[n];

    for(int i=0;i<TaskCount();i++){
        if(toInteger(startDate)>toInteger(alltaskarray[i].endDate) || toInteger(endDate)<toInteger(alltaskarray[i].startDate))
        taskarry[i]=alltaskarray[i];
    }
    return taskarray;

};

//일정의 날짜문자열을 정수로 변환하는 함수
int DatetoInteger(char *Date){
    
    int result = 0;

    for (int i = 0; i < strlen(Date); i++) {
        if (isdigit(Date[i])) {
            result = result * 10 + (Date[i] - '0');
        }
    }

    return result;
}


//날짜 문자열의 문법규칙과 의미규칙 검사
bool DateRuleCheck(char *Date){
    
    char* delimiter = strpbrk(Date, ".-/"); // 주어진 구분자를 찾음
    if (delimiter == NULL) { // 구분자가 없으면 잘못된 형식
        return false;
    }

    char* tokens[3];
    tokens[0] = strtok(date_string, ".-/"); // 첫 번째 토큰
    tokens[1] = strtok(NULL, ".-/"); // 두 번째 토큰
    tokens[2] = strtok(NULL, ".-/"); // 세 번째 토큰

    // 토큰이 세 개가 아니면 잘못된 형식
    if (tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL) {
        return false;
    }

    // 토큰이 모두 숫자인지 검사
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < strlen(tokens[i]); j++) {
            if (tokens[i][j] < '0' || tokens[i][j] > '9') {
                return false;
            }
        }
    }

    // 각 토큰의 길이가 4, 2, 2이면서 숫자 범위가 맞는지 검사
    int year = atoi(tokens[0]);
    int month = atoi(tokens[1]);
    int day = atoi(tokens[2]);

    if (strlen(tokens[0]) != 4 || strlen(tokens[1]) != 2 || strlen(tokens[2]) != 2) {
        return false;
    }

    if (year < 2000 || year > 2040 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // 윤년 검사
    bool is_leap_year = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (month == 2 && (day > 29 || (day == 29 && !is_leap_year))) {
        return false;
    }

    // 4, 6, 9, 11월 검사
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }

    return true; // 모든 검사를 통과하면 유효한 형식
}

//Id의 문법규칙 검사
bool IdGrammerCheck(char *id){
    int i;

    // 길이가 3이 아니면 유효하지 않음
    if (strlen(id) != 3) {
        return false;
    }

    // 한 글자씩 검사
    for (i = 0; i < 3; i++) {
        // 숫자 또는 영어 알파벳이 아니거나 한글 범위에 속하지 않으면 유효하지 않음
        if (!isalnum(id[i]) || (id[i] < 0xAC00 || id[i] > 0xD7A3)) {
            return false;
        }
    }

    return true;
}

//Contents의 문법규칙 검사
int ContentsGrammerCheck(char *Contents){

}

//Compatable의 문법규칙 검사
int CompatableGrammerCheck(char compatable){}


//순수문자열을 생성하는 함수 ver1
char *PureStr() {
    // 난수 발생을 위한 시드값 설정 
    srand((unsigned int)time(NULL));

    // 가능한 문자 범위 설정
    const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYXZㄱㄴㄷㄹㅁㅂㅅㅇㅈㅊㅋㅌㅍㅎㅏㅑㅓㅕㅗㅛㅜㅠㅡㅣㄲㄳㄵㄶㄸㄺㄻㄼㄽㄾㄿㅀㅃㅄㅆㅉㅐㅒㅔㅖㅘㅙㅚㅝㅞㅟㅢ";

    // 문자열 길이도 랜덤? 일단 3으로 지정해놨습니다
    const int length = 3;

    // 문자열 생성
    char purestr[length+1];
    for (int i = 0; i < length; i++) {
        purestr[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    purestr[length] = '\0';
    
    return purestr;   
}

//순수문자열을 생성하는 함수 ver2
char *PureStr(){
    
    srand(time(NULL));  // 랜덤 시드 초기화
    //순수문자열 길이를 3으로 지정
    for (int i = 0; i < 3; i++) {
        int type = rand() % 3;  // 0 ~ 2 중 하나의 숫자를 랜덤하게 선택

        switch (type) {
            case 0:  // 숫자 선택
                str[i] = rand() % 10 + '0';
                break;
            case 1:  // 영어 알파벳 선택
                if (rand() % 2 == 0) {
                    str[i] = rand() % 26 + 'a';  // 소문자 선택
                } else {
                    str[i] = rand() % 26 + 'A';  // 대문자 선택
                }
                break;
            case 2:  // 한글 자음 모음 선택
                str[i] = 0xAC00 + rand() % (0xD7A3 - 0xAC00 + 1);
                break;
        }
    }
    str[len] = '\0';  // 문자열 끝에 NULL 문자 추가

    return purestr;
}
