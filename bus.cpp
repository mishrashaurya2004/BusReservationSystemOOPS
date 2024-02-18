#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Bus {
private:
    char bus_number[6];
    char date[10];
    char source[20];
    char destination[20];
    char starting_time[10];

public:
    Bus() = default;
    Bus(const char* num, const char* dat, const char* src, const char* dest, const char* time) {
        strcpy(bus_number, num);
        strcpy(date, dat);
        strcpy(source, src);
        strcpy(destination, dest);
        strcpy(starting_time, time);
    }

    void setBusInfo() {
        cout << "Enter bus number: ";
        cin >> bus_number;
        cout << "Enter Date: ";
        cin >> date;
        cout << "Enter source: ";
        cin.ignore(); 
        cin.getline(source, sizeof(source));
        cout << "Enter destination: ";
        cin.ignore(); 
        cin.getline(destination, sizeof(destination));
        cout << "Enter starting time: ";
        cin >> starting_time;
    }

    void displayBusInfo() {
        cout << "Bus number: " << bus_number << endl;
        cout << "Date: " << date << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Starting time: " << starting_time << endl;
    }

    const char* getBusNumber() const {
        return bus_number;
    }

    void updateBusInfo() {
        setBusInfo();
    }

    friend ostream& operator<<(ostream& os, const Bus& bus);
};

ostream& operator<<(ostream& os, const Bus& bus) {
    os << "Bus number: " << bus.bus_number << endl;
    os << "Date: " << bus.date << endl;
    os << "Source: " << bus.source << endl;
    os << "Destination: " << bus.destination << endl;
    os << "Starting time: " << bus.starting_time << endl;
    return os;
}

class BusReservationSystem {
public:
    void createBusInfo() {
        Bus bus;
        bus.setBusInfo();

        ofstream ofile("D:/Csd/busRecord.txt", ios::app);
        if (!ofile.is_open()) {
            cout << "Can't open the file" << endl;
        } else {
            ofile << bus;
            cout << "Bus record added successfully" << endl;
        }
        ofile.close();
    }

    void ReadBusRecord() {
        ifstream infile("D:/Csd/busRecord.txt");
        if (!infile.is_open()) {
            cout << "Can't open the file" << endl;
        } else {
            Bus bus;
            cout << "Bus number\t" << "Date\t\t" << "Source\t\t" << "Destination\t\t" << "Starting time\t\t" << endl;
            cout << "**************************************************************************************" << endl;
            while (infile.read((char*)&bus, sizeof(bus))) {
                cout << bus;
            }
            cout << "**************************************************************************************" << endl;
        }
        infile.close();
    }

    void searchBus() {
        char ch[6];
        bool found = false;

        ifstream infile("D:/Csd/busRecord.txt");
        if (!infile.is_open()) {
            cout << "Error in opening the file" << endl;
        } else {
            Bus bus;
            cout << "Enter the bus number you are looking for: ";
            cin >> ch;

            while (infile.read((char*)&bus, sizeof(bus))) {
                if (strcmp(bus.getBusNumber(), ch) == 0) {
                    cout << "The bus information you are looking for is:" << endl;
                    cout << bus;
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cout << "Sorry, the bus you are looking for is not found" << endl;
        }

        infile.close();
    }

    void updateBusInfo() {
        char ch[6];
        bool found = false;
        cout << "Enter the bus number to be modified: ";
        cin >> ch;
        fstream file;
        file.open("D:/Csd/busRecord.txt", ios::in | ios::out);
        if (file.fail()) {
            cout << "Error in opening the file" << endl;
        } else {
            Bus bus;

            while (file.read((char*)&bus, sizeof(bus))) {
                if (strcmp(bus.getBusNumber(), ch) == 0) {
                    cout << "Enter the new details of the bus:" << endl;
                    bus.updateBusInfo();
                    int back = -1 * sizeof(bus);
                    file.seekp(back, ios::cur);
                    file.write((char*)&bus, sizeof(bus));
                    found = true;
                    cout << "Modified successfully" << endl;
                    break;
                }
            }

            if (!found) {
                cout << "Bus record not found" << endl;
            }
        }
        file.close();
    }

    void deleteBusRecord() {
        char ch[6];
        cout << "Enter the bus number that you want to delete: ";
        cin >> ch;
        ifstream infile;
        infile.open("D:/Csd/busRecord.txt");
        ofstream ofile;
        ofile.open("D:/Csd/temp.txt");
        Bus bus;

        while (infile.read((char*)&bus, sizeof(bus))) {
            if (strcmp(bus.getBusNumber(), ch) != 0) {
                ofile.write((char*)&bus, sizeof(bus));
            }
        }

        ofile.close();
        infile.close();
        remove("D:/Csd/busRecord.txt");
        rename("D:/Csd/temp.txt", "D:/Csd/busRecord.txt");
        cout << "Bus record is deleted successfully" << endl;
    }
};

void intro() {
    cout << setw(90) << "              BUS RESERVATION SYSTEM                                " << endl;
    cout << setw(80) << "********************************************************************" << endl;
    cout << setw(80) << "*                WELCOME TO BUS RESERVATION SYSTEM                 *" << endl;
    cout << setw(80) << "*                            PROJECT                               *" << endl;
    cout << setw(80) << "*             MADE BY : Shaurya and Akshat (JOINTLY)               *" << endl;
    cout << setw(80) << "********************************************************************" << endl;
}

void menu() {
    BusReservationSystem busSystem;

    while (true) {
        int choice;
        cout << "               ------------MAIN MENU-----------------                  \n\n";
        cout << "-------------------------------------------------------------------------\n";
        cout << "* Enter [1] To  Create Bus Record                                       *\n";
        cout << "* Enter [2] To  Display Bus record                                      *\n";
        cout << "* Enter [3] To  Search specific Bus Record                              *\n";
        cout << "* Enter [4] To  Modify/Update Bus Record                                *\n";
        cout << "* Enter [5] To  Delete Bus Record                                       *\n";
        cout << "* Enter [6] To  Exit                                                    *\n";
        cout << "-------------------------------------------------------------------------\n";

        tryagain:
        cout << "Please enter your choice [1-6] from menu \n";
        cin >> choice;
        switch (choice) {
            case 1:
                busSystem.createBusInfo();
                break;
            case 2:
                busSystem.ReadBusRecord();
                break;
            case 3:
                busSystem.searchBus();
                break;
            case 4:
                busSystem.updateBusInfo();
                break;
            case 5:
                busSystem.deleteBusRecord();
                break;
            case 6:
                exit(0);
            default:
                cout << "You entered an incorrect number. Please enter again." << endl;
                goto tryagain;
                break;
        }
    }
}

int main() {
    intro();
    menu();
    return 0;
}