//애네들은 무결성 검사시 필요한 애들 다 실패시 return  -1 애네들은 주석 제대로 안해놓고 나만 쓸거 같음
int check_compatable();//진리값에 들어가는 문자 점검
int check_id();//아이디 점검
int check_special(char* date); //날짜 점검1
int check_day(int date); //날짜 점검2
int change_date(char* date); //날짜 점검3
int check_calandr();//겹치면 날짜 점검

int TaskCount();// 문자열 갯수 세기

TaskList readfile() {
    // CSV 파일 열기
    FILE* csv_file = fopen("data.csv", "r");


    // CSV 파일에서 데이터 읽기
    char line[1000];
    Task* datas = NULL;
    int i = 0;
    const char* sim = ",";
    while (fgets(line, 1000, csv_file)) {
        // 쉼표로 구분된 데이터를 파싱하여 구조체 필드에 저장
        char* field;
        Task data;
        field = strtok(line, sim);
        data.id = _strdup(field);

        field = strtok(NULL, sim);
        data.compatable = field[0];

        field = strtok(NULL, sim);
        data.startDate = _strdup(field);

        field = strtok(NULL, sim);
        data.endDate = _strdup(field);

        field = strtok(NULL, "\n");
        data.contents = _strdup(field);

        // 구조체 배열에 추가
        datas = realloc(datas, (i + 1) * sizeof(Task));
        datas[i] = data;

        i++;
    }

    // CSV 파일 닫기
    fclose(csv_file);

    TaskList datalink;
    datalink.tasks = datas;
    datalink.count = TaskCount();

    return datalink;
}


void enrollTask(Task newTask) {

    FILE* file = fopen("data.csv", "a");

    Task fir = newTask;;

    if (TaskCount() == 0)
        fprintf(file, "%s,%c,%s,%s,%s", fir.id, fir.compatable, fir.startDate, fir.endDate, fir.contents);
    else
        fprintf(file, "\n%s,%c,%s,%s,%s", fir.id, fir.compatable, fir.startDate, fir.endDate, fir.contents);

    // CSV 파일 닫기
    fclose(file);

}


void deleteTask(const char* idA) {

    // CSV 파일 열기
    FILE* csv_file = fopen("data.csv", "r");

    // CSV 파일에서 데이터 읽기
    char line[1000];
    Task* datas = NULL;
    int i = 0;
    const char* sim = ",";

    while (fgets(line, 1000, csv_file)) {
        // 쉼표로 구분된 데이터를 파싱하여 구조체 필드에 저장
        char* field;
        Task data;
        field = strtok(line, sim);
        data.id = _strdup(field);

        field = strtok(NULL, sim);
        data.compatable = field[0];

        field = strtok(NULL, sim);
        data.startDate = _strdup(field);

        field = strtok(NULL, sim);
        data.endDate = _strdup(field);

        field = strtok(NULL, "\n");
        data.contents = _strdup(field);

        // 구조체 배열에 추가
        datas = realloc(datas, (i + 1) * sizeof(Task));
        datas[i] = data;

        i++;
    }
    fclose(csv_file);


    FILE* file = fopen("data.csv", "w");

    for (int q = 0; q < i - 1; q++) {
        Task row = datas[q];
        if (!(strcmp(row.id, idA) == 0)) {
            fprintf(file, "%s,%c,%s,%s,%s\n", row.id, row.compatable, row.startDate, row.endDate, row.contents);
        }


    }

    Task end = datas[i - 1];

    if (!(strcmp(end.id, idA) == 0)) {
        fprintf(file, "%s,%c,%s,%s,%s", end.id, end.compatable, end.startDate, end.endDate, end.contents);
    }

    // CSV 파일 닫기
    fclose(file);
}

int TaskCount() {

    // CSV 파일 열기
    FILE* csv_file = fopen("data.csv", "r");

    // CSV 파일에서 데이터 읽기
    char line[1000];
    Task* datas = NULL;
    int count = 0;

    while (fgets(line, 1000, csv_file)) {
        // 쉼표로 구분된 데이터를 파싱하여 구조체 필드에 저장
        char* field;
        field = strtok(line, "\n");
        count++;
    }
    fclose(csv_file);
    return count;
}

