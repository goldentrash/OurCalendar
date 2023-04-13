#include <task.h>

void fileDiagnosis(); //무결성검사 실패시 return -1
Task* readFile();//Task 동적으로 저장
void enrollTask(Task);//파일 추가
void deleteTask(const char*);//파일 지우기
int taskCount();// Task 갯수 인트 반환
int fileDiagnosis();
TaskList readFile();
void enrollTask(Task);
void deleteTask(const char *);

