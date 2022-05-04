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

	if (root == NULL) { //tree�� �������� �ʰų�, ���ܳ����� Ž���� ������ ��
		printf("key���� �������� ����"); //key���� �������� ������ ����ϰ� ����
		return 0;
	}

	if (value == root->key) {
		printf("key���� ������");
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

	// ���� �б� ����
	while (true) {
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) break;
		insert(intTemp, &root);
	}

	// ������ Ʈ������ Ű �˻�
	printf("�˻��� key�� �Է��ϼ���: ");
	scanf("%d", &sKey);
	searchKey(sKey, root);

	//���� ���·� ��ȯ
	fclose(pFile);          //close file
	return 0;
}