//
// Created by abbes on 8/8/23.
//

#include<iostream>
#include<fstream>

using namespace std;

class shopping {
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void edit();
    void administrator();
    void buyer();
    void add();
    void rem();
    void list();
    void receipt();
};

void shopping :: menu() {
    m:
    int choice;
    string email;
    string password;

    cout << "________________________________  \n";
    cout << "      Supermarket Main menu       \n";
    cout << "________________________________  \n";
    cout << "|____ 1) Administrator __________|\n";
    cout << "|____ 2) Buyer __________________|\n";
    cout << "|____ 3) Exit ___________________|\n";
    cout << "Please select \n";
    cin >> choice;
    cout<<"\n";
    switch (choice) {
        case 1: {
            cout << "Please Login\n";
            cout << "Enter Email\n";
            cin >> email;
            cout << "Enter password\n";
            cin >> password;

            if (email=="abbesmohamed717@gmail.com" && password=="123456")
            {
                administrator();
            }
            else
            {
                cout << "Invalid credentials\n";
            }
            break;
        }
        case 2: {
            buyer();
        }
        case 3 : {
            exit(0);
        }
        default: {
            cout <<"Please select from the given options";
        }
    }
    goto m;
}

void shopping :: administrator() {
    m:
    int choice;

    cout<<"\n\n\n Administrator menu";
    cout<<"\n|____ 1) Add the product_______|";
    cout<<"\n|____ 2) Modify the product____|";
    cout<<"\n|____ 3) Delete the product____|";
    cout<<"\n|____ 4) Back to the main menu_|";

    cout<<"\nPlease enter your choice: ";
    cin>>choice;

    switch(choice)
    {
        case 1: {
            add();
            break;
        }
        case 2: {
            edit();
            break;
        }
        case 3: {
            rem();
            break;
        }
        case 4: {
            menu();
            break;
        }
        default: {
            cout<<"Invalid choice!";
        }
    }
    goto m;
}

void shopping :: buyer() {
    m:
    int choice;
    cout<<"|____ 1) Buyer __________\n";
    cout<<"|____ 2) Buy product ___ \n";
    cout<<"|____ 3) Go back _______ \n";

    cin>>choice;

    switch(choice) {
        case 1: {
            receipt();
            break;
        }
        case 2: {
            menu();
            break;
        }
        default:
            cout<<"Invalid choice\n";
    }
    goto m;
}

void shopping ::add() {
    m:
    fstream data;
    int c;
    int token=0;
    float p;
    float d;
    string n;

    cout<<"\nAdd new product ";
    cout<<"Product code: ";
    cin>>pcode;
    cout<<"Product name: ";
    cin>>pname;
    cout<<"Product price: ";
    cin>>price;
    cout<<"Product discount: ";
    cin>>dis;

    data.open("database.txt", ios::in);

    // if the file doesn't exist
    if(!data)
    {
        // ios app for append and ios out for write mode
        data.open("database.txt", ios::app|ios::out);
        // this is how we write inside a file
        data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
        // this is how we close a file
        data.close();
    }
    // if it exists we read from it
    else
    {
        // this how we read from a file
        data>>c>>n>>p>>d;

        while(!data.eof())
        {
            if(c == pcode )
            {
                token++;
            }
            data>>c>>n>>p>>d;
        }
        data.close();
    }
    if(token==1)
        goto m;
    else {
        data.open("database.txt", ios::app|ios::out);
        data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
        data.close();
    }

    cout<<"\n\n\t\t\t Product added !";


}

void shopping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\nModify the product";
    cout << "\nProduct code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\nFile doesn't exist!";
    } else {
        data1.open("database1.txt", ios::app | ios::out);

        data >> pcode >> pname >> price >> dis;

        while (!data.eof()) {
            if (pkey == pcode) {
                cout << "\nProduct new code: ";
                cin >> c;
                cout << "\nProduct name: ";
                cin >> n;
                cout << "\nProduct price: ";
                cin >> p;
                cout << "\nProduct discount: ";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\t\t\t Product edited";
                token++;
            } else {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }

        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n Product not found sorry!";
        }
    }
}

void shopping :: rem() {
    fstream data, data1;
    int pkey;
    int token = 0;
    cout<<"\n\n\t Delete product";
    cout<<"\n\n\t Product code: ";
    cin>>pkey;
    data.open("database.txt", ios::in);
    if(!data){
        cout<<"File doesnt exist";
    }
    else {
        data1.open("database1.txt", ios::app|ios::out);
        data>>pcode>>pname>>price>>dis;
        while(!data.eof()) {
            if(pcode==pkey){
                cout<<"\n\n\t\t Product deleted successfully";
                token++;
            }
            else {
                data1<<" "<<pcode<<" "<<pname<<" "<<dis<<"\n";
            }
            data>>pcode>>pname>>price>>dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token==0) {
            cout<<"\n\n Product not found";
        }
    }
}

void shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    cout<<"\n\n|______________________________________________\n";
    cout<<"Product number\t\tName\t\tPrice\n";
    cout<<"\n\n|______________________________________________\n";
    data>>pcode>>pname>>price>>dis;

    while(!data.eof()) {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping ::receipt() {
    fstream data;
    int arrc[100];
    int arrq[100];
    char choice;
    float amount=0;
    int c=0;
    int dis=0;
    float total=0;

    cout<<"\n\n\t\t\t RECEIPT";
    data.open("database.txt", ios::in);
    if(!data) {
        cout<<"\n\nEmpty database";
    }
    else {
        data.close();
        list();
        cout<<"\n______________________________________\n";
        cout<<"\n|                                     \n";
        cout<<"\n Please place the order               \n";
        cout<<"\n|                                     \n";
        cout<<"\n______________________________________\n";
        do{
            m:
            cout<<"\n\n Enter the product code :";
            cin>>arrc[c];
            cout<<"\n\n Enter the product quatity :";
            cin>>arrq[c];
            for (int i = 0; i < c; ++i) {
                if (arrc[c] == arrc[i]) {
                    cout<<"\n\n Duplicate product code. Please try again";
                    goto m;
                }
            }
            c++;
            cout<<"\n\n Do you want to buy another product? if so then press y else n";
            cin>>choice;
        } while(choice == 'y' );
            cout<<"\n\n\t\t\t _______RECEIPT_______\n";
            cout<<"\n Product No\t Product name\tProduct quantity\tprice\tAmount with discount\n ";
                for (int i = 0; i < c; ++i) {
                    data.open("database.txt", ios::in);
                    data>>pcode>>pname>>price>>dis;
                    while(!data.eof()){
                        if(pcode==arrc[i]) {
                            amount=price*arrq[i];
                            dis=amount-(amount*dis/100);
                            total=total+dis;
                            cout<<"\n"<<pcode<<"\t\t"<<pname<<"\t\t"<<arrq[i]<<"\t\t"<<price<<"\t\t"<<amount<<"\t\t"<<dis;
                        }
                        data>>pcode>>pname>>price>>dis;
                    }
                }
                data.close();
        }
        cout<<"\n\n_________________________________";
        cout<<"\n Total amount : "<<total;

}

int main() {
    shopping s;
    s.menu();
};