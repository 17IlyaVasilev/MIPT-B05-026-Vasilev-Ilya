#include <iostream>
#include <string>
#include <vector>

using namespace std;


class BigInteger {
private:
	vector <int> v;
	void swap(BigInteger& s) {
		std::swap(s.v, v);
	}
	void zero_destroy() {
		reverse(v.begin(), v.end());
		while (v.size() > 1 && v.back() == 0)v.pop_back();
		reverse(v.begin(), v.end());
	}

	BigInteger operator^ (const int& b) {
		BigInteger copy;
		if ((b == 0) || (*this == 0)) {
			BigInteger a = 0;
			return a;
		}
		size_t buff = 0;
		for (size_t i = v.size(); i > 0; i--) {
			copy.v.push_back((v[i - 1] * b + buff) % 10);
			buff = (v[i - 1] * b + buff) / 10;
		}
		if (buff != 0) {
			copy.v.push_back(buff % 10);
			if (buff / 10 > 0)
				copy.v.push_back(buff / 10);
		}
		reverse(copy.v.begin(), copy.v.end());
		return copy;
	}
public:
	BigInteger() {}
	friend std::ostream& operator <<(std::ostream& out, const BigInteger& s);
	friend std::istream& operator >>(std::istream& in, BigInteger& s);
	friend bool operator==(const BigInteger&, const BigInteger&);
	friend bool operator!=(const BigInteger&, const BigInteger&);
	friend bool operator<=(const BigInteger&, const BigInteger&);
	friend bool operator>=(const BigInteger&, const BigInteger&);
	friend bool operator<(const BigInteger&, const BigInteger&);
	friend bool operator>(const BigInteger&, const BigInteger&);
	friend bool operator==(const BigInteger&, const int&);
	friend bool operator!=(const BigInteger&, const int&);
	friend bool operator<=(const BigInteger&, const int&);
	friend bool operator>=(const BigInteger&, const int&);
	friend bool operator<(const BigInteger&, const int&);
	friend bool operator>(const BigInteger&, const int&);
	friend bool operator==(const int&, const BigInteger&);
	friend bool operator!=(const int&, const BigInteger&);
	friend bool operator<=(const int&, const BigInteger&);
	friend bool operator>=(const int&, const BigInteger&);
	friend bool operator<(const int&, const BigInteger&);
	friend bool operator>(const int&, const BigInteger&);
	string toString();
	string toString() const;
	BigInteger(int a) {
		if (a == 0)
			v.push_back(0);
		else {
			bool g = false;
			if (a < 0) {
				a *= -1;
				g = true;
			}
			while (a) {
				v.push_back(a % 10);
				a /= 10;
			}
			reverse(v.begin(), v.end());
			if (g)v[0] *= -1;
		}
	}

	BigInteger& operator=(BigInteger a) {
		reverse(a.v.begin(), a.v.end());
		while (a.v.size() > 1 && a.v.back() == 0)a.v.pop_back();
		reverse(a.v.begin(), a.v.end());
		swap(a);
		return *this;
	}

	BigInteger& operator=(int a) {
		BigInteger b(a);
		swap(b);
		return *this;
	}

	BigInteger& operator-=(const BigInteger& a) {
		if (a.v[0] < 0) {
			BigInteger c = a;
			c.v[0] *= -1;
			*this += c;
			return *this;
		}
		else if (v[0] < 0) {
			BigInteger c = a;
			v[0] *= -1;
			c += *this;
			*this = -c;
			return *this;
		}
		else {
			BigInteger res;
			BigInteger c = a;
			BigInteger b = *this;
			reverse(c.v.begin(), c.v.end());
			reverse(b.v.begin(), b.v.end());
			if (c.v.size() > b.v.size()) {
				c.v.push_back(0);
				while (c.v.size() > b.v.size()) {
					b.v.push_back(0);
				}
			}
			else {
				b.v.push_back(0);
				while (c.v.size() < b.v.size()) {
					c.v.push_back(0);
				}
			}
			int d = 0;
			if (*this > a) {
				int e = 0;
				for (size_t i = 0; i < b.v.size(); ++i) {
					if (b.v[i] - d - c.v[i] < 0) {
						b.v[i] += 10 - d;
						d = 1;
						e = b.v[i] - c.v[i];
					}
					else {
						e = b.v[i] - c.v[i] - d;
						d = 0;
					}
					res.v.push_back(e);
				}
				reverse(res.v.begin(), res.v.end());
				*this = res;
			}
			else {
				int e = 0;
				for (size_t i = 0; i < b.v.size(); ++i) {
					if (c.v[i] - d - b.v[i] < 0) {
						c.v[i] += 10 - d;
						d = 1;
						e = c.v[i] - b.v[i];
					}
					else {
						e = c.v[i] - b.v[i] - d;
						d = 0;
					}
					res.v.push_back(e);
				}
				reverse(res.v.begin(), res.v.end());
				*this = -res;
			}
			return *this;
		}
	}

