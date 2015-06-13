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
          char*s = "Dimitrov") : People(n, a),
                                 Mother(n, a, eye),
                                 Father(n, a, s) {
        cout << "Child constr.\n";
    }

    ~Child() {
        cout << "Child destr.\n";
    }

    void printPeople() const {
        People::printPeople();
    }

};




// moodle
class Ticket {
protected:
    char*name;
    double price;

    void copyTicket(char*n, double p) {
        delete[] this -> name;
        this -> name = new char[strlen(n) + 1];
        assert(this -> name);
        strcpy(this -> name, n);

        this -> price = p;
    }

public:
    void setPrice(double pr) {
        this -> price = pr;
    }

    const double getPrice() const {
        return this -> price;
    }

    Ticket(char*n = "Pepelqshka", double p = 10) {
        this -> name = NULL;
        copyTicket(n, p);
    }

    const void printTicket() const {
        cout << this -> name << ' ' << this -> price << endl;
    }

};

Ticket &isItForAdultOrStudent(bool document) {
    if(document)
    {
        Ticket *ticketForAdultOrStudent;
        ticketForAdultOrStudent = new Ticket;
        ticketForAdultOrStudent -> setPrice(5);
        return *ticketForAdultOrStudent;
    }
}

double totalPrice(Ticket*all, int allSize) {
    double priceOfTickets = 0;

    for(int i = 0; i < allSize; i++) {
        priceOfTickets += all[i].getPrice();
    }

    return priceOfTickets;
}





class Vehicle {
private:
    char*name;
    char*model;
    double height;
    double weight;

    void copyVehicle(char*n, char*m, double h, double w) {
        delete[]this -> name;
        this -> name = new char[strlen(n) + 1];
        assert(this -> name);
        strcpy(this -> name, n);

        delete[]this -> model;
        this -> model = new char[strlen(m) + 1];
        assert(this -> model);
        strcpy(this -> model, m);

        this -> height = h;

        this -> weight = w;
    }

public:
    Vehicle(char*n = "Kola",
            char*m = "BMW",
            double h = 250,
            double w = 2) {
        this -> name = NULL;
        this -> model = NULL;
        copyVehicle(n, m, h, w);
    }

    ~Vehicle() {
        delete[]this -> name;
        delete[]this -> model;
    }

    Vehicle(const Vehicle &other) {
        copyVehicle(other.name, other.model, other.height, other.weight);
    }

    Vehicle &operator=(const Vehicle &other) {
        if(this != &other) {
            copyVehicle(other.name, other.model, other.height, other.weight);
        }
        return *this;
    }

    bool canPassUnderBridge(float bridge)  const {
        return this -> height < bridge;
    }

    bool canPassOverBridge(float tons) const {
        return this -> weight < tons;
    }

};

class landVehicle : virtual public Vehicle {
private:
    double maxSpeed;
    int HP;

public:
    landVehicle(char*n = "Mercedes",
                char*m = "S",
                double h = 150,
                double w = 2.5,
                double mSpeed = 300,
                int hp = 200) : Vehicle(n, m, h, w) {
        this -> maxSpeed = mSpeed;
        this -> HP = hp;
    }

    float getTime(float distance) const {
        return distance / this -> maxSpeed;
    }
};

class waterVehicle : virtual public Vehicle {
private:
    double vodoizmestimost;
    double maxSpeedInNotes;

public:
    waterVehicle(char*n = "Vidra",
                 char*m = "Hidra",
                 double h = 400,
                 double w = 3.4,
                 double v = 5.1,
                 double mSp = 200) : Vehicle(n, m, h, w) {
        this -> vodoizmestimost = v;
        this -> maxSpeedInNotes = mSp;
    }

    float getSpeedUpStream(float speedStream) const {
        return this -> maxSpeedInNotes - speedStream;
    }

    float getSpeedDownStream(float speedStreem) const {
        return this -> maxSpeedInNotes + speedStreem;
    }

    float getTimeUpStream(float distanceToTravel,
                          float speedStream) const {
        return distanceToTravel / getSpeedUpStream(speedStream);
    }

    float getTimeDownStream(float distanceToTravel,
                            float speedStreem) const {
        return distanceToTravel / getSpeedDownStream(speedStreem);
    }
};

class AmphibiousVehicle : public landVehicle, public waterVehicle {
public:
    AmphibiousVehicle(char*n = "Amphibia",
                      char*m = "c200",
                      double h = 111,
                      double w = 2.75,
                      double mSpeed = 150,
                      int hp = 222,
                      double v = 3.14,
                      double mSp = 30) : Vehicle(n, m, h, w),
                                         landVehicle(n, m, h, w, mSpeed, hp),
                                         waterVehicle(n, m, h, w, v, mSp) { }
    bool canGetThrough(int earthDist,
                       float bridgeHeight,
                       float waterDist,
                       float stream) {
        return getTime(earthDist) +
               waterVehicle::getTimeUpStream(waterDist, stream) < 60.0 &&
               canPassUnderBridge(bridgeHeight);
    }
};





class Player {
protected:
    char*name;
    double athletic;
    double discipline;
    char skill;

public:
    //THE BIG 4 !

    virtual void setName(char*n) = 0;

    virtual char*getName() const = 0;

    virtual double getPotential() const = 0;

    virtual double getPercentToFail() const = 0;

    virtual double getSalary() const = 0;

    virtual char*getType() const = 0;

};

class FP : public Player {
private:
    double monthSalary;

public:
    //THE BIG 4 !

    virtual double getPotential() const {
        return this -> athletic * this -> skill + this -> discipline;
    }

    virtual double getPercentToFail() const {
        return this -> discipline - this -> skill;
    }

    virtual double getSalary() const {
        return this -> monthSalary;
    }

    virtual char*getType() const {
        return "football player";
    }

};

class VP : public Player {
private:
    double daySalary;

public:
    //THE BIG 4 !

    virtual double getPotential() const {
        return this -> athletic + this -> skill + this -> discipline;
    }

    virtual double getPercentToFail() const {
        return this -> discipline - this -> skill - this -> athletic;
    }

    virtual double getSalary() const {
        return this -> daySalary * 30;
    }

    virtual char*getType() const {
        return "volleyball player";
    }

};


class Team {
private:
    char*name;
    Player*all;
    int numberOfPlayers;

public:
    // THE BIG 4 !

    virtual bool addPlayer(Player &some) = 0;

    virtual bool rmvPlayer(char*n) = 0;

    virtual double calculateBills() = 0;

};

class FT : virtual public Team {
public:
     //THE BIG 4 !

     virtual bool addPlayer(Player &some) {
        if(strcmp(some.getName(), "football player") == 0) {
            //...
            return true;
        }
        else
            return false;
     }

     virtual bool rmvPlayer(char*n) {
        //for...
     }

     virtual double calculateBills() {
        //find the size of array

        //return teamSize * getSalary();
     }

};

class VT : virtual public Team {
public:
    //THE BIG 4 !

    //the same as FT

};

class CT : public FT, public VT {
public:
    //THE BIG 4 !

    virtual bool addPlayer(Player &some) {
        //if football || volleyball..
    }

    virtual bool rmvPlayer(char*n) {
        //for...
     }

    virtual double calculateBills() {
        //find the size of array

        //return teamSize * getSalary();
     }

};




int main()
{



    return 0;
}
