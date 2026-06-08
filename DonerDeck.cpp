#include <iostream>
#include <string>
#include <fstream>
using namespace std;
const int MAX = 100;

// DONOR CLASS

class Donor {
private:
    string name, contact, blood;
    int age, donatedQty;
public:
    void input() {
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        do {
            cout << "Enter Age (18-60): ";
            cin >> age;
            if(age < 18 || age > 60)
                cout << "Invalid age! Donor must be between 18 and 60.\n";
        } while(age < 18 || age > 60);
        do {
            cout << "Enter Contact (11 digits): ";
            cin >> contact;
            if(contact.length() != 11)
                cout << "Invalid contact number!\n";
        } while(contact.length() != 11);
        do {
            cout << "Enter Blood Group: ";
            cin >> blood;
            if(blood != "A+" && blood != "A-" && blood != "B+" && blood != "B-" &&
               blood != "AB+" && blood != "AB-" && blood != "O+" && blood != "O-")
                cout << "Invalid blood group!\n";
        } while(blood != "A+" && blood != "A-" && blood != "B+" && blood != "B-" &&
                blood != "AB+" && blood != "AB-" && blood != "O+" && blood != "O-");
        do {
            cout << "Enter Blood Donation Quantity (minimum 350ml): ";
            cin >> donatedQty;
            if(donatedQty < 350)
                cout << "Cannot accept blood less than 350ml!\n";
        } while(donatedQty < 350);
    }
    void display() {
        cout << name << " | Age: " << age
             << " | Blood: " << blood
             << " | Contact: " << contact
             << " | Donated: " << donatedQty << " ml" << endl;
    }
    string getName() { return name; }
    string getBlood() { return blood; }
    int getQty() { return donatedQty; }

    void update() {
        cout << "Enter New Name: ";
        cin.ignore();
        getline(cin, name);
        do {
            cout << "Enter New Age (18-60): ";
            cin >> age;
            if(age < 18 || age > 60)
                cout << "Invalid age!\n";
        } while(age < 18 || age > 60);
        do {
            cout << "Enter New Contact (11 digits): ";
            cin >> contact;
            if(contact.length() != 11)
                cout << "Invalid contact number!\n";
        } while(contact.length() != 11);
        cout << "Donor updated successfully!\n";
    }
    void saveToFile(ofstream &f) {
        f << name << endl << age << endl << contact << endl << blood << endl << donatedQty << endl;
    }
    void loadFromFile(ifstream &f) {
        getline(f, name);
        f >> age; f.ignore();
        getline(f, contact);
        getline(f, blood);
        f >> donatedQty; f.ignore();
    }
};
// RECIPIENT CLASS

class Recipient {
private:
    string name, contact, blood;
    int age, urgency;
public:
    void input() {
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        do {
            cout << "Enter Age (18-60): ";
            cin >> age;
            if(age < 18 || age > 60)
                cout << "Invalid age! Recipient must be between 18 and 60.\n";
        } while(age < 18 || age > 60);
        do {
            cout << "Enter Contact (11 digits): ";
            cin >> contact;
            if(contact.length() != 11)
                cout << "Invalid contact number!\n";
        } while(contact.length() != 11);
        do {
            cout << "Required Blood: ";
            cin >> blood;
            if(blood != "A+" && blood != "A-" && blood != "B+" && blood != "B-" &&
               blood != "AB+" && blood != "AB-" && blood != "O+" && blood != "O-")
                cout << "Invalid blood group!\n";
        } while(blood != "A+" && blood != "A-" && blood != "B+" && blood != "B-" &&
                blood != "AB+" && blood != "AB-" && blood != "O+" && blood != "O-");
        do {
            cout << "Urgency (1-5): ";
            cin >> urgency;
            if(urgency < 1 || urgency > 5)
                cout << "Invalid urgency level!\n";
        } while(urgency < 1 || urgency > 5);
    }
    void display() {
        cout << "Name: " << name
             << " | Age: " << age
             << " | Blood Needed: " << blood
             << " | Urgency Level: " << urgency
             << " | Contact: " << contact << endl;
    }
    string getName() { return name; }
    string getBlood() { return blood; }

    void update() {
        cout << "Enter New Name: ";
        cin.ignore();
        getline(cin, name);
        do {
            cout << "Enter New Age (18-60): ";
            cin >> age;
            if(age < 18 || age > 60)
                cout << "Invalid age!\n";
        } while(age < 18 || age > 60);
        do {
            cout << "Enter New Contact (11 digits): ";
            cin >> contact;
            if(contact.length() != 11)
                cout << "Invalid contact number!\n";
        } while(contact.length() != 11);
        do {
            cout << "Enter New Urgency (1-5): ";
            cin >> urgency;
            if(urgency < 1 || urgency > 5)
                cout << "Invalid urgency level!\n";
        } while(urgency < 1 || urgency > 5);
        cout << "Recipient updated successfully!\n";
    }
    void saveToFile(ofstream &f) {
        f << name << endl << age << endl << contact << endl << blood << endl << urgency << endl;
    }
    void loadFromFile(ifstream &f) {
        getline(f, name);
        f >> age; f.ignore();
        getline(f, contact);
        getline(f, blood);
        f >> urgency; f.ignore();
    }
};
// BLOOD UNIT CLASS

