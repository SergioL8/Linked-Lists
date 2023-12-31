#include <iostream>
#include "browserHistory.hpp"
using namespace std;


int main() {

    // variable declaration
    int input = 0;
    int tempID;
    int start;
    int end;
    string tempURL;
    string tempPreviousURL;
    string tempOwner;
    BrowserHistory browserHistory;
    WebPage* previousTemp;
    WebPage* tempWebPage;



    cout << "Welcome to your browsing history!" << endl;
    cout << "These is your current browser history:" << endl;
    // display history
    while (1) {

        cout << "Select an action by typing the corresponding number: "<< endl;
        cout << "1. Build history" << endl;
        cout << "2. Display history" << endl;
        cout << "3. Add a new webpage" << endl;
        cout << "4. Add owner to webapge" << endl;
        cout << "5. Increase the view count of a webpage" << endl;
        cout << "6. Delete history" << endl;
        cout << "7. Quit" << endl << endl;
        spot1:
        cin>> input;

        
        switch (input)
        {
// ----// Build History // ----------------------------------------------------------
        case 1:
            browserHistory.buildBrowserHistory();
            break;

// ----// Display History // --------------------------------------------------------
        case 2:
            // execute display history
            browserHistory.displayHistory();
            break;

// ----// Add new webpage // --------------------------------------------------------
        case 3:
            previousTemp = new WebPage();
            tempWebPage = new WebPage();

            // ask for input user
            cout << "Enter the new web page's url: ";
            cin >> tempURL;
            cout << endl;

            cout << "Enter the web page's owner (if no owner, just hit enter)" << endl;
            cin.ignore (10000, '\n'); // There seems to be an extra `\n` in the stream clear out any in the buffer
            getline(cin, tempOwner);
            
            cout << "Enter the new web page's id: ";
            cin>> tempID;
            cout << endl;


            // checks if the selected ID is already in use
            while (browserHistory.searchPageByID(tempID) != nullptr) {
                cout << "ID already in use. Try again: ";
                cin>> tempID;
                cout << endl;
            }

            cout << "Enter the previous page's URL (or First)" << endl;
            cin>> tempPreviousURL;

            // check if input is first
            if (tempPreviousURL == "First") {
                previousTemp = nullptr; // no previous node (the case of previous been null is handled in te add function)
            } else { 
                // this loop is executed if the input is not First, and checks that the inputed URL exists
                while ((previousTemp = browserHistory.searchPageByURL(tempPreviousURL)) == nullptr) { // if the URL does not exists, then execute the code inside the loop, otherwise, previousTemp is already assigned
                    cout << "URL not found in the list, please try again:";
                    cin>> tempPreviousURL;
                    cout << endl;
                    
                    if (tempPreviousURL == "First") { // if after inputing an invalid url, the user decides to set the URL to first, break the loop
                        previousTemp = nullptr; // no previous node (the case of previous been null is handled in te add function)
                        break;
                    }
                }
            }

            // create the new webpage
            tempWebPage->id = tempID;
            tempWebPage->url = tempURL;
            tempWebPage->owner = tempOwner;

            // add the webpage to the link list
            browserHistory.addWebPage(previousTemp, tempWebPage);

            // update the views of the webpage being added (to 1)
            browserHistory.updateViews(tempURL);

            break;

// ----// Add owner to webpage // --------------------------------------------------------
        case 4:
            // ask the user for input
            cout << "Enter URL of the web page to add the owner:" << endl;
            cin >> tempURL;

            while (browserHistory.searchPageByURL(tempURL) == nullptr) { // while the input doesn't exists
                cout << "Page not found. Try again." << endl;
                cin >> tempURL;
            }

            cout << "Enter the name of the owner." << endl;
            cin.ignore (10000, '\n'); // There seems to be an extra `\n` in the stream clear out any in the buffer
            getline(cin, tempOwner);
            browserHistory.addOwner(tempURL, tempOwner);

            break;

// ----// Increase the view count of a webpage // ----------------------------------------
        case 5:
            // as the user for input
            cout << "Enter the URL of the web page." << endl;
            cin>> tempURL;
            
            // check for input
            while(browserHistory.searchPageByURL(tempURL) == nullptr) { // while the input doesn't exists
                cout << "Page not found. Try again." << endl;
                cin >> tempURL;
            }

            browserHistory.updateViews(tempURL); // increas the view count

            break;


// ----// Delete history // --------------------------------------------------------
        case 6:
            // as for input
            cout << "Insert the first page that will be deleted" << endl;
            cin >> start;

            cout << "Insert the end page that will be deleted" << endl;
            cin >> end;

            browserHistory.removeWebPages(start, end);


            break;






// ----// Quit // --------------------------------------------------------
        case 7:
            return 1;
            break;
        
        default:
            cout << "That's not a valid input." << endl;
            goto spot1;
            break;
        }
        cout << endl << endl;
    }
    return 1;
}