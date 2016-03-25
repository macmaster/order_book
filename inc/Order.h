/*******************************Order.h******************************************/
/* Author: Ronald Macmaster
 * Date: 1/31/2016
 *
 * Order class which represents market book orders                              */
 
#include <iostream>
#include <stdexcept>

#include <map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

enum ordertype {null, buy, sell};

// functors for comparing orders
struct CompareBuyOrders{
	bool operator()(string lhs_id, string rhs_id);
};
struct CompareSellOrders{
	bool operator()(string lhs_id, string rhs_id);
};


class Order{
  
 public:
   string id;
   float price;
   int quantity;
   ordertype type;
   
   static map<string, Order> order_book;
   static priority_queue<string, vector<string>, CompareBuyOrders> buy_queue;
	static priority_queue<string, vector<string>, CompareSellOrders> sell_queue;
      
   // Order constructor. default order values are invalid
   Order(string order_id = "", ordertype order_type = null, 
         float order_price = -1, int order_quantity = -1){
          
      id = order_id;
      type = order_type;
      price = order_price;
      quantity = order_quantity;
      
   }
   
   // Copy Constructor
   Order(const Order &copy){
      id = copy.id;
      price = copy.price;
      quantity = copy.quantity;
      type = copy.type;
   }
   
   static void AddOrder(string &order_string);
   static void ReduceOrder(string &order_string);
   
};

