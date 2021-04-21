#include <iostream>
#include <vector>


using namespace std;


template<class T>
class Deque {
private:
	const size_t bucket_size = 4;
	vector<T*> mas;
	size_t first_mas = 0;
	size_t last_mas = 0;
	size_t first_ind = 0;
	size_t last_ind = 0;
	size_t length_mas = 0;


	void grow_buffer() {
		//cerr << "GB" << endl;
		size_t new_size = length_mas * 2;

		vector<T*> newmas(new_size - 1);
		for (size_t i = mas.size(); i < new_size - 1; ++i) {
			newmas[i] = mas[i - length_mas + 1];
		}
		mas = newmas;

		for (size_t i = length_mas; i < new_size - 1; ++i) {
			for (size_t j = 0; ((j < bucket_size && i < sz - 2) || (j <= last_ind && i == sz - 2)); ++j) {
				(newmas[i] + j)->~T();
			}
			delete[] newmas[i];
		}

		first_mas += new_size / 2 - 1;
		last_mas += new_size / 2 - 1;
		T* temp_mas = reinterpret_cast<T*>(new int8_t[sizeof(T) * bucket_size]);
		mas[first_mas - 1] = temp_mas;
	}

public:
	template<bool IsConst>
	struct common_iterator {
		using T_type = conditional_t<IsConst, const T&, T&>;
		using T_ptr_type = conditional_t<IsConst, const T*, T*>;
		size_t bucket_size = 4;
		const vector<T*>* mas;
		size_t bucket = 0;
		size_t ind = 0;
		T_ptr_type ptr;
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using pointer = T_ptr_type;
		using reference = T_type;
		using difference_type = sptrdiff_t;

		common_iterator(T_ptr_type ptr, size_t bucket, size_t ind, const vector<T*>* mas) : mas(mas), bucket(bucket), ind(ind), ptr(ptr) {
			//cerr << "I4" << endl;
		}

		common_iterator(T_ptr_type ptr) : ptr(ptr) {
			cerr << "I" << endl;
		}

		bool operator== (const common_iterator& iter) {
			//cerr << "==" << endl;

			return (ptr == iter.ptr);
		}

		bool operator!= (const common_iterator& iter) {
			//cerr << "!=" << endl;

			return !(ptr == iter.ptr);
		}

		bool operator<= (const common_iterator& iter) {
			//cerr << "<=" << endl;
			if (bucket == iter.bucket) {

				return (ind <= iter.ind);
			}
			else {

				return (bucket <= iter.bucket);
			}
		}

		bool operator>= (const common_iterator& iter) {
			//cerr << ">=" << endl;
			if (bucket == iter.bucket) {

				return (ind >= iter.ind);
			}
			else {

				return (bucket >= iter.bucket);
			}
		}

		bool operator< (const common_iterator& iter) {
			//cerr << "<" << endl;

			return (*this != iter) && (*this <= iter);
		}

		bool operator> (const common_iterator& iter) {
			//cerr << ">" << endl;

			return (*this != iter) && (*this >= iter);
		}

		common_iterator& operator++() {
			//cerr << "++" << endl;
			if (ind == bucket_size - 1) {
				bucket++;
				ind = 0;
				ptr = (*mas)[bucket];
			}
			else {
				ind++;
				++ptr;
			}

			return (*this);
		}

		common_iterator& operator--() {
			//cerr << "--" << endl;
			if (ind == 0) {
				bucket--;
				ind = bucket_size - 1;
				ptr = (*mas)[bucket] + ind;
			}
			else {
				ind--;
				--ptr;
			}

			return (*this);
		}

		common_iterator& operator++(int) {
			//cerr << "++i" << endl;
			common_iterator copy = *this;
			++(*this);

			return copy;
		}

		common_iterator& operator--(int) {
			//cerr << "--i" << endl;
			common_iterator copy = *this;
			--(*this);

			return (copy);
		}

		common_iterator& operator+=(const int& a) {
			//cerr << "+=" << endl;
			auto temp = bucket * bucket_size + ind + a;

			bucket = temp / bucket_size;
			ind = temp % bucket_size;
			ptr = (*mas)[bucket] + ind;

			return (*this);
		}

		common_iterator& operator-=(const int& a) {
			//cerr << "-=" << endl;
			*this += -a;

			return (*this);
		}

