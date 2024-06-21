#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Product {
protected:
    int id;
    double price;
    string name;
    int quantity; 

public:
    Product(int id, double price, const string& name, int quantity)
        : id(id), price(price), name(name), quantity(quantity) {}

    int getId() const {
        return id;
    }

    int getQuantity() const {
        return quantity;
    }

    void reduceQuantity(int amount) {
        quantity -= amount;
    }

    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Price: " << price << ", Quantity: " << quantity << endl;
    }

    virtual ~Product() {}
};

class PerishableProduct : public Product {
private:
    string expirationDate;

public:
    PerishableProduct(int id, double price, const string& name, int quantity, const string& expDate)
        : Product(id, price, name, quantity), expirationDate(expDate) {}

    void display() const override {
        cout << "Perishable Product - ";
        Product::display();
        std::cout << "Expiration Date: " << expirationDate << endl;
    }
};

class ImperishableProduct : public Product {
public:
    ImperishableProduct(int id, double price, const string& name, int quantity)
        : Product(id, price, name, quantity) {}

    void display() const override {
        std::cout << "Imperishable Product - ";
        Product::display();
    }
};

class Order {
private:
    string customerName;
    vector<pair<int, int>> productsOrdered; 

public:
    Order(const string& customerName)
        : customerName(customerName) {}

    void addProduct(Product* product, int quantity) {
        productsOrdered.push_back(make_pair(product->getId(), quantity));
    }

    void display() const {
        cout << "Customer: " << customerName << ", Products in order:" << endl;
        for (const auto& pair : productsOrdered) {
            cout << "Product ID: " << pair.first << ", Quantity: " << pair.second << endl;
        }
    }
};

class Store {
private:
    vector<Product*> inventory;
    vector<Order> orders;

public:
    void addProduct() {
        char type;
        cout << "Enter type of product (P for perishable, I for imperishable): ";
        cin >> type;

        int qty, id;
        double price;
        string name;

        cout << "Enter quantity: ";
        cin >> qty;
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter name: ";
        cin.ignore(); 
        getline(cin, name);
        cout << "Enter ID: ";
        cin >> id;

        if (type == 'P') {
            string expDate;
            cout << "Enter expiration date: ";
            cin.ignore(); 
            getline(cin, expDate);
            inventory.push_back(new PerishableProduct(id, price, name, qty, expDate));
        } else if (type == 'I') {
            inventory.push_back(new ImperishableProduct(id, price, name, qty));
        } else {
            cout << "Invalid product type. Product not added." << endl;
            return;
        }

        cout << "Product added successfully." << endl;
    }

    void createOrder() {
        if (inventory.empty()) {
            cout << "Inventory is empty. Cannot create order." << endl;
            return;
        }

        cout << "Available Products:" << endl;
        displayAllProducts();

        string customerName;
        cout << "Enter customer name for the order: ";
        cin.ignore(); 
        getline(cin, customerName);

        Order newOrder(customerName);
        char addAnother;
        do {
            int productId, quantity;
            cout << "Enter product ID to add to order: ";
            cin >> productId;

            bool found = false;
            for (Product* product : inventory) {
                if (product->getId() == productId) {
                    cout << "Enter quantity to add: ";
                    cin >> quantity;

                    if (quantity > product->getQuantity()) {
                        cout << "Error: Insufficient quantity available." << endl;
                        continue;
                    }

                    newOrder.addProduct(product, quantity);
                    product->reduceQuantity(quantity);
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Product not found in inventory. Please enter a valid ID." << endl;
            }

            cout << "Do you want to add another product to the order? (Y/N): ";
            cin >> addAnother;
        } while (addAnother == 'Y' || addAnother == 'y');

        orders.push_back(newOrder);
        cout << "Order successfully created." << endl;
    }

    void displayAllProducts() const {
        if (inventory.empty()) {
            cout << "Inventory is empty." << endl;
        } else {
            cout << "Products in Inventory:" << endl;
            for (const auto& product : inventory) {
                product->display();
            }
        }
    }

    void displayAllOrders() const {
        if (orders.empty()) {
            cout << "No orders placed yet." << endl;
        } else {
            cout << "All Orders:" << endl;
            for (const auto& order : orders) {
                order.display();
            }
        }
    }

    ~Store() {
        for (Product* product : inventory) {
            delete product;
        }
        inventory.clear();
    }
};

int main() {
    Store store;

    int choice;
    do {
        cout << "\nGrocery Store Management System\n"
                     "1. Add Product\n"
                     "2. Create Order\n"
                     "3. Display All Products\n"
                     "4. Display All Orders\n"
                     "5. Exit\n"
                     "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                store.addProduct();
                break;
            case 2:
                store.createOrder();
                break;
            case 3:
                store.displayAllProducts();
                break;
            case 4:
                store.displayAllOrders();
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}