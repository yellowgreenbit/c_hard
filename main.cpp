#include "iostream"
#include "vector"
#include "algorithm"
#include "math.h"

using namespace std;

// Task 1

template<class T>
vector<T> insert_sorted(vector<T> &first, const T el){
    vector<T> newVector;
    auto it = find_if(first.begin(), first.end(), [&el](T i){
        return i > el;
    });

    if(it != first.end()){
        copy(first.begin(), it, back_inserter(newVector));
        newVector.push_back(el);
        copy(it, first.end(), back_inserter(newVector));
    } else {
        cout << "pushback" << endl;
        newVector = first;
        newVector.push_back(el);
    }

    return newVector;
}

int main() {

    // Task 1
    vector<int> vec1 = {2, 3, 7};

    vector<int> vec2 = insert_sorted(vec1, 8);
    vector<int> vec3 = insert_sorted(vec2, 1);
    vector<int> vec4 = insert_sorted(vec3, 5);

    for (auto e : vec4) {
        cout << e << ' ';
    }
    cout << endl;

    vector<char> vecA1 = {'A', 'C', 'D'};
    vector<char> vecA2 = insert_sorted(vecA1, 'B');

    for (auto e : vecA2) {
        cout << e << ' ';
    }
    cout << endl;


    // Task 2

    vector<float> analog(100);
    generate (analog.begin(), analog.end(), [](){
        return (rand() / 100.0);
    });

    for (float e : analog) {
        cout << e << ' ';
    }
    cout << endl;

    vector<float> digital;
    float err;
    transform(analog.begin(), analog.end(), back_inserter(digital), [&err](float elF){
        int elI = static_cast<int>(elF);
        err += pow(elF - elI, 2);
        return elI;
    });

    for (float e : digital) {
        cout << e << ' ';
    }
    cout << endl;

    cout << err;

    return 0;
}