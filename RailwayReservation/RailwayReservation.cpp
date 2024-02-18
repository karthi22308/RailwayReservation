
#include <iostream>
#include "ticket.h"

using namespace std;
int main()
{
	int n;
	RRS obj;
	while (true) {
		cin >> n;
		if (n == 1) {
			obj.print();

		}
		else if(n==2){
			int s, e, t;
			cin >> s >> e >> t;
			obj.bookticket(s, e, t);
		}
		else if (n == 3) {
			int pnr, count;
			cin >> pnr >> count;
			obj.cancelticket(pnr, count);
		}
		else if (n == 4) {
			obj.printbookedtickets();
		}
	}
  
   
}
