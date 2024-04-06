#include <iostream>
#include "Stock.h"
#include "Bill.h"

// Function to display current stock
void displayCurrentStock(const Stock& supermarketStock) {
    cout << "\nCurrent Stock:" << endl;
    supermarketStock.displayStock();
}

// Function to add a new product to the stock
void addProductToStock(Stock& supermarketStock) {
    string name;
    int id, quantity;
    float price;

    cout << "\nEnter product details:" << endl;
    cout << "Name: ";
    cin >> name;
    cout << "ID: ";
    cin >> id;
    cout << "Price: ";
    cin >> price;
    cout << "Quantity: ";
    cin >> quantity;

    Product productToAdd(name, id, price, quantity);
    supermarketStock.addProduct(productToAdd);

    cout << "\nProduct added to stock successfully." << endl;
}

// Function to generate a bill for a customer and update stock simultaneously
void generateBillAndUpdateStock(Stock& supermarketStock, Bill& supermarketBill) {
    // Display current stock
    displayCurrentStock(supermarketStock);

    // Adding products to the bill
    char choice;
    do {
        string name;
        int id, quantity;
        float price;

        cout << "\nEnter product details:" << endl;
        cout << "Name: ";
        cin >> name;
        cout << "ID: ";
        cin >> id;
        cout << "Price: ";
        cin >> price;
        cout << "Quantity: ";
        cin >> quantity;

        Product productToAdd(name, id, price, quantity);
        supermarketBill.addProduct(productToAdd);

        cout << "\nDo you want to add another product? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Display the bill
    cout << "\nGenerated Bill:" << endl;
    supermarketBill.generateBill();

    // Update stock based on products sold
    cout << "\nUpdating stock..." << endl;
    supermarketStock.updateStock(supermarketBill.getProducts());

    // Display updated stock
    displayCurrentStock(supermarketStock);
}

int main() {
    Stock supermarketStock;
    Bill supermarketBill;

    // Add the full path to the stock file
    string stockFileName = "stock.txt";


    // Load existing stock from file
    supermarketStock.loadStock(stockFileName);

    int choice;
    do {
        cout << "1. Display current stock" << endl;
        cout << "2. Add a new product to the stock" << endl;
        cout << "3. Update product details" << endl;
        cout << "4. Generate bill for a customer and update stock" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayCurrentStock(supermarketStock);
                break;
            case 2:
                addProductToStock(supermarketStock);
                // Store updated stock to file
                if (supermarketStock.storeStock(stockFileName)) {
                    cout << "\nStock updated and stored successfully." << endl;
                } else {
                    cout << "\nFailed to update and store stock." << endl;
                }
                break;
            case 3:
                 \
                // Call updateProductDetails function
                supermarketStock.updateProductDetails();
                // Store updated stock to file
                if (supermarketStock.storeStock(stockFileName)) {
                    cout << "\nStock updated and stored successfully." << endl;
                } else {
                    cout << "\nFailed to update and store stock." << endl;
                }
                break;
            case 4:
                generateBillAndUpdateStock(supermarketStock, supermarketBill);
                // Store updated stock to file
                if (supermarketStock.storeStock(stockFileName)) {
                    cout << "\nStock updated and stored successfully." << endl;
                } else {
                    cout << "\nFailed to update and store stock." << endl;
                }
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}
