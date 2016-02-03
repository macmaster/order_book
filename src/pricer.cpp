/****************************Order Book Pricer**********************************/
/* Author: Ronald Macmaster
 * Date: 1/31/2016
 * Last Modified: 2/1/2016
 *
 * Purpose: Analyzes an order book log file. 
   Reads a market data log on standard input. 
   As the book is modified, 
   Pricer prints (on standard output) the total expense you would incur 
      if you bought target-size shares 
         (by taking as many asks as necessary, lowest first), 
      and the total income you would receive if you sold target-size shares 
         (by hitting as many bids as necessary, highest first). 
   Each time the income or expense changes, it prints the changed value.
 *
 * Inputs: target-size (command_line argument) 
 *                                                                             */
 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

#include <map>
#include "Order.h"

#define DEBUG
 
using namespace std;

void stopwatch();

int main(int argc, char *args[]){
    
   int target_size = 1;
   string order_string;
   map<string, Order> order_book;
   Order_queue buy_queue;
   Order_queue sell_queue;
   
   // Parse int from target_size
   try{ 
      target_size = atoi(args[1]);
      if(target_size <= 0){
         throw invalid_argument("target size less than 1!");
      }
      clog << "Target Size: " << target_size << endl; 
   }
   catch(const invalid_argument &ia){
      cerr << "Error: Invalid Target Size " << 
         "(Enter an integer greater than 0!)" << endl;
   }
   
   // Analyze Market Log
   while(getline(cin, order_string)){

      int npos;
      string time_stamp;
      char command;
      
      try{
         
         // extract time_stamp
         npos = order_string.find(" ");
         time_stamp = order_string.substr(0, npos);
         order_string.erase(0, npos+1);
         
         // extract command (Add/Reduce)
         npos = order_string.find(" ");
         command = order_string.at(1);
         order_string.erase(0, npos+1);
                  
         switch(command){
            case 'A':
               Order::AddOrder(order_string, order_book);
               break;
            case 'R':
               Order::ReduceOrder(order_string, order_book);
               break;
            default:
               throw invalid_argument("invalid order command!");
         }
         
      }
      catch(const invalid_argument &ia){
         cerr << ia.what() << endl;
      }
      catch(...){
         if(!time_stamp.compare("\n")){ // single newline = success
            cerr << "Error: Invalid order at time: " << time_stamp << endl;
         }
         else{
            clog << "scan finished!" << endl;
            // exit(0);
         }
      }
   }
      
   #ifdef DEBUG
   //print order database
   string bs[3] = {"empty", "buy ", "sell"};
   for(map<string, Order>::iterator itr = order_book.begin(); itr != order_book.end(); itr++){
      Order obj = itr->second;
      cout << "id: " << obj.id << "   \t" <<  bs[obj.type];
      cout << "\tprice: " << obj.price << "\tquantity: " << obj.quantity << endl;
   }
   clog << "obj log finished!" << endl;
   #endif
   
}

#ifdef DEBUG
/****************************stopwatch()****************************************/
/* Purpose: Toggle a stopwatch
 * 1) call it to start the stopwatch
 * 2) call it to stop the stopwatch and print the results
/******************************************************************************/
void stopwatch(){
   static int flag = 1;
   static clock_t timer;
   if(flag){
      timer = clock();
   }
   else{
      cout << " Time delay: " <<  clock()-timer << endl;
   }
   flag ^= 1;
}
#endif

