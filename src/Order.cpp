/*******************************Order.cpp******************************************/
/* Author: Ronald Macmaster
 * Date: 1/31/2016
 *
 * Order class methods which perform actions on a market book  				    */
 
 #include "Order.h"
 #include "Util.h"
 
 #undef DEBUG
/****************************AddOrder()**********************************/
/* Purpose: Add an order to the order book
 * Inputs: 
 *		1) order_string: string that has the parameters to build an Order
 *		2) order_book: Database with all the current orders listed by ID  
/************************************************************************/
void Order::AddOrder(string &order_string, map<string, Order> &order_book){	
	
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
	
	// add order to database
	order_book[id] = Order(id, action, price, quantity);
	
	#ifdef DEBUG
	string bs[3] = {"empty", "buy ", "sell"};
	cout << bs[action] << "\tprice: " << price << "\tquantity: " << quantity << endl;
	#endif
	
}

/****************************ReduceOrder()**********************************/
/* Purpose: Reduce an order already in the order book
 * Inputs: 
 *		1) order_string: string that has the parameters to perform the reduce
 *		2) order_book: Database with all the current orders listed by ID  
/**************************************************************************/
void Order::ReduceOrder(string &order_string, map<string, Order> &order_book){	
	
	int npos;
	int quantity;
	string id;
	
	// extract order id and quantity
	npos = order_string.find(" ");
	id = order_string.substr(0, npos);
	order_string.erase(0, npos+1);
	quantity = stoi(order_string);
	
	#ifdef DEBUG
	cout << "red" << "\tid:\t" << id << "\tquantity: " << quantity << endl;
	#endif
	
}
