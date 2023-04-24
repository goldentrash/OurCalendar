#include <userio.h>
#include <command.h>
#include <constants.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fileio.h>

int main()
{
    if (fileDiagnosis() == -1)
        exit(1);

    char usrIpt[INP_LIMIT];
    while (true)
    {
        getUsrIpt(usrIpt);

        switch (cmdType(usrIpt))
        {
        case Add:
            add(usrIpt);
            break;
        case Del:
            del(usrIpt);
            break;
        case Search:
            search(usrIpt);
            break;
        case Quit:
            return 0;
        case Help:
        default:
            help(usrIpt);
            break;
        }
    }
    return 0;
}
