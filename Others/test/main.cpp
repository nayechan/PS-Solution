#include <iostream>

using namespace std;

class Person{
    int age;
    string name;
    friend std::hash<Person>;
public:
    Person(int age, string name):age(age),name(name){}
};

template <typename T>
class allocator{
    public:
        template <typename U>
        struct rebind
        {
            typedef allocator<U> other;
        };
};

namespace std{
    template <>
    struct hash<Person>
    {
        size_t operator()(const Person &person) const
        {
            return person.age ^ hash<string>()(person.name);
        }
    };
}



int main()
{
    int age;
    string name;
    cin >> age >> name;
    cout << hash<Person>()(Person(age, name));
    return 0;
}