		int operator- (const common_iterator& iter) {
			//cerr << "-it" << endl;
			return ((bucket - iter.bucket + 1) * bucket_size - iter.ind - bucket_size + ind);
		}

		common_iterator operator+ (const int& n) {
			//cerr << "+" << endl;
			auto temp = *this;
			temp += n;

			return (temp);
		}

		common_iterator operator- (const int& n) {
			//cerr << "-" << endl;
			auto temp = *this;
			temp -= n;

			return (temp);
		}

		T_type operator*() {
			//cerr << "*" << endl;
			return (*ptr);
		}

		T_ptr_type operator->() {
			//cerr << "->" << endl;

			return (ptr);
		}
	};


	using iterator = common_iterator<false>;
	using const_iterator = common_iterator<true>;

	using reverse_iterator = reverse_iterator<iterator>;
	using const_reverse_iterator = reverse_iterator<const_iterator>;

	iterator begin() {
		//cerr << "b" << endl;

		return (iterator(mas[first_mas] + first_ind, first_mas, first_ind, &mas));
	}

	iterator end() {
		//cerr << "e" << endl;
		if (last_ind < bucket_size - 1) {

			return (iterator(mas[last_mas] + (last_ind + 1), last_mas, last_ind + 1, &mas));
		}
		else {

			return (iterator(mas[last_mas + 1], last_mas + 1, 0, &mas));
		}
	}

	const_iterator cbegin() {
		//cerr << "ccb" << endl;

		return (const_iterator(mas[first_mas] + first_ind, first_mas, first_ind, &mas));
	}

	const_iterator cend() {
		//cerr << "cce" << endl;
		if (last_ind < bucket_size - 1) {

			return (const_iterator(mas[last_mas] + (last_ind + 1), last_mas, last_ind + 1, &mas));
		}
		else {

			return (const_iterator(mas[last_mas + 1], last_mas + 1, 0, &mas));
		}
	}

	const_iterator begin() const {
		//cerr << "cbc" << endl;

		return (const_iterator(mas[first_mas] + first_ind, first_mas, first_ind, &mas));
	}

	const_iterator end() const {
		//cerr << "cec" << endl;
		if (last_ind < bucket_size - 1) {

			return (const_iterator(mas[last_mas] + (last_ind + 1), last_mas, last_ind + 1, &mas));
		}
		else {

			return (const_iterator(mas[last_mas + 1], last_mas + 1, 0, &mas));
		}
	}

	const_iterator cbegin() const {
		//cerr << "ccbc" << endl;

		return (const_iterator(mas[first_mas] + first_ind, first_mas, first_ind, &mas));
	}

	const_iterator cend() const {
		//cerr << "ccec" << endl;
		if (last_ind < bucket_size - 1) {

			return (const_iterator(mas[last_mas] + (last_ind + 1), last_mas, last_ind + 1, &mas));
		}
		else {

			return (const_iterator(mas[last_mas + 1], last_mas + 1, 0, &mas));
		}
	}

	reverse_iterator crend() const {

		return (const_reverse_iterator(cbegin() - 1));
	}

	reverse_iterator crbegin() const {

		return (const_reverse_iterator(cend() - 1));
	}

	const_reverse_iterator rend() {

		return (reverse_iterator(begin() - 1));
	}

	const_reverse_iterator rbegin() {

		return (reverse_iterator(end() - 1));
	}

	Deque() {
		//cerr << "D" << endl;
		mas.resize(bucket_size);

		for (size_t i = 0; i < bucket_size; ++i) {
			mas[i] = reinterpret_cast<T*>(new int8_t[sizeof(T) * bucket_size]);
		}

		first_mas = 2;
		last_mas = 2;
		first_ind = 0;
		last_ind = 0;
		length_mas = 0;
	}

	Deque(const Deque& deque) {
		//cerr << "DD" << endl;
		first_mas = deque.first_mas;
		last_mas = deque.last_mas;
		first_ind = deque.first_ind;
		last_ind = deque.last_ind;
		length_mas = deque.length_mas;
		mas.resize(deque.mas.size());

		try {
			for (size_t i = first_mas; i <= last_mas; ++i) {
				T* temp_mas = reinterpret_cast<T*>(new int8_t[sizeof(T) * bucket_size]);
				mas[i] = temp_mas;

				for (size_t j = 0; j < bucket_size; ++j) {
					new(mas[i] + j)T(deque.mas[i][j]);
				}
			}
		}

		catch (...) {

			throw;
		}
	}

