#include "iostream"
#include "thread"
#include "mutex"
#include "random"
#include "chrono"
#include "algorithm"

using namespace std;

// Task 1
mutex m;

void pcout(int number) {
    m.lock();
    cout << "start thread " << number << endl;
    m.unlock();
}

//Task 2
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
void getSimpleNum(const int Limit, int &count, int &result) {

    for (int i = 2; i < Limit; ++i) {
        count++;
        bool isSimple = true;

        for (int tempJ = 2; tempJ < Limit; ++tempJ) {
            if(i!=tempJ && i % tempJ == 0){
                isSimple = false;
                break;
            }
        }

        if(isSimple) {
            result = i;
        }
    }
}


void printCount(const int &count, const int &total) {
    while (count < total-2){
        cout << "progress:" << static_cast<float>(count) / total * 100 << '\n';
    }
}

//Task 3

int32_t getRandom() {
    mt19937 gen(time(0));
    return gen();
}

void addItem(vector<int> &vec) {
    for (int i = 0; i < 20; ++i) {
        this_thread::sleep_for(chrono::milliseconds(1000));
        // add random val
        int el = getRandom() % 100;
        cout << "add el " << el << endl;
        vec.push_back(el);
    }
}

void removeItem(vector<int> &vec) {
    for (int i = 0; i < 20; ++i) {
        this_thread::sleep_for(chrono::milliseconds (500));
        //cout << "size:" << vec.size() << endl;
        if(vec.size()){
            cout << "remove el " << *max_element(vec.begin(), vec.end());
            vec.erase(max_element(vec.begin(), vec.end()));
        }

    }
}

int main(){
//
//    // Task 1
    thread th1(pcout, 1);
    thread th2(pcout, 2);
    thread th3(pcout, 3);
    th1.join();
    th2.join();
    th3.join();


    // Task 2
    int countSimpleNum {0};
    const int totalCountSimpleNum {1'000'00};
    int result {0};

    Timer timer;
    timer.Start("Get Simple Num");
    thread th4(getSimpleNum, ref(totalCountSimpleNum), ref(countSimpleNum), ref(result));
    thread th5(printCount, ref(countSimpleNum), totalCountSimpleNum);
    th4.detach();
    th5.join();

    cout << "result: " << result << '\n';
    timer.Print();


//    // Task 3
    vector<int> Things;
    thread Owner(addItem, ref(Things));
    thread Thief(removeItem, ref(Things));
    Owner.join();
    Thief.join();

    return 0;
}