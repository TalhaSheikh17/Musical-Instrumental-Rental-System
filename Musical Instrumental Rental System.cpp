#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ANSI Colors
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

// ================= BASE CLASS =================
class Instrument {
protected:
    string name;
    string condition;
    bool available;
    int id;

public:
    Instrument(string n, string c, int i) {
        name = n;
        condition = c;
        id = i;
        available = true;
    }

    virtual ~Instrument() {}

    virtual double calculateRental(int days) = 0;
    virtual void showDetails() = 0;

    bool isAvailable() { return available; }
    void rent() { available = false; }
    void makeAvailable() { available = true; }

    int getId() { return id; }
    string getName() { return name; }
    string getCondition() { return condition; }
};

// ================= DERIVED CLASSES =================
class Guitar : public Instrument {
public:
    Guitar(int id) : Instrument("Guitar", "New", id) {}

    double calculateRental(int days) {
        return days * 20.0;
    }

    void showDetails() {
        cout << "Guitar | Condition: " << condition << " | ID: " << id << endl;
    }
};

class Piano : public Instrument {
public:
    Piano(int id) : Instrument("Piano", "Used", id) {}

    double calculateRental(int days) {
        return days * 35.0;
    }

    void showDetails() {
        cout << "Piano | Condition: " << condition << " | ID: " << id << endl;
    }
};

class Drum : public Instrument {
public:
    Drum(int id) : Instrument("Drum", "New", id) {}

    double calculateRental(int days) {
        return days * 25.0;
    }

    void showDetails() {
        cout << "Drum | Condition: " << condition << " | ID: " << id << endl;
    }
};

class Violin : public Instrument {
public:
    Violin(int id) : Instrument("Violin", "N/M", id) {}

    double calculateRental(int days) {
        return days * 15.0;
    }

    void showDetails() {
        cout << "Violin | Condition: " << condition << " | ID: " << id << endl;
    }
};

class Flute : public Instrument {
public:
    Flute(int id) : Instrument("Flute", "Used", id) {}

    double calculateRental(int days) {
        return days * 10.0;
    }

    void showDetails() {
        cout << "Flute | Condition: " << condition << " | ID: " << id << endl;
    }
};

// ================= CUSTOMER CLASS =================
class Customer {
    string name;
    int bookingId;
    static int nextId;

public:
    Customer(string n) {
        name = n;
        bookingId = ++nextId;
    }

    int getBookingId() { return bookingId; }
    string getName() { return name; }
};

int Customer::nextId = 1000;

// ================= RENTAL SYSTEM =================
class RentalSystem {
    vector<Instrument*> instruments;

public:
    RentalSystem() {
        instruments.push_back(new Guitar(1));
        instruments.push_back(new Piano(2));
        instruments.push_back(new Drum(3));
        instruments.push_back(new Violin(4));
        instruments.push_back(new Flute(5));
    }

    ~RentalSystem() {
        for (int i = 0; i < instruments.size(); i++) {
            delete instruments[i];
        }
    }

    void displayInstruments() {
        cout << "\n---------------------------------------------\n";
        cout << "| ID | Instrument | Condition | Status      |\n";
        cout << "---------------------------------------------\n";

        for (int i = 0; i < instruments.size(); i++) {
            cout << "| " << setw(2) << instruments[i]->getId()
                 << " | " << setw(10) << instruments[i]->getName()
                 << " | " << setw(10) << instruments[i]->getCondition()
                 << " | " << (instruments[i]->isAvailable()  ? "Available" : "Rented") << " |\n";
        }

        cout << "---------------------------------------------\n";
    }

    void showRates() {
        cout << "\nRental Rates Per Day:\n";
        cout << "Guitar : $20\n";
        cout << "Piano  : $35\n";
        cout << "Drum   : $25\n";
        cout << "Violin : $15\n";
        cout << "Flute  : $10\n";
    }

    void rentInstrument() {
        string cname;
        int id, days;

        cout << "\nEnter your name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, cname);

        Customer c(cname);

        displayInstruments();

        cout << "\nEnter Instrument ID: ";
        cin >> id;

        cout << "Enter days: ";
        cin >> days;

        for (int i = 0; i < instruments.size(); i++) {
            if (instruments[i]->getId() == id && instruments[i]->isAvailable()) {

                double cost = instruments[i]->calculateRental(days);
                instruments[i]->rent();

                cout << GREEN;
                cout << "\n===== RENT CONFIRMATION =====\n";
                cout << "Customer: " << c.getName() << endl;
                cout << "Booking ID: " << c.getBookingId() << endl;
                cout << "Instrument: " << instruments[i]->getName() << endl;
                cout << "Days: " << days << endl;
                cout << "Total Cost: $" << cost << endl;
                cout << "============================\n";
                cout << RESET;

                return;
            }
        }

        cout << RED << "\nInvalid ID or already rented!\n" << RESET;
    }
};

// ================= MAIN =================
int main() {
    RentalSystem system;
    int choice;

    cout << "===== MUSIC RENTAL SYSTEM =====\n";

    do {
        cout << "\n1. Show Instruments";
        cout << "\n2. Rent Instrument";
        cout << "\n3. Show Rates";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.displayInstruments();
            break;

        case 2:
            system.rentInstrument();
            break;

        case 3:
            system.showRates();
            break;

        case 4:
            cout << "\nThank you!\n";
            break;

        default:
            cout << RED << "Invalid choice!\n" << RESET;
        }

    } while (choice != 4);

    return 0;
}
