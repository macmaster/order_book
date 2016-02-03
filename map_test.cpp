#include <map>
#include <iostream>

using namespace std;
int main(){
	map<string, string> mymap;
	
	mymap["get out"] = "ho ho ho";
	
	if(mymap["get out!"])
	cout << "hello world"  << endl;
}
