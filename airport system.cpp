#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

class Passenger {
protected:
    string name;
    int age;
    float weight;
    double balance;
    int seatNumber;
public:
    Passenger(string n, int a, float w, double b) : name(n), age(a), weight(w), balance(b), seatNumber(-1) {}
    virtual ~Passenger() {}
    virtual double getTicketPrice() const = 0;
    void setSeatNumber(int seat) { seatNumber = seat; }
    int getSeatNumber() const { return seatNumber; }
    string getName() const { return name; }
    double getBalance() const { return balance; }
    void deductBalance(double amount) { balance -= amount; }
};

class BusinessPassenger : public Passenger {
public:
    BusinessPassenger(string n, int a, float w, double b) : Passenger(n, a, w, b) {}
    double getTicketPrice() const override { return 500.0; }
};

class EconomyPassenger : public Passenger {
public:
    EconomyPassenger(string n, int a, float w, double b) : Passenger(n, a, w, b) {}
    double getTicketPrice() const override { return 200.0; }
};

class Airplane {
private:
    vector<Passenger*> seats;
    int capacity;
public:
    Airplane(int c) : capacity(c) { seats.resize(c, nullptr); }
    ~Airplane() {
        for (auto p : seats) if (p) delete p;
    }

    bool bookSeat(Passenger* p, int seat) {
        if (seat < 0 || seat >= capacity || seats[seat] != nullptr) {
            cout << "Seat not available!\n";
            return false;
        }
        double price = p->getTicketPrice();
        if (p->getBalance() < price) {
            cout << "Not enough balance!\n";
            return false;
        }
        p->deductBalance(price);
        p->setSeatNumber(seat);
        seats[seat] = p;
        cout << "Seat booked successfully!\n";
        return true;
    }

    void removeBooking(int seat) {
        if (seat < 0 || seat >= capacity || !seats[seat]) {
            cout << "Invalid seat number!\n";
            return;
        }
        delete seats[seat];
        seats[seat] = nullptr;
        cout << "Booking removed successfully!\n";
    }

    void swapSeats(int s1, int s2) {
        if (s1 < 0 || s1 >= capacity || s2 < 0 || s2 >= capacity || !seats[s1] || !seats[s2]) {
            cout << "Invalid swap operation!\n";
            return;
        }
        swap(seats[s1], seats[s2]);
        seats[s1]->setSeatNumber(s1);
        seats[s2]->setSeatNumber(s2);
        cout << "Seats swapped successfully!\n";
    }

    void searchPassenger(string name) {
        for (auto p : seats) {
            if (p && p->getName() == name) {
                cout << "Passenger " << name << " found at seat " << p->getSeatNumber() << "\n";
                return;
            }
        }
        cout << "Passenger not found!\n";
    }
};

void menu() {
    Airplane plane(10);
    while (true) {
        cout << "\n1. Book Seat\n2. Remove Booking\n3. Swap Seats\n4. Search Passenger\n5. Exit\nChoose: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            string name;
            int age, type, seat;
            float weight;
            double balance;
            cout << "Enter Name, Age, Weight, Balance: ";
            cin >> name >> age >> weight >> balance;
            cout << "Enter 1 for Business, 2 for Economy: ";
            cin >> type;
            cout << "Enter Seat Number: ";
            cin >> seat;
            Passenger* p = (type == 1) ? (Passenger*)new BusinessPassenger(name, age, weight, balance) : (Passenger*)new EconomyPassenger(name, age, weight, balance);
            plane.bookSeat(p, seat);
        } else if (choice == 2) {
            int seat;
            cout << "Enter Seat Number: ";
            cin >> seat;
            plane.removeBooking(seat);
        } else if (choice == 3) {
            int s1, s2;
            cout << "Enter two seat numbers to swap: ";
            cin >> s1 >> s2;
            plane.swapSeats(s1, s2);
        } else if (choice == 4) {
            string name;
            cout << "Enter Passenger Name: ";
            cin >> name;
            plane.searchPassenger(name);
        } else if (choice == 5) {
            break;
        }
    }
}

int main() {
    menu();
    return 0;
}