	Deque(const int& n, const T& x = T()) {
		//cerr << "DIT " << n << endl;
		size_t temp = (n - 1) / bucket_size + 1;
		size_t nn = size_t(n);
		mas.resize(2 * temp + 1);
		first_mas = temp;
		last_mas = 2 * temp - 1;
		first_ind = 0;

		if (nn % bucket_size == 0) {
			last_ind = bucket_size - 1;
		}
		else {
			last_ind = nn % bucket_size - 1;
		}

		length_mas = nn;
		size_t i = first_mas;
		size_t j = 0;

		try {
			for (i = first_mas; i <= last_mas; ++i) {
				T* temp_mas = reinterpret_cast<T*>(new int8_t[sizeof(T) * bucket_size]);
				mas[i] = temp_mas;

				for (j = 0; ((j < bucket_size) && (((i - first_mas) * bucket_size + j) < nn)); ++j) {
					new(mas[i] + j)T(x);
				}
			}

			T* temp_mas = reinterpret_cast<T*>(new int8_t[sizeof(T) * bucket_size]);
			mas[last_mas + 1] = temp_mas;
		}

		catch (...) {
			for (size_t ii = first_mas; ii <= i; ++ii) {
				for (size_t jj = 0; ((jj < bucket_size && ii < i) || (jj < j && ii == i)); ++jj) {
					(mas[ii] + jj)->~T();
				}

				delete[] mas[ii];
			}

			throw;
		}
	}

	Deque& operator= (const Deque& deque) {
		//cerr << "D=" << endl;
		first_mas = deque.first_mas;
		last_mas = deque.last_mas;
		first_ind = deque.first_ind;
		last_ind = deque.last_ind;
		length_mas = deque.length_mas;
		size_t sz = mas.size();

		for (size_t i = 0; i < sz; ++i) {
			for (size_t j = 0; j < bucket_size; ++j) {
				(mas[i] + j)->~T();
			}

			delete[] reinterpret_cast<int8_t*>(mas[i]);
		}

		mas.clear();
		mas.resize(deque.mas.size());

		try {
			for (size_t i = first_mas; i <= last_mas; ++i) {
				T* temp_mas = reinterpret_cast<T*>(new int8_t[sizeof(T) * bucket_size]);
				mas[i] = temp_mas;

				for (size_t j = 0; j < bucket_size; ++j) {
					new(mas[i] + j)T(deque.mas[i][j]);
				}
			}
		}

		catch (...) {

			throw;
		}

		return (*this);
	}

	size_t size() const {
		//cerr << "size" << endl;

		return (length_mas);
	}

	T& operator[] (const size_t& i) {
		//cerr << "[]" << endl;

		return (mas[first_mas + (i + first_ind) / bucket_size][(i + first_ind) % bucket_size]);
	}

	T& at(const size_t& i) {
		//cerr << "at" << endl;

		if (i >= length_mas) {

			throw out_of_range("....");
		}

		return (mas[first_mas + (i + first_ind) / bucket_size][(i + first_ind) % bucket_size]);
	}

	const T& operator[] (const size_t& i) const {
		//cerr << "[]c" << endl;

		return (mas[first_mas + (i + first_ind) / bucket_size][(i + first_ind) % bucket_size]);
	}

	const T& at(const size_t& i) const {
		//cerr << "atc" << endl;
		if (i >= length_mas) {

			throw out_of_range("....");
		}

		return (mas[first_mas + (i + first_ind) / bucket_size][(i + first_ind) % bucket_size]);
	}

	void push_back(const T& x) {
		//cerr << "pub" << endl;
		try {
			if (length_mas == 0) {
				new(mas[last_mas] + last_ind)T(x);
				length_mas++;
			}
			else {
				if (last_ind + 1 == bucket_size) {
					last_ind = 0;
					last_mas++;
					if (last_mas + 1 == mas.size()) {
						T* temp_mas = reinterpret_cast<T*>(new int8_t[sizeof(T) * bucket_size]);
						mas.push_back(temp_mas);
					}
				}
				else {
					last_ind++;
				}

				new(mas[last_mas] + last_ind)T(x);
				length_mas++;
			}
		}

		catch (...) {

			throw;
		}
	}

