#include <iostream>
#include <cstring>

class String {
public:
    String() = default;
    ~String();
    String(const char* c) {
        memcpy(str, c, strlen(c));
        sz = strlen(c);
        if (buf_sz <= sz) {
            buf_sz = sz;
            growbuffer();
        }
    }

    String(size_t ssz, const char c = '\0') : sz(ssz), str(new char[ssz]) {
        memset(str, c, sz);
        if (buf_sz <= sz) {
            buf_sz = sz;
            growbuffer();
        }
    }

    String(const String& s) : String(s.sz) {
        memcpy(str, s.str, sz);
        if (buf_sz <= sz) {
            buf_sz = sz;
            growbuffer();
        }
    }

    String(char c) : sz(1), str(new char[1]) {
        memset(str, c, 1);
    }

    String& operator=(String s) {
        swap(s);
        return *this;
    }

    String& operator=(char x) {
        String s(1, x);
        swap(s);
        return *this;
    }

    char& operator[](size_t x) {
        return str[x];
    }

    char operator[](size_t x) const {
        return str[x];
    }

    String& operator+=(const String& s) {
        for (size_t i = 0; i < s.sz; ++i) {
            this->push_back(s[i]);
        }
        return *this;
    }

    String& operator+=(const char& c) {
        this->push_back(c);
        return *this;
    }

    friend bool operator==(const String&, const String&);
    size_t length();
    size_t length() const;
    bool empty();
    bool empty() const;
    void clear();
    void push_back(char);
    void pop_back();
    char& front();
    char& back();
    char front() const;
    char back() const;
    size_t find(const String&);
    size_t rfind(const String&);
    String substr(const size_t, const size_t);
    size_t find(const String&) const;
    size_t rfind(const String&) const;
    String substr(const size_t&, const size_t&) const;

private:
    size_t sz = 0;
    size_t buf_sz = 8;
    char* str = new char[buf_sz];
    void swap(String&);
    void growbuffer();
    void decreasebuffer();
};

void String::growbuffer() {
    buf_sz *= 2;
    char* newstr = new char[buf_sz];
    memcpy(newstr, str, sz);
    delete[] str;
    str = newstr;
}

void String::decreasebuffer() {
    buf_sz = sz;
    char* newstr = new char[buf_sz];
    memcpy(newstr, str, sz);
    delete[] str;
    str = newstr;
}

void String::swap(String& s) {
    std::swap(sz, s.sz);
    std::swap(str, s.str);
}

size_t String::length() {
    return sz;
}

size_t String::length() const {
    return sz;
}

bool String::empty() {
    return !sz;
}

bool String::empty() const {
    return !sz;
}

void String::clear() {
    sz = 0;
    String s(sz, '\0');
    str = nullptr;
    this->buf_sz = 8;
}

void String::push_back(char x) {
    if (sz + 1 == buf_sz) growbuffer();
    str[sz++] = x;
}

void String::pop_back() {
    sz--;
    if (buf_sz / 2 > sz)decreasebuffer();
}

char& String::front() {
    return str[0];
}

char& String::back() {
    return str[sz - 1];
}

char String::front() const {
    return str[0];
}

char String::back() const {
    return str[sz - 1];
}

bool operator ==(const String& s1, const String& s2) {
    if (s1.length() == s2.length()) {
        if (s1.length() == 0)
            return memcmp(s1.str, s2.str, s1.length()) == 0;
        else return true;
    }
    else return false;
}

String operator+(const String& a, const String& b) {
    String copy = a;
    copy += b;
    return copy;
}

String operator+(const String& a, const char& b) {
    String copy = a;
    copy += b;
    return copy;
}

String operator+(const char& a, const String& b) {
    String copy(1, a);
    copy += b;
    return copy;
}

std::ostream& operator<<(std::ostream& out, const String& s)
{
    for (size_t i = 0; i < s.length(); ++i)
        out << s[i];
    return out;
}

std::istream& operator>>(std::istream& in, String& s) {
    char c;
    do {
        c = in.get();
    } while (isspace(c));
    while (!in.eof() && !isspace(c)) {
        s.push_back(c);
        c = in.get();
    }
    return in;
}

size_t String::find(const String& s) {
    for (size_t i = 0; i <= sz - s.sz; ++i) {
        for (size_t j = i; j < s.sz + i; ++j) {
            if (s[j - i] != (*this)[j])j = s.sz + i;
            if (j - i == s.sz - 1)
                return i;
        }
    }
    return sz;
}

String String::substr(const size_t st, const size_t ct) {
    String s(ct);
    memcpy(s.str, str + st, ct);
    return s;
}

String String::substr(const size_t& st, const size_t& ct) const {
    String s(ct);
    memcpy(s.str, str + st, ct);
    return s;
}

size_t String::find(const String& s) const {
    for (size_t i = 0; i <= sz - s.sz; i++) {
        for (size_t j = i; j < s.sz + i; j++) {
            if (s[j - i] != (*this)[j])j = s.sz + i;
            if (j - i == s.sz - 1)
                return i;
        }
    }
    return sz;
}

size_t String::rfind(const String& s) const {
    for (size_t i = 0; i <= sz - s.sz; i++) {
        size_t ii = sz - s.sz - i;
        for (size_t j = ii; j < s.sz + ii; j++) {
            if (s[j - ii] != (*this)[j])j = s.sz + ii;
            if (j - ii == s.sz - 1)
                return ii;
        }
    }
    return sz;
}

size_t String::rfind(const String& s) {
    for (size_t i = 0; i <= sz - s.sz; i++) {
        size_t ii = sz - s.sz - i;
        for

            (size_t j = ii; j < s.sz + ii; j++) {
            if (s[j - ii] != (*this)[j])j = s.sz + ii;
            if (j - ii == s.sz - 1)
                return ii;
        }
    }
    return sz;
}

String::~String() {
    if (str)delete[] str;
}