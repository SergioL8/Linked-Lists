#include "browserHistory.hpp"

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
BrowserHistory::BrowserHistory() {
    head = nullptr; // set head to a null pointer
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool BrowserHistory::isEmpty() {
    return (head == NULL); // if the list is empty (head points to null)
}


/*
 * Purpose: prints the current list of pages 
 * @param none
 * @return none
 */
void BrowserHistory::displayHistory() {
    
    // variable declaration
    WebPage* current;

    cout << "== CURRENT BROWSER HISTORY ==" << endl;
    
    // check if the list is empty
    if (isEmpty()) {
        cout << "There is nothing in the browsing history." << endl;
        return;
    }

    current = head;
    while(current != nullptr) { // while the current node exists (no null) print it's content 
        cout << current->views <<" view(s). [ID:: " << current->id << "]-(URL::" << current->url << ") - {Owner::" << current->owner << "}" << endl;
        current = current->next; // move to the next node
    }
    return;
}


/*
 * Purpose: Add a new webpage to the browser history LL
 *   between the previous and the page that follows it in the list.
 * @param previousPage, the show that comes before the new page
 * @param newPage, the webpage to be added. 
 * @return none
 */
void BrowserHistory::addWebPage(WebPage* previousPage, WebPage* newPage) {

    if (previousPage == nullptr) { // if the list is empty or we are adding the node to the beginging of the list
        newPage->next = head; // this is necessary in case the list was not empty, but we are adding a node to the begining of the list
        head = newPage; // set the new page to the head
        cout << "Adding: [" << newPage->id << "]-" << newPage->url << "(HEAD)" << endl;
    } else {
        newPage->next = previousPage->next; // this is necessary in the case that you are inserting the new node between two nodes
        previousPage->next = newPage;
        cout << "Adding: [" << newPage->id << "]-" << newPage->url << "((prev: " << "[" << previousPage->id << "])" << endl;
    }
}


/*
 * Purpose: populates the BrowserHistory with the predetermined pages
 * @param none
 * @return none
 */
void BrowserHistory::buildBrowserHistory() {

    head = nullptr;

    WebPage* page1 = new WebPage();
    page1->url = "https://www.colorado.edu/";
    page1->id = 10;
    page1->views = 0;
    page1->owner = "";

    addWebPage(head, page1);

    
    WebPage* page2 = new WebPage();
    page2->url = "https://www.wikipedia.org/";
    page2->id = 11;
    page2->views = 0;
    page2->owner = "";

    addWebPage(page1, page2);

    WebPage* page3 = new WebPage();
    page3->url = "https://brilliant.org/";
    page3->id = 12;
    page3->views = 0;
    page3->owner = "";

    addWebPage(page2, page3);

    WebPage* page4 = new WebPage();
    page4->url = "https://www.khanacademy.org/";
    page4->id = 13;
    page4->views = 0;
    page4->owner = "";

    addWebPage(page3, page4);

    WebPage* page5 = new WebPage();
    page5->url = "https://www.numberphile.com/";
    page5->id = 14;
    page5->views = 0;
    page5->owner = "";
    
    addWebPage(page4, page5);
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by ID and return a pointer to that node.
 * @param int id - ID of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByID(int id) {
    
    WebPage* current = head; // set the current node to the begining of the list
    while (current != nullptr){ // while we haven't traversed the entire list
        if (current->id == id){ // if ID found return the current node
            return current;
        }
        current = current->next; // traverse to the next node
    }

    return nullptr; // id was not found
}



/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by the URL and return a pointer to that node.
 * @param string url - url of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByURL(std::string url) {
   
    WebPage* current = head; // set the current node to the begining of the list

    while (current != nullptr){ // while we haven't traversed the entire list
        if (current->url == url){ // if the url matches then return the current node
            return current;
        }
        current = current->next; // traverse to the next node
    }

    return nullptr; // if no node found
}


/*
 * Purpose: Give an owner to a web page.
 * @param receiver - name of the show that is receiving the rating
 * @param rating - the rating that is being given to a show
 * @return none
 */
void BrowserHistory::addOwner(std::string url, string owner) {

    WebPage *current = new WebPage();

    current = searchPageByURL(url);
    if (current == nullptr) {
        cout << "Page not found." << endl;
        return;
    } else {
        current->owner = owner;
        cout << "The owner (" << owner << ") has been added to " << current->url << endl;
        return;
    }
}

/*
* Purpose: Update views and show the current views of a web page.
* @param url - url of the webpage that has to be updated
* return none
*/
void BrowserHistory::updateViews(string url) {

    // no need to check here if current is nullptr because when called in main we are already making sure that the URL exists however if used for other case, we should check
    WebPage* current = searchPageByURL(url);
    current->views++;
    cout << "The webpage (" << current->url << ") has " << current->views << " view(s)." << endl;
}



/*
 * Purpose: Has to remove all the WebPage nodes from [start, end] inclusive.
 * Has to print appropriate messages on cout like below if the linkedlist is empty
 * or if the values of start/ end are improper
 * follow the same order for couts in the writeup - check empty list first, then check wrong start/end values
 * @param integers start and end (1 based indexing not 0 based)
 * @return none
 */
void BrowserHistory::removeWebPages(int start, int end) {

    int length = 1;
    int counter = 0;
    WebPage *current = head;
    WebPage *previous = head;
    WebPage *startNode = head;

    // check if the list is empty
    if (head == nullptr) {
        cout << "List already empty" << endl;
        return;
    }

    // traverse the linked list to check for its length
    while (current != nullptr) {
        current = current->next;
        length++;
    }


    // check that the inputs are valid
    if (start > end || start < 0 || end > length-1) {
        cout << "Start or end values not valid." << endl;
        return;
    }

    current = head->next; // at this point, previous is at node 0 and current at node 1
    if (start == 0) { // this handles the case in which the first node to be deleted is node 0
        delete previous; // delete the first node
        previous = current; // traverse
        if (current->next != nullptr) { // traverse the current if there is more list
            current = current->next;
        }
        counter++;
    } else {
        // if we don't beging at the first node, then get to the first node to be deleted
        while (counter < start-1) { // the -1 is necessary because we are deleting the current, which always goes one node in advance
            current = current->next;
            previous = previous->next;
            counter++;
        }
    }

    // traverse trough the link list unitl you reach the end node
    while (counter <= end && current != nullptr) {
        previous->next = current->next; // jump to the node above the current node
        delete current;
        current = previous->next; 
        counter++;
    }
    if (start == 0) {
        head = previous;
    }

    cout << "Selected history deleted sucessfully." << endl;


}
