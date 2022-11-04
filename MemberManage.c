#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct member
{
    char id[5];
    char name[30];
    char address[100];
    char phonenum[15];
    struct member *next;
} member;

void registerMember();
void searchMember();
void modifyMember();
void deleteMember();
void printMember();
void modify(member *p);
void changeFile();

member *head;
FILE *fp;

int main()
{
    head = malloc(sizeof(member));
    head->next = NULL;
    member *p = head;
    int menu;

    if ((fp = fopen("member.txt", "r+")) == NULL)
    {
        fp = fopen("member.txt", "w+");
    }

    while (1)
    {
        member *node = malloc(sizeof(member));
        node->id[0] = '\0';
        node->name[0] = '\0';
        node->address[0] = '\0';
        node->phonenum[0] = '\0';

        fscanf(fp, "%[^#\0]s", node->id);
        if (node->id[0] == '\0')
        {
            break;
        }
        fseek(fp, 1, SEEK_CUR);
        fscanf(fp, "%[^#]s", node->name);
        fseek(fp, 1, SEEK_CUR);
        fscanf(fp, "%[^#]s", node->address);
        fseek(fp, 1, SEEK_CUR);
        fscanf(fp, "%s", node->phonenum);
        fgetc(fp);

        p->next = node;
        node->next = NULL;
        p = p->next;

        if (feof(fp) != 0)
        {
            break;
        }
    }

    fclose(fp);

    while (1)
    {
        printf("\n");
        printf("1. 회원 등록\n");
        printf("2. 회원 검색\n");
        printf("3. 회원 정보 수정\n");
        printf("4. 회원 삭제\n");
        printf("5. 전체 회원 출력\n");
        printf("6. 프로그램 종료\n");
        printf("숫자를 입력하세요 : ");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            registerMember();
            break;

        case 2:
            searchMember();
            break;

        case 3:
            modifyMember();
            break;

        case 4:
            deleteMember();
            break;

        case 5:
            printMember();
            break;

        case 6:
            exit(0);
            break;
        }
    }
}

void registerMember() //회원 등록
{

    member *node = malloc(sizeof(member));
    member *p = head;

    if ((fp = fopen("member.txt", "r+")) == NULL)
    {
        fp = fopen("member.txt", "w+");
    }

    fseek(fp, 0, SEEK_END);

    printf("회원 id를 입력하세요 : ");
    scanf("%s", node->id);
    printf("회원 이름을 입력하세요 : ");
    scanf("%s", node->name);
    getchar();
    printf("회원 주소를 입력하세요 : ");
    gets(node->address);
    printf("회원 전화번호를 입력하세요 : ");
    scanf("%s", node->phonenum);
    node->next = NULL;

    //파일에 입력
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = node;

    fprintf(fp, "%s#%s#%s#%s\n", node->id, node->name, node->address, node->phonenum);
    fclose(fp);
}

void searchMember() //회원 검색
{
    member *p = head;
    char id[5];

    printf("id를 입력해주세요 : ");
    scanf("%s", id);

    //링크드리스트에서 회원 검색 -> 출력
    while (p->next != NULL)
    {
        p = p->next;

        if (strcmp(p->id, id) == 0)
        {
            printf("%s %s %s %s\n", p->id, p->name, p->address, p->phonenum);
            break;
        }
    }
    if (p == NULL)
    {
        printf("이 id는 없는 아이디입니다\n");
    }
}

void modifyMember() //회원 정보 수정
{
    member *p = head;
    char id[5];

    printf("id를 입력해주세요 : ");
    scanf("%s", id);

    //링크드리스트에서 회원 검색
    while (p->next != NULL)
    {
        p = p->next;

        if (strcmp(p->id, id) == 0)
        {
            modify(p);
            break;
        }
    }
    if (p == NULL)
    {
        printf("이 id는 없는 아이디입니다\n");
    }
}

void deleteMember() //회원 삭제
{
    member *p = head->next;
    member *q = head;
    char id[5];

    printf("id를 입력하세요 : ");
    scanf("%s", id);

    //링크드리스트에서 회원 검색 -> 삭제
    while (p != NULL)
    {
        if (strcmp(p->id, id) == 0)
        {
            q->next = p->next;
            free(p);
            changeFile();

            break;
        }

        p = p->next;
        q = q->next;
    }
    if (p == NULL)
    {
        printf("이 id는 없는 아이디입니다\n");
    }
}

void printMember() //전체 회원 출력
{
    member *p = head;

    //링크드리스트에서 전체 회원 출력
    while (p->next != NULL)
    {
        p = p->next;
        printf("[%s] [%s] [%s] [%s]\n", p->id, p->name, p->address, p->phonenum);
    }
}

void modify(member *p) //회원 정보 수정(수정할 정보 입력 받기)
{
    member *q = head;

    printf("수정할 이름을 입력하세요 : ");
    scanf("%s", p->name);
    getchar();
    printf("수정할 주소를 입력하세요 : ");
    gets(p->address);
    printf("수정할 전화번호를 입력하세요 : ");
    scanf("%s", p->phonenum);
    getchar();

    changeFile();
}

void changeFile() //파일에 수정된 정보 입력
{
    member *p = head;

    fp = fopen("member.txt", "w");
    while (p->next != NULL)
    {
        p = p->next;
        fprintf(fp, "%s#%s#%s#%s\n", p->id, p->name, p->address, p->phonenum);
    }
    fclose(fp);
}
