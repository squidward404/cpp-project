#include "functions.h"
#include <iostream>
#include <string>

using namespace std;

void updateProduct(Product inventory[], int count) {
    int id;
    cout << "Enter Product ID to update: ";
    cin >> id;

    int index = searchProductByID(inventory, count, id);

    if (index == -1) {
        cout << "Product not found!\n";
        return;
    }

    int choice;
    cout << "\nWhat do you want to update?\n";
    cout << "1. Name\n";
    cout << "2. Price\n";
    cout << "3. Quantity\n";
    cout << "4. Category\n";
    cout << "5. Expiry Date\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Enter new name: ";
            cin >> inventory[index].name;
            break;

        case 2:
            cout << "Enter new price: ";
            cin >> inventory[index].price;
            break;

        case 3:
            cout << "Enter new quantity: ";
            cin >> inventory[index].quantity;
            break;

        case 4:
            cout << "Enter new category: ";
            cin >> inventory[index].category;
            break;

        case 5:
            cout << "Enter new expiry date: ";
            cin >> inventory[index].expiryDate;
            break;

        default:
            cout << "Invalid choice!\n";
            return;
    }

    cout << "Product updated successfully!\n";
}


void lowStockAlert(Product inventory[], int count) {
    int threshold;
    cout << "\n--- Low Stock Alert ---\n";
    cout << "Enter threshold: ";
    cin >> threshold;
    
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (inventory[i].quantity < threshold) {
            cout << "WARNING: " << inventory[i].name
                 << " | Quantity: " << inventory[i].quantity
                 << endl;
            found = true;
        }
    }
    if (!found)
        cout << "All products are sufficiently stocked.\n";
}