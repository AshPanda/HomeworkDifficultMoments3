/*
1. Написать функцию, добавляющую в конец списка вещественных чисел
элемент, значение которого равно среднему арифметическому всех его
элементов.
2. Создать класс, представляющий матрицу. Реализовать в нем метод,
вычисляющий определитель матрицы. Для реализации используйте
контейнеры из STL.
3. Реализовать собственный класс итератора, с помощью которого можно будет
проитерироваться по диапазону целых чисел в цикле for-range-based
*/

#include <iostream>
#include <list>
#include <vector>


using namespace std;

//Task #1

void Task1(list <double>& task1)
{
    list < double > ::const_iterator  p = task1.begin();
    double sum(0);
    int    n=0;
    while (p != task1.end())
    {
        sum = sum + *p;
        ++n;
        ++p;
    }
    if (n != 0) task1.push_back(sum / n);
    cout << "\nArithmetic mean: "<< sum/n << endl;
 }

//Task #2
class Matrix
{
public:
    Matrix() {
        cout << "Enter the size of a matrix: " << endl;
        int size;
        int rows;
        int columns;
        cin >> size;
        columns = size;
        rows = columns;
        srand(time(0));

        cout << "Matrix: " << endl;

        MyMatrix.resize(rows);
        for (int i = 0; i < MyMatrix.size(); i++)
        {
            MyMatrix[i].resize(columns);
            for (int j = 0; j < MyMatrix[i].size(); j++)
            {

                MyMatrix[i][j] = rand() % 150;
                cout << MyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    void getMatrixWithoutRowAndCol(int** MyMatrix, int size, int row, int col, int** tempMyMatrix) {
        int offsetRow = 0;
        int offsetCol = 0;
        for (int i = 0; i < size - 1; i++) {
            if (i == row) {
                offsetRow = 1;
            }

            offsetCol = 0;
            for (int j = 0; j < size - 1; j++) {
                if (j == col) {
                    offsetCol = 1;
                }

                tempMyMatrix[i][j] = MyMatrix[i + offsetRow][j + offsetCol];
            }
        }
    }
    int Determinant(int** MyMatrix, int size) {
        int determinant = 0;
        int degree = 1;

        if (size == 1) {
            return MyMatrix[0][0];
        }
        if (size == 2) {
            return MyMatrix[0][0] * MyMatrix[1][1] - MyMatrix[0][1] * MyMatrix[1][0];
        }

        int** tempMyMatrix = new int* [size - 1];
        for (int i = 0; i < size - 1; i++) {
            tempMyMatrix[i] = new int[size - 1];
        }
        for (int j = 0; j < size; j++) {
            getMatrixWithoutRowAndCol(MyMatrix, size, 0, j, tempMyMatrix);
            determinant = determinant + (degree * MyMatrix[0][j] * Determinant(tempMyMatrix, size - 1));
            degree = -degree;
        }
        for (int i = 0; i < size - 1; i++) {
            delete[] tempMyMatrix[i];
        }
        delete[] tempMyMatrix;

        return determinant;
        cout << determinant << endl;
    }

protected:
    vector< vector< int > > MyMatrix;
    vector< vector< int > > tempMyMatrix;

};
//Task #3
class MyRange {
private:
    size_t MyIdx;
    const vector<int>& MyValues;
public:
    MyRange( const vector<int>& values) :  MyValues(values) {}

    auto operator*() const { return MyValues[MyIdx]; }
    auto& operator++()
    {
        MyIdx++;
        return *this;
    }
    bool operator!=(const MyRange& rhs) const { return MyIdx != rhs.MyIdx; }
    auto begin() const -> decltype(MyValues.begin()) { return MyValues.begin(); }
    auto end() const -> decltype(MyValues.end()) { return MyValues.end(); }
};

int main()
{
    cout << "Task #1" << endl;
    list<double> task1{ 10,223,36,4 };
    cout << "List:" << endl;
    for (auto listNumber : task1)
    {
        cout  << listNumber << " ";
    }
    Task1(task1);
    cout << "\n" << endl;
    cout << "Task #2" << endl;
    Matrix MyMatrix;

    cout << "\n" << endl;
    cout << "Task #3" << endl;
    const vector<int> values = { 1, 2, 3, 4, 6, 2 };
    for (const int& val : MyRange(values))
    {
       cout << val << endl;
    }

    return 0;

}
