#include<stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Tree tree;
struct Tree { //tree�� node ����ü�� ����
	int key; //key��
	tree* left; //���� �ڽĳ��
	tree* right; //������ �ڽĳ��
};

void LL(tree** node) { //LL �����̼�
	tree* temp;

	temp = (*node)->left;
	(*node)->left = temp->right;
	temp->right = (*node);
	(*node) = temp;
}

void RR(tree** node) { //RR�����̼�
	tree* temp;

	temp = (*node)->right;
	(*node)->right = temp->left;
	temp->left = (*node);
	(*node) = temp;
}

int getHeight(tree* node) { //Ʈ���� ���̸� ���ϴ� �Լ�

	if (node != NULL) {

		if (node->left == NULL && node->right == NULL) { //�ܸ� ����̸�
			return 1; //1�� ��ȯ
		}
		else {
			int left = getHeight(node->left); //���� �ڽĳ�带 ����� ȣ��
			int right = getHeight(node->right); //������ �ڽĳ�带 ����� ȣ��

			int max = (left > right) ? left : right; //���� �ڽĳ���� ��ȯ���� ������ �ڽĳ���� ��ȯ�� ��, �� ū ���� max
			return max + 1; // max + 1(=����)�� ��ȯ
		}
	}
	return 0;
}

int calBal(tree* node) { //�����μ��� ����ϴ� �Լ�
	int factor = getHeight(node->left) - getHeight(node->right); //���� ����Ʈ���� ������ ����Ʈ���� ���̸� ���Ͽ� �����μ� ���
	return factor;
}

void adjustBal(tree** node) { //Ʈ���� ������ ���ߴ� �Լ�
	int factor = calBal(*node); //�����μ��� ���

	if (factor >= 2) { //�����μ��� 2 �̻��� ��
		if (calBal((*node)->left) >= 1) { //���� �ڽĳ���� �����μ��� 1 �̻��̸�
			LL(node); //LL����, LLȸ���Լ��� ȣ��
		}
		else { //LR ����, LR ȸ���� ��Ű�� ���� RRȸ���� LL�Լ��� ���޾� ȣ��
			RR(&(*node)->left); //���� �ڽĳ�带 �������� RRȸ��
			LL(node); //������ �������� LLȸ��
		}
	}
	else if (factor <= -2) { //�����μ��� -2 ������ ��
		if (calBal((*node)->right) <= -1) { //������ �ڽĳ���� �����μ��� -1 ���ϸ�
			RR(node); //RRȸ��
		}
		else { //RLȸ��
			LL(&(*node)->right);
			RR(node);
		}
	}
}

tree* makeNode(int value) { //node�� ����� �Լ�, �����Ҵ� �� key���� �ڽĳ�带 �ʱ�ȭ�� �� ��ȯ
	tree* nNode = (tree*)malloc(sizeof(tree));
	nNode->key = value;
	nNode->left = NULL;
	nNode->right = NULL;

	return nNode;
}

void insert(int value, tree** node) { //����
	if (*node == NULL) { //���� ��尡 ����ִٸ�
		*node = makeNode(value); //��带 ���� 
	}

	else { //���� ��忡 ���� �ִٸ�
		if (value < (*node)->key) { //key���� ��, value�� �� ������
			insert(value, &(*node)->left); //���� �ڽĳ�带 ȣ���Ͽ� ����
			adjustBal(node); //���� �� ��Ʈ���� ������ �˻�, ������
		}
		else { //value�� �� ũ��
			insert(value, &(*node)->right);
			adjustBal(node);
		}
	}
}

int searchKey(int value, tree* node) { //key���� �˻��ϴ� �Լ�

	if (node == NULL) { //tree�� �������� �ʰų�, ���ܳ����� Ž���� ������ ��
		printf("key���� �������� ����"); //key���� �������� ������ ����ϰ� ����
		return 0;
	}

	if (value == node->key) { //key���� ã���� ��
		printf("key���� ������"); //Ž���� �����ϰ� key���� �������� ���
		return 0;
	}
	else if (value < node->key) { //ã���� �ϴ� key���� �� ���� ��
		searchKey(value, node->left); //���� �ڽĳ���
	}
	else if (value > node->key) { //ã���� �ϴ� key���� �� Ŭ ��
		searchKey(value, node->right); //������ �ڽĳ���
	}
}

int main(void)
{
	FILE* pFile = fopen("test.txt", "r"); //read mode 
	int intTemp = -1;
	int sKey = -1;
	tree* root = NULL; //��ü AVL Ʈ���� ��Ʈ��带 ����

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}

	// ���� �б� ����
	while (1) {
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) break; //-1�̸� ������ ��
		insert(intTemp, &root); //key�� ����
	}

	// ������ Ʈ������ Ű �˻�
	printf("�˻��� key�� �Է��ϼ���: ");
	scanf("%d", &sKey);
	searchKey(sKey, root);

	//���� ���·� ��ȯ
	fclose(pFile);          //close file
	return 0;
}