	void pop_back() {
		//cerr << "pob" << endl;
		try {
			if (length_mas > 0) {
				(mas[last_mas] + last_ind)->~T();
				length_mas--;
				if (length_mas > 0) {
					if (last_ind == 0) {
						last_ind = bucket_size - 1;
						last_mas--;
					}
					else {
						last_ind--;
					}
				}
				else {
					last_mas = first_mas;
					last_ind = first_ind;
				}
			}
		}

		catch (...) {

			throw;
		}
	}

	void push_front(const T& x) {
		//cerr << "puf" << endl;
		try {
			if (length_mas == 0) {
				new(mas[first_mas] + first_ind)T(x);
				length_mas++;
			}
			else {
				if (first_ind == 0 && first_mas == 1) {
					grow_buffer();
				}

				if (first_ind == 0) {
					first_ind = bucket_size - 1;
					first_mas--;
					T* temp_mas = reinterpret_cast<T*>(new int8_t[sizeof(T) * bucket_size]);
					mas[first_mas] = temp_mas;
				}
				else {
					first_ind--;
				}

				new(mas[first_mas] + first_ind)T(x);
				length_mas++;
			}
		}

		catch (...) {

			throw;
		}
	}

	void pop_front() {
		//cerr << "pof" << endl;
		try {
			if (length_mas > 0) {
				(mas[first_mas] + first_ind)->~T();
				length_mas--;
				if (length_mas > 0) {
					if (first_ind + 1 == bucket_size) {
						first_ind = 0;
						first_mas++;
					}
					else {
						first_ind++;
					}
				}
				else {
					first_mas = last_mas;
					first_ind = last_ind;
				}
			}
		}
		catch (...) {

			throw;
		}
	}

	void insert(iterator iter, const T& x) {
		//cerr << "in1" << endl;
		try {
			iterator temp_iter(mas[last_mas] + last_ind, last_mas, last_ind, &mas);
			T temp = *temp_iter;

			while (temp_iter > iter) {
				iterator temp_iter_2(temp_iter);
				(temp_iter_2.ptr)->~T();
				new(temp_iter_2.ptr)T(*(--temp_iter));
			}

			(temp_iter.ptr)->~T();
			new(temp_iter.ptr)T(x);
			push_back(temp);
		}

		catch (...) {

			throw;
		}
	}

	void insert(const_iterator iter, const T& x) {
		//cerr << "in2" << endl;
		try {
			iterator temp_iter(mas[last_mas] + last_ind, last_mas, last_ind, &mas);
			T temp = *temp_iter;

			while (temp_iter > iter) {
				iterator temp_iter_2(temp_iter);
				(temp_iter_2.ptr)->~T();
				new(temp_iter_2.ptr)T(*(--temp_iter));
			}

			(temp_iter.ptr)->~T();
			new(temp_iter.ptr)T(x);
			push_back(temp);
		}

		catch (...) {

			throw;
		}
	}

	void erase(iterator iter) {
		//cerr << "er1" << endl;
		try {
			iterator temp_iter(iter);
			iterator temp_iter_2(--end());

			while (temp_iter != temp_iter_2) {
				iterator temp_iter_2(temp_iter);
				(temp_iter_2.ptr)->~T();
				new(temp_iter_2.ptr)T(*(++temp_iter));
			}

			pop_back();
		}

		catch (...) {

			throw;
		}
	}

	void erase(const_iterator iter) {
		//cerr << "er2" << endl;
		try {
			iterator temp_iter(iter);
			iterator temp_iter_2(--end());

			while (temp_iter != temp_iter_2) {
				iterator temp_iter_2(temp_iter);
				(temp_iter_2.ptr)->~T();
				new(temp_iter_2.ptr)T(*(++temp_iter));
			}

			pop_back();
		}

		catch (...) {

			throw;
		}
	}

	~Deque() {
		for (size_t i = 0; i < mas.size(); ++i) {
			for (size_t j = 0; ((j < bucket_size && i < mas.size() - 1) || (j <= last_ind && i == mas.size() - 1)); ++j) {
				(mas[i] + j)->~T();
			}

			delete[] mas[i];
		}
	}

};
