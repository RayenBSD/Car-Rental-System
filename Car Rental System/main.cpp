#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstdbool>
using namespace std;

class User {
    private:
        string name, password;
    public:
        void rentalAcar();
        //setter
        void setName ();
        void setPassword ();

        //getter
        string getName ();
        string getPassword ();
};
class Admin:public User {
    private:
        string carName, carPrice;
    public:
        void setNewCar();   
        //setter
        void setCarName ();
        void setPrice ();

        //getter
        string getCarName ();
        string getPrice ();
};

void userAccount();
void adminAccount();
void userORadmin(int &);
void userPresentation (int &);
void adminPresentation (int &);
void search();

int main () {

    bool mainLoop = 1, loop = 1;
    int mainChoice, choice;

    while (mainLoop) {
        userORadmin(mainChoice);
        (mainChoice != 0) ? loop = 1 : (mainLoop = 0, loop = 0);
        //check if really admin or user
        while (loop) {
            
            if (mainChoice == 1) {
                userPresentation (choice);
                if (choice == 0) {
                    loop = 0;
                }
                else if (choice == 1) {
                    search();
                }
                else if (choice == 2) {
                    User user;
                    user.rentalAcar();
                }
                else if (choice == 3) {
                    userAccount();
                }
                else {
                    cout<< "enter a correct choice !!!"<< endl;
                }
            }
            else if (mainChoice == 2) {
                adminPresentation (choice);
                if (choice == 0) {
                    loop = 0;
                }
                else if (choice == 1) {
                    search();
                }
                else if (choice == 2) {
                    User adminRental;
                    adminRental.rentalAcar();
                }
                else if (choice == 3) {
                    Admin newCar;
                    newCar.setNewCar();
                }
                else if (choice == 4) {
                    adminAccount();
                }
                else {
                    cout<< "enter a correct choice !!!"<< endl;
                }
            }
            else {
                cout<< "enter a correct choice!!!"<< endl;
                loop = 0;
            }            
        }
    }
}
void userORadmin(int &choice) {
    cout<< "0.Quit"<< endl;
    cout<< "1.User"<< endl;
    cout<< "2.Admin"<< endl;
    cout<< "enter your choice: "; cin>> choice;
}
void userPresentation(int &choice) {
    cout<< "0.Quit"<< endl;
    cout<< "1.Search"<< endl;
    cout<< "2.Rental a car"<< endl;
    cout<< "3.New account"<< endl;
    cout<< "enter your choice: "; cin>> choice;
}
void adminPresentation(int &choice) {
    cout<< "0.Quit"<< endl;
    cout<< "1.Search"<< endl;
    cout<< "2.Rental a car"<< endl;
    cout<< "3.Add a new car"<< endl;
    cout<< "4.New account"<< endl;
    cout<< "enter your choice: "; cin>> choice;
}
void userAccount() {
    User newUser;
    newUser.setName();
    newUser.setPassword();

    fstream fout(newUser.getName(), ios::out);

    fout<< "Name: "<< newUser.getName()<< endl;
    fout<< "Password: "<< newUser.getPassword()<< endl;
    fout<< "Type: user"<< endl;
    fout<< "Rental: None"; 
}
void adminAccount() {
    Admin newAdmin;
    newAdmin.setName();
    newAdmin.setPassword();

    fstream fout(newAdmin.getName(), ios::out);

    fout<< "Name: "<< newAdmin.getName()<< endl;
    fout<< "Password: "<< newAdmin.getPassword()<< endl;
    fout<< "Type: admin"<< endl;
    fout<< "Rental: None";     
}
void search() {
    string strMain;
    fstream finMain("all cars.txt", ios::in);

    while (finMain>> strMain) {

        fstream fin(strMain, ios::in);
        cout<< "-> "<< strMain<< " <-"<< endl;
    }
}

void User::rentalAcar() {
     
    setName();
    setPassword();
    string str, checkPassword, checkName;
    int counter = 0, exict = 0;

    fstream fin(getName(), ios::in);
    while (fin>> str) {
        counter++;
        if (counter == 2) {
            checkName = str;
        }
        else if (counter == 4) {
            checkPassword = str;
        }
    }
    if (checkPassword == getPassword() && checkName == getName()) {
        string car_name, rn;
        counter = 0;

        cout<< "Car's name: "; cin>> car_name;
        fstream fin(car_name, ios::in);
        //check if the car exict!!!!!!!!!!!!!!!!!!
        while (fin>> str) {
            exict = 1;
            counter++;
            if (counter == 2) {
                rn = str;
            }
            if (counter%2 == 0) {
                cout<< str<< endl;
            }
            else {
                cout<< str<< ' ';
            }
        }
        if (exict == 0) {
            cout<< "check if the car really exict !!!"<< endl;
            return;
        }
        char *sure = new char[5];
        cout<< "Are you sure?(yes/no): "; cin>> sure;

        if (!strcmp(strlwr(sure),"yes")) {
            fstream fin(getName(), ios::in);
            //name, password, type, car name
            string nm, pswd, tp;
            counter = 0;

            while(fin>> str) {
                counter++;
                if (counter == 2) {
                    nm = str;
                }
                else if (counter == 4) {
                    pswd = str;
                }
                else if (counter == 6) {
                    tp = str;
                }       
            }
            fstream fout(getName(), ios::out);
            fout<< "Name: "<< nm<< endl;
            fout<< "Password: "<< pswd<< endl;
            fout<< "Type: "<< tp<< endl;
            fout<< "Rental: "<< rn<< endl;
        }
        else {
            return;
        }
    }
    else {
        cout<< "check your information!!!"<< endl;
    }
}
void Admin::setNewCar() {
    setName();
    setPassword();
    string str, checkPassword, checkName;
    int counter = 0;

    fstream fin(getName(), ios::in);
    while(fin>> str) {
        counter++;
        if (counter == 2) {
            checkName = str;
        }
        else if (counter == 4) {
            checkPassword = str;
        }
        else if (counter == 6) {
            if (str != "admin") {
                cout<< "you are not an admin!!!"<< endl;
                return;
            }
        }
    }
    if (checkPassword == getPassword() && checkName == getName()) {
        setCarName();
        setPrice();

        fstream foutall("all cars.txt", ios::app);
        foutall<< getCarName()<< endl;

        fstream fout(getCarName(), ios::out);
        fout<< "Name: "<< getCarName()<< endl;
        fout<< "Price: "<< getPrice()<< '$'<< endl;
    }
    else {
        cout<< "check your informations!!!"<< endl;
    }
}

/*setter*/
void Admin::setCarName () {
    cout<< "Car name: "; cin>> carName;
}
void Admin::setPrice() {
    cout<< "Price: "; cin>> carPrice;
}
void User::setName() {
    cout<< "Name: "; cin>> name;
}
void User::setPassword() {
    cout<< "Password: "; cin>> password;
}

/*getter*/
string User::getName() {
    return name;
}
string User::getPassword() {
    return password;
}
string Admin::getCarName () {
    return carName;
}
string Admin::getPrice() {
    return carPrice;
}