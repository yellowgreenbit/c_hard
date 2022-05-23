#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;


// Task 1
template <typename T>
void Swap (T &first, T &second) {
    T temp = first;
    first = second;
    second = temp;
}

// Task 2
template <typename T>
void SortPointers ( vector <T*> &vec) {
    sort(vec.begin(), vec.end(), [](T* first, T* second){
        return *first < *second;
    });
}

// Task 3
class Timer{
private:
    using clock_t = chrono::high_resolution_clock;
    using second_t = chrono::duration<double, ratio<1> >;

    string m_name;
    chrono::time_point<clock_t> m_beg;

    double elapsed() const
    {
        return chrono::duration_cast<second_t>(clock_t::now() -m_beg).count();
    }

public:
    Timer() : m_beg(clock_t::now()){}
    Timer(string name) : m_name(name), m_beg(clock_t::now()) {}

    void Start(string name){
        m_name = name;
        m_beg = clock_t::now();
    }

    void Print() const {
        cout << m_name << ":\t" << elapsed() * 100 << "ms" << endl;
    }

};

const string vowelLetters = "AEIOUYaeiouy";

// count_if и find
int GetVowelLetters1(const string &FilebookText){
    size_t countLetters {0};

    countLetters += count_if(FilebookText.begin(), FilebookText.end(), [&](const char &letter){
        return vowelLetters.find(letter) != string::npos;
    });

    return countLetters;
}

//count_if и цикл for
int GetVowelLetters2(const string &FilebookText){
    size_t countLetters {0};

    countLetters += count_if(FilebookText.begin(), FilebookText.end(), [&](const char &letter){
        bool result {false};
        for (auto c : vowelLetters) {
            if(c == letter){
                result = true;
                break;
            }
        }
        return result;
    });

    return countLetters;
}

//цикл for и find
int GetVowelLetters3(const string &FilebookText){
    size_t countLetters {0};

    for (char letter : FilebookText) {
        if(vowelLetters.find(letter) != string::npos){
            countLetters++;
        };
    }

    return countLetters;
}

//цикл for и for
int GetVowelLetters4(const string &FilebookText){
    size_t countLetters {0};

    for (char letter : FilebookText) {
        for (auto c : vowelLetters) {
            if (c == letter && c != string::npos){
                countLetters++;
            }
        }
    }

    return countLetters;
}

int main() {

// Task 1
    int *a = new int {3};
    int *b = new int {5};

    cout << "a: " << *a  << " " << a << "; b: " << *b << " " << b << endl;
    Swap(*a, *b);
    cout << "a: " << *a  << " " << a << "; b: " << *b << " " << b << endl;


// Task 2

    int *c = new int {7};
    int *d = new int {5};
    int *e = new int {1};
    int *f = new int {6};

    vector<int*> IntVector {c, d, e, f};

    for (auto elem : IntVector) {
        cout << "vector element" << *elem  << " " << elem << endl;
    }

    SortPointers(IntVector);

    cout << "sorted" << endl;

    for (auto elem : IntVector) {
        cout << "vector element" << *elem  << " " << elem << endl;
    }


// Task 3

    ifstream filebook("../War_and_peace.txt");

    if(filebook.is_open()){
        filebook.seekg(0, ios_base::end);
        size_t size = filebook.tellg();
        filebook.seekg(0);
        string text(size, ' ');
        filebook.read(&text[0], size);

        Timer timer;
        timer.Start("GetVowelLetters1");
        cout << "count: " << GetVowelLetters1(text) << endl;
        timer.Print();

        timer.Start("GetVowelLetters2");
        cout << "count: " << GetVowelLetters2(text) << endl;
        timer.Print();

        timer.Start("GetVowelLetters3");
        cout << "count: " << GetVowelLetters3(text) << endl;
        timer.Print();

        timer.Start("GetVowelLetters4");
        cout << "count: " << GetVowelLetters4(text) << endl;
        timer.Print();
    }


    filebook.close();
    return 0;
}