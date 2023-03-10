#include <iostream>
#include <fstream>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <unistd.h> // for fork()
#include <sys/wait.h> // for wait()

int main() {
    int n = 5; // size of the matrix and number of processes

    // Generate random number for creating processes
    std::srand(std::time(nullptr)); // seed the random number generator with current time
    int random_num = std::rand() % 99 + 10; // generate a random number between 10 and 99
    int last_digit_roll = 5; // replace this with the last digit of your roll number
    random_num *= last_digit_roll;
    int division_result = 100 / random_num; // divide your roll number with the generated number
    int mod_result = division_result % 25; // take the mod with 25
    if (mod_result < 10) {
        mod_result += 15; // if less than 10, add 15 to it
    }

    // Create and populate the matrix randomly
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = std::rand() % mod_result;
        }
    }

    // Save the matrix to a file
    std::ofstream outfile("matrix.txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            outfile << matrix[i][j] << " ";
        }
        outfile << std::endl;
    }
    outfile.close();

    // Perform matrix multiplication with fork
    for (int i = 0; i < n; i++) {
        int pid = fork();
        if (pid == -1) {
            std::cerr << "Error: Fork failed.\n";
            return 1;
        }
        else if (pid == 0) {
            // Child process
            std::ofstream result_file("result_" + std::to_string(i) + ".txt");
            for (int j = 0; j < n; j++) {
                int result = 0;
                for (int k = 0; k < n; k++) {
                    result += matrix[i][k] * matrix[k][j];
                }
                result_file << result << " ";
            }
            result_file.close();
            return 0;
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < n; i++) {
        wait(nullptr);
    }

    // Deallocate memory for the matrix
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
