#include <iostream>
#include <string>
#include<iomanip>
using namespace std;
const int Max = 100;
int count = 0;
struct product{
int id;
string name;
string category;
double price;
int quantity;
string expiry_date;
}inventory[Max];
int generateID(vector<product> &inventory);
int searchProductByName(product inventory[], int count, string name);
void add_product(product inventory[],int &count);
int searchProduct(product inventory[], int count, int id);
void searchProductMenu(product inventory[], int count);
void sellProduct(product inventory[], int count);
void displayProducts(product inventory[], int count);
void deleteProduct(product inventory[], int &count);
void updateProduct(product inventory[], int count);
void lowStockAlert(product inventory[], int count);
double calculateInventoryValue(product inventory[], int count);
int main(){
int choice;
do{
display_menu();
cin >> choice;
switch(choice)
{
case 1:
add_product(inventory, count);
break;
case 2:
sellProduct(inventory, count);
break;
case 3:
searchProductMenu(inventory, count);
break;
case 4:
displayProducts(inventory, count);
break;
case 5:
updateProduct(inventory, count);
break;
case 6:
deleteProduct(inventory, count);
break;
case 7:
lowStockAlert(inventory, count);
break;
case 8:
cout << "Total Inventory Value: ";
cout << calculateInventoryValue(inventory,count)<<endl;
break;
case 9:
cout << "Program exited.\n";
break;
default:
cout << "Invalid choice.\n";
}
} while(choice != 9);
return 0;
}
void display_menu(){
cout<<"=>What do you want to do:\n";
cout<<"\t1.Add Product\n";
cout<<"\t2.Sell Product\n";
cout<<"\t3.Search Product\n";
cout<<"\t4.Display Products\n";
cout<<"\t5.Update Product\n";
cout<<"\t6.Delete Product\n";
cout<<"\t7.Low stock alert\n";
cout<<"\t8.Inventory Value\n";
cout<<"\t9.Exit\n";
cout<<"Enter choice: ";
}
int searchProduct(product inventory[], int count, int id){
for(int i=0;i<count;i++){
if(inventory[i].id==id){
return i;
}
}
return -1;
}
void sellProduct(product inventory[], int count){
int id;
int sellQuantity;
cout<<"Enter product ID: ";
cin>>id;
int index = searchProduct(inventory, count, id);
if(index==-1){
cout<<"Product not found.\n";
return;
}
cout<<"Enter quantity to sell: ";
cin>>sellQuantity;
if(sellQuantity>inventory[index].quantity){
cout<<"Not enough stock available.\n";
return;
}
inventory[index].quantity-=sellQuantity;
cout<<"Sale completed.\n";
}
double calculateInventoryValue(product inventory[], int count){
double total=0;
for(int i=0;i<count;++i){
total+=inventory[i].price*inventory[i].quantity;
}
return total;
}
void updateProduct(product inventory[], int count){
int id;
cout<<"Enter product ID to update: ";
cin>>id;
int index=searchProduct(inventory,count,id);
if(index==-1){
cout<<"Product not found.\n";
return ;
}
cin.ignore();
cout<<"Enter new name: ";
getline(cin, inventory[index].name);
cout<<"Enter new category: ";
getline(cin, inventory[index].category);
cout<<"Enter new price: ";
cin>>inventory[index].price;
cout<<"Enter new quantity: ";
cin>>inventory[index].quantity;
cin.ignore();
cout<<"Enter new expiry date: ";
getline(cin, inventory[index].expiry_date);
cout<<"Product updated successfully.\n";
}
int searchProductByName(product inventory[], int count, string name){
    for(int i = 0; i < count; i++){
        if(inventory[i].name == name){
            return i;
        }
    }
    return -1;
}
int generateID(product inventory[], int count){
    if(count == 0){
        return 1000;
    }
    return inventory[count - 1].id + 1;
}

void add_product(product inventory[], int &count){
    if(count >= Max){
        cout << "Inventory is full.\n";
        return;
    }

    product p;
    string name;
    int searchChoice;
    char updateChoice;
    int index = -1;

    cout << "Do you want to search using:\n";
    cout << "1 - Name\n";
    cout << "2 - ID\n";
    cout << "Choice: ";
    cin >> searchChoice;

    if(searchChoice == 1){
        cout << "Enter product name: ";
        cin.ignore();
        getline(cin, name);
        index = searchProductByName(inventory, count, name);
    }
    else if(searchChoice == 2){
        cout << "Enter product ID: ";
        cin >> p.id;
        index = searchProduct(inventory, count, p.id);
    }
    else{
        cout << "Invalid choice.\n";
        return;
    }

    if(index != -1){
        cout << "Product already exists.\n";
        cout << "Do you want to update it? (y/n): ";
        cin >> updateChoice;

        if(updateChoice == 'y' || updateChoice == 'Y'){
            updateProduct(inventory, count);
        }
        return;
    }

    if(searchChoice == 1){
        p.name = name;
    }
    else{
        cin.ignore();
        cout << "Enter product name: ";
        getline(cin, p.name);
    }

    p.id = generateID(inventory, count);

    cout << "Enter price: ";
    cin >> p.price;

    cout << "Enter quantity: ";
    cin >> p.quantity;

    cin.ignore();
    cout << "Enter category: ";
    getline(cin, p.category);

    cout << "Enter expiry date: ";
    getline(cin, p.expiry_date);

    inventory[count] = p;
    count++;

    cout << "Product added successfully.\n";
    cout << "Generated ID: " << p.id << endl;
}
}