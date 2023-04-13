#include "task.h"
#include "fileio.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct
{
    char *id;
    char compatable;
    char *startDate;
    char *endDate;
    char *contents;
} Task;

typedef struct {
    Task* tasks;
    int count;
} TaskList;

char *pureStr();//순수문자열 생성

// 일정 배열을 terminal에 출력
void printTasks(TaskList taskList){
    for(int i=0;i<taskList.count;i++)
    printf("%s/t%c %s~%s\n%s\n",taskList.tasks[i].id,taskList.tasks[i].compatable,taskList.tasks[i].startDate,taskList.tasks[i].endDate,taskList.tasks[i].contents);
};


// 일정 생성 (id 자동 생성)
Task mkTask(char compatable, char * startDate, char * endDate, char * contents){
    Task task;
    task.compatable=compatable;
    task.startDate=starDate;
    task.endDate=endDate;
    taxk.contents=contents;
    task.id= pureStr();//길이 2의 순수문자열(한글, 알파벳, 숫자)
    return task;
};


// 동일한 일정인지 확인 (id 기준)
int isEqualTask(Task a, Task b){ 
    if(strcmp(a.id,b.id)==0)
    return 1;
    else
    return -1;
};


//등록된 일정인지 확인 -> 삭제할 때 찾는 함수
int isEnrolledTask(char * id){
    Task* alltaskarray=readFile().tasks;
    for(int i=0;i<readFile().count;i++){
        if(isEqualTask(alltaskarray[i],id)){
            free(alltaskarray);
            return 1;
        }
    }
    free(alltaskarray);
    return -1;
}


// 일정이 겹치는지 확인
int isOverlapped(Task a, Task b){
    if((strcmp(a.startDate,b.endDate) <=0) && (strcmp(a.endDate,b.startDate)>=0))
    return 1;
    else
    return -1;    
};


//입력한 기간에 시작하는 모든 등록된 일정 반환 
TaskList findTasks(char* startDate, char* endDate) {
    int n = 0;
    Task* alltaskarray = readFile().tasks;
    for (int i = 0; i < readFile().count; i++) {
        if ((strcmp(startDate, alltaskarray[i].startDate) <= 0) &&
            (strcmp(alltaskarray[i].startDate, endDate) <= 0))
            n++;
    }

    if (n == 0) {
        free(alltaskarray);
        return (TaskList){ .tasks = NULL, .count = 0 };
    }

    Task* taskarray = (Task*)malloc(sizeof(Task) * n);

    int j = 0;
    for (int i = 0; i < readFile().count; i++) {
        if ((strcmp(startDate, alltaskarray[i].startDate) <= 0) &&
            (strcmp(alltaskarray[i].startDate, endDate) <= 0)) {
            taskarray[j] = alltaskarray[i];
            j++;
        }
    }

    TaskList taskList = { .tasks = taskarray, .count = n };
    free(alltaskarray);
    return taskList;
}


//입력한 기간과 겹치는 등록된 일정을 찾는 함수
TaskList findOverlappedTask(char* startDate, char* endDate) {
    int n = 0;
    Task* alltaskarray = readFile().tasks;
    for(int i = 0; i < readFile().count; i++){
        if(strcmp(startDate,alltaskarray[i].endDate) <= 0 && strcmp(endDate,alltaskarray[i].startDate) >= 0)//함수로 대체
            n++;
    }

    if (n == 0) {
        free(alltaskarray);
        return (TaskList){ .tasks = NULL, .count = 0 };
    }

    Task* taskarray = (Task*) malloc(sizeof(Task) * n);

    int j = 0;
    for(int i = 0; i < readFile().count; i++){
        if(strcmp(startDate,alltaskarray[i].endDate) <= 0 && strcmp(endDate,alltaskarray[i].startDate) >= 0){ // 함수로 대체
            taskarray[j] = alltaskarray[i];
            j++;
        }
    }
   
    TaskList taskList = { .tasks = taskarray, .count = n };
    free(alltaskarray);
    return taskList;
}

//순수문자열을 생성하는 함수 
char *pureStr(){
    
    char* str = (char*)malloc(sizeof(char) * 3); // 2글자 + NULL 문자
    
    srand(time(NULL));  // 랜덤 시드 초기화
    
    for (int i = 0; i < 2; i++) {
        int type = rand() % 3;  // 0 ~ 2 중 하나의 숫자를 랜덤하게 선택

        switch (type) {
            case 0:  // 숫자 선택
                purestr[i] = rand() % 10 + '0';
                break;
            case 1:  // 영어 알파벳 선택
                if (rand() % 2 == 0) {
                    puestr[i] = rand() % 26 + 'a';  // 소문자 선택
                } else {
                    purestr[i] = rand() % 26 + 'A';  // 대문자 선택
                }
                break;
            case 2:  // 한글 선택
                if(rand()%4==0)
                
                purestr[i] = 0xAC00 + rand() % (0xD7A3 - 0xAC00 + 1);  //한글 자음, 모음의 조합 선택
                break;
        }
    }
    purestr[2] = '\0';  // 문자열 끝에 NULL 문자 추가

    return purestr;
}

