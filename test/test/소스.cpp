#include<stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

struct node {
	int key;
	node* left;
	node* right;
};

node* makeNode(int value) {
	node* nNode = (node*)malloc(sizeof(node));
	nNode->key = value;
	nNode->left = NULL;
	nNode->right = NULL;

	return nNode;
}

void insert(int value, node** root) {
	if (*root == NULL) {
		*root = makeNode(value);
	}

	else {
		if (value < (*root)->key) {
			insert(value, &(*root)->left);
		}
		else {
			insert(value, &(*root)->right);
		}
	}
}

int searchKey(int value, node* root) {

	if (root == NULL) { //tree가 존재하지 않거나, 말단노드까지 탐색을 마쳤을 때
		printf("key값이 존재하지 않음"); //key값이 존재하지 않음을 출력하고 종료
		return 0;
	}

	if (value == root->key) {
		printf("key값이 존재함");
		return 0;
	}
	else if (value < root->key) {
		searchKey(value, root->left);
	}
	else if (value > root->key) {
		searchKey(value, root->right);
	}
}

int main(void)
{
	FILE* pFile = fopen("test1.txt", "r"); //read mode 
	int intTemp = -1;
	int sKey = -1;
	node* root = NULL;

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}

	// 파일 읽기 성공
	while (true) {
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) break;
		insert(intTemp, &root);
	}

	// 생성된 트리에서 키 검색
	printf("검색할 key를 입력하세요: ");
	scanf("%d", &sKey);
	searchKey(sKey, root);

	//파일 형태로 반환
	fclose(pFile);          //close file
	return 0;
}