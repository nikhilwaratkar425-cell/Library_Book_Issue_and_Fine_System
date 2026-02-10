#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Book class
class Book {
public:
    string bookId;
    string title;
    bool isIssued;

    Book(string id, string t) {
        bookId = id;
        title = t;
        isIssued = false;
    }
};

// User class
class User {
public:
    string userId;
    string name;
    vector<string> issuedBooks;
    int totalFine;

    User(string id, string n) {
        userId = id;
        name = n;
        totalFine = 0;
    }
};

// Library class
class Library {
public:
    vector<Book> books;
    vector<User> users;

    void addBook(Book b) {
        books.push_back(b);
    }

    void addUser(User u) {
        users.push_back(u);
    }

    Book* findBook(string bookId) {
        for (auto &b : books) {
            if (b.bookId == bookId)
                return &b;
        }
        return NULL;
    }

    User* findUser(string userId) {
        for (auto &u : users) {
            if (u.userId == userId)
                return &u;
        }
        return NULL;
    }

    void issueBook(string userId, string bookId, int days) {
        User* user = findUser(userId);
        Book* book = findBook(bookId);

        if (user == NULL || book == NULL)
            return;

        if (user->issuedBooks.size() >= 3) {
            cout << "User cannot issue more than 3 books" << endl;
            return;
        }

        if (book->isIssued) {
            cout << "Book already issued" << endl;
            return;
        }

        book->isIssued = true;
        user->issuedBooks.push_back(bookId);
        cout << "Book " << bookId << " issued successfully" << endl;
    }

    void returnBook(string userId, string bookId, int days) {
        User* user = findUser(userId);
        Book* book = findBook(bookId);

        if (user == NULL || book == NULL)
            return;

        book->isIssued = false;

        int fine = 0;
        if (days > 7)
            fine = (days - 7) * 10;

        user->totalFine += fine;

        if (fine > 0)
            cout << "Book " << bookId << " returned late. Fine: " << fine << endl;
        else
            cout << "Book " << bookId << " returned successfully" << endl;
    }
};

// Main function
int main() {
    Library lib;

    int bookCount;
    cout<<"Number of book : ";
    cin >> bookCount;

    for (int i = 0; i < bookCount; i++) {
        string id, title;
        cout<<"book ID and Title : ";
        cin >> id >> title;
        lib.addBook(Book(id, title));
    }

    int userCount;
    cout<<"Number of User : ";
    cin >> userCount;

    for (int i = 0; i < userCount; i++) {
        string id, name;
        cout<<"Student ID and Name : ";
        cin >> id >> name;
        lib.addUser(User(id, name));
    }

    string command;
    while (true) {
        cout << "\nEnter command (ISSUE / RETURN / EXIT): ";
        cin >> command;

        if (command == "EXIT")
            break;

        string userId, bookId;
        int days;

        cout << "Enter UserId BookId Days: ";
        cin >> userId >> bookId >> days;

        if (command == "ISSUE") {
            lib.issueBook(userId, bookId, days);
        }
        else if (command == "RETURN") {
            lib.returnBook(userId, bookId, days);
        }
        else {
            cout << "Invalid command!" << endl;
        }
    }


    // Output final fine
    for (auto &u : lib.users) {
        cout << "User: " << u.name
             << " | Total Fine: " << u.totalFine << endl;
    }

    return 0;
}