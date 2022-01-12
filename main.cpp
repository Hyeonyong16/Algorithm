#include <iostream>
#include <vector>

using namespace std;

//6.3 문제
//항상 서로 친구인 학생들끼리만 짝을 지어줘야함
//각 학생들의 쌍에 대해 이들이 서로 친구인지 여부가 주어질 때, 학생들을 짝지을 수 있는 방법의 수를 계산하는 프로그램 작성
//===================================
//입력의 첫 줄에는 테스트 케이스의 수 C(C<=50)가 주어짐
//각 테스트 케이스의 첫줄에는 학생의 수 n(2<=n<=10)과 친구쌍의 수(0<=m<=(n*(n-1))/2)가 주어짐
//그 다음 줄에 m개의 정수쌍으로 서로 친구인 두 학생의 번호가 주어짐
//번호는 0 ~ n-1 사이의 정수, 같은 쌍은 입력에 두 번 주어지지 않음
//학생들의 수는 짝수
//출력 -> 각 테스트 케이스마다 한 줄에 모든 학생을 친구끼리만 짝지어줄 수 있는 방법의 수 출력

typedef bool PAIR[10];

//6.3문제 소풍
class inputData {
private:
	int studentNum;		//입력받을 학생 숫자
	int friendPairNum;	//입력받을 친구 쌍의 숫자

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
		//입력부분
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

int pairingFriends(bool check[10], inputData& data) {
	int frontNum = -1;	//현재 짝을 확인해야할 학생 (-1이면 없는것)

	for (int i = 0; i < data.getStudentNum(); i++) {
		if (!check[i]) {
			frontNum = i;
			break;
		}
	}

	if (frontNum == -1) return 1;
	bool (*friendPair)[10] = data.getFriendPair();
	int result = 0;

	for (int i = frontNum + 1; i < data.getStudentNum(); i++) {
		if (!check[i] && friendPair[frontNum][i]) {
			check[frontNum] = true;
			check[i] = true;
			result += pairingFriends(check, data);
			check[frontNum] = false;
			check[i] = false;
		}
	}

	return result;
}

//6.8문제 시계 맞추기

int main() {
	int question = 1;
	if (question == 0) {

		int testCaseNum = 0;			//입력받을 테스트 케이스 숫자
		inputData data;
		vector <int> inputFriendPair;	//입력받은 친구쌍을 저장해놓을 벡터

		bool pairCheck[10] = { false };	//짝이 맺어졌는지 확인용 배열


		//입력부분
		/*cin >> studentNum >> friendPairNum;
		for (int i = 0; i < friendPairNum * 2; i++) {
			cin >> inputNum;
			inputFriendPair.push_back(inputNum);
		}*/
		cin >> testCaseNum;
		cin.clear();

		for (int i = 0; i < testCaseNum; i++) {
			data.dataInput(inputFriendPair);
			cout << "방법의 수: " << pairingFriends(pairCheck, data) << endl;
			data.initData();
			inputFriendPair.clear();
		}
	}

	else if (question == 1) {

	}
}