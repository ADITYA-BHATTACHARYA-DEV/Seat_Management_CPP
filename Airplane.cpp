#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

class Airline {
private:
    string Flight, Des, Dep;
    int Seats;

public:
    Airline(string flight, string des, string dep, int seats)
        : Flight(flight), Des(des), Dep(dep), Seats(seats) {}

    string getFlight() { return Flight; }
    string getDes() { return Des; }
    string getDep() { return Dep; }
    int getSeat() { return Seats; }

    void update() {
        ifstream in("C:/Users/samit/OneDrive/Desktop/CBCPP/Flight.txt");
        ofstream out("C:/Users/samit/OneDrive/Desktop/CBCPP/Flight_Temp.txt");
        if (!in || !out) {
            cout << "Error: Unable to open file!" << endl;
            return;
        }

        string line;
        while (getline(in, line)) {
            if (line.find(Flight) != string::npos) {
                // Update seat count
                int current = Seats - 1;
                Seats = current;

                stringstream ss;
                ss << current;
                string strCurrent = ss.str();

                size_t seatPos = line.find_last_of(':');
                line.replace(seatPos + 2, string::npos, strCurrent);
            }
            out << line << endl;
        }
        in.close();
        out.close();

        remove("C:/Users/samit/OneDrive/Desktop/CBCPP/Flight.txt");
        rename("C:/Users/samit/OneDrive/Desktop/CBCPP/Flight_Temp.txt", "C:/Users/samit/OneDrive/Desktop/CBCPP/Flight.txt");

        cout << "Seat Reserved Successfully!" << endl;
    }

    static void display() {
        ifstream in("C:/Users/samit/OneDrive/Desktop/CBCPP/Flight.txt");
        if (!in) {
            cout << "Error: File can't open!" << endl;
            return;
        }

        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
    }
};

int main() {
    Airline flight1("F101", "UAE", "England", 50);
    Airline flight2("F202", "UAE", "USA", 40);
    Airline flight3("F303", "UAE", "Canada", 2);

    ofstream out("C:/Users/samit/OneDrive/Desktop/CBCPP/Flight.txt");
    if (!out) {
        cout << "Error: File can't open!" << endl;
        return -1;
    }

    out << flight1.getFlight() << " : " << flight1.getDes() << " : " << flight1.getDep()
        << " : " << flight1.getSeat() << endl;

    out << flight2.getFlight() << " : " << flight2.getDes() << " : " << flight2.getDep()
        << " : " << flight2.getSeat() << endl;

    out << flight3.getFlight() << " : " << flight3.getDes() << " : " << flight3.getDep()
        << " : " << flight3.getSeat() << endl;

    out.close();
    cout << "Data Saved Successfully!" << endl;

    bool exit = false;
    while (!exit) {
        system("cls");
        cout << "\t Welcome To Airline Management System" << endl;
        cout << "\t ************************************" << endl;
        cout << "\t 1. Reserve A Seat." << endl;
        cout << "\t 2. Exit." << endl;
        cout << "\t Enter Your Choice: ";
        int val;
        cin >> val;

        if (val == 1) {
            system("cls");
            Airline::display();
            string flight;
            cout << "Enter Flight No: ";
            cin >> flight;

            if (flight == flight1.getFlight() && flight1.getSeat() > 0) {
                flight1.update();
            } else if (flight == flight2.getFlight() && flight2.getSeat() > 0) {
                flight2.update();
            } else if (flight == flight3.getFlight() && flight3.getSeat() > 0) {
                flight3.update();
            } else {
                cout << "Sorry, Seat Not Available!" << endl;
            }
            Sleep(3000);
        } else if (val == 2) {
            system("cls");
            exit = true;
            cout << "Good Luck!" << endl;
            Sleep(3000);
        }
    }

    return 0;
}
