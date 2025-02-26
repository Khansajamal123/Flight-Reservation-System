#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// Structure to store flight details
struct Flight {
    string flightNumber;
    string departure;
    string arrival;
    string departureTime;
    string arrivalTime;
    int firstClassSeats;
    int businessClassSeats;
    int economyClassSeats;
    float firstClassPrice;
    float businessClassPrice;
    float economyClassPrice;
};

// Function prototypes
void userSignUp();
bool userSignIn();
void bookFlight(Flight flights[], int size, string type);
void cancelFlight(Flight flights[], int size);
void displayTicket(string name, string cnic, string flightNumber, string departure, string arrival, string departureTime, string arrivalTime, string seatType, float price);

int main()
{
    Flight internationalFlights[3] = 
    {
        {"int1", "pakistan", "London", "08:00 AM", "08:00 PM", 5, 10, 20, 1500.0, 1000.0, 500.0},
        {"int2", "pakistan", "Paris", "10:00 AM", "06:00 PM", 3, 12, 25, 1600.0, 1100.0, 600.0},
        {"int3", "pakistan", "Sydney", "02:00 PM", "10:00 AM", 5, 13, 24, 1800.0, 1300.0, 700.0}
    };

    Flight domesticFlights[3] = 
    {
        {"DM1", "Islamabad", "Karachi", "09:00 AM", "11:00 AM", 5, 10, 20, 500.0, 300.0, 100.0},
        {"DM02", "Karachi", "Lahore", "01:00 PM", "02:30 PM", 3, 15, 24, 600.0, 400.0, 200.0},
        {"DM3", "Islamabad", "Skardu", "05:00 PM", "09:00 PM", 6, 12, 21, 550.0, 350.0, 150.0}
    };

    int choice;
    string flightType;

    cout<<"Welcome to the Flight Reservation System!"<<endl;
    cout<<"1. Sign Up"<<endl;
    cout<<"2. Sign In"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;

    if (choice == 1) 
    {
        userSignUp();
        if(!userSignIn())  
        {
            cout<<"Invalid credentials. Exiting..."<< endl;
            return 0;
        }
    } 
    else if (choice == 2) 
    {
    	userSignIn();
        if (!userSignIn()) 
        {
            cout<<"Invalid credentials. Exiting..."<<endl;
            return 0;
        }
    } 
    else
    {
        cout<<"Invalid choice. Exiting..."<<endl;
        return 0;
    }

    do
    {
        cout<<"\nMain Menu:"<<endl;
        cout<<"1. International Flights"<<endl;
        cout<<"2. Domestic Flights"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;

        if(choice == 1) 
        {
            flightType="International";
            bookFlight(internationalFlights, 3, flightType);
        } 
        else if(choice == 2) 
        {
            flightType="Domestic";
            bookFlight(domesticFlights, 3, flightType);
        } 
        else if(choice == 3) 
        {
            cout<<"Thank you for using the Flight Reservation System. Goodbye!"<< endl;
        } 
        else 
        {
            cout<<"Invalid choice. Please try again."<<endl;
        }
    } 
    while(choice != 3);
    return 0;
}

void userSignUp() 
{
    string username, password;
    ofstream userFile("users.txt", ios::app);

    cout<<"\nSign Up:" << endl;
    cout<<"Enter username: ";
    cin.ignore();
    getline(cin, username);
    cout<<"Enter password: ";
    getline(cin, password);

    userFile<<username<<" "<<password<<endl;
    userFile.close();

    cout<<"Sign up successful! You can now sign in." << endl;
}

bool userSignIn() 
{
    string username, password, fileUsername, filePassword;
    ifstream userFile("users.txt");

    cout<<"\nSign In:" << endl;
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;

    while(userFile>>fileUsername>>filePassword) 
    {
        if(username==fileUsername && password==filePassword) 
        {
            cout<<"Sign in successful!"<<endl;
            return true;
        }
    }

    userFile.close();
    return false;
}

