#include <iostream>         // Include input/output stream for console I/O
#include <string>           // Include string class for handling text
using namespace std;        // Use the standard namespace so we can use cout, cin, etc. without std::

/* --------- ANSI color codes for terminal text formatting --------- */
const string RESET = "\033[0m";      // Resets text color to default
const string RED = "\033[31m";       // Sets text color to red
const string GREEN = "\033[32m";     // Sets text color to green
const string YELLOW = "\033[33m";    // Sets text color to yellow
const string CYAN = "\033[36m";      // Sets text color to cyan

/* --------- Structure definition for Quote --------- */
struct Quote {
    string text;    // Quote text itself
    string author;  // Name of the author
    string date;    // Date added in the format YYYY-MM-DD
};

/* --------- Global Variables --------- */
const int MAX_QUOTES = 100;   // Maximum 100 number of quotes allowed
Quote quotes[MAX_QUOTES];     // Array of Quote objects to store quotes
int quoteCount = 0;           // Counter to keep track of current number of stored quotes

/* --------- Function to insert a new quote --------- */
void insertQuote() {
    // Check if quote storage is full
    if (quoteCount >= MAX_QUOTES) {
        cout << RED << "Quote list is full! Cannot add more quotes." << RESET << "\n";
        return;
    }

    Quote q;  // Create a temporary Quote object

    // Prompt for quote text input
    cout << CYAN << "Enter quote text: " << RESET;
    getline(cin, q.text);  // Read full line (including spaces)

    // Prompt for author name
    cout << CYAN << "Enter author name: " << RESET;
    getline(cin, q.author);

    // Prompt for date input
    cout << CYAN << "Enter date (e.g., 2025-07-02): " << RESET;
    getline(cin, q.date);

    // Save the new quote in the array and increment quote count
    quotes[quoteCount] = q;
    quoteCount++;

    cout << GREEN << "Quote added successfully!" << RESET << "\n";
}

/* --------- Function to display all stored quotes --------- */
void displayAllQuotes() {
    // Check if there are any quotes to display
    if (quoteCount == 0) {
        cout << RED << "No quotes to display." << RESET << "\n";
        return;
    }

    cout << CYAN << "\n--- All Quotes ---\n" << RESET;

    // Loop over all stored quotes and print their details
    for (int i = 0; i < quoteCount; i++) {
        cout << YELLOW << "Quote #" << (i + 1) << ":" << RESET << "\n";
        cout << "Text  : " << quotes[i].text << "\n";
        cout << "Author: " << quotes[i].author << "\n";
        cout << "Date  : " << quotes[i].date << "\n";
        cout << "------------------------\n";
    }
}

/* --------- Function to search for quotes by keyword or author --------- */
void searchQuotes() {
    // If no quotes are stored, exit
    if (quoteCount == 0) {
        cout << RED << "No quotes stored to search." << RESET << "\n";
        return;
    }

    // Ask for the search term (can be keyword or author name)
    cout << CYAN << "Enter search term (keyword or author name): " << RESET;
    string term;
    getline(cin, term);  // Read full line input

    bool found = false;  // Flag to check if any match is found

    cout << CYAN << "\n--- Search Results ---\n" << RESET;

    // Loop through all quotes to find matches
    for (int i = 0; i < quoteCount; i++) {
        // Use string::find to check if term exists in either text or author
        if (quotes[i].text.find(term) != string::npos || quotes[i].author.find(term) != string::npos) {
            cout << YELLOW << "Quote #" << (i + 1) << ":" << RESET << "\n";
            cout << "Text  : " << quotes[i].text << "\n";
            cout << "Author: " << quotes[i].author << "\n";
            cout << "Date  : " << quotes[i].date << "\n";
            cout << "------------------------\n";
            found = true;
        }
    }

    // If no quotes were found
    if (!found) {
        cout << RED << "No quotes found matching the search term." << RESET << "\n";
    }
}

/* --------- Function to delete a quote by its exact text --------- */
void deleteQuote() {
    // Check if there are any quotes to delete
    if (quoteCount == 0) {
        cout << RED << "No quotes stored to delete." << RESET << "\n";
        return;
    }

    // Ask user for the exact quote text to delete
    cout << CYAN << "Enter exact quote text to delete: " << RESET;
    string target;
    getline(cin, target);

    bool found = false;
    int index = -1;

    // Loop through quotes to find exact match
    for (int i = 0; i < quoteCount; i++) {
        if (quotes[i].text == target) {
            found = true;
            index = i;  // Store index where match is found
            break;
        }
    }

    // If not found, inform user
    if (!found) {
        cout << RED << "Quote not found." << RESET << "\n";
        return;
    }

    // Shift all quotes after the deleted one to fill the gap
    for (int i = index; i < quoteCount - 1; i++) {
        quotes[i] = quotes[i + 1];
    }

    quoteCount--;  // Reduce total quote count by 1

    cout << GREEN << "Quote deleted successfully." << RESET << "\n";
}

/* --------- Function to sort quotes by date in ascending order --------- */
void sortQuotesByDate() {
    // Check if there are quotes to sort
    if (quoteCount == 0) {
        cout << RED << "No quotes to sort." << RESET << "\n";
        return;
    }

    // Use bubble sort to sort based on date (YYYY-MM-DD format supports string comparison)
    for (int i = 0; i < quoteCount - 1; i++) {
        for (int j = 0; j < quoteCount - i - 1; j++) {
            if (quotes[j].date > quotes[j + 1].date) {
                // Swap quotes if they are out of order
                Quote temp = quotes[j];
                quotes[j] = quotes[j + 1];
                quotes[j + 1] = temp;
            }
        }
    }

    cout << GREEN << "Quotes sorted by date successfully." << RESET << "\n";
}

/* --------- Main function - Entry point of the program --------- */
int main() {
    cout << CYAN << "Welcome to Daily Quote Organizer!" << RESET << "\n";

    // Infinite loop for menu system
    while (true) {
        // Display menu options
        cout << CYAN << "\nMenu:\n" << RESET;
        cout << YELLOW << "1. Insert new quote\n";
        cout << "2. Display all quotes\n";
        cout << "3. Search quotes\n";
        cout << "4. Delete a quote\n";
        cout << "5. Sort quotes by date\n";
        cout << "6. Exit\n" << RESET;

        // Ask for user choice
        cout << CYAN << "Choose an option: " << RESET;
        int choice;
        cin >> choice;        // Read numeric choice
        cin.ignore();         // Clear newline from input buffer

        // Call corresponding function based on user's choice
        if (choice == 1) {
            insertQuote();
        } else if (choice == 2) {
            displayAllQuotes();
        } else if (choice == 3) {
            searchQuotes();
        } else if (choice == 4) {
            deleteQuote();
        } else if (choice == 5) {
            sortQuotesByDate();
        } else if (choice == 6) {
            cout << CYAN << "Goodbye!" << RESET << "\n";
            break;  // Exit loop and end program
        } else {
            // If invalid choice entered
            cout << RED << "Invalid option, please try again." << RESET << "\n";
        }
    }

    return 0;  // Program finished successfully
}