	BigInteger& operator+=(const BigInteger& a) {
		if (a.v[0] < 0) {
			BigInteger c = a;
			c.v[0] *= -1;
			*this -= c;
			return *this;
		}
		else if (v[0] < 0) {
			BigInteger c = a;
			v[0] *= -1;
			c -= *this;
			*this = c;
			return *this;
		}
		else {
			BigInteger res;
			BigInteger c = a;
			BigInteger b = *this;
			reverse(c.v.begin(), c.v.end());
			reverse(b.v.begin(), b.v.end());
			if (c.v.size() > b.v.size()) {
				c.v.push_back(0);
				while (c.v.size() > b.v.size()) {
					b.v.push_back(0);
				}
			}
			else {
				b.v.push_back(0);
				while (c.v.size() < b.v.size()) {
					c.v.push_back(0);
				}
			}
			int d = 0;
			for (size_t i = 0; i < b.v.size(); ++i) {
				int e = b.v[i] + c.v[i] + d;
				res.v.push_back(e % 10);
				d = e / 10;
			}
			reverse(res.v.begin(), res.v.end());
			*this = res;
			return *this;
		}
	}

	BigInteger& operator*=(const BigInteger& b) {
		BigInteger sum = 0;
		size_t g = 1;
		if (v[0] < 0) {
			v[0] *= -1;
			g *= -1;
		}
		if (b.v[0] < 0)g *= -1;
		for (size_t i = b.v.size(); i > 0; i--) {
			BigInteger temp = (*this) ^ abs(b.v[i - 1]);
			sum += temp;
			v.push_back(0);
		}
		sum.v[0] *= g;
		*this = sum;
		return *this;
	}

	BigInteger& operator/=(const BigInteger& a) {
		bool z = true;
		if (v[0] < 0) {
			v[0] = -v[0];
			z = false;
		}
		BigInteger t = a;
		bool y = true;
		if (a.v[0] < 0) {
			t.v[0] = -t.v[0];
			y = false;
		}
		BigInteger copy;
		BigInteger b = 0;
		vector<int> result;
		if (t > * this) {
			*this = 0;
			return *this;
		}
		else {
			for (size_t i = 0; i < t.v.size(); ++i)
				copy.v.push_back(v[i]);
			int j = 0;
			for (j = 0; j < 10; ++j) {
				if (copy < b) {
					if (!(j == 1 && result.size() == 0))
						result.push_back(j - 1);
					for (int l = 0; l < j - 1; ++l) {
						copy -= t;
					}
					break;
				}
				b += t;
			}
			if (j == 10) {
				result.push_back(j - 1);
				for (int l = 0; l < j - 1; ++l) {
					copy -= t;
				}
			}
			for (size_t i = t.v.size(); i < v.size(); ++i) {
				copy.v.push_back(0);
				copy += v[i];
				int j = 0;
				b = 0;
				for (j = 0; j < 10; ++j) {
					if (copy < b) {
						if (!(j == 1 && result.size() == 0))
							result.push_back(j - 1);
						for (int l = 0; l < j - 1; ++l) {
							copy -= t;
						}
						break;
					}
					b += t;
				}
				if (j == 10) {
					result.push_back(j - 1);
					for (int l = 0; l < j - 1; ++l) {
						copy -= t;
					}
				}
			}
			v.clear();
			v = result;
			if ((!y && z) || (!z && y)) return -*this;
			return *this;
		}
	}

	BigInteger& operator%=(const BigInteger& a) {
		BigInteger temp = *this;
		temp /= a;
		temp *= a;
		*this -= temp;
		return *this;
	}

