#include <iostream>
#include <string>
using namespace std;
const int Max = 100;
int count = 0;
struct product
{
    int id;
    string name;
    string catagory;
    double price;
    int quantity;
    string expiry_date;
} inventory[Max];

void display_menu();
void add_product(product inventory[], int &count);
int searchProductByID(product inventory[], int count, int id);
void sellProduct(product inventory[], int count);
float calculateInventoryValue(product inventory[], int count);

void pressEnterToContinue()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

int main()

{
    display_menu();
    return 0;
}

void display_menu()
{
    cout << "=>What do you want to do:\n";
    cout << "\t1.Add Product\n";
    cout << "\t2.Sell Product\n";
    cout << "\t3.Search Product\n";
    cout << "\t4.Display Product\n";
    cout << "\t5.Delete Product\n";
    cout << "\t6.Update Product\n";
    cout << "\t7.Low stock alert\n";
    cout << "\t8.Inventory Value\n";
    cout << "\t9.Exit\n";
}

int searchProductByID(product inventory[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (inventory[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void sellProduct(product inventory[], int count)
{
    int id;
    int sellQuantity;

    cout << "Enter product ID: ";
    cin >> id;

    int index = searchProductByID(inventory, count, id);
    if (index == -1)
    {
        cout << "Product not found.\n";
        return;
    }

    cout << "Enter quantity to sell: ";
    cin >> sellQuantity;

    if (sellQuantity > inventory[index].quantity)
    {
        cout << "Not enough stock available.\n";
        return;
    }

    inventory[index].quantity -= sellQuantity;
    cout << "Sale completed.\n";
}

float calculateInventoryValue(product inventory[], int count)
{
    float totalValue = 0;

    for (int i = 0; i < count; i++)
    {
        totalValue += inventory[i].price * inventory[i].quantity;
    }

    return totalValue;
}

void updateProduct(product inventory[Max], int count)
{
    cout << "\nUpdate Product\n";
    cout << "  Enter product ID to update: ";
    int id;
    cin >> id;

    int index = searchProductByID(inventory, count, id);
    if (index == -1)
    {
        cout << "  Product not found.\n";
        pressEnterToContinue();
        return;
    }

    product &p = inventory[index];
    cout << "  Editing: " << p.name << " (ID: " << p.id << ")\n";

    cout << "  What would you like to update?\n";
    cout << "  1. Name       (current: " << p.name << ")\n";
    cout << "  2. Price      (current: " << p.price << ")\n";
    cout << "  3. Quantity   (current: " << p.quantity << ")\n";
    cout << "  4. Category   (current: " << p.catagory << ")\n";
    cout << "  5. Expiry Date(current: " << p.expiry_date << ")\n";
    cout << "  0. Cancel\n";
    cout << "  Choice: ";
    int choice;
    cin >> choice;

    cin.ignore();
    switch (choice)
    {
    case 1:
        cout << "  New name : ";
        getline(cin, p.name);
        cout << "  ✓ Name updated.\n";
        break;
    case 2:
        cout << "  New price : ";
        cin >> p.price;
        cout << "  ✓ Price updated.\n";
        break;
    case 3:
        cout << "  New quantity : ";
        cin >> p.quantity;
        cout << "  ✓ Quantity updated.\n";
        break;
    case 4:
        cout << "  New category : ";
        getline(cin, p.catagory);
        cout << "  ✓ Category updated.\n";
        break;
    case 5:
        cout << "  New expiry date : ";
        getline(cin, p.expiry_date);
        cout << "  ✓ Expiry date updated.\n";
        break;
    case 0:
        cout << "  Update cancelled.\n";
        break;
    default:
        cout << "  Invalid choice.\n";
    }
    pressEnterToContinue();
}
