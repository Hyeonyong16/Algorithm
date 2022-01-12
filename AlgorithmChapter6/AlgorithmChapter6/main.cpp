#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//6.3 ����
//�׻� ���� ģ���� �л��鳢���� ¦�� ���������
//�� �л����� �ֿ� ���� �̵��� ���� ģ������ ���ΰ� �־��� ��, �л����� ¦���� �� �ִ� ����� ���� ����ϴ� ���α׷� �ۼ�
//===================================
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C(C<=50)�� �־���
//�� �׽�Ʈ ���̽��� ù�ٿ��� �л��� �� n(2<=n<=10)�� ģ������ ��(0<=m<=(n*(n-1))/2)�� �־���
//�� ���� �ٿ� m���� ���������� ���� ģ���� �� �л��� ��ȣ�� �־���
//��ȣ�� 0 ~ n-1 ������ ����, ���� ���� �Է¿� �� �� �־����� ����
//�л����� ���� ¦��
//��� -> �� �׽�Ʈ ���̽����� �� �ٿ� ��� �л��� ģ�������� ¦������ �� �ִ� ����� �� ���

typedef bool PAIR[10];

//6.3���� ��ǳ
class inputData {
private:
	int studentNum;		//�Է¹��� �л� ����
	int friendPairNum;	//�Է¹��� ģ�� ���� ����

	bool friendPair[10][10];

public:
	inputData() : studentNum(0), friendPairNum(0) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				friendPair[i][j] = false;
			}
		}
	}

	~inputData() {}

	void setFriendPair(vector<int>& inputFriendPair) {
		for (int i = 0; i < friendPairNum; i++) {
			friendPair[inputFriendPair[2 * i]][inputFriendPair[(2 * i) + 1]] = true;
			friendPair[inputFriendPair[(2 * i) + 1]][inputFriendPair[2 * i]] = true;
		}
	}

	int getStudentNum() {
		return  studentNum;
	}

	int getFriendPairNum() {
		return friendPairNum;
	}

	PAIR* getFriendPair() {
		return friendPair;
	}

	void dataInput(vector<int>& inputFriendPair) {
		//�Էºκ�
		int inputNum;

		cin >> studentNum >> friendPairNum;
		for (int i = 0; i < friendPairNum * 2; i++) {
			cin >> inputNum;
			inputFriendPair.push_back(inputNum);
			cin.clear();
		}

		setFriendPair(inputFriendPair);
	}

	void initData() {
		studentNum = 0;
		friendPairNum = 0;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				friendPair[i][j] = false;
			}
		}
	}
};

int PairingFriends(bool check[10], inputData& data) {
	int frontNum = -1;	//���� ¦�� Ȯ���ؾ��� �л� (-1�̸� ���°�)

	for (int i = 0; i < data.getStudentNum(); i++) {
		if (!check[i]) {
			frontNum = i;
			break;
		}
	}

	if (frontNum == -1) return 1;
	bool(*friendPair)[10] = data.getFriendPair();
	int result = 0;

	for (int i = frontNum + 1; i < data.getStudentNum(); i++) {
		if (!check[i] && friendPair[frontNum][i]) {
			check[frontNum] = true;
			check[i] = true;
			result += PairingFriends(check, data);
			check[frontNum] = false;
			check[i] = false;
		}
	}

	return result;
}

//6.8���� �ð� ���߱�
const bool switches[10][16] = {
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//0
		{0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},	//1
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},	//2
		{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},	//3
		{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},	//4
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},	//5
		{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},	//6
		{0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},	//7
		{0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//8
		{0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}	//9
};

void PushSwitch(vector<int>& clocks, int activeSwitch) {
	for (int i = 0; i < 16; i++) {
		if (switches[activeSwitch][i]) {
			clocks[i] += 3;
			if (clocks[i] == 15) clocks[i] = 3;
		}
	}
}

bool IsClockMatched(vector<int>& clocks) {
	bool checked = true;
	for (int i = 0; i < 16; i++) {
		if (clocks[i] != 12) {
			checked = false;
			break;
		}
	}

	return checked;
}

int FindSolution(vector<int>& clocks, int curSwitch) {
	if (curSwitch == 10) {
		bool temp;
		temp = IsClockMatched(clocks);
		if (temp) return 0;
		else return 9999;
	}

	int val = 99999;
	for (int i = 0; i < 4; i++) {
		val = min(val, i + FindSolution(clocks, curSwitch + 1));
		PushSwitch(clocks, curSwitch);
	}

	return val;
}

int main() {
	int question = 2;

	//6.3 ��ǳ
	if (question == 0) {

		int testCaseNum = 0;			//�Է¹��� �׽�Ʈ ���̽� ����
		inputData data;
		vector <int> inputFriendPair;	//�Է¹��� ģ������ �����س��� ����

		bool pairCheck[10] = { false };	//¦�� �ξ������� Ȯ�ο� �迭


		//�Էºκ�
		/*cin >> studentNum >> friendPairNum;
		for (int i = 0; i < friendPairNum * 2; i++) {
			cin >> inputNum;
			inputFriendPair.push_back(inputNum);
		}*/
		cin >> testCaseNum;
		cin.clear();

		for (int i = 0; i < testCaseNum; i++) {
			data.dataInput(inputFriendPair);
			cout << "����� ��: " << PairingFriends(pairCheck, data) << endl;
			data.initData();
			inputFriendPair.clear();
		}
	}

	//6.8 �ð� ���߱�
	else if (question == 2) {
		int testCaseNum = 0;
		int input;

		vector<int> clocks;

		cin >> testCaseNum;
		cin.clear();

		for (int i = 0; i < 16; i++) {
			cin >> input;
			cin.clear();

			clocks.push_back(input);
		}

		cout << "�ּ� ȸ��: " << FindSolution(clocks, 0) << endl;
	}
}