class BloodUnit {
private:
    string group;
    int qty;
public:
    void setData(string g, int q) { group = g; qty = q; }
    void display() { cout << group << " : " << qty << " ml" << endl; }
    string getGroup() { return group; }
    int getQty() { return qty; }
    void add(int q) { qty += q; }
    void reduce(int q) { qty -= q; }
    void saveToFile(ofstream &f) { f << group << endl << qty << endl; }
    void loadFromFile(ifstream &f) { getline(f, group); f >> qty; f.ignore(); }
};

// BLOOD BANK SYSTEM

class BloodBank {
private:
    Donor donors[MAX];
    Recipient recipients[MAX];
    BloodUnit stock[MAX];
    string transactions[MAX];
    int dCount = 0, rCount = 0, sCount = 0, tCount = 0;
public:
    void loadData() {
        ifstream file;
        
        file.open("donors.txt");
        if(file.is_open()) {
            file >> dCount; file.ignore();
            for(int i = 0; i < dCount; i++) donors[i].loadFromFile(file);
            file.close();
        }
        file.open("recipients.txt");
        if(file.is_open()) {
            file >> rCount; file.ignore();
            for(int i = 0; i < rCount; i++) recipients[i].loadFromFile(file);
            file.close();
        }
        file.open("stock.txt");
        if(file.is_open()) {
            file >> sCount; file.ignore();
            for(int i = 0; i < sCount; i++) stock[i].loadFromFile(file);
            file.close();
        }
        file.open("transactions.txt");
        if(file.is_open()) {
            file >> tCount; file.ignore();
            for(int i = 0; i < tCount; i++) getline(file, transactions[i]);
            file.close();
        }
    }
    void saveData() {
        ofstream file;

        file.open("donors.txt");
        file << dCount << endl;
        for(int i = 0; i < dCount; i++) donors[i].saveToFile(file);
        file.close();

        file.open("recipients.txt");
        file << rCount << endl;
        for(int i = 0; i < rCount; i++) recipients[i].saveToFile(file);
        file.close();

        file.open("stock.txt");
        file << sCount << endl;
        for(int i = 0; i < sCount; i++) stock[i].saveToFile(file);
        file.close();

        file.open("transactions.txt");
        file << tCount << endl;
        for(int i = 0; i < tCount; i++) file << transactions[i] << endl;
        file.close();
    }
    void deleteAllData() {
        dCount = rCount = sCount = tCount = 0;
        remove("donors.txt");
        remove("recipients.txt");
        remove("stock.txt");
        remove("transactions.txt");
        cout << "All data deleted successfully! Starting fresh.\n";
    }
    void addDonor() {
        if(dCount == MAX) { cout << "Database full\n"; return; }
        donors[dCount].input();

        string bg = donors[dCount].getBlood();
        int qty = donors[dCount].getQty();

        bool found = false;
        for(int i=0; i<sCount; i++) {
            if(stock[i].getGroup() == bg) {
                stock[i].add(qty);
                found = true;
                break;
            }
        }
        if(!found) {
            stock[sCount].setData(bg, qty);
            sCount++;
        }
        transactions[tCount++] = "Donor added and blood donated";
        dCount++;
        cout << "Donor registered successfully\n";
        saveData();
    }
    void addRecipient() {
        if(rCount == MAX) { cout << "Database full\n"; return; }
        recipients[rCount].input();
        transactions[tCount++] = "Recipient added";
        rCount++;
        cout << "Recipient added successfully\n";
        saveData();
    }
    void requestBlood() {
        string bg; int need;
        cout << "Enter required blood: "; cin >> bg;
        cout << "Enter quantity: "; cin >> need;

        bool found = false;
        for(int i=0; i<sCount; i++) {
            if(stock[i].getGroup() == bg) {
                found = true;
                if(stock[i].getQty() >= need) {
                    stock[i].reduce(need);
                    cout << "Blood provided\n";
                    transactions[tCount++] = "Blood given";
                } else {
                    cout << "Not enough quantity\n";
                }
                break;
            }
        }
        if(!found) cout << "This blood group is not available\n";
        saveData();
    }
    void showStock() {
        if(sCount == 0) { cout << "No blood available\n"; return; }
        for(int i=0; i<sCount; i++) stock[i].display();
    }
    void searchBlood() {
        string bg;
        cout << "Enter blood group: "; cin >> bg;
        bool found = false;
        for(int i=0; i<sCount; i++) {
            if(stock[i].getGroup() == bg) {
                stock[i].display();
                found = true;
            }
        }
        if(!found) cout << "No blood found\n";
    }
    void searchDonor() {
        string name;
        cin.ignore();
        cout << "Enter donor name: ";
        getline(cin, name);

        bool found = false;
        for(int i=0; i<dCount; i++) {
            if(donors[i].getName() == name) {
                donors[i].display();
                found = true;
            }
        }
        if(!found) cout << "No donor found with this name\n";
    }
    void searchRecipient() {
        string bg;
        cout << "Enter required blood group: "; cin >> bg;
        bool found = false;
        for(int i=0; i<rCount; i++) {
            if(recipients[i].getBlood() == bg) {
                recipients[i].display();
                found = true;
            }
        }
        if(!found) cout << "No recipient found\n";
    }
    void updateDonor() {
        string name;
        cin.ignore();
        cout << "Enter donor name: "; 
        getline(cin, name);
        for(int i=0; i<dCount; i++) {
            if(donors[i].getName() == name) {
                donors[i].update();
                saveData();
                return;
            }
        }
        cout << "Donor not found\n";
    }
    void updateRecipient() {
        string name;
        cin.ignore();
        cout << "Enter recipient name: "; 
        getline(cin, name);
        for(int i=0; i<rCount; i++) {
            if(recipients[i].getName() == name) {
                recipients[i].update();
                saveData();
                return;
            }
        }
        cout << "Recipient not found\n";
    }
    void deleteDonor() {
        string name;
        cin.ignore();
        cout << "Enter donor name: "; 
        getline(cin, name);
        for(int i=0; i<dCount; i++) {
            if(donors[i].getName() == name) {
                for(int j=i; j<dCount-1; j++) donors[j] = donors[j+1];
                dCount--;
                cout << "Donor deleted\n";
                saveData();
                return;
            }
        }
        cout << "Donor not found\n";
    }
    void deleteRecipient() {
        string name;
        cin.ignore();
        cout << "Enter recipient name: "; 
        getline(cin, name);
        for(int i=0; i<rCount; i++) {
            if(recipients[i].getName() == name) {
                for(int j=i; j<rCount-1; j++) recipients[j] = recipients[j+1];
                rCount--;
                cout << "Recipient deleted\n";
                saveData();
                return;
            }
        }
        cout << "Recipient not found\n";
    }
    void compatibilityCheck() {
        string d, r;
        cout << "Enter donor blood: "; cin >> d;
        cout << "Enter recipient blood: "; cin >> r;

        bool donorFound = false, recipientFound = false;
        for(int i=0; i<dCount; i++) if(donors[i].getBlood() == d) donorFound = true;
        for(int i=0; i<rCount; i++) if(recipients[i].getBlood() == r) recipientFound = true;

        if(!donorFound || !recipientFound) {
            cout << "No donor or recipient available for compatibility check\n";
            return;
        }
        if(d == r || d == "O-") cout << "Compatible\n";
        else cout << "Not compatible\n";
    }
    void stats() {
        cout << "Total donors: " << dCount << endl;
        cout << "Total recipients: " << rCount << endl;
        cout << "Total blood groups in stock: " << sCount << endl;
    }

