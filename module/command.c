#include <command.h>
#include <userio.h>
#include <constants.h>
#include <string.h>

// 문자열을 받아서 명령어 종류 판가름
Cmd cmdType(const char * str){
  if(strType(str) == NotStr) return Help;

  char command[INP_LIMIT];
  stepStr(str, 0, PureStr, command);

  if(!strcmp(command, "add")) return Add;
  if(!strcmp(command, "delete")) return Del;
  if(!strcmp(command, "search")) return Search;
  if(!strcmp(command, "quit")) return Quit;

  return Help;
};

// help 명령어 실행
void help(const char * str){};

// add 명령어 실행
void add(const char * str){};

// del 명령어 실행
void del(const char * str){};

// search 명령어 실행
void search(const char * str){
  const ** p[6];
  parseParameters(str, [PureStr, SpaceStr, DateStr, SpaceStr, DateStr, LnBrkChr], p);

};

// 사용자 입력에서 인자를 파싱하고, 그럴 수 없으면 raise exception
// 예시)
// parseParameters("delete abc123\r\n", [PureStr, SpaceStr, PureStr, LnBrkStr], parameters);
// parameters[0]에는 첫 번째 인자가 저장된다.
void parseParameters(const char * usrIpt, const Str * cmdSyntax, const char ** parameters){};