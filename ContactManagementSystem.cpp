#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Contact
{
public:
    string fname;
    string lname;
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
        while (file >> contact.fname >> contact.lname >> contact.phone >> contact.email)
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
        file << contact.fname << " " <<contact.lname << " " <<contact.phone << " " << " " << contact.email << endl;
    }
    file.close();
}

void addContact()
{
    Contact contact;
    cout << "\nEnter first name: ";
    cin >> contact.fname;
     cout << "Enter last name: ";
    cin >> contact.lname;
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
        cout << "first name: " << contact.fname <<"\nlast name: " << contact.lname << "\nPhone: " << contact.phone << "\nEmail: " << contact.email << "\n";
        cout << "--------------------------------------------\n";
    }
}

void searchContact()
{
    string fname;
    cout << "\nEnter first name of the Name to Search: ";
    cin >> fname;
    auto it = find_if(contacts.begin(), contacts.end(), [&fname](const Contact &c)
                      { return c.fname == fname; });

    if (it != contacts.end())
    {
        cout << "first name: " << it->fname <<"last name: " << it->lname << "\nPhone: " << it->phone
             << "\nEmail: " << it->email << "\n";
    }
    else
    {
        cout << "Contact not found.\n";
    }
}

void deleteContact()
{
    string fname;
    cout << "\nEnter first name of the Name to Delete: ";
    cin >> fname;
    auto it = remove_if(contacts.begin(), contacts.end(), [&fname](const Contact &c)
                        { return c.fname == fname; });

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
    string fnameToEdit;
    cout << "\nEnter the first name of the Contact to Edit: ";
    cin.ignore();
    getline(cin, fnameToEdit);

    // Search for the contact by fname
    auto it = find_if(contacts.begin(), contacts.end(), [&fnameToEdit](const Contact &c)
                      { return c.fname == fnameToEdit; });

    if (it != contacts.end())
    {
        Contact &contactToEdit = *it; // Reference to the contact
        int choice;

        do
        {
            cout << "\nWhat would you like to edit?";
            cout << "\n[1] first name";
            cout << "\n[2] last name";
            cout << "\n[3] Phone Number";
            cout << "\n[4] Email";
            cout << "\n[5] Exit Editing";
            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                cout << "Enter the New first name: ";
                cin.ignore();
                getline(cin, contactToEdit.fname);
                cout << "fname updated successfully!\n";
                break;
            }
              case 2:
            {
                cout << "Enter the New last name: ";
                cin.ignore();
                getline(cin, contactToEdit.lname);
                cout << "last name updated successfully!\n";
                break;
            }
            case 3:
            {
                cout << "Enter the New Phone Number: ";
                cin.ignore();
                getline(cin, contactToEdit.phone);
                cout << "Phone Number updated successfully!\n";
                break;
            }
            case 4:
            {
                cout << "Enter the New Email: ";
                cin.ignore();
                getline(cin, contactToEdit.email);
                cout << "Email updated successfully!\n";
                break;
            }
            case 5:
                cout << "Exiting edit menu...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
            }
        } while (choice != 5);

        // Save the changes to the file
        ofstream outFile("contacts.txt", ios::out);
        for (const auto &contact : contacts)
        {
            outFile << contact.fname << "," << contact.phone << ","
                    << "," << contact.email << "\n";
        }
        outFile.close();
    }
    else
    {
        cout << "Contact not found.\n";
    }
}