    void showTransactions() {
        if(tCount == 0) { cout << "No transactions\n"; return; }
        for(int i=0; i<tCount; i++)
            cout << i+1 << ". " << transactions[i] << endl;
    }
};

// MAIN

int main() {
    BloodBank b;
    b.loadData();

    int choice;
    do {
        cout << "\n--- Blood Bank System ---\n";
        cout << "1. Add Donor\n2. Add Recipient\n3. Request Blood\n4. Show Blood Stock\n";
        cout << "5. Search Blood\n6. Search Donor\n7. Search Recipient\n8. Update Donor\n";
        cout << "9. Update Recipient\n10. Delete Donor\n11. Delete Recipient\n";
        cout << "12. Check Compatibility\n13. Statistics\n14. Transactions\n";
        cout << "15. Delete All Data\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: b.addDonor(); break;
            case 2: b.addRecipient(); break;
            case 3: b.requestBlood(); break;
            case 4: b.showStock(); break;
            case 5: b.searchBlood(); break;
            case 6: b.searchDonor(); break;
            case 7: b.searchRecipient(); break;
            case 8: b.updateDonor(); break;
            case 9: b.updateRecipient(); break;
            case 10: b.deleteDonor(); break;
            case 11: b.deleteRecipient(); break;
            case 12: b.compatibilityCheck(); break;
            case 13: b.stats(); break;
            case 14: b.showTransactions(); break;
            case 15: b.deleteAllData(); break;
            case 0: 
                b.saveData();
                cout << "Data saved successfully. Exiting...\n"; 
                break;
            default: cout << "Invalid choice\n";
        }
    } while(choice != 0);
    
    return 0;
}
