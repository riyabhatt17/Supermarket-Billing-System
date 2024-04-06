#ifndef STOCK_H
#define STOCK_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Product {
private:
    string name;
    int id;
    float price;
    int quantity;

public:
    Product() {
        name = "";
        id = 0;
        price = 0.0;
        quantity = 0;
    }

    Product(string n, int i, float p, int q) {
        name = n;
        id = i;
        price = p;
        quantity = q;
    }

    string getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    int getId() const {
        return id;
    }

    float getPrice() const {
        return price;
    }

    void setPrice(float newPrice) {
        price = newPrice;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int q) {
        quantity = q;
    }

    // Function to serialize product data
    string serialize() const {
        return name + "," + to_string(id) + "," + to_string(price) + "," + to_string(quantity);
    }

    // Function to deserialize product data
    static Product deserialize(const string& data) {
        stringstream ss(data);
        string name;
        int id, quantity;
        float price;
        getline(ss, name, ',');
        ss >> id;
        ss.ignore();
        ss >> price;
        ss.ignore();
        ss >> quantity;
        return Product(name, id, price, quantity);
    }
};

class Stock {
private:
    vector<Product> products;

public:
    // Function to load stock from file
    void loadStock(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            products.clear();
            string line;
            while (getline(file, line)) {
                products.push_back(Product::deserialize(line));
            }
            file.close();
            cout << "Stock loaded successfully from file: " << filename << endl;
        } else {
            cout << "Unable to open file for loading stock: " << filename << endl;
        }
    }

   
   // Function to display stock details
void displayStock() const {
    cout << "Stock Details:" << endl;
    for (const auto& product : products) {
        if (product.getId() != 0) { // Check if the product is initialized
            cout << "Name: " << product.getName() << "\tID: " << product.getId() << "\tPrice: " << product.getPrice() << "\tQuantity: " << product.getQuantity() << endl;
        }
    }
}


    // Function to update stock after generating a bill
    void updateStock(const vector<Product>& soldProducts) {
    for (const auto& soldProduct : soldProducts) {
        if (soldProduct.getQuantity() <= 0) {
            cout << "Product '" << soldProduct.getName() << "' is already out of stock. Stock not updated." << endl;
            continue; // Skip updating stock if quantity is 0 or negative
        }
        
        for (auto& product : products) {
            if (product.getId() == soldProduct.getId()) {
                product.setQuantity(product.getQuantity() - soldProduct.getQuantity());
                break;
            }
        }
    }
}

    // Function to store stock to file
    bool storeStock(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& product : products) {
                file << product.serialize() << endl;
            }
            file.close();
            cout << "Stock details stored in file: " << filename << endl;
            return true; // Return true indicating success
        } else {
            cout << "Unable to open file for storing stock: " << filename << endl;
            return false; // Return false indicating failure
        }
    }

    // Function to add a new product to the stock
    void addProduct(const Product& newProduct) {
        products.push_back(newProduct);
        cout << "New product added to stock." << endl;
    }
    
    // Function to update the details of an existing product
	// Declaration of updateProductDetails() function
	void updateProductDetails();
};

// Function to update the details of an existing 
// Definition of updateProductDetails() function
void Stock::updateProductDetails() {
    int id;
    cout << "\nEnter the ID of the product to update: ";
    cin >> id;

    // Search for the product by ID
    bool found = false;
    for (auto& product : products) {
        if (product.getId() == id) {
            // Product found, update its details
            string name;
            float price;
            int quantity;
            cout << "Enter new name: ";
            cin >> name;
            cout << "Enter new price: ";
            cin >> price;
            cout << "Enter new quantity: ";
            cin >> quantity;

            product.setName(name);
            product.setPrice(price);
            product.setQuantity(quantity);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Product with ID " << id << " not found." << endl;
    } else {
        cout << "Product details updated successfully." << endl;
    }
}


#endif // STOCK_H
