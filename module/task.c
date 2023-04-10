#include <task.h>

// 일정을 terminal에 출력 (userio/printSysMsg활용)
void printTask(Task task){};

// 일정 생성 (id 자동 생성)
void mkTask(char compatable, char * startDate, char * endDate, char * contents){}

// 동일한 일정인지 확인 (id 기준)
bool isEqualTask(Task a, Task b){ return true;};

// 등록된 일정인지 확인
bool isEnrolledTask(char * id){ return true;}

// 일정이 겹치는지 확인
bool isOverlapped(Task a, Task b){return true;}

// 일정 유효 검사, 유효한 일정이 아니면 raise exception
void taskDiagnosis(Task task){};
