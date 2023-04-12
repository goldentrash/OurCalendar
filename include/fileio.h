#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <task.h>

void fileDiagnosis(); //���Ἲ�˻� ���н� return -1
Task* readFile();//Task �������� ����
void enrollTask(Task);//���� �߰�
void deleteTask(const char*);//���� �����
int TaskCount();// Task ���� ��Ʈ ��ȯ


//�ֳ׵��� ���Ἲ �˻�� �ʿ��� �ֵ� �� ���н� return  -1 �ֳ׵��� �ּ� ����� ���س��� ���� ���� ����
int check_compatable();//�������� ���� ���� ����
int check_id();//���̵� ����
int check_special(char* date); //��¥ ����1
int check_day(int date); //��¥ ����2
int change_date(char* date); //��¥ ����3
int check_calandr();//��ġ�� ��¥ ����

Task* readfile() {
    // CSV ���� ����
    FILE* csv_file = fopen("data.csv", "r");

    if (csv_file == NULL) {
        csv_file = fopen("data.csv", "w");
    }

    // CSV ���Ͽ��� ������ �б�
    char line[MAX_LINE];
    Task* datas = NULL;
    int i = 0;
    const char* sim = ",";
    while (fgets(line, MAX_LINE, csv_file)) {
        // ��ǥ�� ���е� �����͸� �Ľ��Ͽ� ����ü �ʵ忡 ����
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

        // ����ü �迭�� �߰�
        datas = realloc(datas, (i + 1) * sizeof(Task));
        datas[i] = data;

        i++;
    }

    // CSV ���� �ݱ�
    fclose(csv_file);

    return datas;
} //Task �������� ����


void enrollTask(Task newTask) {//���� �߰�

    FILE* file = fopen("data.csv", "a");

    Task fir = newTask;;

    fprintf(file, "\n%s,%c,%s,%s,%s", fir.id, fir.compatable, fir.startDate, fir.endDate, fir.contents);


    // CSV ���� �ݱ�
    fclose(file);

}

void deleteTask(const char* idA) {//���� ����� ���̵� ������ ���� ������ �ƹ��� ����

    // CSV ���� ����
    FILE* csv_file = fopen("data.csv", "r");

    // CSV ���Ͽ��� ������ �б�
    char line[MAX_LINE];
    Task* datas = NULL;
    int i = 0;
    const char* sim = ",";

    while (fgets(line, MAX_LINE, csv_file)) {
        // ��ǥ�� ���е� �����͸� �Ľ��Ͽ� ����ü �ʵ忡 ����
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

        // ����ü �迭�� �߰�
        datas = realloc(datas, (i + 1) * sizeof(Task));
        datas[i] = data;

        i++;
    }
    fclose(csv_file);


    FILE* file = fopen("data.csv", "w");

    for (int q = 0; q < i - 1; q++) {
        Task row = datas[q];
        if (!(strcmp(row.id, idA) == NULL)) {
            fprintf(file, "%s,%c,%s,%s,%s\n", row.id, row.compatable, row.startDate, row.endDate, row.contents);
        }


    }

    Task end = datas[i - 1];

    if (!(strcmp(end.id, idA) == NULL)) {
        fprintf(file, "%s,%c,%s,%s,%s", end.id, end.compatable, end.startDate, end.endDate, end.contents);
    }

    // CSV ���� �ݱ�
    fclose(file);
}


int TaskCount() { // Task ���� ��Ʈ ��ȯ

    // CSV ���� ����
    FILE* csv_file = fopen("data.csv", "r");

    // CSV ���Ͽ��� ������ �б�
    char line[MAX_LINE];
    Task* datas = NULL;
    int count = 0;

    while (fgets(line, MAX_LINE, csv_file)) {
        // ��ǥ�� ���е� �����͸� �Ľ��Ͽ� ����ü �ʵ忡 ����
        char* field;
        field = strtok(line, "\n");
        count++;
    }
    fclose(csv_file);
    return count;
}



int fileDiagnosis() { //���Ἲ�˻� ���н� return -1

    FILE* csv_file = fopen("data.csv", "r");

    if (csv_file == NULL) {
        csv_file = fopen("data.csv", "w");
    }

    int num_count = 0;
    char line[MAX_LINE];
    int count = 0;
    while (fgets(line, MAX_LINE, csv_file)) {
        // ���� ���� ��� -1 ��ȯ
        if (strlen(line) <= 1)
            return -1;

        int comma = 0;

        for (int j = 0; j < strlen(line); j++) { //��ǥ ���� ����
            if (line[j] == ',') {
                comma++;
            }
        }
        if (comma != 4)//,�� 4���� �ƴϸ� -1
            return -1;


        Task data;

        char* field = strtok(line, ",");
        if (num_count == 0) {
            if (strlen(field) <= 0)
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
        data.contents = _strdup(field);

        count++;
        num_count = 0;

        //��¥ üũ
        if (change_date(data.startDate) == -1)
            return -1;
        if (change_date(data.endDate) == -1)
            return -1;
        if (change_date(data.startDate) > change_date(data.endDate))
            return -1;
    }

    if (check_id() == -1)//���̵� �ߺ� �˻�
        return -1;
    if (check_compatable() == -1)//������ üũ
        return -1;

    if (check_calandr() == -1)//������,��¥ �ߺ��� üũ
        return -1;



    fclose(csv_file);
    return 1;
} //���Ἲ�˻� ���н� return -1

int check_compatable() {

    Task* data = readfile();
    int num = TaskCount();
    for (int i = 0; i < num; i++) {

        if (data[i].compatable == 'N') {}
        else if (data[i].compatable == 'Y') {}
        else
            return -1;

    }
    return 1;

}

int check_id() {

    Task* data = readfile();
    int num = TaskCount();

    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            if (((strcmp(data[i].id, data[j].id) == 0))) {
                return -1; // �ߺ��� ���� ������ -1�� ��ȯ
            }
        }
    }
    return 0;

}

int check_special(char* date) {

    char temp[100];
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
    Task* data = readfile();
    int num = TaskCount();
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            if ((data[i].compatable == 'N') || (data[j].compatable == 'N')) {
                int start_i = change_date(data[i].startDate);
                int end_i = change_date(data[i].endDate);
                int start_j = change_date(data[j].startDate);
                int end_j = change_date(data[j].endDate);
                if ((start_i <= start_j && start_j <= end_i) || (start_i <= end_j && end_j <= end_i) || (start_j <= start_i && start_i <= end_j) || (start_j <= end_i && end_i <= end_j)) {
                    return -1;
                }
            }
        }
    }
    return 1;
}