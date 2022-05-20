#include <iostream>
#include <optional>
#include <tuple>
#include <vector>
#include <fstream>
#include <any>
#include <algorithm>

using namespace std;


// Task 1

struct Person {
    string Family, Name;
    optional<string> Surname;

    Person(string family, string name, optional<string> surname) : Family(family), Name(name), Surname(surname){}
    Person(string family, string name) : Family(family), Name(name){}

    friend bool operator< (const Person& person1, const Person& person2);
    friend bool operator== (const Person& person1, const Person& person2);

    virtual ~Person(){}
};

ostream &operator<< (ostream &os, const Person& person){
    return os << person.Family << " " << person.Name << " " << person.Surname.value_or("");
}

bool operator< (const Person& person1, const Person& person2) {
    return tie(person1.Family, person1.Name, person1.Surname) < tie(person2.Family, person2.Name, person2.Surname);
}

bool operator== (const Person& person1, const Person& person2) {
    return tie(person1.Family, person1.Name, person1.Surname) == tie(person2.Family, person2.Name, person2.Surname);
}


// Task 2

struct PhoneNumber {
    int CountryCode, CityCode;
    string Number;
    optional<int> AdditionalNum;
    PhoneNumber(int country, int city, string num, optional<int> add_num)
        : CountryCode(country), CityCode(city), Number(num), AdditionalNum(add_num){}

    PhoneNumber(int country, int city, string num)
        : CountryCode(country), CityCode(city), Number(num){}

    friend bool operator< (const PhoneNumber& pn1, const PhoneNumber& pn2);
    friend bool operator== (const PhoneNumber& pn1, const PhoneNumber& pn2);

    virtual ~PhoneNumber(){}
};

ostream &operator<< (ostream &os, const PhoneNumber& pn) {
    os << "+" << pn.CountryCode << "(" << pn.CityCode << ")" <<  pn.Number;

    if(pn.AdditionalNum.has_value()) {
        os << " " << pn.AdditionalNum.value();
    }
    return os;
}

bool operator< (const PhoneNumber& pn1, const PhoneNumber& pn2) {
    return tie(pn1.CountryCode, pn1.CityCode, pn1.Number, pn1.AdditionalNum)
        < tie(pn2.CountryCode, pn2.CityCode, pn2.Number, pn2.AdditionalNum);
}

bool operator== (const PhoneNumber& pn1, const PhoneNumber& pn2) {
    return tie(pn1.CountryCode, pn1.CityCode, pn1.Number, pn1.AdditionalNum)
        == tie(pn2.CountryCode, pn2.CityCode, pn2.Number, pn2.AdditionalNum);
}

// Task 3
// Создайте класс PhoneBook, который будет в контейнере хранить пары: Человек – Номер телефона.
// Конструктор этого класса должен принимать параметр типа ifstream – поток данных, полученных из файла.
// В теле конструктора происходит считывание данных из файла и заполнение контейнера.
// Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.

optional<string> getStrVal(string s) {
    if(s != "*"){
        return s;
    }
    else
        return nullopt;
}

optional<int> getIntVal(string s) {
    if(s != "*" && !s.empty()) {
        return atoi(s.c_str());
    }
    else
        return nullopt;
}

using PhonePair = pair<Person, PhoneNumber>;

class PhoneBook {
private:

public:
    vector<PhonePair> container;

    PhoneBook(ifstream& readFile) {
        vector<string> TempWords;
        string Word;
        size_t index;

        while (readFile >> Word)
        {
            TempWords.push_back(Word);
        }

        for (const string &parametr : TempWords) {
            if(!(index % 7)){
                const string Fam = TempWords[index + 0];
                const string Name = TempWords[index + 1];
                const optional<string> Secondname = getStrVal(TempWords[index + 2]);

                const int CountryCode = std::stoi(TempWords[index + 3]);
                const int CityCode = std::stoi(TempWords[index + 4]);
                const string Number = TempWords[index + 5];
                const optional<int> AdditionalNum = getIntVal(TempWords[index + 6]);

                Person p (Fam, Name, Secondname);
                PhoneNumber pn(CountryCode, CityCode, Number, AdditionalNum);

                container.push_back(make_pair(p, pn));
            }
            ++index;
        }
    }

    void SortByName() {
        sort(container.begin(), container.end(), [](const PhonePair &pp1, const PhonePair &pp2) {
            return pp1.first.Family < pp2.first.Family;
        });
    }

    void SortByPhone() {
        sort(container.begin(), container.end(), [](const PhonePair &pp1, const PhonePair &pp2) {
            return pp1.second < pp2.second;
        });
    }

    tuple<string, vector<PhoneNumber>> GetPhoneNumber(const string &FindFamily) {
        int result = 0;
        vector<PhoneNumber> phoneNumbers;

        for(auto &item : container) {
            if(item.first.Family == FindFamily){
                ++result;
                phoneNumbers.push_back(item.second);
            }
        }

        switch (result) {
            case 0: {
                return {"not found", phoneNumbers};
            }
            case 1: {
                return {"", phoneNumbers};
            }
            default: {
                return {"found more than 1", phoneNumbers};
            }
        }
    }

    void ChangePhoneNumber(const Person &p, const PhoneNumber &pn)
    {
        auto entry = find_if(container.begin(), container.end(), [&](const auto &entry)
        {
            return entry.first == p;
        });

        if (entry != container.end())
        {
            entry->second = pn;
        }
    }


    friend ostream& operator<<(ostream &out, const PhoneBook &pb)
    {
        for (const auto& [first, second] : pb.container)
        {
            out << first << ' ' << second << endl;
        }

        return out;
    }

    virtual ~PhoneBook() {}
};



int main() {


    // Task 1
    Person Nikolay("Ivanov", "Ivan", "Ivanovich");
    cout << Nikolay << endl;

    Person Mihail("Petrov", "Michail");
    cout << Mihail << endl;

    Person MihailBro("Petrov", "Michail");

    cout << boolalpha << (Mihail < Nikolay) << endl;
    cout << boolalpha << (Mihail == MihailBro) << endl;

    // Task 2
    PhoneNumber NikolayPhone(7, 3422, "89321213");
    PhoneNumber MihailPhone(7, 563, "54354356", 12);
    PhoneNumber MihailBroPhone(7, 563, "54354356", 12);

    cout << NikolayPhone << endl;
    cout << boolalpha << (NikolayPhone < MihailPhone) << endl;
    cout << boolalpha << (NikolayPhone == MihailPhone) << endl;
    cout << boolalpha << (MihailBroPhone == MihailPhone) << endl;

    // Task 3
    ifstream filebook("../phoneBook.txt");

    if(filebook.is_open()){
        PhoneBook book(filebook);

        cout << book << endl;

        book.SortByName();

        cout << book << endl;

        book.SortByPhone();

        cout << book << endl;

        auto print_phone_number = [&book](const string& surname) {
            cout << surname << "\t";
            auto answer = book.GetPhoneNumber(surname);
            if (get<0>(answer).empty())
            {
                for (size_t i = 0; i < get<1>(answer).size(); ++i)
                {
                    cout << get<1>(answer)[i];
                }
            }
            else
                cout << get<0>(answer);
            cout << endl;
        };

        // вызовы лямбды
        print_phone_number("Ivanov");
        print_phone_number("Petrov");

        book.ChangePhoneNumber(Person { "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber { 7, 123, "15344458", nullopt });
        book.ChangePhoneNumber(Person { "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber { 16, 465, "9155448", 13 });

    }


    return 0;
}
