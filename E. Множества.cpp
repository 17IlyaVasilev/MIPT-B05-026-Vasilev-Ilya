#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Struct_of_set {

public:

	Struct_of_set();
	~Struct_of_set();
	void Add(long long, long long);
	void Delete(long long, long long);
	void Clear(long long);
	void Listset(long long);
	void Listsetsof(long long);

private:

	vector < set<long long>> v;
	map <long long, set<long long>> g;

};

Struct_of_set::Struct_of_set() {

	v.resize(100001);

}

Struct_of_set::~Struct_of_set() {

	v.clear();
	g.clear();

}

void Struct_of_set::Add(long long e, long long s) {

	v[s].insert(e);
	g[e].insert(s);

}

void Struct_of_set::Delete(long long e, long long s) {

	v[s].erase(e);
	g[e].erase(s);

}

void Struct_of_set::Clear(long long s) {

	for (auto i : v[s])g[i].erase(s);
	v[s].clear();

}

void Struct_of_set::Listset(long long s) {

	if (v[s].size() > 0) {

		for (auto i : v[s]) {

			cout << i << ' ';

		}

	}
	else
	{

		cout << -1;

	}

	cout << endl;

}

void Struct_of_set::Listsetsof(long long e) {

	if (g[e].size() > 0) {

		for (auto i : g[e]) {

			cout << i << ' ';

		}

	}
	else
	{

		cout << -1;

	}

	cout << endl;

}

int main() {

	Struct_of_set st;
	string t;
	long long n, m, k, e, s;

	cin >> n >> m >> k;

	for (long long j = 0; j < k; ++j) {

		cin >> t;

		if (t == "ADD") {

			cin >> e >> s;
			st.Add(e, s);

		}
		else if (t == "DELETE") {

			cin >> e >> s;
			st.Delete(e, s);

		}
		else if (t == "CLEAR") {

			cin >> s;
			st.Clear(s);

		}
		else if (t == "LISTSET") {

			cin >> s;
			st.Listset(s);

		}
		else if (t == "LISTSETSOF") {

			cin >> e;
			st.Listsetsof(e);

		}

	}

	return 0;

}