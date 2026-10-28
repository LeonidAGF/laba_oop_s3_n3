#pragma once

#include <cstddef>
#include <utility>
#include <algorithm>
#include <iostream>

struct GeoCoordinate {
	double latitude
	double longitude
};

class Set final {
public:
	Set();
	Set(const Set& x);
	Set(Set&& x) noexcept;
	Set& operator=(const Set& other);
	void swap(Set& other) noexcept;
	Set& operator=(Set&& x) noexcept;
	~Set();
	bool add(const GeoCoordinate& x);
	bool remove(const GeoCoordinate& x);
	bool contains(const GeoCoordinate& x) const;
	// true — множество изменилось 
	// true — элемент был и удалён 
	bool operator()(const GeoCoordinate& x) const; // принадлежность 
	std::size_t size() const;
	bool empty() const;
	Set& operator+=(const GeoCoordinate& x);
	Set& operator-=(const GeoCoordinate& x);
	// количество элементов 
	// size() == 0 
	Set operator|(const Set& x) const; // объединение 
	Set operator&(const Set& x) const; // пересечение 
	Set operator-(const Set& x) const; // разность 
	bool operator==(const Set& x) const;
	bool operator!=(const Set& x) const;
	friend std::ostream& operator<<(std::ostream&, const Set&);

private:
	GeoCoordinate** data_;
	std::size_t size_;
	std::size_t capacity_;
};