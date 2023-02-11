/* Title: project-01.cpp* 
Abstract: Create an automat for a "vending machine on steroids"
Author: Bailey Miller
Email: baimiller@csumb.edu
Estimate: 6 hours
Date: 09/28/2021 */
#include <iostream>
using namespace std;

//Note: Main should be placed on line 108

//food object class
class Food{
  public:
  Food();
  Food(string name, int calories, double price);
  string getName();
  int getCalories();
  double getPrice();
  void setName(string name);
  void setCalories(int calories);
  void setPrice(double price);
  void display();

  private:
  string myName;
  int myCalories;
  double myPrice;
};

//drink object class
class Drink{
  public:
    Drink();
    Drink(string name, int ounces, double price);
    string getName();
    int getOunces();
    double getPrice();
    void setName(string name);
    void setOunces(int ounces);
    void setPrice(double price);
    void display();

  private:
  string myName;
  int myOunces;
  double myPrice;
};

//automat object class + const int for queue arrays
const int AUTOMAT_MAX = 10;
class Automat{
  public:
    Automat();
    bool emptyFood();
    bool emptyDrink();
    void enqueue(Food f);
    void enqueue(Drink d);
    void dequeueFood();
    void dequeueDrink();
    Food frontFood();
    Drink frontDrink();
    int foodCount();
    int drinkCount();
    int getTotalCalories();
    int getTotalOunces();
    double getTotalPrice();
    void display();

  private:
    int myFoodFrontAutomat;
    int myFoodBackAutomat;
    int myDrinkFrontAutomat;
    int myDrinkBackAutomat;
    Food myFoodAutomat[AUTOMAT_MAX];
    Drink myDrinkAutomat[AUTOMAT_MAX];
};

//order object class + const int for stack array max
const int ORDER_MAX = 5;
class Order{
  public:
    Order();
    bool emptyFood();
    bool emptyDrink();
    void push(Food f);
    void push(Drink d);
    void popFood();
    void popDrink();
    Food topFood();
    Drink topDrink();
    int foodCount();
    int drinkCount();
    double getTotalPrice();
    void display();
    void cancel(Automat &);
    void purchase();
    static int getTotalOrders();
  private:
    int myFoodTopOrder;
    int myDrinkTopOrder;
    Food myFoodOrder[ORDER_MAX];
    Drink myDrinkOrder[ORDER_MAX];
    static int myTotalOrders;
};

//============ MAIN GOES BELOW THIS LINE ============
int main(){
  Drink d("Coke", 12, 5.99);
  Food f("Takis", 300, 4.99);
  Order o;
  o.push(d);
  o.push(f);
  o.display();
  f.display();
}
//============ MAIN GOES ABOVE THIS LINE ============

//food default constructor
Food::Food(){
  Food("No Item", 0, 0.00);
}

//food parameterized constructor
Food::Food(string name, int calories, double price){
  myName = name;
  myCalories = calories;
  myPrice = price;
}

//food method for getName
string Food::getName(){
  return myName;
}

//food method for getCalories
int Food::getCalories(){
  return myCalories;
}

//food method for getPrice
double Food::getPrice(){
  return myPrice;
}

//food method for setName
void Food::setName(string name){
  myName = name;
}

//food method for setCalories
void Food::setCalories(int calories){
  myCalories = calories;
}

//food method for setPrice
void Food::setPrice(double price){
  myPrice = price;
}

//food method for display()
void Food::display(){
  cout << "\nName: " << myName << "\nCalories: " << myCalories << "\nPrice: $" << myPrice << "\n";
}

//drink default constructor
Drink::Drink(){
  Drink("No Name", 0, 0.00);
}

//drink parameterized constructor
Drink::Drink(string name, int ounces, double price){
  myName = name;
  myOunces = ounces;
  myPrice = price;
}

//drink method for getName
string Drink::getName(){
  return myName;
}

//drink method for getOunces
int Drink::getOunces(){
  return myOunces;
}

//drink method for getPrice
double Drink::getPrice(){
  return myPrice;
}

//drink method for setName
void Drink::setName(string name){
  myName = name;
}

//drink method for setOunces
void Drink::setOunces(int ounces){
  myOunces = ounces;
}

//drink method for setPrice
void Drink::setPrice(double price){
  myPrice = price;
}

//drink method for display
void Drink::display(){
  cout << "\nName: " << myName << "\nOunces: " << myOunces << "\nPrice: $" << myPrice << "\n";
}

//automat class default constructor
Automat::Automat(){
  myFoodFrontAutomat = 0;
  myFoodBackAutomat = 0;
  myDrinkFrontAutomat = 0;
  myDrinkBackAutomat = 0;
}

//automat method for emptyFood
bool Automat::emptyFood(){
  if(myFoodFrontAutomat == myFoodBackAutomat){
    return true;
  }else{
    return false;
  }
}