void bookFlight(Flight flights[], int size, string type) 
{
    int flightChoice,seatChoice;
    string name,cnic;
    bool booking=true;

    while (booking) {
        cout<<"\nAvailable " << type << " Flights:\n";
        for (int i = 0; i < size; i++)
        {
            cout << i + 1 <<". Flight "<<flights[i].flightNumber<<" from "<<flights[i].departure<<" to "<< flights[i].arrival
                 <<"Departure: "<<flights[i].departureTime<<" | Arrival: "<<flights[i].arrivalTime<< endl;
            cout <<"First Class: "<<flights[i].firstClassSeats<<" seats available, RS"<<flights[i].firstClassPrice<<endl;
            cout <<"Business Class: "<<flights[i].businessClassSeats<<" seats available, RS"<<flights[i].businessClassPrice<<endl;
            cout <<"Economy Class: "<<flights[i].economyClassSeats<<" seats available, RS"<<flights[i].economyClassPrice<<endl;
        }

        cout<<"Select a flight (1-" << size << "): ";
        cin>>flightChoice;

        if (flightChoice < 1 || flightChoice > size)
        {
            cout<<"Invalid choice. Try again.\n";
            continue;
        }

        Flight &selectedFlight = flights[flightChoice - 1];

        cout<<"Choose seat type:\n";
        cout<<"1. First Class\n2. Business Class\n3. Economy Class\n";
        cout<<"Enter your choice: ";
        cin>>seatChoice;

        string seatType;
        float price=0.0;

        if (seatChoice==1 && selectedFlight.firstClassSeats>0)
        {
            seatType="First Class";
            price=selectedFlight.firstClassPrice;
            selectedFlight.firstClassSeats--;
        } 
        else if(seatChoice == 2 && selectedFlight.businessClassSeats>0)
        {
            seatType="Business Class";
            price=selectedFlight.businessClassPrice;
            selectedFlight.businessClassSeats--;
        } 
        else if(seatChoice==3 && selectedFlight.economyClassSeats>0) 
        {
            seatType="Economy Class";
            price=selectedFlight.economyClassPrice;
            selectedFlight.economyClassSeats--;
        } 
        else 
        {
            cout<<"Selected seat type is not available. Please try again.\n";
            continue;
        }

        cout<<"Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout<<"Enter your CNIC: ";
        cin>>cnic;

        displayTicket(name, cnic, selectedFlight.flightNumber, selectedFlight.departure, selectedFlight.arrival, selectedFlight.departureTime, selectedFlight.arrivalTime, seatType, price);

        ofstream ticketFile("ticket.txt");
        ticketFile<<"Ticket Details\n";
        ticketFile<<"Name: "<<name<<"\n";
        ticketFile<<"CNIC: "<<cnic<<"\n";
        ticketFile<<"Flight Number: "<<selectedFlight.flightNumber<<"\n";
        ticketFile<<"Departure: "<<selectedFlight.departure<<"\n";
        ticketFile<<"Arrival: "<<selectedFlight.arrival<<"\n";
        ticketFile<<"Departure Time: "<<selectedFlight.departureTime<<"\n";
        ticketFile<<"Arrival Time: "<<selectedFlight.arrivalTime<<"\n";
        ticketFile<<"Seat Type: "<<seatType<<"\n";
        ticketFile<<"Price: $"<<price<<"\n";
        ticketFile.close();

        cout << "Do you want to cancel your booking? (1 for Yes, 0 for No): ";
        int cancelChoice;
        cin >> cancelChoice;
        if(cancelChoice == 1) 
        {
            cancelFlight(&selectedFlight, seatChoice);
            cout<<"Your booking has been canceled."<<endl;
        } 
        else 
        {
            cout<<"Booking confirmed!\n";
        }

        cout<<"Do you want to book another flight? (1 for Yes, 0 for No): ";
        cin>>booking;
    }
}

void cancelFlight(Flight *selectedFlight, int seatChoice) 
{
    if (seatChoice == 1) 
    {
        selectedFlight->firstClassSeats++;
    } 
    else if (seatChoice == 2) 
    {
        selectedFlight->businessClassSeats++;
    } 
    else if (seatChoice == 3) 
    {
        selectedFlight->economyClassSeats++;
    }
}

void displayTicket(string name, string cnic, string flightNumber, string departure, string arrival, string departureTime, string arrivalTime, string seatType, float price) {
    cout<<"\nTicket Details:\n";
    cout<<"Name: "<<name<<endl;
    cout<<"CNIC: "<<cnic<<endl;
    cout<<"Flight Number: "<<flightNumber<<endl;
    cout<<"Departure: "<<departure<<endl;
    cout<<"Arrival: "<<arrival<<endl;
    cout<<"Departure Time: "<<departureTime<<endl;
    cout<<"Arrival Time: "<<arrivalTime<<endl;
    cout<<"Seat Type: "<<seatType<<endl;
    cout<<"Price: $"<<price<<endl;
}
