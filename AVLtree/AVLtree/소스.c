#include<stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Tree tree;
struct Tree { //tree의 node 구조체를 선언
	int key; //key값
	tree* left; //왼쪽 자식노드
	tree* right; //오른쪽 자식노드
};

void LL(tree** node) { //LL 로테이션
	tree* temp;

	temp = (*node)->left;
	(*node)->left = temp->right;
	temp->right = (*node);
	(*node) = temp;
}

void RR(tree** node) { //RR로테이션
	tree* temp;

	temp = (*node)->right;
	(*node)->right = temp->left;
	temp->left = (*node);
	(*node) = temp;
}

int getHeight(tree* node) { //트리의 높이를 구하는 함수

	if (node != NULL) {

		if (node->left == NULL && node->right == NULL) { //단말 노드이면
			return 1; //1을 반환
		}
		else {
			int left = getHeight(node->left); //왼쪽 자식노드를 재귀적 호출
			int right = getHeight(node->right); //오른쪽 자식노드를 재귀적 호출

			int max = (left > right) ? left : right; //왼쪽 자식노드의 반환값과 오른쪽 자식노드의 반환값 비교, 더 큰 쪽이 max
			return max + 1; // max + 1(=높이)를 반환
		}
	}
	return 0;
}

int calBal(tree* node) { //균형인수를 계산하는 함수
	int factor = getHeight(node->left) - getHeight(node->right); //왼쪽 서브트리와 오른쪽 서브트리의 높이를 구하여 균형인수 계산
	return factor;
}

void adjustBal(tree** node) { //트리의 균형을 맞추는 함수
	int factor = calBal(*node); //균형인수를 계산

	if (factor >= 2) { //균형인수가 2 이상일 때
		if (calBal((*node)->left) >= 1) { //왼쪽 자식노드의 균형인수가 1 이상이면
			LL(node); //LL유형, LL회전함수를 호출
		}
		else { //LR 유형, LR 회전을 시키기 위해 RR회전과 LL함수를 연달아 호출
			RR(&(*node)->left); //왼쪽 자식노드를 기준으로 RR회전
			LL(node); //본인을 기준으로 LL회전
		}
	}
	else if (factor <= -2) { //균형인수가 -2 이하일 때
		if (calBal((*node)->right) <= -1) { //오른쪽 자식노드의 균형인수가 -1 이하면
			RR(node); //RR회전
		}
		else { //RL회전
			LL(&(*node)->right);
			RR(node);
		}
	}
}

tree* makeNode(int value) { //node를 만드는 함수, 동적할당 후 key값과 자식노드를 초기화한 뒤 반환
	tree* nNode = (tree*)malloc(sizeof(tree));
	nNode->key = value;
	nNode->left = NULL;
	nNode->right = NULL;

	return nNode;
}

void insert(int value, tree** node) { //삽입
	if (*node == NULL) { //현재 노드가 비어있다면
		*node = makeNode(value); //노드를 생성 
	}

	else { //현재 노드에 값이 있다면
		if (value < (*node)->key) { //key값과 비교, value가 더 작으면
			insert(value, &(*node)->left); //왼족 자식노드를 호출하여 삽입
			adjustBal(node); //삽입 후 흐트러진 균형을 검사, 재조정
		}
		else { //value가 더 크면
			insert(value, &(*node)->right);
			adjustBal(node);
		}
	}
}

int searchKey(int value, tree* node) { //key값을 검색하는 함수

	if (node == NULL) { //tree가 존재하지 않거나, 말단노드까지 탐색을 마쳤을 때
		printf("key값이 존재하지 않음"); //key값이 존재하지 않음을 출력하고 종료
		return 0;
	}

	if (value == node->key) { //key값을 찾았을 때
		printf("key값이 존재함"); //탐색을 종료하고 key값이 존재함을 출력
		return 0;
	}
	else if (value < node->key) { //찾고자 하는 key값이 더 작을 때
		searchKey(value, node->left); //왼쪽 자식노드로
	}
	else if (value > node->key) { //찾고자 하는 key값이 더 클 때
		searchKey(value, node->right); //오른쪽 자식노드로
	}
}

int main(void)
{
	FILE* pFile = fopen("test.txt", "r"); //read mode 
	int intTemp = -1;
	int sKey = -1;
	tree* root = NULL; //전체 AVL 트리의 루트노드를 생성

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}

	// 파일 읽기 성공
	while (1) {
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) break; //-1이면 파일의 끝
		insert(intTemp, &root); //key를 삽입
	}

	// 생성된 트리에서 키 검색
	printf("검색할 key를 입력하세요: ");
	scanf("%d", &sKey);
	searchKey(sKey, root);

	//파일 형태로 반환
	fclose(pFile);          //close file
	return 0;
}