//automat method for emptyDrink
bool Automat::emptyDrink(){
  if(myDrinkFrontAutomat == myDrinkBackAutomat){
    return true;
  }else{
    return false;
  }
}

//automat method for enqueue (food)
void Automat::enqueue(Food f){
  int newFoodBack = (myFoodBackAutomat + 1) % AUTOMAT_MAX;

  if(newFoodBack != myFoodFrontAutomat){
    myFoodAutomat[myFoodBackAutomat] = f;
    myFoodBackAutomat = newFoodBack;
  }else{
    cerr << "Food queue is full\n";
  }
}

//automat method for enqueue (drink)
void Automat::enqueue(Drink d){
  int newDrinkBack = (myDrinkBackAutomat + 1) % AUTOMAT_MAX;

  if(newDrinkBack != myDrinkBackAutomat){
    myDrinkAutomat[myDrinkBackAutomat] = d;
    myDrinkBackAutomat = newDrinkBack;
  }else{
    cerr << "Drink queue is full\n";
  }
}

//automat method for dequeueFood
void Automat::dequeueFood(){
  myFoodFrontAutomat = (myFoodFrontAutomat + 1) % AUTOMAT_MAX;
}

//automat method for dequeueDrink
void Automat::dequeueDrink(){
  myDrinkFrontAutomat = (myDrinkFrontAutomat + 1) % AUTOMAT_MAX;
}

//automat method for retriving front food
Food Automat::frontFood(){
  return myFoodAutomat[myFoodFrontAutomat];
}

//automat method for retriving front drink
Drink Automat::frontDrink(){
  return myDrinkAutomat[myDrinkFrontAutomat];
}

//automat method for foodCount
int Automat::foodCount(){
  int count = 0;
  for(int i = myFoodFrontAutomat; i != myFoodBackAutomat; i = (i + 1) % AUTOMAT_MAX){
    count++;
  }
  return count;
}

//automat method for drinkCount
int Automat::drinkCount(){
  int count = 0;
  for(int i = myFoodFrontAutomat; i != myFoodBackAutomat; i = (i + 1) % AUTOMAT_MAX){
    count++;
  }
  return count;
}

//automat method for getTotalCalories
int Automat::getTotalCalories(){
  int totalCalories = 0;
  for(int i = myFoodFrontAutomat; i != myFoodBackAutomat; i++){
    totalCalories = totalCalories + myFoodAutomat[i].getCalories();
  }
  return totalCalories;
}

//automat method for getTotalOunces
int Automat::getTotalOunces(){
  int totalOunces = 0;
  for(int i = myDrinkFrontAutomat; i != myDrinkBackAutomat; i++){
    totalOunces = totalOunces + myDrinkAutomat[i].getOunces();
  }
  return totalOunces;
}

//automat method for getTotalPrice
double Automat::getTotalPrice(){
  double totalPrice = 0;
  for(int i = myFoodFrontAutomat; i != myFoodBackAutomat; i = (i + 1) % AUTOMAT_MAX){
    totalPrice = totalPrice + myFoodAutomat[i].getPrice();
  }
  for(int i = myDrinkFrontAutomat; i != myDrinkBackAutomat; i = (i + 1) % AUTOMAT_MAX){
    totalPrice = totalPrice + myDrinkAutomat[i].getPrice();
  }
  return totalPrice;
}

//automat method for display
void Automat::display(){
  cout << "Automat :\n\t";
  cout << "Food: \n";
  for(int i = myFoodFrontAutomat; i != myFoodBackAutomat; i = (i + 1) % AUTOMAT_MAX){
    cout << "\t\t" << myFoodAutomat[i].getName() << ": " << myFoodAutomat[i].getCalories() << " calories, $" << myFoodAutomat[i].getPrice() << "\n";
  }
  int foodCount = 0;
  for(int i = myFoodFrontAutomat; i != myFoodBackAutomat; i = (i + 1) % AUTOMAT_MAX){
    foodCount++;
  }
  int totalCalories = 0;
  for(int i = myFoodFrontAutomat; i != myFoodBackAutomat; i++){
    totalCalories = totalCalories + myFoodAutomat[i].getCalories();
  }

  cout << "\t\t" << foodCount << " food items - Total Calories: " << totalCalories << "\n";
  cout << "\tDrinks:\n";
  for(int i = myDrinkFrontAutomat; i != myDrinkBackAutomat; i = (i + 1) % AUTOMAT_MAX){
    cout << "\t\t" << myDrinkAutomat[i].getName() << ": " << myDrinkAutomat[i].getOunces() << " ounces, $" << myDrinkAutomat[i].getPrice() << "\n";
  }

  int drinkCount = 0;
  for(int i = myDrinkFrontAutomat; i != myDrinkBackAutomat; i = (i + 1) % AUTOMAT_MAX){
    drinkCount++;
  }
  int totalOunces = 0;
  for(int i = myDrinkFrontAutomat; i != myDrinkBackAutomat; i++){
    totalOunces = totalOunces + myDrinkAutomat[i].getOunces();
  }
  cout << "\t\t" << drinkCount << " drink items - Total Ounces: " << totalOunces << "\n\n";
}

