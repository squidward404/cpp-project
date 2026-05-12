#include<iostream>
#include<string>
using namespace std;
const int Max=100;int count=0;
struct product{
int id;
string name;
string catagory;
double price;
int quantity;
string expiry_daye;
}inventory[Max];
void display_menu();
void add_product(product inventory[],int &count);
int searchProductByID(product inventory[], int count, int id);
void sellProduct(product inventory[], int count);
float calculateInventoryValue(product inventory[], int count);
int main(){
display_menu();
return 0;
}
void display_menu(){
cout<<"=>What do you want to do:\n";
cout<<"\t1.Add Product\n";
cout<<"\t1.Sell Product\n";
cout<<"\t1.Search Product\n";
cout<<"\t1.Display Product\n";
cout<<"\t1.Delete Product\n";
cout<<"\t1.Update Product\n";
cout<<"\t1.Low stock alert\n";
cout<<"\t1.Inventory Value\n";
cout<<"\t1.Exit\n";
}

int searchProductByID(product inventory[], int count, int id){
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

int index = searchProductByID(inventory, count, id);
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

float calculateInventoryValue(product inventory[], int count){
float totalValue=0;

for(int i=0;i<count;i++){
totalValue+=inventory[i].price*inventory[i].quantity;
}

return totalValue;
}
