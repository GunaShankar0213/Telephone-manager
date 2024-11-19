#include <iostream>
#include <string>
#include <stack>
#include <cctype> // For toupper() function
#include <algorithm> // For transform() function
using namespace std;

struct Contact {
    string name;
    string phoneNumber;
    string dateOfBirth;
    string anniversary;
    string contactGroup;
};

class Phonebook {
private:
    stack<Contact> contacts;

public:
    void addContact(const string& name, const string& phoneNumber, const string& dateOfBirth, const string& anniversary, const string& contactGroup) {
        if (phoneNumber.length() != 10) {
            cout << "Wrong phone number format. Phone number should be 10 digits." << endl;
            return;
        }

        Contact newContact = {name, phoneNumber, dateOfBirth, anniversary, contactGroup};
        contacts.push(newContact);
        cout << "Contact added successfully." << endl;
    }

    void searchContact(const string& name) {
        stack<Contact> tempStack;
        bool found = false;

        string searchName = name;
        // Convert searchName to all lowercase to perform case-insensitive search
        transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

        while (!contacts.empty()) {
            Contact contact = contacts.top();
            contacts.pop();

            string contactName = contact.name;
            // Convert contactName to all lowercase for case-insensitive comparison
            transform(contactName.begin(), contactName.end(), contactName.begin(), ::tolower);

            if (contactName == searchName) {
                displayContact(contact);
                found = true;
                break;
            }

            tempStack.push(contact);
        }

        while (!tempStack.empty()) {
            contacts.push(tempStack.top());
            tempStack.pop();
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
    }

    void searchContact(const string& name, const string& phoneNumber) {
        stack<Contact> tempStack;
        bool found = false;

        while (!contacts.empty()) {
            Contact contact = contacts.top();
            contacts.pop();

            if (contact.name == name && contact.phoneNumber == phoneNumber) {
                displayContact(contact);
                found = true;
                break;
            }

            tempStack.push(contact);
        }

        while (!tempStack.empty()) {
            contacts.push(tempStack.top());
            tempStack.pop();
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
    }

    void deleteContact(const string& name) {
        stack<Contact> tempStack;
        bool found = false;

        while (!contacts.empty()) {
            Contact contact = contacts.top();
            contacts.pop();

            if (contact.name != name) {
                tempStack.push(contact);
            } else {
                cout << "Contact deleted successfully." << endl;
                found = true;
                break;
            }
        }

        while (!tempStack.empty()) {
            contacts.push(tempStack.top());
            tempStack.pop();
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
    }

    void displayContacts() {
        stack<Contact> tempStack;

        cout << "Contacts:" << endl;
        while (!contacts.empty()) {
            Contact contact = contacts.top();
            contacts.pop();

            displayContact(contact);

            tempStack.push(contact);
        }

        while (!tempStack.empty()) {
            contacts.push(tempStack.top());
            tempStack.pop();
        }
    }

private:
    void displayContact(const Contact& contact) {
        cout << "Name: " << contact.name << endl;
        cout << "Phone Number: " << contact.phoneNumber << endl;
        cout << "Date of Birth: " << contact.dateOfBirth << endl;
        cout << "Anniversary: " << contact.anniversary << endl;
        cout << "Contact Group: " << contact.contactGroup << endl;
        cout << "--------------------------------" << endl;
    }
};

int main() {
    Phonebook phonebook;
    int choice;
    string name, phoneNumber, dateOfBirth, anniversary, contactGroup;

    do {
        cout << "Phonebook Management System" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Search Contact by Name" << endl;
        cout << "3. Search Contact by Name and Phone Number" << endl;
        cout << "4. Delete Contact" << endl;
        cout << "5. Display Contacts" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Phone Number: ";
                getline(cin, phoneNumber);
                cout << "Enter Date of Birth: ";
                getline(cin, dateOfBirth);
                cout << "Enter Anniversary: ";
                getline(cin, anniversary);
                cout << "Enter Contact Group: ";
                getline(cin, contactGroup);
                phonebook.addContact(name, phoneNumber, dateOfBirth, anniversary, contactGroup);
                break;
            case 2:
                cout << "Enter Name to search: ";
                cin.ignore();
                getline(cin, name);
                phonebook.searchContact(name);
                break;
            case 3:
                cout << "Enter Name to search: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Phone Number to search: ";
                getline(cin, phoneNumber);
                phonebook.searchContact(name, phoneNumber);
                break;
            case 4:
                cout << "Enter Name to delete: ";
                cin.ignore();
                getline(cin, name);
                phonebook.deleteContact(name);
                break;
            case 5:
                phonebook.displayContacts();
                break;
            case 6:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }

        cout << endl;

    } while (choice != 6);

    return 0;
}
