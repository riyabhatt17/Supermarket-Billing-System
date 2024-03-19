#include <iostream>
#include "Stock.h"
#include "Bill.h"


	int main() {
    Stock supermarketStock;
    Bill supermarketBill;

    // Add the full path to the stock file
    string stockFileName = "C:\\Program Files (x86)\\Desktop\\stock.txt";
    supermarketStock.loadStock(stockFileName);

    // Display existing stock
    cout << "Existing Stock:" << endl;
    supermarketStock.displayStock();

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
    supermarketStock.updateStock(supermarketBill.getProducts());

    // Store updated stock to file
    supermarketStock.storeStock(stockFileName);

    return 0;
}
