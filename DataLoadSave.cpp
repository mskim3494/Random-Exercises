// 김민수

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>

typedef struct PersonalInfo{
    char* name;
    int age;
} PI;

typedef struct SListNode{
    PI Data;
    struct SListNode *pNext;
} NODE;

NODE *pHead = NULL;
int Count = 0;

int Menu();
void AddData(PI data);
void DisplayData();
void DeleteData(char* toDelete);
void RemoveAllData();
void SaveDataToFile();
void LoadDataFromFile();

int main()
{
    int Select;
    char buffer[20];

    memset(buffer, '\0', 20);
    
    while(1){
        Select = Menu();
        if(Select == 1){
            int Temp;
            PI tmp;
            printf("이름 입력: ");
            scanf("%s", buffer);
            printf("나이 입력: ");
            scanf("%d", &Temp);
            tmp.name = strdup(buffer);
            tmp.age = Temp;
            AddData(tmp);
            Count++;
            memset(buffer, '\0',20);
        }
        else if(Select == 2){
            DisplayData();
        }
        else if(Select == 3){
            int Temp;
            printf("삭제 항목: ");
            scanf("%s", buffer);
            DeleteData(buffer);
            memset(buffer, '\0',20);
        }
        else if(Select == 4){
            RemoveAllData();
        }
        else if(Select == 5){
            SaveDataToFile();
        }
        else if(Select == 6){
            LoadDataFromFile();
        }
        else if(Select == 7) break;
    }
    
    RemoveAllData();
    
    return 0;
}

int Menu()
{
    printf("-----------------------------------\n");
    printf("   << 싱글 링크드 리스트 >>\n");
    printf("-----------------------------------\n");
    printf("   1-추가\n");
    printf("   2-출력\n");
    printf("   3-검색 삭제\n");
    printf("   4-일괄 삭제\n");
    printf("-----------------------------------\n");
    printf("   5-파일 저장\n");
    printf("   6-파일 읽기\n");
    printf("-----------------------------------\n");
    printf("   7-종료\n");
    printf("-----------------------------------\n");
    printf("메뉴 선택 =>");
    
    int Select;
    scanf("%d", &Select);
    
    return Select;
}

void AddData(PI data)
{
    NODE *pNode = (NODE *)malloc(sizeof(NODE));
    pNode->Data = data;
    pNode->pNext = NULL;
    
    if(pHead == NULL) pHead = pNode;
    else {
        NODE *p = pHead;
        while(p->pNext != NULL) p = p->pNext;
        
        p->pNext = pNode;
    }
}

void DisplayData()
{
    NODE* p = pHead;
    printf("이름    나이\n");
    while(p != NULL){
        printf("%s   %d\n", p->Data.name, p->Data.age);
        p = p->pNext;
    }
}

void DeleteData(char* toDelete)
{
    NODE *curr, *prev;
    curr = pHead;
    
    if (!strcmp(curr->Data.name,toDelete)) {
        pHead = pHead->pNext;
        free(curr);
        Count--;
    } else {
        prev = curr;
        curr = curr->pNext;
        while(curr != NULL) {
            if(!strcmp(curr->Data.name,toDelete)) {
                prev->pNext = curr->pNext;
                free(curr->Data.name);
                free(curr);
                Count--;
                return;
            } else {
                prev = curr;
                curr = curr->pNext;
            }
        } printf("선택 항목이 없습니다\n");
    }
}

void RemoveAllData()
{
    NODE* p = pHead;
    
    if (!p){
        return;
    }
    NODE* next = p->pNext;;
    while (p) {
        if (!next) {
            free(p->Data.name);
            free(p);
            break;
        } else {
            free(p->Data.name);
            free(p);
            p = next;
            next = p->pNext;
        }
    }
    pHead = NULL;
    Count = 0;
}

// ----- 선생님 코드 ------
// ---------------------

void SaveDataToFile()
{
    if(!pHead)
        return;
    
    NODE *pNode = pHead;
    FILE *pFile = fopen ("data.dat", "wb");
    int len;
    
    if(pFile != NULL){
        fwrite(&Count, sizeof(int), 1, pFile);
        
        while(pNode != NULL){
            len = strlen(pNode->Data.name)+1;
            fwrite(&len, sizeof(int), 1, pFile);
            fwrite(pNode->Data.name, sizeof(char), len, pFile);
            fwrite(&pNode->Data.age, sizeof(int), 1, pFile);
            pNode = pNode->pNext;
        }
        fclose(pFile);
    } else {
        printf("파일 생성에 실패했습니다!!\n");
    }
}

void LoadDataFromFile()
{
    RemoveAllData();
    
    FILE *pFile = fopen ("data.dat", "rb");
    
    if(pFile != NULL){
        fread(&Count, sizeof(int), 1, pFile);
        printf("%d", Count);
        int i, age, len;
        char buffer[20];
        PI Temp;
        
        memset(buffer, 0, 20);
        
        for(i=0;i<Count; i++){
            fread(&len, sizeof(int), 1, pFile);
            fread(&buffer, sizeof(char), len, pFile);
            fread(&age, sizeof(int), 1, pFile);
            Temp.name = strdup(buffer);
            Temp.age = age;
            AddData(Temp);
            memset(buffer, 0, 20);
        }
        fclose(pFile);
    } else {
        printf("파일 생성에 실패했습니다!!\n");
    }
}

// -------- 개인 코드 -------
// ------------------------

/*
void SaveDataToFile()
{
    FILE* file = fopen("data.txt", "w");
    NODE* curr = pHead;
    
    while (curr) {
        fprintf(file, "%s\n%d\n", curr->Data.name, curr->Data.age);
        curr = curr->pNext;
    }
    fclose (file);
    printf("성공적으로 저장 되었습니다\n");
}


void LoadDataFromFile()
{
    FILE* file = fopen("data.txt", "r");
    char buffer[24];
    char name[20];
    int i, age, len;
    unsigned check = 0; // 0 for name and 1 for age
    
    memset(buffer, '\0', 24);
    age = 0;
    
    if (pHead)
        RemoveAllData();
    
    while (fgets(buffer, sizeof(buffer), file)){
        if(check == 0){
            strncpy(name, buffer, strlen(buffer)-1);
            check = 1;
        } else if (check == 1){
            len = strlen(buffer)-1;
            for(i=0;i<len;i++){
                age += (buffer[i]-48) * pow(10, len-1);
            }
            PI tmp;
            tmp.name = strdup(name);
            tmp.age = age;
            AddData(tmp);
            age = 0;
            check = 0;
        }
    }
}
*/

