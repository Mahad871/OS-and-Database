//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <string>
//#include <cstring>
//#include<sstream>
//#pragma warning(disable : 4996)
//using namespace std;
//
////int total_time = 0;
//
//// Graph class to represent a weighted graph
//class Graph
//{
//public:
//	int num_vertices;
//	int** adj_list;
//
//	Graph(int n)
//	{
//		num_vertices = n;
//		adj_list = new int* [n];
//		for (int i = 0; i < n; i++)
//		{
//			adj_list[i] = new int[n];
//			for (int j = 0; j < n; j++)
//			{
//				adj_list[i][j] = 0; // initialize all elements to 0
//			}
//		}
//	}
//
//	// add an edge to the graph
//	void addEdge(int src, int dest, int weight)
//	{
//		adj_list[src][dest] = weight;
//		adj_list[dest][src] = weight;
//	}
//
//	// print the graph
//	void printGraph()
//	{
//		for (int i = 0; i < num_vertices; i++)
//		{
//			cout << "Vertex " << i << ": ";
//			for (int j = 0; j < num_vertices; j++)
//			{
//				if (adj_list[i][j] != 0)
//				{
//					cout << "(" << j << ", " << adj_list[i][j] << ") ";
//				}
//			}
//			cout << endl;
//		}
//	}
//
//	int* findHamiltonianCircuits(int* shortPath, int* path, bool* visited, int start, int* arr, int curr_pos = 1) {
//		int n = num_vertices;
//		static int shortest_time = INT_MAX; // initialize shortest_time to maximum possible value
//		int total_time = 0; // initialize total_time for this iteration
//		// Base case: if the path contains all vertices and the last vertex is adjacent to the start vertex, it's a valid Hamiltonian circuit
//		if (curr_pos == n && adj_list[path[curr_pos - 1]][start] != 0)
//		{
//			// Calculate total time for this path
//			total_time += arr[path[0]] + adj_list[path[n - 1]][start]; // time to complete the circuit
//			for (int i = 0; i < n - 1; i++)
//			{
//				total_time += arr[path[i + 1]] + adj_list[path[i]][path[i + 1]];
//			}
//
//			// Check if this path has the shortest time
//			if (total_time < shortest_time)
//			{
//				// Update shortest_time and print the path
//				shortest_time = total_time;
//				int i = 0;
//				for (; i < n; i++)
//				{
//					shortPath[i] = path[i];
//					cout << path[i] << " ";
//				}
//				cout << start << " ";
//				shortPath[i] = start;
//				cout << "Total time: " << shortest_time << endl;
//			}
//
//			return shortPath;
//		}
//
//		// Recursive case: extend the path with all unvisited adjacent vertices
//		for (int v = 0; v < n; v++)
//		{
//			if (adj_list[path[curr_pos - 1]][v] != 0 && !visited[v])
//			{
//				bool flag = false;
//				for (int i = 0; i < curr_pos; i++)
//				{
//					if (path[i] == v)
//					{
//						flag = true;
//						break;
//					}
//				}
//				if (!flag)
//				{
//					visited[v] = true;
//					path[curr_pos] = v;
//					findHamiltonianCircuits(shortPath, path, visited, start, arr, curr_pos + 1);
//					visited[v] = false;
//				}
//			}
//		}
//		return shortPath;
//
//	}
//
//	int return_index(char c)
//	{
//		char vertices[27];
//		for (int i = 0; i < 27; i++)
//		{
//			vertices[i] = '\0';
//		}
//		vertices[0] = 'h';
//		for (int i = 1; i < 27; i++)
//		{
//			vertices[i] = 'A' + i - 1; // set capital letters at subsequent indices
//		}
//
//		for (int i = 0; i < 27; i++)
//		{
//			if (vertices[i] == c)
//			{
//				return i;
//			}
//		}
//
//
//	}
//
//
//};
//
//
//int main()
//{
//	ifstream inputFile("P2_test1.txt");
//	vector<vector<char>> lines;
//
//	char c;
//	vector<char> line;
//	while (inputFile.get(c))
//	{
//		if (c == '\n')
//		{
//			lines.push_back(line);
//			line.clear();
//		}
//		else
//		{
//			if (c != ',' && c != '=' && c != '(' && c != '{' && c != ')' && c != '}')
//			{
//				line.push_back(c);
//			}
//		}
//	}
//
//	if (!line.empty())
//	{
//		lines.push_back(line);
//	}
//
//	inputFile.close();
//
//	//// iterate over the lines vector and print each line
//	cout << "TEXT READ FROM FILE" << endl;
//	for (int i = 0; i < lines.size(); i++)
//	{
//		for (int j = 0; j < lines[i].size(); j++)
//		{
//			cout << lines[i][j];
//		}
//		cout << endl;
//	}
//	cout << endl;
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//	int number_of_vertices = 0;
//	for (int i = 1; i < lines[0].size(); i++)
//	{
//		number_of_vertices++;
//		//cout << lines[0][i];
//	}
//	cout << endl;
//	Graph g(number_of_vertices);
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	int numberofedges = lines[1].size() - 1;
//
//	//cout << numberofedges;
//
//	int* edges = new int[numberofedges + 1];
//	int z = 0;
//	for (int i = 1; i < lines[1].size(); i++)
//	{
//		cout << lines[1][i];
//		edges[z] = g.return_index(lines[1][i]);
//		z++;
//	}
//	cout << endl;
//
//
//	for (int i = 0; i < numberofedges; i++)
//	{
//		cout << edges[i];
//	}
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	cout << endl;
//
//	int* weights = new int[numberofedges / 2];
//	z = 0;
//	for (int i = 7; i < lines[1].size(); i++)
//	{
//		cout << lines[2][i];
//		weights[z] = lines[2][i] - 48;
//		z++;
//	}
//	cout << endl;
//	for (int i = 0; i < numberofedges / 2; i++)
//	{
//		cout << weights[i];
//	}
//	cout << endl;
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	int* time = new int[number_of_vertices];
//	time[0] = 0;
//
//	char* liness = new char[lines[3].size() + 1] {'\0'}; // replace with your line
//
//	cout << lines[3][0];
//
//	for (int i = 0; i < lines[3].size(); i++)
//	{
//		liness[i] = lines[3][i];
//	}
//	for (int i = 0; i < lines[3].size(); i++)
//	{
//		cout << liness[i];
//	}
//
//
//	int size = strlen(liness); // get the size of the line
//	int* numbers = new int[size]; // create a dynamic array of integers with the same size as the line
//	int count = 1; // keep track of the number of integers found
//	for (int i = 0; i < size; i++)
//	{
//
//		if (isdigit(liness[i]))
//		{ // if the current character is a digit
//			time[count] = atoi(&liness[i]); // convert the substring starting from the current position to an integer
//			count++; // increment the counter
//			while (isdigit(liness[i + 1])) i++; // skip to the end of the number
//		}
//	}
//	cout << endl;
//	// now you can use the array of integers as needed
//	for (int i = 0; i < count; i++) {
//		cout << time[i] << " ";
//	}
//
//	//////////////////////
//
//	int* waitingTime = new int[number_of_vertices];
//
//	char* waitingLiness = new char[lines[4].size() + 1] {'\0'}; // replace with your line
//
//	cout << lines[4][0];
//
//	for (int i = 0; i < lines[4].size(); i++)
//	{
//		waitingLiness[i] = lines[4][i];
//	}
//	for (int i = 0; i < lines[4].size(); i++)
//	{
//		cout << waitingLiness[i];
//	}
//
//
//	int size1 = strlen(waitingLiness); // get the size1 of the line
//	int* numbers1 = new int[size1]; // create a dynamic array of integers with the same size1 as the line
//	int count1 = 0; // keep track of the number of integers found
//	for (int i = 0; i < size1; i++)
//	{
//
//		if (isdigit(waitingLiness[i]))
//		{ // if the current character is a digit
//			waitingTime[count1] = atoi(&waitingLiness[i]); // convert the substring starting from the current position to an integer
//			count1++; // increment the count1er
//			while (isdigit(waitingLiness[i + 1])) i++; // skip to the end of the number
//		}
//	}
//	cout << endl;
//	// now you can use the array of integers as needed
//	for (int i = 0; i < count1; i++) {
//		cout << waitingTime[i] << " ";
//	}
//
//	
//
//
//
//
//
//
//
//
//
//	//// add edges to the graph
//
//
//	//g.addEdge(0, 1, 2);
//	//g.addEdge(0, 2, 2);
//	//g.addEdge(0, 3, 3);
//	//g.addEdge(1, 2, 4);
//	//g.addEdge(1, 3, 5);
//	//g.addEdge(2, 3, 8);
//	//
//	//// create an array of vertex weights
//	//int* arr = new int[4];
//	//arr[0] = 0;
//	//arr[1] = 5;
//	//arr[2] = 10;
//	//arr[3] = 8;
//	//
//	////// print the graph
//	////cout << "Graph:\n";
//	//g.printGraph();
//	//
//	//int* shortPath = new int[5] {-1, -1, -1, -1, -1}; //5==n+1
//	//
//	//// find Hamiltonian circuits in the graph starting from vertex 0
//	//cout << "Hamiltonian circuits starting from vertex 0:\n";
//	//int path[4] = { 0 };
//	//bool visited[4] = { false,false,false,false };
//	//visited[0] = true;
//	//int* pth = g.findHamiltonianCircuits(shortPath,path, visited, 0, arr);
//	//
//	//for (int i = 0; i < 5; i++) 
//	//{
//	//	cout << pth[i] << " ";
//	//}
//
//	return 0;
//}
