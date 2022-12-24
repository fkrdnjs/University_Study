#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int count = 0;                                          //첫 번째 트리인지를 판별하는 전역변수

typedef struct tree {                                   //트리 구조체
    char elem[101];                                     //질문과 정답, 왼쪽 자식, 오른쪽 자식을 원소로 가짐.   
    struct tree* left;
    struct tree* right;
    struct tree* parent;                                //부모 트리의 주소 저장하는 원소
}tree;

tree* newtree() {                                       //새로운 트리 선언하는 함수

    tree* new;

    new = (tree*)malloc(sizeof(tree));                  //새로운 트리 동적할당
    if (new == NULL)
        return -1;

    new->left = NULL;                                   //왼쪽, 오른쪽 자식 NULL로 초기화
    new->right = NULL;

    return new;
}

tree* makeExternalNode() {                              //외부트리 만드는 함수

    tree* v;

    v = newtree();                                     //새로운 트리 생성

    printf("Enter decision:");

    gets(v->elem);                                      //대답 저장

    return v;
}

tree* makeInternalNode(int k) {                         //내부 트리 생성하는 함수

    tree* v;
    char answer[4];

    v = newtree();                                      //새로운 트리 생성

    if (count == 0) {                                   //첫 번째 트리일 경우 부모 원소를 NULL로 초기화
        v->parent = NULL;
        count += 1;                                     //이후 count 변수는 사용하지 않음
    }

    printf("Enter question : ");
    gets(v->elem);                                      //질문 입력

    printf("Question if yes to '%s'? ", v->elem);
    scanf("%s", answer);                                //대답 입력
    getchar();

    if (k == 0 || k == 1) {                             //첫번째 혹은 두 번째 질문일 경우
        if (strcmp(answer, "yes") == 0)                 //대답에 상관없이 무조건 질문 생성
            v->left = makeInternalNode(k + 1);
        else if ((strcmp(answer, "no") == 0))
            v->left = makeInternalNode(k + 1);
        v->left->parent = v;                            //left의 부모 요소를 v로

        printf("Question if no to '%s'? ", v->elem);
        scanf("%s", answer);
        getchar();

        if (strcmp(answer, "yes") == 0)                 //무조건 질문 만들기
            v->right = makeInternalNode(k + 1);
        else if ((strcmp(answer, "no") == 0))
            v->right = makeInternalNode(k + 1);
        v->right->parent = v;                           //right의 부모 요소를 v로
    }

    else if (k == 2 || k == 3) {                        //세번째 혹은 네번째 질문일 경우
        if (strcmp(answer, "yes") == 0)                 //yes일 경우 질문 만들기
            v->left = makeInternalNode(k + 1);
        else if ((strcmp(answer, "no") == 0))           //no일 경우 대답 만들기
            v->left = makeExternalNode();
        v->left->parent = v;

        printf("Question if no to '%s'? ", v->elem);
        scanf("%s", answer);
        getchar();

        if (strcmp(answer, "yes") == 0)                 //반복
            v->right = makeInternalNode(k + 1);
        else if ((strcmp(answer, "no") == 0))
            v->right = makeExternalNode();
        v->right->parent = v;
    }

    else {                                              //다섯번째 질문 이상일 경우
        if (strcmp(answer, "yes") == 0)                 //answer에 상관 없이 무조건 답변 만들기
            v->left = makeExternalNode();
        else if ((strcmp(answer, "no") == 0))
            v->left = makeExternalNode();
        v->left->parent = v;

        printf("Question if no to '%s'? ", v->elem);
        scanf("%s", answer);
        getchar();

        if (strcmp(answer, "yes") == 0)                 //반복
            v->right = makeExternalNode();
        else if ((strcmp(answer, "no") == 0))
            v->right = makeExternalNode();
        v->right->parent = v;
    }

}

tree* buildDecisionTree() {                             //질문 생성하는 함수

    return makeInternalNode(0);                         //가장 처음에는 0을 인자로 주고 재귀로 돌면서 1씩 증가하는 방식

}

void processNode(tree* root) {                          //질문 혹은 답변 출력하는 함수

    char answer[4];

    printf("%s ", root->elem);                          //출력

    if (root->left == NULL && root->right == NULL) {    //마지막 트리일 경우 줄바꾸고 종료
        printf("\n");
        return;
    }

    scanf("%s", answer);                                //답변 입력
    getchar();

    if (strcmp(answer, "yes") == 0)                     //yes일 경우 왼쪽으로 이동
        processNode(root->left);
    else if (strcmp(answer, "no") == 0)                 //no일 경우 오른쪽으로 이동
        processNode(root->right);
}

void runDecisionTree(tree* root) {                                               //사용자의 대답 입력받는 함수

    printf("***Please answer questions\n");
    processNode(root);
}

void freehelp(tree* root) {                                                     //전체 트리 프리 도와주는 함수

    if (root == NULL)                                                           //마지막 트리면 리턴
        return;

    freehelp(root->left);                                                       //재귀로 돌면서 계속 이동
    freehelp(root->right);
    free(root);
}

int main(void) {

    tree* root;
    int i;

    root = buildDecisionTree();                                  //buildDecisionTree 함수 호출
    printf("Tree complete. Now Running!!\n");

    while (1) {
        if (root->parent == NULL)                               //root를 가장 위를 가리키도록 하는 코드
            break;
        root = root->parent;
    }

    for (i = 0; i < 3; i++) {                                    //세번 runDecisionTree 함수 호출
        runDecisionTree(root);
    }

    freehelp(root);                                              //할당된 트리 프리 후 종료

    return 0;
}