	BigInteger& operator+=(const int& b) {
		BigInteger b1 = BigInteger(b);
		*this += b1;
		return *this;
	}

	BigInteger& operator-=(const int& b) {
		BigInteger b1 = BigInteger(b);
		*this -= b1;
		return *this;
	}

	BigInteger& operator*=(const int& b) {
		BigInteger b1 = BigInteger(b);
		*this *= b1;
		return *this;
	}

	BigInteger& operator/=(const int& b) {
		BigInteger b1 = BigInteger(b);
		*this /= b1;
		return *this;
	}

	BigInteger& operator%=(const int& b) {
		BigInteger b1 = BigInteger(b);
		*this %= b1;
		return *this;
	}

	BigInteger& operator-() {
		zero_destroy();
		v[0] *= -1;
		return *this;
	}

	operator bool() {
		if (v.size() == 0)return 0;
		return v[0];
	}

	BigInteger& operator++() {
		*this += BigInteger(1);
		return *this;
	}

	BigInteger operator++(int) {
		BigInteger copy = *this;
		++(*this);
		return copy;
	}

	BigInteger& operator--() {
		*this -= BigInteger(1);
		return *this;
	}

	BigInteger operator--(int) {
		BigInteger copy = *this;
		--(*this);
		return copy;
	}
};

BigInteger operator ""_bi(unsigned long long a) {
	return BigInteger(a);
}

string BigInteger::toString() {
	string s = "";
	for (size_t i = 0; i < (*this).v.size(); i++) {
		if ((*this).v[i] < 0) {
			s += '-';
			s += char(48 - (*this).v[i]);
		}
		else s += char(48 + (*this).v[i]);
	}
	return s;
}

string BigInteger::toString() const {
	string s = "";
	for (size_t i = 0; i < (*this).v.size(); i++) {
		if ((*this).v[i] < 0) {
			s += '-';
			s += char(48 - (*this).v[i]);
		}
		else s += char(48 + (*this).v[i]);
	}
	return s;
}

std::ostream& operator <<(std::ostream& out, const BigInteger& s) {
	for (auto i : s.v) {
		out << i;
	}
	return out;
}

std::istream& operator >> (std::istream& in, BigInteger& s) {
	char c;
	bool less = false;
	s = 0;
	do {
		c = in.get();
	} while (isspace(c));
	while (!in.eof() && !isspace(c)) {
		if (c != '-') {
			if (s)s *= 10;
			s += BigInteger(int(c) - 48);
		}
		else less = true;
		c = in.get();
	}
	if (less)s.v[0] *= -1;
	return in;
}

bool operator==(const BigInteger& a, const BigInteger& b) {
	if (a.v.size() != b.v.size())return false;
	for (size_t i = 0; i < a.v.size(); i++)if (a.v[i] != b.v[i])return false;
	return true;
}

bool operator!=(const BigInteger& a, const BigInteger& b) {
	return !(a == b);
}

bool operator<=(const BigInteger& a, const BigInteger& b) {
	if (a.v[0] <= 0 && b.v[0] >= 0)return true;
	if (a.v[0] >= 0 && b.v[0] <= 0)return false;
	bool f = false;
	if (a.v[0] <= 0 && b.v[0] <= 0)f = true;
	if (a.v.size() < b.v.size()) {
		if (!f)return true;
		return false;
	}
	if (a.v.size() > b.v.size()) {
		if (!f)return false;
		return true;
	}
	for (size_t i = 0; i < a.v.size(); i++) {
		if (a.v[i] < b.v[i]) {
			if (!f)return true;
			return false;
		}
		if (a.v[i] > b.v[i]) {
			if (!f)return false;
			return true;
		}
	}
	return true;
}

bool operator>=(const BigInteger& a, const BigInteger& b) {
	if (a.v[0] <= 0 && b.v[0] >= 0)return false;
	if (a.v[0] >= 0 && b.v[0] <= 0)return true;
	bool f = false;
	if (a.v[0] <= 0 && b.v[0] <= 0)f = true;
	if (a.v.size() < b.v.size()) {
		if (f)return true;
		return false;
	}
	if (a.v.size() > b.v.size()) {
		if (f)return false;
		return true;
	}
	for (size_t i = 0; i < a.v.size(); i++) {
		if (a.v[i] < b.v[i]) {
			if (f)return true;
			return false;
		}
		if (a.v[i] > b.v[i]) {
			if (f)return false;
			return true;
		}
	}
	return true;
}

