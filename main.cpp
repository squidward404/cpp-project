#include<iostream>
using namespace std;

struct supplier{
int supplier_id;
string supplier_name;
string phone;
};
struct product{
int product_id;
int supplier_id;
string name;
double price;
};
struct customer{
int customer_id;
string name;
string phone;
};
struct inventory_item{
int inventory_id;
int product_id;
int quantity;
};
struct sale{
int sale_id;
int product_id;
int customer_id;
int quantity_sold;
int sold_date;
};
int main(){
  
    return 0;
}
