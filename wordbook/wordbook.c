#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

typedef struct word
{
    struct word *next;
    char english[30];
    char korean[30];
} word;

word *head;
FILE *fp;
int count = 0;

void inputWord();
void searchWord();
void removeWord();
void printWord();
void hangman();
void printHangman(int i);

int main()
{

    head = malloc(sizeof(word));
    head->next = NULL;
    word *p = head;

    // words.txt ?????? ?????? ???? ?????? ???????
    if ((fp = fopen("words.txt", "r+")) == NULL)
    {
        fp = fopen("words.txt", "w+");
    }

    // words.txt?? ??? ??? ?????????? ????
    while (feof(fp) == 0)
    {
        word *node = malloc(sizeof(word));
        fscanf(fp, "%s", node->english);
        fscanf(fp, "%s", node->korean);
        p->next = node;
        node->next = NULL;
        p = p->next;

        count++;
    }

    count--;
    while (1)
    {
        //????? ??????? ????? ????????
        int num = -1;

        printf("\n");
        printf("=======menu=======\n");
        printf("1. ??? ???\n");
        printf("2. ??? ???\n");
        printf("3. ??? ????\n");
        printf("4. ??? ???\n");
        printf("5. ??? ????\n");
        printf("6. ??????? ????\n");
        printf("==================\n");

        printf("????? ???????? :");
        scanf("%d", &num);
        getchar();

        //?? ????? ?????? ????? ????????
        switch (num)
        {
        case 1:
            inputWord();
            break;

        case 2:
            searchWord();
            break;

        case 3:
            removeWord();
            break;

        case 4:
            printWord();
            break;

        case 5:
            hangman();
            break;

        case 6:
            p = head->next;
            while (p != NULL)
            {
                word *next = p->next;
                free(p);
                p = next;
            }
            exit(0);
            break;

        default:
            printf("1-6 ?????? ????? ??????????\n");
        }
    }
}

void inputWord()
{

    word *node = malloc(sizeof(word));
    node->next = NULL;
    word *p = head;

    //?????? ???? ????????
    printf("????? ??? :");
    scanf("%s", node->english);
    printf("??? ?? ??? :");
    scanf("%s", node->korean);

    //?????? ??? words.txt?? ??????
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = node;

    fprintf(fp, "%s %s\n", node->english, node->korean);
    fflush(fp);

    count++;
}

void searchWord()
{
    word *p = head->next;
    char input[30];

    //????? ????????
    printf("????? ??? :");
    scanf("%s", input);

    //????? ??? ????? ??? ?? ???? ????, ????? ????????? ??????
    while (p != NULL)
    {
        if (strcmp(p->english, input) == 0)
        {
            printf("%s %s\n", p->english, p->korean);
            break;
        }
        p = p->next;
    }
    if (p == NULL)
    {
        printf("?????? ???? ???????\n");
    }
}

void removeWord()
{
    word *p = head->next;
    word *front = head;
    word *q;
    char input[30];
    char c;

    //????? ????????
    printf("????? ??? :");
    scanf("%s", input);
    getchar();

    while (p != NULL)
    {
        //????? ????? ??????
        if (strcmp(p->english, input) == 0)
        {
            //??? ?????? ?????? ??????
            printf("??? ?????????????? (Y/N)\n");
            c = getchar();

            //??? ???????? ???
            if (c == 'Y' || 'y')
            {
                //???????????? ???????
                front->next = p->next;
                free(p);
                count--;

                //?????? ??? ??? ?? ?? ?????????? ??? ??? ??????
                fclose(fp);
                fp = fopen("words.txt", "w+");

                q = head->next;
                while (q->next != NULL)
                {
                    fprintf(fp, "%s %s\n", q->english, q->korean);
                    q = q->next;
                }
                printf("??? ??????????\n");
                break;
                //??? ???????? ?????? ??? ??? ?????? ??????
            }
            else if (c == 'N' || 'n')
            {
                printf("??? ?????? ?????????\n");
                // Y ??? N?? ????? ??? ?????? ??????
            }
            else
            {
                printf("Y ??? N???? ????? ?????\n");
            }
        }
        p = p->next;
        front = front->next;
    }
    //????? ??? ?????? ????????? ??????
    if (p == NULL)
    {
        printf("?????? ???? ???????\n");
    }
}

void printWord()
{
    word *p = head->next;
    int menu;
    char c;

    //????? ????????
    printf("1. ??????? 2. ??????\n");
    printf("????? ???????? :");
    scanf("%d", &menu);
    getchar();

    //???????
    if (menu == 1)
    {
        //??????? ????????
        printf("????? ??? :");
        scanf("%c", &c);

        //??????? ????????? ??????? ??? ????? ?????? ?? ???? ???? ??????
        while (p != NULL)
        {
            if (p->english[0] == c)
            {
                printf("%s %s\n", p->english, p->korean);
            }
            p = p->next;
        }
    }
    //??????
    else if (menu == 2)
    {
        //?????????? ??? ???? ???? ??????
        while (p->next != NULL)
        {
            printf("%s %s\n", p->english, p->korean);
            p = p->next;
        }
    }
}

void hangman()
{
    int random;
    word *p = head;
    char quizWord[30];
    char input;
    bool check[30] = {
        0,
    };
    int correct = 0;
    int wrong = 0;

    //???????? ??? ?????? ????? ????? ??????
    srand((int)time(NULL));
    random = (int)rand() % count + 1;

    //?????? ????? ???????? P?? ???? quizword?? ?? p?? ????? ?????? ????? ??????
    for (int i = 0; i < random; i++)
    {
        p = p->next;
    }
    strcpy(quizWord, p->english);

    //??????? ????? ??????? _?? ??????
    printf("\n");
    for (int i = 0; i < strlen(quizWord); i++)
    {
        printf("_ ");
    }
    printf("\n\n");

    while (1)
    {
        bool flag = 0;

        //??????? ????????
        printf("??????? ???????? :");
        scanf("%c", &input);
        getchar();

        //?? ??????? ??? ????? ?????? ????? worng ?????? 1?? ?????
        for (int i = 0; i < strlen(quizWord); i++)
        {

            if (quizWord[i] == input)
            {
                check[i] = 1;
                correct++;
                flag = 1;
            }
        }
        if (flag == 0)
            wrong++;
        printHangman(wrong);
        if (wrong == 6)
        {
            printf("\n?????? %s????\n", quizWord);
            break;
        }

        //??????? ??? ????? ??????
        printf("\n");
        for (int i = 0; i < strlen(quizWord); i++)
        {
            if (check[i])
            {
                printf("%c ", quizWord[i]);
            }
            else
            {
                printf("_ ");
            }
        }
        printf("\n\n");

        //?? ?????? ????
        if (correct == strlen(quizWord))
        {
            printf("????????!\n");
            break;
        }
    }
}

void printHangman(int i)
{
    switch (i)
    {

    case 1:
        printf("\n\n\n_________________\n");
        break;

    case 2:
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("_________________\n");
        break;

    case 3:
        printf("_________________\n");
        printf("|                |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("_________________\n");
        break;

    case 4:
        printf("_________________\n");
        printf("|                |\n");
        printf("O                |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("_________________\n");
        break;

    case 5:
        printf("_________________\n");
        printf("|                |\n");
        printf("O                |\n");
        printf("T                |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("_________________\n");
        break;

    case 6:
        printf("_________________\n");
        printf("|                |\n");
        printf("O                |\n");
        printf("T                |\n");
        printf("??               |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("                 |\n");
        printf("_________________\n");
        break;
    }
}
