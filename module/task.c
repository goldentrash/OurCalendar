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
void printTask(Task task){
    
    printf("%s/t%c %s~%s\n%s\n",task.id,task.compatable,task.startDate,task.endDate,task.contents);

};

//일정 받고 해당하는 일정 반환
Task findTask(Task *, const *){



};

// 일정 생성 (id 자동 생성)
// 일정 구조체의 주소를 반환하는 함수 버전
void mkTask(char compatable, char * startDate, char * endDate, char * contents){
    
    Task* task=(Task*)malloc(sizeof(Task));
    task->compatable=compatable;
    task->startDate=starDate;
    task->endDate=endDate;
    taxk->contents=contents;
    task->id= //순수문자열(한글, 알파벳, 숫자)

};

//일정 구조체 그 자체를 반환하는 함수 버전
Task mkTask(char compatable, char * startDate, char * endDate, char * contents){
    
    Task task;
    task.compatable=compatable;
    task.startDate=starDate;
    task.endDate=endDate;
    taxk.contents=contents;
    task.id= //순수문자열(한글, 알파벳, 숫자)
    return task;

};


// 동일한 일정인지 확인 (id 기준) -> 혹시라도 id가 같을 때를 대비하는 함수일까요?
bool isEqualTask(Task a, Task b){ 
    
    if(strcmp(a.id,b.id)==0)
    return true;
    else
    return false;
    
};

// 등록된 일정인지 확인
bool isEnrolledTask(char * id){ 
    
    Task task=readLn();
    if(strcmp(id,task.id)==0)
    return true;
    else
    return false;    
}

// 일정이 겹치는지 확인
bool isOverlapped(Task a, Task b){
    
    if(toInteger(a.startDate)>toInteger(b.endDate) || toInteger(a.endDate)<toInteger(b.startDate))
    return true;
    else
    return false;    
}

// 일정 유효 검사, 유효한 일정이 아니면 raise exception -> 언제 쓰는 함수인지?? add의 첫번째 입력?, delete의 첫번째 입력?
void taskDiagnosis(Task task){

    if(task.id&&task.compatable&&task.starDate&&task.endDate&&task.contents&&toInteger(task.startDate)>=toInteger(task.endDate))

    else
    raise exception;


};

//일정의 날짜문자열을 정수로 변환하는 함수
int toInteger(char *Date){
    
    int result = 0;

    for (int i = 0; i < strlen(Date); i++) {
        if (isdigit(Date[i])) {
            result = result * 10 + (Date[i] - '0');
        }
    }

    return result;
}
