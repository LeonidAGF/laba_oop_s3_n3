#include "set.hpp"

Set::Set():size_(0), capacity_(1){
	data_ = new GeoCoordinate[capacity_];
}
Set::Set(const Set& x):size_(x.size_), capacity_(x.capacity_) {
	data_ = new GeoCoordinate[capacity_];
	std::memcpy(data_, x.data_, size_*sizeof(GeoCoordinate));
}
Set::Set(Set&& x) noexcept : data_(x.data_), size_(x.size_), capacity_(x.capacity_)  {
	x.data_ = nullptr;
	x.capacity_ = 0;
	x.size_ = 0;
}
Set& Set::operator=(const Set& other) {
	if (this == &other)
		return *this;
	Set tmp(other);
	std::swap(data_, tmp.data_);
	std::swap(size_, tmp.size_);
	std::swap(capacity_, tmp.capacity_);
	return *this;
}

Set& Set::operator=(Set&& x) noexcept {

	if(this == &x)
		return *this;

	delete[] data_;
	data_ = x.data_;
	capacity_ = x.capacity_;
	size_ = x.size_;
	x.data_ = nullptr;
	x.capacity_ = 0;
	x.size_ = 0;
	return *this;
}
Set::~Set() {
	delete[] data_;
}

bool Set::contains(const GeoCoordinate& x) const {
	if (data_) {
		size_t L = 0, R = size_, M;
		while (L < R) {
			M = (L + R) / 2;
			if (data_[M] < x)
				L = M+1;
			else if (data_[M] == x) {
				return 1;
			}
			else 
				R = M;
		}
		return L < size_ && data_[L] == x;
	}
	return 0;
}

bool Set::add(const GeoCoordinate& x) {
	if (contains(x))
		return false;

	GeoCoordinate el;
	el.latitude = x.latitude;
	el.longitude = x.longitude;

	if (size_ == capacity_) {
		size_t new_capacity = (capacity_>0? capacity_:1) *2;
		GeoCoordinate* new_data = new GeoCoordinate[new_capacity];
		std::memcpy(new_data, data_, size_*sizeof(GeoCoordinate));
		delete[] data_;
		data_ = new_data;
		capacity_ = new_capacity;
	}

	size_t L = 0, R = size_, M;
	while (L < R) {
		M = (L + R) / 2;
		if (data_[M] < x)
			L = M + 1;
		else if (data_[M] == x) {
			return 0;
		}
		else
			R = M;
	}
	
	for (size_t i = size_; i > R; --i)
		data_[i] = data_[i - 1];
	data_[R] = el;
	size_++;
	return true;
}
bool Set::remove(const GeoCoordinate& x) {
	size_t L = 0, R = size_,M;
	while (L < R) {
		M = L + (R - L) / 2;
		if (data_[M] < x)
			L = M + 1;
		else
			R = M;
	}
	if (L >= size_ || !(data_[L] == x))
		return false;
	for (size_t i = L + 1; i < size_; ++i)
		data_[i - 1] = data_[i];
	--size_;
	return true;
}

bool Set::operator()(const GeoCoordinate& x) const {
	return contains(x);
}
std::size_t Set::size() const {
	return size_;
}
bool Set::empty() const {
	return size_ == 0;
}
Set& Set::operator+=(const GeoCoordinate& x) {
	add(x);
	return *this;
}
Set& Set::operator-=(const GeoCoordinate& x) {
	remove(x);
	return *this;
}
Set Set::operator|(const Set& x) const {
	Set s;
	size_t i = 0, j = 0;
	while (i < size_ && j < x.size_) {
		if (data_[i] < x.data_[j]) {
			s.add(data_[i]);
			++i;
		}
		else if (x.data_[j] < data_[i]) {
			s.add(x.data_[j]);
			++j;
		}
		else {
			s.add(data_[i]);
			++i;
			++j;
		}
	}
	while (i < size_) 
		s.add(data_[i++]);
	while (j < x.size_)
		s.add(x.data_[j++]);
	return s;
}
Set Set::operator&(const Set& x) const {
	Set s;
	size_t i = 0, j = 0;
	while (i < size_ && j < x.size_) {
		if (data_[i] < x.data_[j])
			++i;
		else if (x.data_[j] < data_[i])
			++j;
		else {
			s.add(data_[i]);
			++i;
			++j;
		}
	}
	return s;
}
Set Set::operator-(const Set& x) const {
	Set s;
	size_t i = 0, j = 0;
	while (i < size_ && j < x.size_) {
		if (data_[i] < x.data_[j]) {
			s.add(data_[i]);
			++i;
		}	
		else if (x.data_[j] < data_[i])
			++j;
		else {
			
			++i;
			++j;
		}
	}
	while (i < size_) 
		s.add(data_[i++]);
	return s;
}
bool Set::operator==(const Set& x) const {
	bool res = 1;
	if (size_ != x.size_) {
		res = 0;
	}
	else {
		for (size_t i = 0; i < size_; ++i) {
			res = data_[i] == x.data_[i];
			if (!res)
				break;
		}
	}
	return res;
}
bool Set::operator!=(const Set& x) const {
	return !((*this)==x);
}

bool Set::operator<=(const Set& x) const {
	size_t i = 0, j = 0;
	while (i < size_ && j < x.size_) {
		if (data_[i] < x.data_[j])
			return false;
		else if (x.data_[j] < data_[i])
			++j;
		else {
			++i;
			++j;
		}
	}
	return i == size_;
}

std::ostream& operator<<(std::ostream& os, const Set& s) {
	os << "{";
	for (std::size_t i = 0; i < s.size_; ++i) {
		if (i != 0) os << ", ";
		os << '(' << s.data_[i].latitude
			<< ", " << s.data_[i].longitude << ')';
	}
	return os << "}";
}