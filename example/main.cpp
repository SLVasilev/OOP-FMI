#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

class People {
private:
    char*name;
    int age;
    void init(char*n, int a) {
        delete[]this -> name;
        this -> name = new char[strlen(n) + 1];
        assert(name);
        strcpy(this -> name, n);

        this -> age = a;
    }

public:
    People(char*n = "Ivan", int a = 20) {
        cout << "constr. People\n";
        this -> name = NULL;
        init(n, a);
    }

    ~People() {
        cout << "destr.People\n";
        delete[]this -> name;
    }

    People(const People &other) {
        cout << "copy constr. People\n";
        init(other.name, other.age);
    }

    People &operator=(const People &other) {
        cout << "operator= People\n";
        if(this != &other) {
            init(other.name, other.age);
        }
        return *this;
    }

    virtual void printPeople() const {
        cout << this -> name << ' ' << this -> age << endl;
    }

};

class Mother : virtual public People {
private:
    char*eyeColour;

public:
    void setEyeColour(char*eye) {
        delete[]this -> eyeColour;
        this -> eyeColour = new char[strlen(eye) + 1];
        assert(eyeColour);
        strcpy(this -> eyeColour, eye);
    }

    Mother(char*n = "Maria", int a = 30, char*e = "Blue") : People(n, a) {
            cout << "Mother constr.\n";
        this -> eyeColour = NULL;
        setEyeColour(e);
    }

    ~Mother() {
        cout << "destr. Mother\n";
        delete[]this -> eyeColour;
    }

    Mother(const Mother &other) : People(other) {
        cout << "copy constr. Mother\n";
        setEyeColour(other.eyeColour);
    }

    Mother &operator=(const Mother &other) {
        if(this != &other) {
            People::operator=(other);
            setEyeColour(other.eyeColour);
        }
        return *this;
    }

    void printPeople() const {
        People::printPeople();
        cout << this -> eyeColour << endl;
    }

};

class Father : virtual public People {
private:
    char*surName;

public:
    void setSurName(char*s) {
        delete[]this -> surName;
        this -> surName = new char[strlen(s) + 1];
        assert(surName);
        strcpy(this -> surName, s);
    }

    Father(char*n = "Mitko", int a = 40, char*s = "Ivanov") : People(n, a) {
        cout << "Father constr\n";
        this -> surName = NULL;
        setSurName(s);
    }

    ~Father() {
        cout << "Father destr.\n";
        delete[]this -> surName;
    }

    Father(const Father &other) : People(other) {
        cout << "Father constr.\n";
        setSurName(other.surName);
    }

    Father &operator=(const Father &other) {
        cout << "Father operator=\n";
        if(this != &other) {
            People::operator=(other);
            setSurName(other.surName);
        }
        return *this;
    }

    void printPeople() const {
        People::printPeople();
        cout << this -> surName << endl;
    }

};

class Child : virtual public People, public Mother, public Father {
public:
    Child(char*n = "Geoshko",
          int a = 10,
          char*eye = "Green",
          char*s = "Dimitrov") : People(n, a), Mother(eye), Father(s) {
        cout << "Child constr.\n";
    }

    ~Child() {
        cout << "Child destr.\n";
    }

    void printPeople() const {
        People::printPeople();
    }

};


int main()
{
    Child c;
    Mother m;
    Father f;
    c.printPeople();

    return 0;
}