bool operator<(const BigInteger& a, const BigInteger& b) {
	return (a <= b && a != b);
}

bool operator>(const BigInteger& a, const BigInteger& b) {
	return (a >= b && a != b);
}

bool operator==(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	if (a.v.size() != b1.v.size())return false;
	for (size_t i = 0; i < a.v.size(); i++)if (a.v[i] != b1.v[i])return false;
	return true;
}

bool operator!=(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	return !(a == b1);
}

bool operator<=(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	if (a.v.size() < b1.v.size())return true;
	if (a.v.size() > b1.v.size())return false;
	for (size_t i = 0; i < a.v.size(); i++) {
		if (a.v[i] < b1.v[i])return true;
		if (a.v[i] > b1.v[i])return false;
	}
	return true;
}

bool operator>=(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	if (a.v.size() > b1.v.size())return true;
	if (a.v.size() < b1.v.size())return false;
	for (size_t i = 0; i < a.v.size(); i++) {
		if (a.v[i] > b1.v[i])return true;
		if (a.v[i] < b1.v[i])return false;
	}
	return true;
}

bool operator<(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	return (a <= b1 && a != b1);
}

bool operator>(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	return (a >= b1 && a != b1);
}

bool operator==(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	if (a1.v.size() != b.v.size())return false;
	for (size_t i = 0; i < a1.v.size(); i++)if (a1.v[i] != b.v[i])return false;
	return true;
}

bool operator!=(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	return !(a1 == b);
}

bool operator<=(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	if (a1.v.size() < b.v.size())return true;
	if (a1.v.size() > b.v.size())return false;
	for (size_t i = 0; i < a1.v.size(); i++) {
		if (a1.v[i] < b.v[i])return true;
		if (a1.v[i] > b.v[i])return false;
	}
	return true;
}

bool operator>=(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	if (a1.v.size() > b.v.size())return true;
	if (a1.v.size() < b.v.size())return false;
	for (size_t i = 0; i < a1.v.size(); i++) {
		if (a1.v[i] > b.v[i])return true;
		if (a1.v[i] < b.v[i])return false;
	}
	return true;
}

bool operator<(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	return (a1 <= b && a1 != b);
}

bool operator>(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	return (a1 >= b && a1 != b);
}

BigInteger operator+(const BigInteger& a, const BigInteger& b) {
	BigInteger copy = a;
	copy += b;
	return copy;
}

BigInteger operator-(const BigInteger& a, const BigInteger& b) {
	BigInteger copy = a;
	copy -= b;
	return copy;
}

BigInteger operator*(const BigInteger& a, const BigInteger& b) {
	BigInteger copy = a;
	copy *= b;
	return copy;
}

BigInteger operator/(const BigInteger& a, const BigInteger& b) {
	BigInteger copy = a;
	copy /= b;
	return copy;
}

BigInteger operator%(const BigInteger& a, const BigInteger& b) {
	BigInteger copy = a;
	copy %= b;
	return copy;
}

BigInteger operator+(const int& a, const BigInteger& b) {
	BigInteger copy = BigInteger(a);
	copy += b;
	return copy;
}

BigInteger operator-(const int& a, const BigInteger& b) {
	BigInteger copy = BigInteger(a);
	copy -= b;
	return copy;
}

BigInteger operator*(const int& a, const BigInteger& b) {
	BigInteger copy = BigInteger(a);
	copy *= b;
	return copy;
}

BigInteger operator/(const int& a, const BigInteger& b) {
	BigInteger copy = BigInteger(a);
	copy /= b;
	return copy;
}

BigInteger operator%(const int& a, const BigInteger& b) {
	BigInteger copy = BigInteger(a);
	copy %= b;
	return copy;
}

BigInteger operator+(const BigInteger& a, const int& b) {
	BigInteger copy = BigInteger(b);
	copy += a;
	return copy;
}

BigInteger operator-(const BigInteger& a, const int& b) {
	BigInteger copy = a;
	copy -= BigInteger(b);
	return copy;
}

BigInteger operator*(const BigInteger& a, const int& b) {
	BigInteger copy = BigInteger(b);
	copy *= a;
	return copy;
}

