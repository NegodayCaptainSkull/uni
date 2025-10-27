#include <iostream>
#include <vector>
#include <random>

using namespace std;

int random_int(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void task1() {
    int n;
    cout << "Input array length" << endl;
    cin >> n;
    int* randoms = new int[n];
    int sum = 0;

    for (int i = 0; i < n; i++) {
        randoms[i] = random_int(1, 10000);
        sum += randoms[i];
        if (i == 0) {
            cout << "{";
        }
        cout << randoms[i];
        if (i == n - 1) {
            cout << "}" << endl;
        }
        else {
            cout << " ";
        }

    }

    double average = sum / n;
    cout << average;
    delete[] randoms;
}

void task2() {
    int n;
    cout << "Input array length" << endl;
    cin >> n;
    vector<int> randoms;

    int chetCount = 0;
    int nechetCount = 0;

    for (int i = 0; i < n; i++) {
        randoms.push_back(random_int(1, 123213));
        if (randoms[i] % 2 == 0) {
            chetCount++;
        }
        else if (randoms[i] % 2 != 0) {
            nechetCount++;
        }

        if (i == 0) {
            cout << "{";
        }
        cout << randoms[i];
        if (i == n - 1) {
            cout << "}" << endl;
        }
        else {
            cout << " ";
        }
    }

    cout << "Even counter: " << chetCount << endl;
    cout << "Odd counter: " << nechetCount << endl;
}

void task3() {
    int n;
    cout << "Input array length" << endl;
    cin >> n;
    vector<int> randoms;

    int max = 0;
    int min = 0;

    for (int i = 0; i < n; i++) {
        randoms.push_back(random_int(1, 123213));
        if (i == 0) {
            max = randoms[i];
            min = randoms[i];
        }
        else {
            if (randoms[i] > max) {
                max = randoms[i];
            }
            if (randoms[i] < min) {
                min = randoms[i];
            }
        }
    }

    cout << "Max: " << max << endl;
    cout << "Min: " << min << endl;
}

void task4() {
    const int N = 10;
    const int M = 14;
    int matrix[N][M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int num = random_int(1, 541);
            matrix[i][j] = num;
            if (i == 0) {
                if (j == 0) {
                    cout << "{" << num << " ";
                }
                else if (j == M - 1) {
                    cout << num << endl;
                }
                else {
                    cout << num << " ";
                }
            }
            else if (i == N - 1) {
                if (j == M - 1) {
                    cout << " " << num << "}" << endl;
                }
                else {
                    cout << " " << num;
                }
            }
            else {
                if (j == M - 1) {
                    cout << " " << num << endl;
                }
                else {
                    cout << " " << num;
                }
            }
        }
    }
}

void task5() {
    int N;
    int M;
    cout << "Input N: ";
    cin >> N;
    cout << "Input M: ";
    cin >> M;

    int sum = 0;

    vector<vector<int>> matrix;
    for (int i = 0; i < N; i++) {
        vector<int> voidVector;
        matrix.push_back(voidVector);
        for (int j = 0; j < M; j++) {
            matrix[i].push_back(random_int(1, 10));
            sum += matrix[i][j];
        }
    }

    cout << sum << endl;
}

void task6() {
    int N;
    int M;
    cout << "Input N: ";
    cin >> N;
    cout << "Input M: ";
    cin >> M;

    int sum = 0;

    vector<vector<int>> matrix (N, vector<int>(M));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = random_int(1, 10);
            if (i == j) {
                sum += matrix[i][j];
            }
        }
    }

    cout << sum << endl;
}

void task7() {
    int n;
    vector<int> lessons;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int newLesson;
        cin >> newLesson;
        lessons.push_back(newLesson);
    }

    int studentsLeft = 0;

    bool probablyPosibleToDelete = true;
    while (probablyPosibleToDelete) {
        probablyPosibleToDelete = false;
        vector<int> indexesToDelete;
        for (int i = 0; i < lessons.size() - 1; i++) {
            if (lessons[i] == lessons[i + 1]) {
                probablyPosibleToDelete = true;
                indexesToDelete.push_back(i);
                indexesToDelete.push_back(i+1);
            }
        }
        sort(indexesToDelete.begin(), indexesToDelete.end());
        indexesToDelete.erase(unique(indexesToDelete.begin(), indexesToDelete.end()), indexesToDelete.end());
        for (int j = 0; j < indexesToDelete.size(); j++) {
            sort(indexesToDelete.rbegin(), indexesToDelete.rend());
            lessons.erase(lessons.begin() + indexesToDelete[j]);
        }
        studentsLeft += indexesToDelete.size();
    }

    cout << studentsLeft << endl;
}

void task8() {
    int n;
    cout << "Input N: ";
    cin >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
     
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i + j <= n) {
                matrix[i-1][j-1] = 0;
            }
            else if (i + j == n + 1) {
                matrix[i-1][j-1] = 1;
            }
            else if (i + j > n + 1) {
                matrix[i-1][j-1] = 2;
            }
        }
    }

    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != n; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void task9() {
    int N, M, W;
    cin >> N >> M;
    cin >> W;
    vector<vector<int>> positions(W, vector<int>(2));

    vector<vector<int>> map(N, vector<int>(M));

    for (int i = 0; i < W; i++) {
        cin >> positions[i][0] >> positions[i][1];
        map[positions[i][0] - 1][positions[i][1] - 1] = -1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] != -1) {
                int counter = 0;
                for (int iFind = i - 1; iFind <= i + 1; iFind++) {
                    if (iFind < 0 || iFind >= N) {
                        break;
                    }
                    for (int jFind = j - 1; jFind <= j + 1; jFind++) {
                        if (jFind < 0 || jFind >= M) {
                            break;
                        }
                        if (map[iFind][jFind] == -1) {
                            counter++;
                        }
                    }
                }
                map[i][j] = counter;
            }
            if (map[i][j] == -1) {
                cout << "*" << " ";
            }
            else {
                cout << map[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main()
{
    task9();
}