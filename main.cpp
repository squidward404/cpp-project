#include<iostream>
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
int main(){
display_menu();
return 0;
}
void display_menu(){
cout<<"=>What do you want to:\n";
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
