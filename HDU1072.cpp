#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		string method, str;
		deque<int> que;
		int num;
		cin >> n >> method;
		for (int i = 0; i < n; i++) {
			cin >> str;
			if (str == "IN") {
				cin >> num;
				que.push_back(num);
			}
			else {
				if (que.size()) {
					if (method == "FIFO") {
						cout << que.front() << endl;
						que.pop_front();
					}
					else {
						cout << que.back() << endl;
						que.pop_back();
					}
				}
				else {
					cout << "None" << endl;
				}
			}
		}
	}
	return 0;
}