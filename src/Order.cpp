/*******************************Order.cpp******************************************
 * Author: Ronald Macmaster
 * Date: 1/31/2016
 *
 * Order class methods which perform actions on a market book                     
 *********************************************************************************/
 
 #include "Order.h"
 #include "Util.h"
 
 #undef DEBUG
 
<<<<<<< HEAD
/********************************AddOrder()****************************************
 * Purpose: Add an order to the order book
 * Inputs: 
 *   1) order_string: string that has the parameters to build an Order
 *   2) order_book: Database with all the current orders listed by ID  
 *********************************************************************************/
void Order::AddOrder(string &order_string, map<string, Order> &order_book){   
=======
/**** Order book / queue managers ******/ 
map<string, Order> Order::order_book;
priority_queue<string, vector<string>, CompareBuyOrders> Order::buy_queue;
priority_queue<string, vector<string>, CompareSellOrders> Order::sell_queue;
 
/****************************AddOrder()**********************************/
/* Purpose: Add an order to the order book
 * Inputs: 
 *   1) order_string: string that has the parameters to build an Order
 * Notes: Accesses order_book (Database with all the current orders listed by ID) 
/************************************************************************/
void Order::AddOrder(string &order_string){   
>>>>>>> 01ea73be24a7cd057acae8d82f51f4305f917401
   
   int npos;
   string id;
   ordertype action;
   float price;
   int quantity;
   
   // extract order id
   npos = order_string.find(" ");
   id = order_string.substr(0, npos);
   order_string.erase(0, npos+1);
   
   // extract action (Buy/Sell)
   npos = order_string.find(" ");
   switch(order_string[1]){
      case 'B':
         action = buy;
         break;
      case 'S':
         action = sell;
         break;
      default:
         throw invalid_argument("invalid order action!");
   }   
   order_string.erase(0, npos+1);
   
   // extract order price and quantity
   npos = order_string.find(" ");
   price = stof(order_string.substr(0, npos)); 
   order_string.erase(0, npos+1);
   quantity = stoi(order_string); 
   
   // add order to database and queue
   Order::order_book[id] = Order(id, action, price, quantity);
   switch(action){
      case buy:
         Order::buy_queue.push(id);
         break;
      case sell:
         Order::sell_queue.push(id);
         break;
   }
   
   #ifdef DEBUG
   string bs[3] = {"empty", "buy ", "sell"};
   cout << bs[action] << "\tprice: " << price << "\tquantity: " << quantity << endl;
   #endif
   
}

/****************************ReduceOrder()*********************************************
 * Purpose: Reduce an order already in the order book
 * Inputs: 
 *   1) order_string: string that has the parameters to perform the reduce
<<<<<<< HEAD
 *   2) order_book: Database with all the current orders listed by ID  
 *************************************************************************************/
void Order::ReduceOrder(string &order_string, map<string, Order> &order_book){   
=======
 * Notes: Accesses order_book (Database with all the current orders listed by ID)  
/**************************************************************************/
void Order::ReduceOrder(string &order_string){   
>>>>>>> 01ea73be24a7cd057acae8d82f51f4305f917401
   
   int npos;
   int quantity;
   string id;
   
   // extract order id and quantity
   npos = order_string.find(" ");
   id = order_string.substr(0, npos);
   order_string.erase(0, npos+1);
   quantity = stoi(order_string);
   
   // reduce order in database (delete if quantity drops below zero
   if(quantity >= Order::order_book[id].quantity){
   	Order::order_book.erase(id);
   }
   else{
   	Order::order_book[id].quantity -= quantity; //reduce order quantity
   }
   
   #ifdef DEBUG
   cout << "red" << "\tid:\t" << id << "\tquantity: " << quantity << endl;
   #endif
   
}

<<<<<<< HEAD
/****************************CompareOrders()******************************************
 * Purpose: Compare the priority of two Order objects
=======

/****************************CompareBuyOrders()**********************************/
/* Purpose: Compare the priority of two Buy Order objects
>>>>>>> 01ea73be24a7cd057acae8d82f51f4305f917401
				Used for ranking in a priority queue
 * Inputs: 
 *   1) lhs_id: key to 1st object to compare
	  2) rhs_id: key to 2nd object to compare
 * Return:
 		 mismatch) log error and return false
<<<<<<< HEAD
 		 sell orders) lhs.price < rhs.price
 		 buy  orders) lhs.price > rhs.price
 ***********&&************************************************************************/
bool CompareOrders::operator()(string lhs, string rhs){
=======
 		 buy  orders) lhs.price < rhs.price
/******************************************************************************/
bool CompareBuyOrders::operator()(string lhs_id, string rhs_id){
	bool err_lhs = Order::order_book.find(lhs_id) == Order::order_book.end();
	bool err_rhs = Order::order_book.find(rhs_id) == Order::order_book.end();
	if(err_lhs){
		//cerr << lhs_id << " is no longer in the buy list!" << endl;
		return false;
	}
	else if(err_rhs){
		//cerr << rhs_id << " is no longer in the buy list!" << endl;
		return false;
	}
	
	Order lhs = Order::order_book[lhs_id];
	Order rhs = Order::order_book[rhs_id];
	
>>>>>>> 01ea73be24a7cd057acae8d82f51f4305f917401
	if((lhs.type == buy)&&(rhs.type == buy)){ //buy orders
		return lhs.price < rhs.price;
	}
	else{ //mismatch error
		cerr << "compare error: mismatch between order types" << endl;
		return false;
	}
}


/****************************CompareSellOrders()**********************************/
/* Purpose: Compare the priority of two Sell Order objects
				Used for ranking in a priority queue
 * Inputs: 
 *   1) lhs_id: key to 1st object to compare
	  2) rhs_id: key to 2nd object to compare
 * Return:
 		 mismatch) log error and return false
 		 sell orders) lhs.price > rhs.price
/******************************************************************************/
bool CompareSellOrders::operator()(string lhs_id, string rhs_id){
	
	bool err_lhs = Order::order_book.find(lhs_id) == Order::order_book.end();
	bool err_rhs = Order::order_book.find(rhs_id) == Order::order_book.end();
	if(err_lhs){
		//cerr << lhs_id << " is no longer in the buy list!" << endl;
		return false;
	}
	else if(err_rhs){
		//cerr << rhs_id << " is no longer in the buy list!" << endl;
		return false;
	}
	
	Order lhs = Order::order_book[lhs_id];
	Order rhs = Order::order_book[rhs_id];
	
	if((lhs.type == sell)&&(rhs.type == sell)){ //sell orders
		return lhs.price > rhs.price;
	}
	else{ //mismatch error
		cerr << "compare error: mismatch between order types" << endl;
		return false;
	}
}

