#include "set.hpp"

/*
	GeoCoordinate** data_;
	std::size_t size_;
	std::size_t capacity_;
*/

Set::Set():size_(0), capacity_(1){
	data_ = new GeoCoordinate*[capacity_];
}
Set::Set(const Set& x):size_(x.size_), capacity_(x.capacity_) {
	data_ = new GeoCoordinate * [capacity_];
	std::memcpy(data_, x.data_, size_);
}
Set::Set(Set&& x) noexcept : data_(x.data_), size_(x.size_), capacity_(x.capacity_)  {
	x.data_ = nullptr;
	x.capacity_ = 0;
	x.size_ = 0;
}
Set& Set::operator=(const Set& other) {
	if (this != &other) {
		Set tmp(other);
		std::swap(data_, tmp.data_);
		std::swap(size_, tmp.size_);
		std::swap(capacity_, tmp.capacity_);
	}
	return *this;
}

Set& Set::operator=(Set&& x) noexcept {
	data_ = x.data_;
	capacity_ = x.capacity_;
	size_ = x.size_;
	x.data_ = nullptr;
	x.capacity_ = 0;
	x.size_ = 0;
	return *this;
}
Set::~Set() {
	if (data_)
		for (size_t i = 0; i < size_; ++i)
			delete data_[i];

	delete[] data_;
}

bool Set::contains(const GeoCoordinate& x) const {
	bool finded = 0;
	if (data_) {
		for (size_t i = 0; i < size_; ++i) {
			if ((*data_[i]) == x) {
				finded = 1;
				break;
			}
		}
	}
	return finded;
}

bool Set::add(const GeoCoordinate& x) {
	if (contains(x))
		return false;

	GeoCoordinate* el = new GeoCoordinate();
	el->latitude = x.latitude;
	el->longitude = x.longitude;

	if (size_ == capacity_) {
		size_t new_capacity = capacity_ *2;
		GeoCoordinate** new_data = new GeoCoordinate * [new_capacity];
		std::memcpy(new_data, data_, size_);
		delete[] data_;
		data_ = new_data;
		capacity_ = new_capacity;
	}
		
	data_[size_] = el;
	size_++;
	return true;
}
bool Set::remove(const GeoCoordinate& x) {
	if (!contains(x))
		return false;
	size_t size = 0;
	GeoCoordinate** new_data = new GeoCoordinate * [size_];
	for (size_t i = 0; i < size_; ++i) {
		if ((*data_[i]) != x)
			new_data[size++] = data_[i];
	}
	delete[] data_;
	data_ = new_data;
}

bool Set::operator()(const GeoCoordinate& x) const {
	return contains(x);
}
std::size_t Set::size() const {
	return size_;
}
bool Set::empty() const {
	if (size_ == 0)
		return true;
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
	for (size_t i = 0; i < size_; ++i) {
		s.add(*data_[i]);
	}
	for (size_t i = 0; i < x.size_; ++i) {
		s.add(*x.data_[i]);
	}
	return s;
}
Set Set::operator&(const Set& x) const {
	Set s;
	for (size_t i = 0; i < size_; ++i) {
		if (x.contains(*data_[i]))
			s.add(*data_[i]);
	}
	return s;
}
Set Set::operator-(const Set& x) const {
	Set s;
	for (size_t i = 0; i < size_; ++i) {
		if (!x.contains(*data_[i]))
			s.add(*data_[i]);
	}
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
	bool res = 1;
	if (size_ > x.size_)
		res = 0;
	else {
		for (size_t i = 0; i < size_; ++i) {
			res = x.contains(*data_[i]);
			if (!res)
				break;
		}
	}
	return res;
}
