#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Contact
{
public:
    string name;
    string phone;
    string email;
};

vector<Contact> contacts;

// Function prototypes
void loadContacts();
void saveContacts();
void addContact();
void viewContacts();
void deleteContact();
void searchContact();
void editContact();

int main()
{
    loadContacts();
    int choice;
    while (true)
    {
        cout << "\n\t**** Welcome to Contact Management System ****";
        cout << "\n\n\t\tMAIN MENU";
        cout << "\n\t\t[1] Add a New Contact";
        cout << "\n\t\t[2] List All Contacts";
        cout << "\n\t\t[3] Search for Contact";
        cout << "\n\t\t[4] Edit a Contact";
        cout << "\n\t\t[5] Delete a Contact";
        cout << "\n\t\t[6] Exit";
        cout << "\n\n\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addContact();
            break;
        case 2:
            viewContacts();
            break;
        case 3:
            searchContact();
            break;
        case 4:
            editContact();
            break;
        case 5:
            deleteContact();
            break;
        case 6:
            saveContacts();
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again!\n";
        }
    }
    return 0;
}

void loadContacts()
{
    ifstream file("contact.txt");
    if (file.is_open())
    {
        Contact contact;
        while (file >> contact.name >> contact.phone >> contact.email)
        {
            contacts.push_back(contact);
        }
        file.close();
    }
}

void saveContacts()
{
    ofstream file("contact.txt");
    for (const auto &contact : contacts)
    {
        file << contact.name << " " << contact.phone << " " << " " << contact.email << endl;
    }
    file.close();
}

void addContact()
{
    Contact contact;
    cout << "\nEnter Name: ";
    cin >> contact.name;
    cout << "Enter Phone Number: ";
    cin >> contact.phone;
    cout << "Enter Email: ";
    cin >> contact.email;
    contacts.push_back(contact);
    cout << "Contact added successfully!\n";
}

void viewContacts()
{
    if (contacts.empty())
    {
        cout << "No contacts available.\n";
        return;
    }
    cout << "\nContacts List:\n";
    cout << "============================================\n";
    for (const auto &contact : contacts)
    {
        cout << "Name: " << contact.name << "\nPhone: " << contact.phone << "\nEmail: " << contact.email << "\n";
        cout << "--------------------------------------------\n";
    }
}

void searchContact()
{
    string name;
    cout << "\nEnter Name to Search: ";
    cin >> name;
    auto it = find_if(contacts.begin(), contacts.end(), [&name](const Contact &c)
                      { return c.name == name; });

    if (it != contacts.end())
    {
        cout << "Name: " << it->name << "\nPhone: " << it->phone
             << "\nEmail: " << it->email << "\n";
    }
    else
    {
        cout << "Contact not found.\n";
    }
}

void deleteContact()
{
    string name;
    cout << "\nEnter Name to Delete: ";
    cin >> name;
    auto it = remove_if(contacts.begin(), contacts.end(), [&name](const Contact &c)
                        { return c.name == name; });

    if (it != contacts.end())
    {
        contacts.erase(it, contacts.end());
        cout << "Contact deleted successfully!\n";
    }
    else
    {
        cout << "Contact not found.\n";
    }
}

void editContact()
{
    string nameToEdit;
    cout << "\nEnter the Name of the Contact to Edit: ";
    cin.ignore();
    getline(cin, nameToEdit);

    // Search for the contact by name
    auto it = find_if(contacts.begin(), contacts.end(), [&nameToEdit](const Contact &c)
                      { return c.name == nameToEdit; });

    if (it != contacts.end())
    {
        Contact &contactToEdit = *it; // Reference to the contact
        int choice;

        do
        {
            cout << "\nWhat would you like to edit?";
            cout << "\n[1] Name";
            cout << "\n[2] Phone Number";
            cout << "\n[3] Email";
            cout << "\n[4] Exit Editing";
            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                cout << "Enter the New Name: ";
                cin.ignore();
                getline(cin, contactToEdit.name);
                cout << "Name updated successfully!\n";
                break;
            }
            case 2:
            {
                cout << "Enter the New Phone Number: ";
                cin.ignore();
                getline(cin, contactToEdit.phone);
                cout << "Phone Number updated successfully!\n";
                break;
            }
            case 3:
            {
                cout << "Enter the New Email: ";
                cin.ignore();
                getline(cin, contactToEdit.email);
                cout << "Email updated successfully!\n";
                break;
            }
            case 4:
                cout << "Exiting edit menu...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
            }
        } while (choice != 4);

        // Save the changes to the file
        ofstream outFile("contacts.txt", ios::out);
        for (const auto &contact : contacts)
        {
            outFile << contact.name << "," << contact.phone << ","
                    << "," << contact.email << "\n";
        }
        outFile.close();
    }
    else
    {
        cout << "Contact not found.\n";
    }
}