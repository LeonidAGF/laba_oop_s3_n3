#include "set.hpp"

/*
	GeoCoordinate** data_;
	std::size_t size_;
	std::size_t capacity_;
*/

Set::Set():size_(0), capacity_(1){
	data = new GeoCoordinate*[capacity_];
}
Set::Set(const Set& x) {

	std::memcpy(value, s.value, size + 1);
}
Set::Set(Set&& x) noexcept;
Set& Set::operator=(const Set& other) {
	if (this != &other) {
		Set tmp(other);
		swap(tmp);
	}
	return *this;
}
void Set::swap(Set& other) noexcept {
	std::swap(data_, other.data_);
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
}
Set& Set::operator=(Set&& x) noexcept {

}
Set::~Set() {

}
bool Set::add(const GeoCoordinate& x) {

}
bool Set::remove(const GeoCoordinate& x) {

}
bool Set::contains(const GeoCoordinate& x) const {

}
bool Set:: operator()(const GeoCoordinate& x) const {

}
std::size_t Set::size() const {

}
bool Set::empty() const {

}
Set& Set::operator+=(const GeoCoordinate& x) {

}
Set& Set::operator-=(const GeoCoordinate& x) {

}
Set Set::operator|(const Set& x) const {

}
Set Set::operator&(const Set& x) const {

}
Set Set::operator-(const Set& x) const {

}
bool Set::operator==(const Set& x) const {

}
bool Set::operator!=(const Set& x) const {

}