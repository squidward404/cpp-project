#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<sqlite3.h>
using namespace std;
const int Max=1000;
int count=0;
sqlite3 *db;
char *errMsg = 0;
struct product{
int id;
string name;
string category;
double price;
int quantity;
string expiry_date;
}inventory[Max];
void display_menu();
void add_product(product inventory[],int &count);
int searchProduct(product inventory[], int count, int id);
int searchProductByName(product inventory[], int count, string name);
int generateID(product inventory[], int count);
void searchProductMenu(product inventory[], int count);
void sellProduct(product inventory[], int count);
void displayProducts(product inventory[], int count);
void deleteProduct(product inventory[], int &count);
void updateProduct(product inventory[], int count);
void lowStockAlert(product inventory[], int count);
double calculateInventoryValue(product inventory[], int count);

void createTable();
void saveProductToDB(product p);
void loadProductsFromDB();
static int loadCallback(void *NotUsed, int argc, char **argv, char **azColName){
inventory[count].id=stoi(argv[0]);
inventory[count].name=argv[1];
inventory[count].category=argv[2];
inventory[count].price=stod(argv[3]);
inventory[count].quantity=stoi(argv[4]);
inventory[count].expiry_date=argv[5];
count++;
return 0;
}
int main(){
int rc=sqlite3_open("inventory.db",&db);
if(rc){
cout<<"Can't open database.\n";
return 1;
}
cout << "Database connected successfully.\n";
createTable();
loadProductsFromDB();
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
sqlite3_close(db);
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
int searchProductByName(product inventory[], int count, string name){
for(int i = 0; i < count; i++){
if(inventory[i].name == name){
return i;
}
}
return -1;
}
void searchProductMenu(product inventory[], int count){
int id;
cout<<"Enter product ID to search: ";
cin>>id;
int index=searchProduct(inventory,count,id);
if(index==-1){
cout<<"Product not found.\n";
return;
}
cout<<"\n#####PRODUCT FOUND#####\n";
cout<<"ID: "<<inventory[index].id<<endl;
cout<<"NAME: "<<inventory[index].name<<endl;
cout<<"CATEGORY: "<<inventory[index].category<<endl;
cout<<"PRICE: "<<inventory[index].price<<endl;
cout<<"QUANTITY: "<<inventory[index].quantity<<endl;
cout<<"EXPIRY DATE: "<<inventory[index].expiry_date<<endl;
}
int generateID(product inventory[], int count){
int maxID=999;
for(int i=0;i<count;i++){
if(inventory[i].id>maxID){
maxID =inventory[i].id;
}
}
return maxID + 1;
}
void add_product(product inventory[], int &count){
if(count >= Max){
cout<<"Inventory is full.\n";
return;
}
product p;
cout << "Enter product name: ";
cin.ignore();
getline(cin,p.name);
int index = searchProductByName(inventory,count,p.name);
if(index!=-1){
int extra;
cout<<"Product already exists.\n";
cout<<"Enter quantity to add: ";
cin>>extra;
inventory[index].quantity+=extra;
string sql="UPDATE products SET quantity = "+
to_string(inventory[index].quantity) +" WHERE id = "+to_string(inventory[index].id) + ";";
sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
cout<<"Stock updated.\n";
return ;
}
p.id = generateID(inventory, count);
cout<<"Enter price: ";
cin>>p.price;
cout<<"Enter quantity: ";
cin>>p.quantity;
cin.ignore();
cout<<"Enter category: ";
getline(cin, p.category);
cout<<"Enter expiry date: ";
getline(cin,p.expiry_date);
inventory[count]=p;
count++;
saveProductToDB(p);
cout<<"Product added successfully.\n";
cout<<"Generated ID: "<<p.id<<endl;
}
void displayProducts(product inventory[], int count){
if(count==0){
cout<<"inventory is empty.\n";
return ;
}
cout << "\n" << right << setw(50)<< "##### PRODUCT LIST #####\n";
cout<<left<<setw(10)<<"ID"<<setw(20)<<"NAME"<<setw(20)<<"CATEGORY"<<setw(10)<<"PRICE"<<setw(10) << "QUANTITY"<< setw(15) << "EXPIRY DATE"<< endl;
for(int i=0;i<count;++i){
cout << left
     << setw(10) << inventory[i].id
     << setw(20) << inventory[i].name
     << setw(20) << inventory[i].category
     << setw(10) << inventory[i].price
     << setw(10) << inventory[i].quantity
     << setw(15) << inventory[i].expiry_date
     << endl;
}
char choice;
cout<<"\nDo you want to save the product list to a text file? (y/n): "; 
cin>>choice;
if(choice=='y' || choice=='Y'){
ofstream file("inventory.txt");
if(!file){
cout<<"Error creating file.\n";
return;
}
file<<"\n"<<right<<setw(50)<<"##### PRODUCT LIST #####\n";
file<<left<<setw(10)<<"ID"<<setw(20)<<"NAME"<<setw(20)<<"CATEGORY"<<setw(10)<<"PRICE"<<setw(10) << "QUANTITY"<< setw(15) << "EXPIRY DATE"<< endl;
for(int i=0;i<count;++i){
file<<left
<<setw(10)<<inventory[i].id
<<setw(20)<<inventory[i].name
<<setw(20)<<inventory[i].category
<<setw(10)<<fixed<<setprecision(2)<<inventory[i].price
<<setw(10)<<inventory[i].quantity
<<setw(15)<<inventory[i].expiry_date
<<endl;
}
file.close();
cout<<"Product list saved successfully to inventory.txt\n";
}
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
string sql="UPDATE products SET quantity = " +
to_string(inventory[index].quantity) +
" WHERE id = "+to_string(id) + ";";
sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
cout<<"Sale completed.\n";
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
string sql ="UPDATE products SET "
"name = '" + inventory[index].name +
"', category = '" + inventory[index].category +
"', price = " + to_string(inventory[index].price) +
", quantity = " + to_string(inventory[index].quantity) +
", expiry_date = '" + inventory[index].expiry_date +
"' WHERE id = " + to_string(id) + ";";
sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
}
void deleteProduct(product inventory[], int &count){
int id;
cout<<"Enter product ID: ";
cin>>id;
int index = searchProduct(inventory, count, id);
if(index==-1){
cout<<"Product not found.\n";
return;
}
inventory[index]=inventory[count - 1];
count--;
string sql ="DELETE FROM products WHERE id = " +to_string(id) + ";";
sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
cout<<"Product deleted successfully.\n";
}
void lowStockAlert(product inventory[], int count){
int threshold;
cout<<"Enter low stock threshold: ";
cin>>threshold;
bool found=false;
for(int i=0;i<count;++i){
if(inventory[i].quantity<=threshold){
found=true;
cout<<"ID: "<<inventory[i].id<<endl;
cout<<"NAME: "<<inventory[i].name<<endl;
cout<<"QUANTITY: "<<inventory[i].quantity<<endl;
}
}
if(!found){
cout<<"No low stock products found.\n";
}
}
double calculateInventoryValue(product inventory[], int count){
double total=0;
for(int i=0;i<count;++i){
total+=inventory[i].price*inventory[i].quantity;
}
return total;
}
void createTable(){
string sql =
"CREATE TABLE IF NOT EXISTS products ("
"id INTEGER PRIMARY KEY, "
"name TEXT, "
"category TEXT, "
"price REAL, "
"quantity INTEGER, "
"expiry_date TEXT);";
int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
if(rc != SQLITE_OK){
cout << "SQL Error: " << errMsg << endl;
sqlite3_free(errMsg);
}
else{
cout << "Table ready.\n";
}
}
void saveProductToDB(product p){
string sql =
"INSERT INTO products (id, name, category, price, quantity, expiry_date) VALUES (" +
to_string(p.id) + ", '" +
p.name + "', '" +
p.category + "', " +
to_string(p.price) + ", " +
to_string(p.quantity) + ", '" +
p.expiry_date + "');";
int rc=sqlite3_exec(db,sql.c_str(),0,0,&errMsg);
if(rc!=SQLITE_OK){
cout << "Failed to save product.\n";
sqlite3_free(errMsg);
}
else{
cout << "Product saved to database.\n";
}
}
void loadProductsFromDB(){
string sql = "SELECT * FROM products;";
int rc = sqlite3_exec(db, sql.c_str(), loadCallback, 0, &errMsg);
if(rc != SQLITE_OK){
cout << "Failed to load products.\n";
sqlite3_free(errMsg);
}
else{
cout << "Products loaded successfully.\n";
}
}

