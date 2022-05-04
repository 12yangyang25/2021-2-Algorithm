#include <iostream>
#include <string>
using namespace std;


struct Node { //������ Ʈ���� ��� ����ü ����
	char value;
	int freq;
	Node* left;
	Node* right;
};

struct Binarycode { //���� �ڵ� ����ü
	char value;
	string code;
};

int alphabet[51] = { 0 }; //A[0]~Z[25], a[26]~Z[51] 
int index = 0;
string str; //�Է� ���� ���ĺ� ���ڿ� 
string encodingStr; //���ڵ� �� ���� ��Ʈ��
string decodingStr; //���ڵ� �� ���ĺ� ���ڿ�

Node* makeNode(char Val, int Freq, Node* left, Node* right) { //���ο� ��带 ����
	Node* nNode = new Node;
	nNode->value = Val;
	nNode->freq = Freq;
	nNode->left = left;
	nNode->right = right;
	
	return nNode;
}

void swap(Node** xp, Node** yp) { //���������� ���� swap �Լ�
	Node* tmp;
	tmp = *xp;
	*xp = *yp;
	*yp = tmp;
}

void selection_sort(Node** freq, int start, int count) { //�������� �Լ�, ������������ ����
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

string code; //���� �ڵ� ������ ���� ���ڿ� 
string str0 = "0"; 
string str1 = "1";

int MakeBcode(Node* node, Binarycode* Bcode) {

	if (node != NULL) {
		if (node->value != NULL) { //value�� NULL�� �ƴϸ� leaf node 
			Bcode[index].value = node->value; //���� �ڵ� �迭�� ���� �߰�
			Bcode[index++].code = code; 

			return 0;
		}
		else {
			if (node->left != NULL) { //���� �ڽ� ��尡 ������
				code += str0; //���� code ���ڿ��� ���� 0�� �߰� 
				MakeBcode(node->left, Bcode); //���� �ڽĳ�带 ����� ȣ��
				code.pop_back(); //ȣ���� ������ ���ƿ��� ���ڿ��� ������ ���� ����
			} 
			if (node->right != NULL) { //������ �ڽ� ��尡 ������ 
				code += str1; //���� code ���ڿ��� ���� 1�� �߰� 
				MakeBcode(node->right, Bcode); //������ �ڽĳ�带 ��� ȣ��
				code.pop_back(); //���ڿ��� ������ ���� ���� 
			}
		}
	}
}

int main() {
	int i, j;
	int len;
	int count = 0;
	Node* Htree;

	cout << "Put the string to encode: "; //���ڵ� �� ���ĺ� ���ڿ��� �Է� ����
	cin >> str;
	cout << "\n";

	len = str.length(); //�Է¹��� ���ڿ��� ���̸� ����

	for (i = 0; i < len; i++) { //���ڿ��� ó������ ������ for�� �ݺ�
		if (str[i] >= 65 && str[i] <= 90) { //���ڰ� �빮�ڶ�� 
			alphabet[str[i] - 65]++; //alphabet �迭�� �ε����� ����
		}
		else { //���ڰ� �ҹ��ڶ�� 
			alphabet[str[i] - 71]++; 
		}
	}

	for (i = 0; i <= 51; i++) { //������ ���ڿ��� ���� ���ĺ��� ������ ���� 
		if (alphabet[i] > 0) {
			count++;
		}
	}

	Node** frequency = new Node * [count]; //���ĺ��� ������ŭ Node �迭 ����

	count = 0;

	for (i = 0; i <= 51; i++) { //���ĺ� �迭�� ó������ ���������� for�� �ݺ� 
		if (alphabet[i] > 0) {
			if (i >= 0 && i <= 25) { //�빮�ڶ��
				frequency[count++] = makeNode(char(i + 65), alphabet[i], NULL, NULL); //frequency �迭�� �󵵼��� ���ĺ��� ���� 
			}
			else { //�ҹ��ڶ��
				frequency[count++] = makeNode(char(i + 71), alphabet[i], NULL, NULL);
			}
		}
	}

	//������ Ʈ���� �����ϴ� ����
	// frequency �迭�� ó������ ������ for�� �ݺ� 
	for (i = 0; i < count - 1; i++) { 
		selection_sort(frequency, i, count); //������������ ������ ���� 
		frequency[i + 1] = makeNode(NULL, (*frequency[i]).freq + (*frequency[i + 1]).freq, frequency[i], frequency[i + 1]);
	} //�󵵰� ���� ���� ��� �ΰ�(index i���� i+1��)�� ��� ��ģ ��带 ������ ��, i+1���� ����, i�� ������Ű�� ��� ��忡 ���� ����

	Htree = frequency[count - 1]; //������ index�� ��尡 ������ Ʈ���� ��Ʈ�� ��
	Binarycode* Bcode = new Binarycode[count]; //���� �ڵ� ����ü�� ���� �迭 ���� 
	MakeBcode(Htree, Bcode); //���� �ڵ� ����


	//���ڵ� ���� 
	for (i = 0; i <= len; i++) {  //���� ���ڿ��� ó������ ������ 
		for (j = count - 1; j >= 0; j--) { // Bcode �迭�� ���������� ���������� ��(�󵵼��� ���� ���ĺ��� �ڵ� ������ �ڿ� ����Ǿ� ����) 
			if (str[i] == Bcode[j].value) { //���ڿ��� ������ Bcode����ü�� value���� ������ 
				encodingStr += Bcode[j].code; //encodingStr�� �ش� ����ü�� �����ڵ� ���� ���ϴ� ���� ����
				break; 
			} 
		}

	} cout << "Encoded result: " << encodingStr << "\n"<< "\n"; //���ڵ� �� ���ڿ��� ���

	//���ڵ� ����
	Node* cNode = NULL;  //���� ��� 
	Node* pNode = Htree; //���� ��� 
	index = 0;

	while (encodingStr[index] != NULL) { // ���ڿ��� ���� �ƴ϶�� 
		if (encodingStr[index] == '0') { //���ڰ� 0�̸� 
			cNode = pNode->left; //���� �ڽĳ��� �̵�
			pNode = cNode; //���� �����͸� ���� 
		}
		else if(encodingStr[index] == '1'){ //���ڰ� 1�̸� 
			cNode = pNode->right; //������ �ڽĳ��� �̵�
			pNode = cNode;
		}

		if (cNode->value != NULL) { //�̵����� �� value�� NULL�� �ƴϸ� => leaf node��
			decodingStr += cNode->value; //decodingStr�� �ش� ����� value�� ���ϴ� ���� ����
			pNode = Htree; //Ʈ���� ��Ʈ�� ���ư�
		}

		index++; //���ڿ��� ���� ���ڷ� ���� ���� ����
	}

	cout << "Decoded result: " << decodingStr << "\n"; //decoding�� ���ڸ� ���
}