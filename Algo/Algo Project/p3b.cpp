//#include <iostream>
//using namespace std;
//
//
//int min_cost(int n, int** c, int* path) {
//	int* dp = new int[n];
//	int* prev = new int[n];
//	dp[0] = 0;
//	prev[0] = -1;
//	for (int i = 1; i < n; i++) {
//		dp[i] = INT_MAX;
//		for (int j = 0; j < i; j++) {
//			if (dp[j] != INT_MAX && c[j][i] != INT_MAX && dp[i] > dp[j] + c[j][i]) {
//				dp[i] = dp[j] + c[j][i];
//				prev[i] = j;
//			}
//		}
//	}
//
//
//	int idx = n - 1;
//	int count = 0;
//	while (idx >= 0) {
//		path[count++] = idx + 1;
//		idx = prev[idx];
//	}
//
//
//	for (int i = 0; i < count / 2; i++) {
//		int temp = path[i];
//		path[i] = path[count - i - 1];
//		path[count - i - 1] = temp;
//	}
//
//
//
//	int min_cost = dp[n - 1];
//
//	delete[] dp;
//	delete[] prev;
//
//	return min_cost;
//}
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////PSEUDOCODE CODE ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
////1. Define a function min_cost with parameters n, cand path.
////2. Create two arrays dp and prev of size n.
////3. Set dp[0] to 0 and prev[0] to - 1.
////4. For i from 1 to n - 1 do:
////	a.Set dp[i] to INT_MAX.
////	b.For j from 0 to i - 1 do :
////		i.Check if dp[j] is not INT_MAX and c[j][i] is not INT_MAX and dp[i] is greater than dp[j] + c[j][i].
////		ii.If the condition is true, set dp[i] to dp[j] + c[j][i] and prev[i] to j.
////5. Construct the path by setting idx to n - 1 and count to 0.
////6. While idx is not - 1 do :
////	a.Set path[count] to idx + 1.
////	b.Set idx to prev[idx].
////	c.Increment count by 1.
////7. Reverse the path by swapping the values at path[i] and path[count - i - 1] for i from 0 to count / 2.
////8. Set min_cost to dp[n - 1].
////9. Delete the dynamically allocated memory for dpand prev.
////10. Return min_cost.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// ASYMPTOTIC TIME-Space COMPLEXITY ANALYSIS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
////
////-The outer loop iterates from i = 1 to n - 1, which takes O(n) time.
////- The inner loop iterates from j = 0 to i - 1, which takes O(n ^ 2) time in total(the sum of the first n integers is n(n + 1) / 2, which is O(n ^ 2)).
////- The operations inside the inner loop(comparisons and assignments) take constant time.
////- The path construction loop iterates at most n times, which takes O(n) time.
////- The loop that reverses the path also takes O(n) time.
////- The memory used by the function is proportional to the input size(O(n ^ 2) for the cost matrix, O(n) for the path array, and O(n) for the dpand prev arrays).Therefore, the space complexity of the function is O(n ^ 2).
////
////Combining these results, we can say that the time complexity of the function is O(n ^ 2), and the space complexity is O(n ^ 2).
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//void q3Test1() {
//	const int n = 8;
//
//	int** c = new int* [n];
//	for (int i = 0; i < n; i++) {
//		c[i] = new int[n];
//		for (int j = 0; j < n; j++) {
//			c[i][j] = INT_MAX;
//		}
//	}
//
//
//
//	c[0][0] = 0;
//	c[0][1] = 100;
//	c[0][2] = 20;
//	c[0][3] = 300;
//	c[0][4] = 400;
//	c[0][5] = 500;
//	c[0][6] = 600;
//	c[0][7] = 700;
//	c[1][1] = 0;
//	c[1][2] = 50;
//	c[1][3] = 10;
//	c[1][4] = 100;
//	c[1][5] = 200;
//	c[1][6] = 300;
//	c[1][7] = 400;
//	c[2][2] = 0;
//	c[2][3] = 30;
//	c[2][4] = 10;
//	c[2][5] = 90;
//	c[2][6] = 10;
//	c[2][7] = 150;
//	c[3][3] = 0;
//	c[3][4] = 80;
//	c[3][5] = 160;
//	c[3][6] = 240;
//	c[3][7] = 320;
//	c[4][4] = 0;
//	c[4][5] = 120;
//	c[4][6] = 240;
//	c[4][7] = 600;
//	c[5][5] = 0;
//	c[5][6] = 120;
//	c[5][7] = 240;
//	c[6][6] = 0;
//	c[6][7] = 120;
//	c[7][7] = 0;
//
//
//	int* path = new int[n];
//	for (int i = 0; i < n; i++) {
//		path[i] == -1;
//	}
//	int minCost = min_cost(n, c, path);
//
//	cout << "Minimum cost: " << minCost << endl;
//
//
//	int pathLength = 0;
//
//	for (int i = 0; i < n; i++) {
//		if (path[i] > 0) {
//			pathLength++;
//		}
//	}
//
//	cout << "Shortest Path: ";
//	for (int i = 0; i < pathLength; i++) {
//		if (path[i] >= 0) {
//			cout << path[i];
//			if (i != pathLength - 1) {
//				cout << " -> ";
//			}
//		}
//	}
//	cout << endl;
//
//	for (int i = 0; i < n; i++) {
//		delete[] c[i];
//	}
//	delete[] c;
//}
//
//void q3Test2() {
//	const int n = 10;
//
//	int** c = new int* [n];
//	for (int i = 0; i < n; i++) {
//		c[i] = new int[n];
//		for (int j = 0; j < n; j++) {
//			c[i][j] = INT_MAX;
//		}
//	}
//
//	c[0][0] = 0;
//	c[0][1] = 100;
//	c[0][2] = 200;
//	c[0][3] = 40;
//	c[0][4] = 250;
//	c[0][5] = 300;
//	c[0][6] = 400;
//	c[0][7] = 500;
//	c[0][8] = 600;
//	c[0][9] = 700;
//	c[1][1] = 0;
//	c[1][2] = 50;
//	c[1][3] = 10;
//	c[1][4] = 100;
//	c[1][5] = 200;
//	c[1][6] = 300;
//	c[1][7] = 400;
//	c[1][8] = 500;
//	c[1][9] = 600;
//	c[2][2] = 0;
//	c[2][3] = 30;
//	c[2][4] = 10;
//	c[2][5] = 90;
//	c[2][6] = 10;
//	c[2][7] = 150;
//	c[2][8] = 200;
//	c[2][9] = 250;
//	c[3][3] = 0;
//	c[3][4] = 80;
//	c[3][5] = 160;
//	c[3][6] = 240;
//	c[3][7] = 320;
//	c[3][8] = 400;
//	c[3][9] = 430;
//	c[4][4] = 0;
//	c[4][5] = 120;
//	c[4][6] = 240;
//	c[4][7] = 600;
//	c[4][8] = 650;
//	c[4][9] = 700;
//	c[5][5] = 0;
//	c[5][6] = 120;
//	c[5][7] = 240;
//	c[5][8] = 300;
//	c[5][9] = 350;
//	c[6][6] = 0;
//	c[6][7] = 120;
//	c[6][8] = 140;
//	c[6][9] = 160;
//	c[7][7] = 0;
//	c[7][8] = 200;
//	c[7][9] = 400;
//	c[8][8] = 0;
//	c[8][9] = 400;
//	c[9][9] = 0;
//
//
//	int* path = new int[n];
//	for (int i = 0; i < n; i++) {
//		path[i] == -1;
//	}
//	int minCost = min_cost(n, c, path);
//
//	cout << "Minimum cost: " << minCost << endl;
//
//
//	int pathLength = 0;
//
//	for (int i = 0; i < n; i++) {
//		if (path[i] > 0) {
//			pathLength++;
//		}
//	}
//
//	cout << "Shortest Path: ";
//	for (int i = 0; i < pathLength; i++) {
//		if (path[i] >= 0) {
//			cout << path[i];
//			if (i != pathLength - 1) {
//				cout << " -> ";
//			}
//		}
//	}
//	cout << endl;
//
//	for (int i = 0; i < n; i++) {
//		delete[] c[i];
//	}
//	delete[] c;
//
//}
//
//int main() {
//	q3Test1();
//	cout << endl;
//	q3Test2();
//
//	return 0;
//}
