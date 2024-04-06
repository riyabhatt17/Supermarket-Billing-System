#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <vector>
#include <string>
#include "Stock.h"

using namespace std;

class Bill {
private:
    vector<Product> products;

public:
    
    // Function to add a product to the bill
	void addProduct(const Product& product) {
	    if (product.getQuantity() <= 0) {
	        cout << "Product '" << product.getName() << "' is out of stock." << endl;
	    } else {
	        products.push_back(product);
	        cout << "Product '" << product.getName() << "' added to the bill." << endl;
	    }
	}
	
	
	    // Function to calculate and display the bill
    void generateBill() const {
        float total = 0.0;
        cout << "Bill Details:" << endl;
        for (const auto& product : products) {
            float totalPrice = product.getPrice() * product.getQuantity();
            total += totalPrice;
            cout << "Name: " << product.getName() << "\tPrice: " << product.getPrice() << "\tQuantity: " << product.getQuantity() << "\tTotal: " << totalPrice << endl;
        }
        cout << "Total Bill Amount: " << total << endl;
    }

    // Function to get the products in the bill
    const vector<Product>& getProducts() const {
        return products;
    }
};

#endif // BILL_H
