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
        printf("1. ȸ�� ���\n");
        printf("2. ȸ�� �˻�\n");
        printf("3. ȸ�� ���� ����\n");
        printf("4. ȸ�� ����\n");
        printf("5. ��ü ȸ�� ���\n");
        printf("6. ���α׷� ����\n");
        printf("���ڸ� �Է��ϼ��� : ");
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

void registerMember() //ȸ�� ���
{

    member *node = malloc(sizeof(member));
    member *p = head;

    if ((fp = fopen("member.txt", "r+")) == NULL)
    {
        fp = fopen("member.txt", "w+");
    }

    fseek(fp, 0, SEEK_END);

    printf("ȸ�� id�� �Է��ϼ��� : ");
    scanf("%s", node->id);
    printf("ȸ�� �̸��� �Է��ϼ��� : ");
    scanf("%s", node->name);
    getchar();
    printf("ȸ�� �ּҸ� �Է��ϼ��� : ");
    gets(node->address);
    printf("ȸ�� ��ȭ��ȣ�� �Է��ϼ��� : ");
    scanf("%s", node->phonenum);
    node->next = NULL;

    //���Ͽ� �Է�
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = node;

    fprintf(fp, "%s#%s#%s#%s\n", node->id, node->name, node->address, node->phonenum);
    fclose(fp);
}

void searchMember() //ȸ�� �˻�
{
    member *p = head;
    char id[5];

    printf("id�� �Է����ּ��� : ");
    scanf("%s", id);

    //��ũ�帮��Ʈ���� ȸ�� �˻� -> ���
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
        printf("�� id�� ���� ���̵��Դϴ�\n");
    }
}

void modifyMember() //ȸ�� ���� ����
{
    member *p = head;
    char id[5];

    printf("id�� �Է����ּ��� : ");
    scanf("%s", id);

    //��ũ�帮��Ʈ���� ȸ�� �˻�
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
        printf("�� id�� ���� ���̵��Դϴ�\n");
    }
}

void deleteMember() //ȸ�� ����
{
    member *p = head->next;
    member *q = head;
    char id[5];

    printf("id�� �Է��ϼ��� : ");
    scanf("%s", id);

    //��ũ�帮��Ʈ���� ȸ�� �˻� -> ����
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
        printf("�� id�� ���� ���̵��Դϴ�\n");
    }
}

void printMember() //��ü ȸ�� ���
{
    member *p = head;

    //��ũ�帮��Ʈ���� ��ü ȸ�� ���
    while (p->next != NULL)
    {
        p = p->next;
        printf("[%s] [%s] [%s] [%s]\n", p->id, p->name, p->address, p->phonenum);
    }
}

void modify(member *p) //ȸ�� ���� ����(������ ���� �Է� �ޱ�)
{
    member *q = head;

    printf("������ �̸��� �Է��ϼ��� : ");
    scanf("%s", p->name);
    getchar();
    printf("������ �ּҸ� �Է��ϼ��� : ");
    gets(p->address);
    printf("������ ��ȭ��ȣ�� �Է��ϼ��� : ");
    scanf("%s", p->phonenum);
    getchar();

    changeFile();
}

void changeFile() //���Ͽ� ������ ���� �Է�
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