BigInteger operator/(const BigInteger& a, const int& b) {
	BigInteger copy = a;
	copy /= BigInteger(b);
	return copy;
}

BigInteger operator%(const BigInteger& a, const int& b) {
	BigInteger copy = a;
	copy %= BigInteger(b);
	return copy;
}

BigInteger nod(BigInteger a, BigInteger b) {
	if (a < 0) {
		a *= -1;
	}
	if (b < 0) {
		b *= -1;
	}
	while (a && b) {
		if (a > b)a %= b;
		else b %= a;
	}
	a += b;
	return a;
}

class Rational {
private:
	BigInteger up = 0;
	BigInteger down = 1;

public:

	Rational();
	~Rational();
	Rational(const BigInteger& a) {
		up = a;
		down = 1;
	}
	Rational(const int& a) {
		up = a;
		down = 1;
	}

	Rational& operator=(const Rational a) {
		up = a.up;
		down = a.down;
		return *this;
	}
	Rational& operator=(const BigInteger a) {
		up = a;
		down = 1;
		return *this;
	}
	Rational& operator=(const int a) {
		up = a;
		down = 1;
		return *this;
	}

	Rational& operator+=(const Rational& a) {
		up = up * a.down + down * a.up;
		down = down * a.down;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}
	Rational& operator+=(const BigInteger& a) {
		up = up + down * a;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}
	Rational& operator+=(const int& a) {
		up = up + down * a;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}

	Rational& operator-=(const Rational& a) {
		up = up * a.down - down * a.up;
		down = down * a.down;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}
	Rational& operator-=(const BigInteger& a) {
		up = up - down * a;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}
	Rational& operator-=(const int& a) {
		up = up - down * a;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}

	Rational& operator*=(const Rational& a) {
		up = up * a.up;
		down = down * a.down;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}
	Rational& operator*=(const BigInteger& a) {
		up = up * a;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}
	Rational& operator*=(const int& a) {
		up = up * a;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}

	Rational& operator/=(const Rational& a) {
		up = up * a.down;
		down = down * a.up;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}
	Rational& operator/=(const BigInteger& a) {
		down = down * a;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}
	Rational& operator/=(const int& a) {
		down = down * a;
		BigInteger Nod = nod(down, up);
		up = up / Nod;
		down = down / Nod;
		if (down < 0) {
			up *= -1;
			down *= -1;
		}
		return *this;
	}

	friend bool operator==(const Rational&, const Rational&);
	friend bool operator==(const Rational&, const BigInteger&);
	friend bool operator==(const Rational&, const int&);
	friend bool operator==(const BigInteger&, const Rational&);
	friend bool operator==(const int&, const Rational&);

	friend bool operator!=(const Rational&, const Rational&);
	friend bool operator!=(const Rational&, const BigInteger&);
	friend bool operator!=(const Rational&, const int&);
	friend bool operator!=(const BigInteger&, const Rational&);
	friend bool operator!=(const int&, const Rational&);

	friend bool operator>(const Rational&, const Rational&);
	friend bool operator>(const Rational&, const BigInteger&);
	friend bool operator>(const Rational&, const int&);
	friend bool operator>(const BigInteger&, const Rational&);
	friend bool operator>(const int&, const Rational&);

	friend bool operator<(const Rational&, const Rational&);
	friend bool operator<(const Rational&, const BigInteger&);
	friend bool operator<(const Rational&, const int&);
	friend bool operator<(const BigInteger&, const Rational&);
	friend bool operator<(const int&, const Rational&);

	friend bool operator>=(const Rational&, const Rational&);
	friend bool operator>=(const Rational&, const BigInteger&);
	friend bool operator>=(const Rational&, const int&);
	friend bool operator>=(const BigInteger&, const Rational&);
	friend bool operator>=(const int&, const Rational&);

	friend bool operator<=(const Rational&, const Rational&);
	friend bool operator<=(const Rational&, const BigInteger&);
	friend bool operator<=(const Rational&, const int&);
	friend bool operator<=(const BigInteger&, const Rational&);
	friend bool operator<=(const int&, const Rational&);

	friend Rational operator/(const BigInteger&, const Rational&);
	friend Rational operator/(const int&, const Rational&);



