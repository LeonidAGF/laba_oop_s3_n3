#include "set.hpp"

int main() {

	Set a;
	std::cout << "size = " << a.size() << ", empty = " << a.empty() << "\n";
	a.add({ 55.75, 37.62 });
	a.add({ 48.85, 2.35 });
	a.add({ 40.71, -74.0 });
	a.add({ 48.85, 2.35 });

	std::cout << "size"  << a.size() << "\n";

	std::cout << a.contains({ 48.85, 2.35 }) << "\n";
	std::cout << a({ 0, 0 }) << "\n";
	a.remove({ 40.71, -74.0 });
	std::cout << "size" << a.size() << "\n";

	a += GeoCoordinate{ 35.68, 139.69 };

	Set b;
	b.add({ 48.85, 2.35 });
	b.add({ 51.5, -0.12 });
	b.add({ 41.9, 12.5 });

	std::cout << "A = " << a << "\n";
	std::cout << "B = " << b << "\n\n";
	std::cout << "A | B = " << (a | b) << "\n";
	std::cout << "A & B = " << (a & b) << "\n";
	std::cout << "A - B = " << (a - b) << "\n";
	std::cout << "B - A = " << (b - a) << "\n\n";

	return 0;
}