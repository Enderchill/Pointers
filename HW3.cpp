#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


bool readInventory(string fname, int numRecords, string * pluPtr, double * pricePtr, string * namePtr, int * typePtr, int * inventoryPtr);
void inventoryPrint(string fname, int numRecords, string * pluPtr, double * pricePtr, string * namePtr, int * typePtr, int * inventoryPtr);
int determineNumRecords(string fname);

double checkout(int numRecords, string * pluPtr, double * pricePtr, int * inventoryPtr);

int getUserChoice();

int searchProduct(string plu, string *pluPtr, int numRecords);


int main(int argc, const char * argv[]) {
    
    //declare dynamic memory pointers
    string *pluPtr = nullptr;
    double *pricePtr = nullptr;
    int *typePtr = nullptr;
    int *inventoryPtr = nullptr;
    string *namePtr = nullptr;
    
    //declare varis
    string fname;
    int numRecords;
    
    //prompt for file name
    cout << "Enter the file name: ";
    cin >> fname;
    ifstream inputFile(fname);
    
    //find num records
    numRecords = determineNumRecords(fname);
    //delcare sizes for pointer to pass values
    pluPtr = new string[numRecords];
    pricePtr = new double[numRecords];
    typePtr = new int[numRecords];
    inventoryPtr = new int[numRecords];
    namePtr = new string[numRecords];
    
    //read inventory them if true, print and display total records
    if (readInventory(fname, numRecords, pluPtr, pricePtr, namePtr, typePtr, inventoryPtr))
    {
        cout << "There are " << numRecords << " records in the file" << endl; //output amount read in file
        cout << endl; //format check
        
        // output Read file list
        cout << "Inventory read from file" << endl;
        cout << "------------------------" << endl;
        inventoryPrint(fname, numRecords, pluPtr, pricePtr, namePtr, typePtr, inventoryPtr); //call
    }
    else
    {
        cout << "Error, File could not be found." << endl; //user validation
    }
    //display menu
    int choice;
    do { //do all this at least once or while user doesnt want to quit
        choice = getUserChoice();
        //switch to help cylce through choices
        switch (choice) {
            case 1:
                checkout(numRecords, pluPtr, pricePtr, inventoryPtr);
                break;
            case 2:
                cout << "Current inventory" << endl; //print current inventory using print inventory function
                cout << "-----------------" << endl;
                inventoryPrint(fname, numRecords, pluPtr, pricePtr, namePtr, typePtr, inventoryPtr);
                break;
            case 3:
                cout << "Updated inventory" << endl;
                cout << "-----------------" << endl;
                inventoryPrint(fname, numRecords, pluPtr, pricePtr, namePtr, typePtr, inventoryPtr);
                cout << "Exiting" << endl;
                //free mememory
                delete [] pluPtr;
                delete [] pricePtr;
                delete [] namePtr;
                delete [] typePtr;
                delete [] inventoryPtr;
                break;
                
            default:
                do {
                       cout << "Invalid choice, reenter: "; //input validation
                       cin >> choice;
                   } while (choice < 1 || choice > 3);
                break;
        }
    } while (choice != 3 );
        
    
}

double checkout(int numRecords, string * pluPtr, double * pricePtr, int * inventoryPtr)
{
    //varis
    double totalPrice = 0;
    string pluChoice;
    int quantity = 0;
    int index;
    do {
        cout << "Enter PLU, 0 if done: "; //prompt
        cin >> pluChoice;
        
        if(pluChoice == "0") //check for ending input
        {
            cout << "Total is: $" << totalPrice << endl; //print total and return
            return totalPrice;
        }
        index = searchProduct(pluChoice, pluPtr, numRecords); //call search function
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << endl; //format endl check
        if(index == -1) //if search returns -1, not found.
        {
            cout << "PLU not found\n" << endl;
            continue;
        }
        while(quantity < 1) //validation
        {
            cout << "Quantity must be positive, reenter: ";
            cin >> quantity;
        }
        
        if(inventoryPtr[index] < quantity) //redifenes quantity to only grab what is left in inventory to stop negative inventory
        {
            quantity = inventoryPtr[index];
        }
            totalPrice = totalPrice + (quantity * pricePtr[index]);
            inventoryPtr[index] = inventoryPtr[index] - quantity;
        quantity = 0; //reset quantity
    } while (pluChoice != "0");
    return 0;
}

bool readInventory(string fname, int numRecords, string * pluPtr, double * pricePtr, string * namePtr, int * typePtr, int * inventoryPtr)
{
    
    ifstream inputFile(fname);
    
    
    
    if(inputFile) //continue program if file opens
    {
        
        for (int i = 0; i < numRecords;i++)
        {
            inputFile >> pluPtr[i] >> namePtr[i] >> typePtr[i] >> pricePtr[i] >> inventoryPtr[i];
        }
        inputFile.close(); //close file
        return true;
    }
    else
    {
        return false;
    }
    
}

void inventoryPrint(string fname, int numRecords, string * pluPtr, double * pricePtr, string * namePtr, int * typePtr, int * inventoryPtr)
{
    
    //add loop to print all records
    for (int i = 0; i < numRecords;i++)
    {
        cout << "PLU: " << pluPtr[i] << ", " << setw(17)<< left << namePtr[i] << ", type: " << typePtr[i] << ", unit price:" << setw(6) << right << pricePtr[i] << ", inventory: " << inventoryPtr[i] << endl;
    }
}

int getUserChoice()
{
    int choice; //display menu and store choice
    cout << "1 - Checkout" <<endl;
    cout << "2 - Print current inventory" << endl;
    cout << "3 - Quit" << endl;
    //store choice
    cin >> choice;
    
    return choice;
}

int determineNumRecords(string fname)
{
    ifstream inputFile(fname);
    
    //create trash variables
    string pluPtr;
    double pricePtr;
    int typePtr;
    int inventoryPtr;
    string namePtr;
    int numRecords = 0;
    while(inputFile >> pluPtr >> namePtr >> typePtr >> pricePtr >> inventoryPtr)
    {
        numRecords++;
    }
    inputFile.close(); //close file
    return numRecords;
}

int searchProduct(string plu, string *pluPtr, int numRecords)
{
    //linear search through pointer
    for(int i = 0;i<numRecords;i++)
    {
        if (pluPtr[i] == plu)
        {
            return i;
        }
        
        
    }
    return -1;
    
    
}