//myTotalOrders initalization
int Order::myTotalOrders = -1;

//order class default constructor
Order::Order(){
  myFoodTopOrder = -1;
  myDrinkTopOrder = -1;
  myTotalOrders++;
}

//order method for emptyFood
bool Order::emptyFood(){
  if(myFoodTopOrder == -1){
    return true;
  }else{
    return false;
  }
}

//order method for emptyDrink
bool Order::emptyDrink(){
  if(myDrinkTopOrder == -1){
    return true;
  }else{
    return false;
  }
}

//order method for push (food)
void Order::push(Food f){
  if(myFoodTopOrder >= (ORDER_MAX-1)){
    cerr << "Food stack is full in order class\n";
  }else{
    myFoodTopOrder++;
    myFoodOrder[myFoodTopOrder] = f;
  }
}

//order method for push (drink)
void Order::push(Drink d){
  if(myDrinkTopOrder == (ORDER_MAX-1)){
    cerr << "Drink stack is full in order class\n";
  }else{
    myDrinkTopOrder++;
    myDrinkOrder[myDrinkTopOrder] = d;
  }
}

//order method for popFood
void Order::popFood(){
  if(myFoodTopOrder > -1){
    myFoodTopOrder--;
  }else{
    cerr << "Unable to pop, food stack empty in order class\n";
  }
}

//order method for popDrink
void Order::popDrink(){
  if(myDrinkTopOrder > -1){
    myDrinkTopOrder--;
  }else{
    cerr << "Unable to pop, drink stack is empty in order class\n";
  }
}

//order method for topFood
Food Order::topFood(){
  return myFoodOrder[myFoodTopOrder];
}

//order method for topDrink
Drink Order::topDrink(){
  return myDrinkOrder[myDrinkTopOrder];
}

//order method for foodCount
int Order::foodCount(){
  int count = 0;
  for(int i = 0; i <= myFoodTopOrder; i++){
    count++;
  }
  return count;
}

//order method for drinkCount
int Order::drinkCount(){
  int count = 0;
  for(int i = 0; i <= myDrinkTopOrder; i++){
    count++;
  }
  return count;
}

//order method for getTotalPrice
double Order::getTotalPrice(){
  double totalPrice = 0;
  for(int i = 0; i <= myFoodTopOrder; i++){
    totalPrice = totalPrice + myFoodOrder[i].getPrice();
  }
  for(int i = 0; i <= myDrinkTopOrder; i++){
    totalPrice = totalPrice + myDrinkOrder[i].getPrice();
  }
  return totalPrice;
}

//order method for display
void Order::display(){
  cout << "Order: \n";
  int foodCount = 0;
  for(int i = 0; i <= myFoodTopOrder; i++){
    foodCount++;
  }
  cout << "\tFood (" << foodCount << " items): \n";

  for(int i = 0; i < foodCount; i++){
    cout << "\t\t" << myFoodOrder[i].getName() << ": " << myFoodOrder[i].getCalories() << " calories, $" << myFoodOrder[i].getPrice() << "\n";
  }
  
  int drinkCount = 0;
  for(int i = 0; i <= myDrinkTopOrder; i++){
    drinkCount++;
  }

  cout << "\tDrink (" << drinkCount << " items): \n";
  
  for(int i = 0; i < drinkCount; i++){
    cout << "\t\t" << myDrinkOrder[i].getName() << ": " << myDrinkOrder[i].getOunces() << " Ounces, $" << myDrinkOrder[i].getPrice() << "\n";
  }

  cout << "\tOrder Total: $";
  double totalPrice = 0;
  for(int i = 0; i <= myFoodTopOrder; i++){
    totalPrice = totalPrice + myFoodOrder[i].getPrice();
  }
  for(int i = 0; i <= myDrinkTopOrder; i++){
    totalPrice = totalPrice + myDrinkOrder[i].getPrice();
  }
  cout << totalPrice << "\n\n";
}

//order method for cancel
void Order::cancel(Automat & automat){
  for(int i = myFoodTopOrder; i > -1; i--){
    automat.enqueue(myFoodOrder[i]);
    myFoodTopOrder--;
  }
  for(int i = myDrinkTopOrder; i > -1; i--){
    automat.enqueue(myDrinkOrder[i]);
    myDrinkTopOrder--;
  }
}

//order method for purchase
void Order::purchase(){
  myFoodTopOrder = -1;
  myDrinkTopOrder = -1;
}

//order method for getTotalOrders
int Order::getTotalOrders(){
  return myTotalOrders;
}