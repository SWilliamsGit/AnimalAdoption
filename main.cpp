/******************************************************************************
This program tracks animal surrenders and adoptions.
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "animals.hpp"
using namespace std;

// Allocates memory and initializes nodePtr->next to NULL
// Pre: None
// Post: Allocated nodePtr with ->next set to NULL
NodePtr CreateNode();

// Returns a pointer to the node with matching last name.
// Pre: Valid NodePtr and string.
// Post: Returns pointer to first matching node or nullptr if not found.
NodePtr SearchNode(NodePtr headPtr, string &animalName);

// Reads data from the structs in a text file
// Pre: data file is open and contains the necessary information
// Post: data fields are read from the file
void GetInfo(ifstream &inData, AnimalInfo &info);

// Loops through file, storing input data
// Pre: None
// Post:
void NodeLoop(NodePtr &headPtr, NodePtr &currPtr, NodePtr &np);

// Inserts node into list in sorted location
// Pre: Valid pointer for list and prefilled NodePtr
// Post: Sorted list
void AddNode(NodePtr &headPtr, NodePtr np);

// Returns a pointer to the node with matching last name.
// Pre: Valid NodePtr and string.
// Post: Returns pointer to first matching node or nullptr if not found.
void DeleteAnimal(NodePtr &headPtr, string deleteAnimal);

// Writes input data from file
// Pre: holds valid AnimalInfo vairable
// Post: all fields of AnimalInfo are written to the screen
void WriteAnimal(AnimalInfo info);

// Allows user to add new animals to file
// Pre: text file with the animal data is open
// Post: new animal data is stored into output file
void AddAnimal(NodePtr &np);

// Searches for a specific animal based on its name
// Pre: animal names are stored in the file
// Post: The correct animal information will be displayed if the name is valid
void AnimalSearch(NodePtr headPtr);

// Displays all animal info
//pre: valid node
//post: file is printed
void DisplayAnimals(NodePtr np);

// Save data to file
// Pre: Valid nodeptr
// Post: file is saved
void SaveFile(NodePtr &headPtr);

int main() {

    ifstream inData;
    ofstream outData;

    NodePtr headPtr = nullptr;
    NodePtr currPtr = nullptr;
    NodePtr np = nullptr;
    string deleteAnimal;
    int options;
    int loop = true;

  while(loop){
    cout << "Menu: " << endl;
    cout << "1. Display all animals\n";
    cout << "2. Search animal by name\n";
    cout << "3. Add new animals\n";
    cout << "4. Delete animals\n";
    cout << "5. Exit\n";
    cin >> options;

    switch(options) {
        NodeLoop(headPtr, currPtr, np);
        case 1: DisplayAnimals(headPtr); break;                     // Doesn't display data
        case 2: AnimalSearch(headPtr); break;                       // Doesn't find animals, despite them being in file
        case 3: AddAnimal(headPtr); break;                          // Does not add animals to file
        case 4: DeleteAnimal(headPtr, deleteAnimal); break;         // Sometimes deletes ALL data from file, rather than just the one animal. Other times deletes nothing.
        case 5: loop = false;
        default: cout << "Exiting..." << endl;
        }
        SaveFile(headPtr);
    }

    inData.close();
    outData.close();

return 0;
}

// **********************************************************************************************

// Allocates memory and initializes nodePtr->next to NULL
// Pre: None
// Post: Allocated nodePtr with ->next set to NULL
NodePtr CreateNode() {

    NodePtr newNode = new NodeType;     // Allocate space for node
    newNode->next = nullptr;            // Set next to nullptr for safety

    return newNode;
}

// **********************************************************************************************

// Returns a pointer to the node with matching last name.
// Pre: Valid NodePtr and string.
// Post: Returns pointer to first matching node or nullptr if not found.
NodePtr SearchNode(NodePtr headPtr, string &animalName) {

    NodePtr currPtr = headPtr;

    while (currPtr != nullptr && animalName != currPtr->info.animalName) {
        currPtr = currPtr->next;
    }
    return currPtr;
}

// **********************************************************************************************

// Reads data from the structs in a text file
// Pre: data file is open and contains the necessary information
// Post: data fields are read from the file
void GetInfo(ifstream &inData, AnimalInfo &info) {

    getline(inData >> ws, info.id, ',');                                    // ws removes whitespace
    inData  >> info.animalName >> info.animalType >> info.surrenderDate
            >> info.owner.formerFirst >> info.owner.formerLast >> info.formerNum
            >> info.owner.formerEmail >> info.adoptDate >> info.owner.currentFirst
            >> info.owner.currentLast >> info.currentNum >> info.owner.currentEmail;
            getline(inData, info.comments);

}

// **********************************************************************************************

void NodeLoop(NodePtr &headPtr, NodePtr &currPtr, NodePtr &np) {

    ifstream inData;
    // Open file
    inData.open("info.dat");

    // Error check
    if (!inData) {
        cout << "File not found.";
    }

    do {
        np = CreateNode();

        if (!inData.eof()) {
            GetInfo(inData, np->info);
        }

        else {
            delete np;
            np = nullptr;
        }

        if (np != nullptr) {
            AddNode(np, headPtr);
        }

    } while (np != nullptr);
}


// **********************************************************************************************

// Inserts node into list in sorted location
// Pre: Valid pointer for list and prefilled NodePtr
// Post: Sorted list
void AddNode(NodePtr &headPtr, NodePtr np) {

    NodePtr currPtr = headPtr;
    NodePtr prevPtr = nullptr;

    // loop to find proper location
    while (currPtr != nullptr && np->info.animalName > currPtr->info.animalName) {
        prevPtr = currPtr;
        currPtr = currPtr->next;
    }

    // update list based on location
    if (currPtr == nullptr && prevPtr == nullptr) {
        headPtr = np;
    }

    // if at the front
    else if (prevPtr == nullptr) {
        np->next = headPtr;
        headPtr = np;
    }

    // if at the end
    else if (currPtr == nullptr) {
        prevPtr->next = np;
    }

    // if in the middle
    else {
        np->next = currPtr;
        prevPtr->next = np;
    }
}

// **********************************************************************************************

// Returns a pointer to the node with matching last name.
// Pre: Valid NodePtr and string.
// Post: Returns pointer to first matching node or nullptr if not found.
void DeleteAnimal(NodePtr &headPtr, string deleteAnimal) {

    NodePtr currPtr = headPtr;
    NodePtr prevPtr = nullptr;

    // Prompt user for animal name
    cout << "Animal Name: ";
    cin >> deleteAnimal;

    // loop to find proper location
    while (currPtr != nullptr && currPtr->info.animalName != deleteAnimal) {
        prevPtr = currPtr;
        currPtr = currPtr->next;
    }

    // if at the front
    if (prevPtr == nullptr) {
        headPtr = currPtr->next;
        delete currPtr;
        return;
    }

    // if at the end
    else if (currPtr == nullptr) {
        prevPtr = currPtr->next;
        delete currPtr;
        return;
    }

    // if not located
    else {
        cout << "Animal not located.";
    }
}

// **********************************************************************************************

// Writes input data from file
// Pre: holds valid AnimalInfo vairable
// Post: all fields of AnimalInfo are written to the screen
void WriteAnimal(AnimalInfo info) {

    cout << "ID: " << info.id << ", Animal Name: " << info.animalName << " Animal Type: " << info.animalType << endl
        << "Surrendered Date (MM/DD/YYYY):" << info.surrenderDate << " Former Owner: " << info.owner.formerFirst << " " << info.owner.formerLast
        << " Phone Number: " << info.formerNum << " Email: " << info.owner.formerEmail << endl
        <<  " Adoption Date (MM/DD/YYYY):" << info.adoptDate << " Current Owner: " << info.owner.currentFirst << " " << info.owner.currentLast
        << " Phone Number: " << info.currentNum << " Email: " << info.owner.currentEmail << endl << "Comments: " << info.comments << endl << endl;
}


// **********************************************************************************************

// Allows user to add new animals to file
// Pre: text file with the animal data is open
// Post: new animal data is stored into output file
void AddAnimal(NodePtr &headPtr) {

    ofstream outData;
    AnimalInfo info;

    NodePtr currPtr = headPtr;

    // open file
    outData.open("info.dat", ios::app);         // ios::app prevents file from being completely overwritten

    // animal info
    cout << "Enter the new animals information, using N/A when not applicable.\n";
    cout << "ID: "; cin >> info.id;
    cout << "Animal Name: "; cin >> info.animalName;
    cout << "Animal Type: "; cin >> info.animalType;

    // former owner info
    cout << "Surrendered Date (MM//DD/YYYY): "; cin >> info.surrenderDate;
    cout << "Former Owner Name: "; cin >> info.owner.formerFirst >> info.owner.formerLast;
    cout << "Former Owner Phone Number: "; cin >> info.formerNum;
    cout << "Former Owner Email: "; cin >> info.owner.formerEmail;

    // new owner info
    cout << "Adoption Date (MM/DD/YYYY): "; cin >> info.adoptDate;
    cout << "Current Owner Name: "; cin >> info.owner.currentFirst >> info.owner.currentLast;
    cout << "Current Owner Phone Number: "; cin >> info.currentNum;
    cout << "Current Owner Email: "; cin >> info.owner.currentEmail;
    cout << "Comments: "; cin >> info.comments;
    getline(cin, info.comments);

    outData << endl << info.id << ", " << info.animalName << ", " << info.animalType << ", "
            << info.surrenderDate << ", " << info.owner.formerFirst << " " << info.owner.formerLast
            << ", " << info.formerNum << ", " << info.owner.formerEmail << ", "
            << info.adoptDate << ", " << info.owner.currentFirst << " " << info.owner.currentLast << ", "
            << info.currentNum << ", " << info.owner.currentEmail << ", " << info.comments;

    currPtr = currPtr->next;
}

// **********************************************************************************************

// Displays all animal info
//pre: valid node
//post: file is printed
void DisplayAnimals(NodePtr np) {

    // loop through list
    while (np != nullptr) {
        WriteAnimal(np->info);
        np = np->next;
    }
    cout << endl;
}

// **********************************************************************************************

// Searches for a specific animal based on its name
// Pre: animal names are stored in the file
// Post: The correct animal information will be displayed if the name is valid
void AnimalSearch(NodePtr headPtr) {

   string animalName;
    NodePtr currPtr = headPtr;

    // Prompt user for animal name
    cout << "Animal Name: ";
    cin >> animalName;

    animalName = animalName + ',';
    currPtr = SearchNode(headPtr, animalName);

    if (currPtr == nullptr) {
        cout << "Animal not found." << endl;
    }

    WriteAnimal(currPtr->info);
}

// **********************************************************************************************

// Save data to file
// Pre: Valid nodeptr
// Post: file is saved
void SaveFile(NodePtr &headPtr) {

    ofstream outData;
    AnimalInfo info;
    NodePtr nodePtr = headPtr;

    // Open file
    outData.open("info.dat");

    // Loop through list
    while (nodePtr != nullptr) {

        outData << endl << info.id << ", " << info.animalName << ", " << info.animalType << ", "
            << info.surrenderDate << ", " << info.owner.formerFirst << " " << info.owner.formerLast
            << ", " << info.formerNum << ", " << info.owner.formerEmail << ", "
            << info.adoptDate << ", " << info.owner.currentFirst << " " << info.owner.currentLast << ", "
            << info.currentNum << ", " << info.owner.currentEmail << ", " << info.comments;

        nodePtr = nodePtr->next;
    }
    // Close file
    outData.close();
}
