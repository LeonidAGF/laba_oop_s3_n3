#pragma once

#include <cstddef>
#include <utility>
#include <algorithm>
#include <iostream>
#include <cstring>

class GeoCoordinate {
public:
	double latitude = 0;
	double longitude = 0;

	bool operator==( const GeoCoordinate& r) const {
		return (latitude == r.latitude && longitude == r.longitude);
	}

	bool operator<(const GeoCoordinate& r) const {
		return (latitude < r.latitude || (latitude == r.latitude && longitude < r.longitude));
	}

};





class Set final {
public:
	Set();
	Set(const Set& x);
	Set(Set&& x) noexcept;
	Set& operator=(const Set& other);
	Set& operator=(Set&& x) noexcept;
	~Set();
	bool add(const GeoCoordinate& x);
	bool remove(const GeoCoordinate& x);
	bool contains(const GeoCoordinate& x) const;
	bool operator()(const GeoCoordinate& x) const;
	std::size_t size() const;
	bool empty() const;
	Set& operator+=(const GeoCoordinate& x);
	Set& operator-=(const GeoCoordinate& x);
	Set operator|(const Set& x) const; 
	Set operator&(const Set& x) const;
	Set operator-(const Set& x) const;
	bool operator==(const Set& x) const;
	bool operator!=(const Set& x) const;
	bool operator<=(const Set& x) const;
	friend std::ostream& operator<<(std::ostream&, const Set&);

private:
	GeoCoordinate* data_ = nullptr;
	std::size_t size_ = 0;
	std::size_t capacity_ = 0;
};