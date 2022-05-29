#include "iostream"
#include "list"
#include "vector"

using namespace std;

// Task 1

void addElement(list<float> *myList ) {
    float average, sum = 0;

    for (auto i : *myList) {
        sum += i;
    }

    average = sum / myList->size();
    myList->push_back(average);
}


// Task 2

using d2Vector = vector<vector<int>>;

class Matrix {
public:
    Matrix(){}

    void getMatrixWithoutRowAndCol(d2Vector &matrix, int size, int row, int col, d2Vector &newMatrix) {
        int offsetRow = 0;
        int offsetCol = 0;

        for(int i = 0; i < size-1; i++) {
            if(i == row) {
                offsetRow = 1;
            }

            offsetCol = 0;
            for(int j = 0; j < size-1; j++) {
                if(j == col) {
                    offsetCol = 1;
                }
                newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
            }
        }
    }

    int matrixDet(d2Vector &matrix, int size) {
        float det = 0;
        int degree = 1;

        if(size == 1) {
            return matrix[0][0];
        }
        if(size == 2) {
            return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
        }

        d2Vector newMatrix( size-1, vector<int> (size-1, 0));

        for(int j = 0; j < size; j++) {
            getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);
            det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size-1));

            degree = -degree;
        }

        return det;
    }
};


// Task 3
template<typename ValueType>
class OwnIterator: public std::iterator<std::input_iterator_tag, ValueType>
{
private:
    OwnIterator<ValueType>(ValueType *p) : p(p) {}
public:
    OwnIterator(const OwnIterator &it){
        p(it.p);
    };

    bool operator!=(OwnIterator const& other) const {
        return p != other.p;
    };
    bool operator==(OwnIterator const& other) const {
        return p == other.p;
    };
    typename OwnIterator::reference operator*() const {
        return *p;
    };
    OwnIterator& operator++() {
        ++p;
        return *this;
    };
private:
    ValueType* p;
};


int main() {

    // Task 1
    list<float> myList {8, 4, 3, 7, 5, 15};

    addElement(&myList);

    for (auto i : myList) {
        cout << "element: " << i << " ";
    }
    cout << '\n';


    // Task 2
    Matrix matrix;

    d2Vector MyVector1 = {{7}};
    d2Vector MyVector2 = {{7, 2}, {-4, -6}};
    d2Vector MyVector3 = {{-1,  7, -6}, {-8, -4, -1}, {2, 1, 5}};
    d2Vector MyVector4 = {{-1,  7, -6,  3}, {-8, -4, -1, 2}, {2, 1, 5, -4}, {6, -1, 3, -1}};

    cout << matrix.matrixDet(MyVector1, 1) << endl;
    cout << matrix.matrixDet(MyVector2, 2) << endl;
    cout << matrix.matrixDet(MyVector3, 3) << endl;
    cout << matrix.matrixDet(MyVector4, 4) << endl;

    
    // Task 3
    int myArr[6] {8, 4, 3, 7, 5, 15};

    for(auto OwnIterator : myArr){
        cout << OwnIterator << "  ";
    }

    return 0;
}
