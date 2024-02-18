#include<iostream>
//#include <map>
#include<vector>
#include<string>
using namespace std;

class ticket {
public:
	int start;
	int end;
	int seats;
	vector<int> rows;
	int confirmed;
	int rac;
	ticket(int s, int e, int t, vector<int> row,int seats,int rac) {
		start = s;
		end = e;
		seats = t;
		rows = row;
		confirmed = seats;
		rac = rac;
	}

};
class RRS {
public:
	int reserved[10][10] = { 0 };
	int rac[5][20] = { 0 };
	vector< ticket> tickets;

	int lastpnr;

	RRS() {
		lastpnr = 0;
	}
	void print() {
		cout << "reservation chart:"<<endl;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << reserved[i][j];
			}
			cout << endl;
		}
		cout << "rac chart:" << endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				cout << rac[i][j];
			}
			cout << endl;
		}
		cout << endl;
		
	}

	bool isticketavailable(int start, int end, int seats) {
		int out = false;
		int avseats = 0;

		for (int i = 0; i < 10; i++) {
			int seatflag = 0;
			int s = start;
			int e = end;
			while (s < e) {
				if (reserved[i][s] == 0)seatflag++;
				s++;
			}
			if (seatflag == end - start )avseats++;

		}
		if (avseats >= seats) {
			out = true;
		}
		return out;
	}
	void bookticket(int start, int end, int seats) {
		if (isticketavailable(start, end, seats)) {
			int booked = 0;
			vector<int> rows;
			for (int i = 0; i < 10; i++) {
			
				int seatflag = 0;
				int s = start;
				int e = end;
				while (s < e) {
					if (reserved[i][s] == 0)seatflag++;
					s++;
				}
				if (seatflag == end - start and booked <seats) {
					s = start;
					e = end;
					while (s <= e) {
						reserved[i][s] = 1;
						s++;
					}
					rows.push_back(i);
					booked++;
				}

			}
			lastpnr += 1;
			ticket obj(start, end, seats,rows,seats, 0);
			cout << "ticket booked with pnr:" << lastpnr << endl;
			tickets.push_back(obj);
		}
		else {
			cout << "seats not available"<<endl;
		}
	}
	void printbookedtickets() {
		int pnr = 1;

		for (ticket t : tickets) {
			cout << "pnr no:" << pnr << " source :" << t.start << " end: " << t.end << "no of seats :" << t.seats << "confirmed tickets:" << t.confirmed << "RAC:" << t.rac << endl;;
			pnr++;
		}
	

	}
	void cancelticket(int pnr, int seats) {
		if (pnr <=lastpnr) {
			ticket tc = tickets[pnr - 1];
			if (seats <= tc.rows.size()) {
				int cancelled = 0;
				while (cancelled < seats) {
					int i = tc.rows[cancelled];
					int s = tc.start;
					int e = tc.end;
					while (s <= e) {
						reserved[i][s] = 0;
						s++;
					}
					tc.rows[cancelled] = -1;
					cancelled++;
					
					//tc.rows.erase(tc.rows.begin() + cancelled);
				}
				vector<int> r;
				for (int i : tc.rows) {
					if (i != -1) {
						r.push_back(i);
					}
				}
				tc.rows = r;
				tc.seats = tc.seats - seats;
				tickets[pnr - 1] = tc;
			}
			else {
				cout << "seats are more then reserved"<<endl;
			}

		}
		else {
			cout << "invalid pnr"<<endl;
		}
	}

};