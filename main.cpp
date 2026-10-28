#include "src/str.hpp"

#define String string

int main() {
	String s1;
	String s2("Hello");
	String s3(s2);
	String s4(std::move(s3));
	s1 = s2;
	s1.append(", World!");
	s1.print(std::cout);
	size_t pos = s1.find("World");
	std::cout << pos << std::endl;
	return 0;
}