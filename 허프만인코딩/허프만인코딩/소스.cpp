#include <iostream>
#include <string>
using namespace std;


struct Node { //허프만 트리의 노드 구조체 정의
	char value;
	int freq;
	Node* left;
	Node* right;
};

struct Binarycode { //이진 코드 구조체
	char value;
	string code;
};

int alphabet[51] = { 0 }; //A[0]~Z[25], a[26]~Z[51] 
int index = 0;
string str; //입력 원문 알파벳 문자열 
string encodingStr; //인코딩 된 이진 스트링
string decodingStr; //디코딩 된 알파벳 문자열

Node* makeNode(char Val, int Freq, Node* left, Node* right) { //새로운 노드를 생성
	Node* nNode = new Node;
	nNode->value = Val;
	nNode->freq = Freq;
	nNode->left = left;
	nNode->right = right;
	
	return nNode;
}

void swap(Node** xp, Node** yp) { //선택정렬을 위한 swap 함수
	Node* tmp;
	tmp = *xp;
	*xp = *yp;
	*yp = tmp;
}

void selection_sort(Node** freq, int start, int count) { //선택정렬 함수, 오름차순으로 정렬
	int n, m, minindex;

	for (n = start; n < count; n++) {
		minindex = n;
		for (m = n + 1; m < count; m++) {
			if ((*freq[minindex]).freq > (*freq[m]).freq) {
				minindex = m;
			}
		}swap(&(freq[minindex]), &(freq[n]));
	}
}

string code; //이진 코드 생성을 위한 문자열 
string str0 = "0"; 
string str1 = "1";

int MakeBcode(Node* node, Binarycode* Bcode) {

	if (node != NULL) {
		if (node->value != NULL) { //value가 NULL이 아니면 leaf node 
			Bcode[index].value = node->value; //이진 코드 배열에 값을 추가
			Bcode[index++].code = code; 

			return 0;
		}
		else {
			if (node->left != NULL) { //왼쪽 자식 노드가 있으면
				code += str0; //현재 code 문자열의 끝에 0을 추가 
				MakeBcode(node->left, Bcode); //왼쪽 자식노드를 재귀적 호출
				code.pop_back(); //호출이 끝나고 돌아오면 문자열의 마지막 문자 제거
			} 
			if (node->right != NULL) { //오른쪽 자식 노드가 있으면 
				code += str1; //현재 code 문자열의 끝에 1을 추가 
				MakeBcode(node->right, Bcode); //오른쪽 자식노드를 재귀 호출
				code.pop_back(); //문자열의 마지막 문자 제거 
			}
		}
	}
}

int main() {
	int i, j;
	int len;
	int count = 0;
	Node* Htree;

	cout << "Put the string to encode: "; //인코딩 할 알파벳 문자열을 입력 받음
	cin >> str;
	cout << "\n";

	len = str.length(); //입력받은 문자열의 길이를 구함

	for (i = 0; i < len; i++) { //문자열의 처음부터 끝까지 for문 반복
		if (str[i] >= 65 && str[i] <= 90) { //문자가 대문자라면 
			alphabet[str[i] - 65]++; //alphabet 배열의 인덱스를 증가
		}
		else { //문자가 소문자라면 
			alphabet[str[i] - 71]++; 
		}
	}

	for (i = 0; i <= 51; i++) { //실제로 문자열에 쓰인 알파벳의 갯수를 세림 
		if (alphabet[i] > 0) {
			count++;
		}
	}

	Node** frequency = new Node * [count]; //알파벳의 갯수만큼 Node 배열 생성

	count = 0;

	for (i = 0; i <= 51; i++) { //알파벳 배열의 처음부터 마지막까지 for문 반복 
		if (alphabet[i] > 0) {
			if (i >= 0 && i <= 25) { //대문자라면
				frequency[count++] = makeNode(char(i + 65), alphabet[i], NULL, NULL); //frequency 배열에 빈도수와 알파벳을 저장 
			}
			else { //소문자라면
				frequency[count++] = makeNode(char(i + 71), alphabet[i], NULL, NULL);
			}
		}
	}

	//허프만 트리를 생성하는 과정
	// frequency 배열의 처음부터 끝까지 for문 반복 
	for (i = 0; i < count - 1; i++) { 
		selection_sort(frequency, i, count); //오름차순으로 정렬을 수행 
		frequency[i + 1] = makeNode(NULL, (*frequency[i]).freq + (*frequency[i + 1]).freq, frequency[i], frequency[i + 1]);
	} //빈도가 가장 작은 노드 두개(index i번과 i+1번)를 골라 합친 노드를 생성한 뒤, i+1번에 대입, i를 증가시키며 모든 노드에 대해 수행

	Htree = frequency[count - 1]; //마지막 index의 노드가 허프만 트리의 루트가 됨
	Binarycode* Bcode = new Binarycode[count]; //이진 코드 구조체를 담을 배열 생성 
	MakeBcode(Htree, Bcode); //이진 코드 생성


	//인코딩 과정 
	for (i = 0; i <= len; i++) {  //원문 문자열의 처음부터 끝까지 
		for (j = count - 1; j >= 0; j--) { // Bcode 배열의 끝에서부터 순차적으로 비교(빈도수가 높은 알파벳과 코드 조합이 뒤에 저장되어 있음) 
			if (str[i] == Bcode[j].value) { //문자열의 문자이 Bcode구조체의 value값과 같으면 
				encodingStr += Bcode[j].code; //encodingStr에 해당 구조체의 이진코드 값을 더하는 연산 수행
				break; 
			} 
		}

	} cout << "Encoded result: " << encodingStr << "\n"<< "\n"; //인코딩 된 문자열을 출력

	//디코딩 과정
	Node* cNode = NULL;  //현재 노드 
	Node* pNode = Htree; //이전 노드 
	index = 0;

	while (encodingStr[index] != NULL) { // 문자열의 끝이 아니라면 
		if (encodingStr[index] == '0') { //문자가 0이면 
			cNode = pNode->left; //왼쪽 자식노드로 이동
			pNode = cNode; //현재 포인터를 저장 
		}
		else if(encodingStr[index] == '1'){ //문자가 1이면 
			cNode = pNode->right; //오른쪽 자식노드로 이동
			pNode = cNode;
		}

		if (cNode->value != NULL) { //이동했을 때 value가 NULL이 아니면 => leaf node면
			decodingStr += cNode->value; //decodingStr에 해당 노드의 value를 더하는 연산 수행
			pNode = Htree; //트리의 루트로 돌아감
		}

		index++; //문자열의 다음 문자로 같은 연산 수행
	}

	cout << "Decoded result: " << decodingStr << "\n"; //decoding된 문자를 출력
}