	string toString() {
		string copy;
		BigInteger x = up;
		if (x < 0) {
			copy += "-";
			x *= -1;
		}
		if (x == 0) {
			copy += "0";
			return copy;
		}
		else {
			string str = x.toString();
			copy += str;
			if (down == 1) {
				return copy;
			}
			else {
				BigInteger x = down;
				copy += "/";
				string str = x.toString();
				copy += str;
				return copy;
			}
		}
	}


	string asDecimal(size_t precision = 0) {
		BigInteger a = up / down;
		BigInteger b = up % down;
		BigInteger c = down;
		string copy;
		if (up < 0) copy = "-"; else copy = "";
		string ccopy = a.toString();
		if (up < 0) copy = "-"; else copy = "";
		copy += ccopy;
		if (precision == 0) {
			return copy;
		}
		else {
			precision++;
			copy += ".";
			for (size_t i = 0; i < precision; ++i) {
				a = b * 10;
				b = a % c;
				a /= c;
				if (a < 0) a *= -1;
				if (a == 0) copy += "0"; else
					if (a == 1) copy += "1"; else
						if (a == 2) copy += "2"; else
							if (a == 3) copy += "3"; else
								if (a == 4) copy += "4"; else
									if (a == 5) copy += "5"; else
										if (a == 6) copy += "6"; else
											if (a == 7) copy += "7"; else
												if (a == 8) copy += "8"; else
													if (a == 9) copy += "9";
			}
			if (int(copy.back()) - 48 >= 5) {
				copy.pop_back();
				int i = copy.size() - 1;
				while (true) {
					if (copy[i] != '9') {
						copy[i] = char(int(copy[i]) + 1);
						break;
					}
					copy[i] = '0';
					i--;
					if (copy[i] == '.')break;
				}
				if (copy[i] == '.')copy = (up / down + 1).toString();
				return copy;
			}
			else {
				copy.pop_back();
				return copy;
			}
		}
	}

	Rational& operator-() {
		up *= -1;
		return *this;
	}

	explicit operator double() {
		string copy = asDecimal(310);
		size_t nach = copy.find(".");
		double k = 1, sum = 0;
		for (int i = nach - 1; i >= 0; i--) {
			char c = copy[i];
			double x = int(c) - 48;
			sum = sum + x * k;
			k = k * 10;
		}
		k = 0.1;
		for (size_t i = nach + 1; i <= 307; i++) {
			char c = copy[i];
			double x = int(c) - 48;
			sum = sum + x * k;
			k = k / 10;
		}
		return sum;
	}

};


Rational::Rational() {
	up = 0;
	down = 1;
}

Rational::~Rational() {

}

Rational operator+(const Rational& a, const Rational& b) {
	Rational copy = a;
	copy += b;
	return copy;
}
Rational operator+(const Rational& a, const BigInteger& b) {
	Rational copy = a;
	copy += b;
	return copy;
}
Rational operator+(const Rational& a, const int& b) {
	Rational copy = a;
	copy += b;
	return copy;
}

Rational operator+(const BigInteger& b, const Rational& a) {
	Rational copy = a;
	copy += b;
	return copy;
}

Rational operator+(const int& b, const Rational& a) {
	Rational copy = a;
	copy += b;
	return copy;
}

Rational operator-(const Rational& a, const Rational& b) {
	Rational copy = a;
	copy -= b;
	return copy;
}

Rational operator-(const Rational& a, const BigInteger& b) {
	Rational copy = a;
	copy -= b;
	return copy;
}

Rational operator-(const Rational& a, const int& b) {
	Rational copy = a;
	copy -= b;
	return copy;
}

Rational operator-(const BigInteger& b, const Rational& a) {
	Rational copy = a;
	copy *= -1;
	copy += b;
	return copy;
}
Rational operator-(const int& b, const Rational& a) {
	Rational copy = a;
	copy *= -1;
	copy += b;
	return copy;
}

Rational operator*(const Rational& a, const Rational& b) {
	Rational copy = a;
	copy *= b;
	return copy;
}
Rational operator*(const Rational& a, const BigInteger& b) {
	Rational copy = a;
	copy *= b;
	return copy;
}

Rational operator*(const Rational& a, const int& b) {
	Rational copy = a;
	copy *= b;
	return copy;
}