int fileDiagnosis() {

    FILE* csv_file = fopen("data.csv", "r");

    if (csv_file == NULL) {
        csv_file = fopen("data.csv", "w");
    }

    int num_count = 0;
    char line[1000];
    int count = 0;
    while (fgets(line, 1000, csv_file)) {
        // 공백 줄인 경우 -1 반환
        if (strlen(line) <= 1)
            return -1;

        int comma = 0;

        for (int j = 0; j < strlen(line); j++) { //쉼표 갯수 세기
            if (line[j] == ',') {
                comma++;
            }
        }
        if (comma != 4)//,가 4개가 아니면 -1
            return -1;


        Task data;

        char* field = strtok(line, ",");
        if (num_count == 0) {
            if (strlen(field) <= 0 || strlen(field) > 100)
                return -1;
        } num_count++;
        data.id = _strdup(field);

        field = strtok(NULL, ",");
        if (num_count == 1) {
            if (strlen(field) != 1)
                return -1;
        } num_count++;

        data.compatable = field[0];

        field = strtok(NULL, ",");
        if (num_count == 2) {
            if (strlen(field) != 10)
                return -1;
        } num_count++;

        data.startDate = _strdup(field);

        field = strtok(NULL, ",");
        if (num_count == 3) {
            if (strlen(field) != 10)
                return -1;
        } num_count++;
        data.endDate = _strdup(field);

        field = strtok(NULL, ",");
        if (strlen(field) > 100)
            return -1;
        data.contents = _strdup(field);

        count++;
        num_count = 0;

        //날짜 체크
        if (change_date(data.startDate) == -1)
            return -1;
        if (change_date(data.endDate) == -1)
            return -1;
        if (change_date(data.startDate) > change_date(data.endDate))
            return -1;
    }

    if (check_id() == -1)
        return -1;

    if (check_compatable() == -1)
        return -1;

    if (check_calandr() == -1)
        return -1;


    fclose(csv_file);
    return 1;
}

int check_compatable() {

    TaskList data = readfile();
    int num = TaskCount();
    for (int i = 0; i < num; i++) {

        if (data.tasks[i].compatable == 'N') {}
        else if (data.tasks[i].compatable == 'Y') {}
        else
            return -1;

    }
    return 1;

}

int check_id() {

    TaskList data = readfile();
    int num = TaskCount();

    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            if (((strcmp(data.tasks[i].id, data.tasks[j].id) == 0))) {
                return -1; // 중복된 값이 있으면 -1을 반환
            }
        }
    }
    return 0;

}

int check_special(char* date) {

    int i, j = 0;
    for (i = 0; i < strlen(date); i++) {
        if (date[i] == '-' || (date[i] >= '0' && date[i] <= '9')) {

        }
        else {
            return -1;
        }
    }
    if (strlen(date) == 10) {
        if (date[4] != '-') {
            return -1;
        }
    }
    return 1;

}

int check_day(int date) {
    int c1 = (date / 100) % 100;
    int c2 = date % 100;
    int c3 = date / 10000;


    if (date < 20000101 || 20401232 < date) {
        return -1;
    }
    if (c1 > 12) {
        return -1;
    }

    if (c1 == 0 || c2 == 0) {
        return -1;
    }

    if (c1 == 1 || c1 == 3 || c1 == 5 || c1 == 7 || c1 == 8 || c1 == 10 || c1 == 12) {
        if (32 <= c2 || c2 < 0) {
            return -1;
        }
    }
    else  if (c1 == 4 || c1 == 6 || c1 == 9 || c1 == 11) {
        if (31 <= c2 || c2 < 0) {
            return -1;
        }
    }
    else if (c1 == 2) {
        if ((c3 % 4 == 0 && c3 % 100 != 0) || c3 % 400 == 0) {
            if (30 <= c2 || c2 < 0) {
                return -1;
            }
        }
        else {
            if (29 <= c2 || c2 < 0) {
                return -1;
            }
        }
    }
    return 1;

}
int change_date(char* date) {

    if (check_special(date) == -1)
        return -1;
    else {
        char temp[100];
        int i, j = 0;

        for (i = 0; i < strlen(date); i++) {
            if (date[i] >= '0' && date[i] <= '9') {
                temp[j] = date[i];
                j++;
            }
        }
        if (check_day(atoi(temp)) == -1)
            return -1;
        else
            return atoi(temp);
    }
}

int check_calandr() {
    TaskList data = readfile();
    int num = TaskCount();
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            if ((data.tasks[i].compatable == 'N') || data.tasks[j].compatable == 'N') {
                int start_i = change_date(data.tasks[i].startDate);
                int end_i = change_date(data.tasks[i].endDate);
                int start_j = change_date(data.tasks[j].startDate);
                int end_j = change_date(data.tasks[j].endDate);
                if ((start_i <= start_j && start_j <= end_i) || (start_i <= end_j && end_j <= end_i) || (start_j <= start_i && start_i <= end_j) || (start_j <= end_i && end_i <= end_j)) {
                    return -1;
                }
            }
        }
    }
    return 1;
}