#include<iostream>
#include<fstream>
#include<windows.h>
#include<sstream>
using namespace std;

// Forward declaration for display function
void display();

class Airline
{
private:
    string Flight, Des, Dep;
    int Seats;

public:
    Airline(string flight, string des, string dep, int seats){
        Flight = flight;
        Des = des;
        Dep = dep;
        Seats = seats;	
    }

    string getFlight()
    {
        return Flight;
    }

    string getDes(){
        return Des;
    }

    string getDep()
    {
        return Dep;
    }

    int getSeat()
    {
        return Seats;
    }

    void setSeat(int seats) {
        Seats = seats;
    }

    bool update(string flight)
    {
        // Fix file paths with double backslashes or forward slashes
        ifstream in("C:\\Users\\preet\\OneDrive\\Desktop\\FlightReservationSystem.txt");
        ofstream out("C:\\Users\\preet\\OneDrive\\Desktop\\FlightTemp.txt");
        
        if (!in || !out) {
            cout << "Error: Cannot open files for updating!" << endl;
            return false;
        }

        string line;
        bool found = false;
        while(getline(in, line))
        {
            int pos = line.find(flight);
            if(pos != string::npos)
            {
                found = true;
                if (Seats > 0) {
                    int current = Seats - 1;
                    Seats = current;
                    stringstream ss;
                    ss << current;
                    string strCurrent = ss.str();

                    int seatPos = line.find_last_of(':');
                    if (seatPos != string::npos) {
                        line.replace(seatPos + 2, line.length() - (seatPos + 2), strCurrent);
                    }
                }
            }
            out << line << endl;
        }
        out.close();
        in.close();
        
        // Fix path consistency
        remove("C:\\Users\\preet\\OneDrive\\Desktop\\FlightReservationSystem.txt");
        rename("C:\\Users\\preet\\OneDrive\\Desktop\\FlightTemp.txt", 
               "C:\\Users\\preet\\OneDrive\\Desktop\\FlightReservationSystem.txt");
        
        if (found && Seats >= 0) {
            cout << "Seat Reserved Successfully!" << endl;
            return true;
        } else {
            cout << "Failed to reserve seat. Flight not found or no seats available." << endl;
            return false;
        }
    }
};

void display(){
    // Fix the file path
    ifstream in("C:\\Users\\preet\\OneDrive\\Desktop\\FlightReservationSystem.txt");
    if(!in){
        cout << "Error: File Can't Open!" << endl;
    }
    else{
        string line;
        while(getline(in, line)){
            cout << line << endl;
        }
        in.close();
    }
}

int main(){
    Airline flight1("F101", "India", "England", 50);
    Airline flight2("F202", "India", "USA", 40);
    Airline flight3("F303", "India", "Japan", 2);

    // Fix the file path
    ofstream out("C:\\Users\\preet\\OneDrive\\Desktop\\FlightReservationSystem.txt");
    if(!out){
        cout << "Error: File can't open!" << endl;
    }
    else{
        out << "\t " << flight1.getFlight() << " : " << flight1.getDes() << " : " << flight1.getDep() 
            << " : " << flight1.getSeat() << endl << endl;

        out << "\t " << flight2.getFlight() << " : " << flight2.getDes() << " : " << flight2.getDep()
            << " : " << flight2.getSeat() << endl << endl;

        out << "\t " << flight3.getFlight() << " : " << flight3.getDes() << " : " << flight3.getDep()
            << " : " << flight3.getSeat() << endl << endl;

        cout << "Data Saved Successfully!" << endl;
        out.close();
    }

    bool exit = false;
    while(!exit){
        system("cls");
        cout << "\t Welcome To Airline Management System" << endl;
        cout << "\t ************************************" << endl;
        cout << "\t 1. Reserve A Seat." << endl;
        cout << "\t 2. Exit." << endl;
        cout << "\t Enter Your Choice: ";
        int val;
        cin >> val;

        if(val == 1){
            system("cls");
            display();
            string flight;
            cout << "Enter Flight No: ";
            cin >> flight;

            bool reservationMade = false;
            
            if(flight == flight1.getFlight()) {
                if(flight1.getSeat() > 0) {
                    reservationMade = flight1.update(flight);
                } else {
                    cout << "Sorry, No Seats Available for " << flight << "!" << endl;
                }
            } 
            else if(flight == flight2.getFlight()) {
                if(flight2.getSeat() > 0) {
                    reservationMade = flight2.update(flight);
                } else {
                    cout << "Sorry, No Seats Available for " << flight << "!" << endl;
                }
            }
            else if(flight == flight3.getFlight()) {
                if(flight3.getSeat() > 0) {
                    reservationMade = flight3.update(flight);
                } else {
                    cout << "Sorry, No Seats Available for " << flight << "!" << endl;
                }
            }
            else {
                cout << "Invalid Flight Number!" << endl;
            }
            
            Sleep(5000);	
        }
        else if(val == 2){
            system("cls");
            exit = true;
            cout << "Good Luck!" << endl;
            Sleep(3000);
        }
        else {
            cout << "Invalid choice! Please try again." << endl;
            Sleep(2000);
        }
    }
    
    return 0;
}
