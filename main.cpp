#include "iostream"
#include "iterator"
#include "set"
#include "vector"
#include "deque"
#include "list"
#include "array"
#include "map"
#include <algorithm>

using namespace std;


//Task1

template<class T>
void Print(T beg, T end){
    set<string> newSet;
    copy(beg, end, inserter(newSet, newSet.end()));
    for(auto i : newSet) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {


    //Task1

    vector<string> v1 = {"one", "two", "three", "one", "two"};
    Print(v1.begin(), v1.end());

    deque<string> d1{"one", "two", "three", "one", "two"};
    Print(d1.begin(), d1.end());

    list<string> l1{"one", "two", "three", "one", "two"};
    Print(l1.begin(), l1.end());

    array<string, 5> a1{"one", "two", "three", "one", "two"};
    Print(a1.begin(), a1.end());


    //Task2

    map<int, string> clauses;
    string str;
    const string clauseLetters = "!?.";

    cout << "Please, enter text" << endl;
    getline(cin, str);

    //str = "Bon is run. Run Bob faster, run! End.";

    int lastPos = 0;
    int countWS = 1;

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') countWS++;
        if (clauseLetters.find(str[i]) != string::npos) {
            clauses.insert({countWS, str.substr (lastPos, i - lastPos + 1)});
            lastPos = str[i + 1] != ' ' ? i + 1 : i + 2;
            countWS = 0;
        }
    }

    for_each(clauses.begin(), clauses.end(),
         [](pair<int, string> item){
             cout << item.first << " " << item.second << "\n";
         });

    return 0;
}