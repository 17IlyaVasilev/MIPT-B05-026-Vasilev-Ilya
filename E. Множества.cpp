#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Struct_of_set {

public:

	Struct_of_set(int);
	~Struct_of_set();
	void Add(long long, long long);
	void Delete(long long, long long);
	void Clear(long long);
	set<long long> Listset(long long);
	set<long long> Listsetsof(long long);

private:

	vector < set<long long>> v;
	map <long long, set<long long>> g;

};

Struct_of_set::Struct_of_set(int m) {

	v.resize(m);

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

set<long long> Struct_of_set::Listset(long long s) {
	set<long long> a;
	if (v[s].size() > 0) {

		for (auto i : v[s]) {

			a.insert(i);

		}

	}
	else
	{

		a.insert(-1);

	}

	return a;

}

set<long long> Struct_of_set::Listsetsof(long long s) {

	set<long long> a;
	if (g[s].size() > 0) {

		for (auto i : g[s]) {

			a.insert(i);

		}

	}
	else
	{

		a.insert(-1);

	}

	return a;

}

int main() {

	string t;
	long long n, m, k, e, s;

	cin >> n >> m >> k;

	Struct_of_set st(m+1);

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
			set<long long> b = st.Listset(s);
			for (auto i : b) {

				cout << i << ' ';

			}
			cout << endl;

		}
		else if (t == "LISTSETSOF") {

			cin >> s;
			set<long long> b = st.Listsetsof(s);
			for (auto i : b) {

				cout << i << ' ';

			}
			cout << endl;

		}

	}

	return 0;

}