Rational operator*(const BigInteger& b, const Rational& a) {
	Rational copy = a;
	copy *= b;
	return copy;
}

Rational operator*(const int& b, const Rational& a) {
	Rational copy = a;
	copy *= b;
	return copy;
}

Rational operator/(const Rational& a, const Rational& b) {
	Rational copy = a;
	copy /= b;
	return copy;
}
Rational operator/(const Rational& a, const BigInteger& b) {
	Rational copy = a;
	copy /= b;
	return copy;
}
Rational operator/(const Rational& a, const int& b) {
	Rational copy = a;
	copy /= b;
	return copy;
}
Rational operator/(const BigInteger& b, const Rational& a) {
	Rational copy;
	copy.up = a.down;
	copy.down = a.up;
	copy *= b;
	BigInteger Nod = nod(copy.down, copy.up);
	copy.up /= Nod;
	copy.down /= Nod;
	return copy;
}

Rational operator/(const int& b, const Rational& a) {
	Rational copy;
	copy.up = a.down;
	copy.down = a.up;
	copy *= b;
	BigInteger Nod = nod(copy.down, copy.up);
	copy.up /= Nod;
	copy.down /= Nod;
	return copy;
}

bool operator==(const Rational& a, const Rational& b) {
	return (a.up == b.up && a.down == b.down);
}
bool operator==(const Rational& a, const BigInteger& b) {
	return (a.up == b && a.down == 1);
}
bool operator==(const Rational& a, const int& b) {
	return (a.up == b && a.down == 1);
}
bool operator==(const BigInteger& b, const Rational& a) {
	return (a.up == b && a.down == 1);
}
bool operator==(const int& b, const Rational& a) {
	return (a.up == b && a.down == 1);
}

bool operator!=(const Rational& a, const Rational& b) {
	return !(a.up == b.up && a.down == b.down);
}
bool operator!=(const Rational& a, const BigInteger& b) {
	return !(a.up == b && a.down == 1);
}
bool operator!=(const Rational& a, const int& b) {
	return !(a.up == b && a.down == 1);
}
bool operator!=(const BigInteger& b, const Rational& a) {
	return !(a.up == b && a.down == 1);
}
bool operator!=(const int& b, const Rational& a) {
	return !(a.up == b && a.down == 1);
}

bool operator>(const Rational& a, const Rational& b) {
	return (a.up * b.down > a.down * b.up);
}
bool operator>(const Rational& a, const BigInteger& b) {
	return (a.up > a.down * b);
}

bool operator>(const Rational& a, const int& b) {
	return (a.up > a.down * b);
}

bool operator>(const BigInteger& b, const Rational& a) {
	return (a.up < a.down* b);
}

bool operator>(const int& b, const Rational& a) {
	return (a.up < a.down* b);
}

bool operator<(const Rational& a, const Rational& b) {
	return (a.up * b.down < a.down* b.up);
}
bool operator<(const Rational& a, const BigInteger& b) {
	return (a.up < a.down* b);
}
bool operator<(const Rational& a, const int& b) {
	return (a.up < a.down* b);
}
bool operator<(const BigInteger& b, const Rational& a) {
	return (a.up > a.down * b);
}
bool operator<(const int& b, const Rational& a) {
	return (a.up > a.down * b);
}

bool operator>=(const Rational& a, const Rational& b) {
	return (a.up * b.down >= a.down * b.up);
}
bool operator>=(const Rational& a, const BigInteger& b) {
	return (a.up >= a.down * b);
}
bool operator>=(const Rational& a, const int& b) {
	return (a.up >= a.down * b);
}
bool operator>=(const BigInteger& b, const Rational& a) {
	return (a.up <= a.down * b);
}
bool operator>=(const int& b, const Rational& a) {
	return (a.up <= a.down * b);
}

bool operator<=(const Rational& a, const Rational& b) {
	return (a.up * b.down <= a.down * b.up);
}
bool operator<=(const Rational& a, const BigInteger& b) {
	return (a.up <= a.down * b);
}
bool operator<=(const Rational& a, const int& b) {
	return (a.up <= a.down * b);
}
bool operator<=(const BigInteger& b, const Rational& a) {
	return (a.up >= a.down * b);
}

bool operator<=(const int& b, const Rational& a) {
	return (a.up >= a.down * b);
}