#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int generateRandomNumber() {

	srand(time(nullptr));

	int random_number = rand() % 100 + 10;

	random_number *= 5;
	random_number = 0475 / random_number;
	random_number %= 25;
	random_number += 15;

	return random_number;
}

int** createMatix(int n) {

	int** mtx = new int* [n];


	for (int i = 0; i < n; i++)
	{
		mtx[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mtx[i][j] = rand() % 100 + 0;
			cout << mtx[i][j] << ",";
		}
		cout << endl;
	}

	return mtx;
}

int main() {


	int n = generateRandomNumber();

	cout << "Random number: " << n<<endl;
	
	int** mtx = createMatix(n);

	




	return 0;
}