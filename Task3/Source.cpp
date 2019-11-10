#include <iostream>
#include <string>
#include <typeinfo>
#include "C:\Users\nguyenhanh\Documents\Visual Studio 2013\Projects\GenScatterHierarchy\GenScatterHierarchy\loki\include\loki\Typelist.h"
#include "C:\Users\nguyenhanh\Documents\Visual Studio 2013\Projects\GenScatterHierarchy\GenScatterHierarchy\loki\include\loki\HierarchyGenerators.h"

template <class T>
struct Holder //sames as before
{
	T value_;
};


// Simplistic test
class NullType {};
#define TYPELIST_1(x)           Loki::Typelist< x, NullType>
#define TYPELIST_2(x, y)        Loki::Typelist< x, TYPELIST_1(y)>
#define TYPELIST_3(x, y, z)     Loki::Typelist< x, TYPELIST_2(y,z)>

int main(int argc, char *argv[])
{
	typedef Loki::GenScatterHierarchy<
		TYPELIST_3(int, std::string, bool), Holder>
		WidgetInfo;
	WidgetInfo foo;
	Loki::Field<0>(foo).value_ = 1;
	Loki::Field<1>(foo).value_ = "hanh";
	Loki::Field<2>(foo).value_ = true;
	int i = Loki::Field<int>(foo).value_;
	std::string name = (static_cast<Holder<std::string>&>(foo)).value_;
	typedef Loki::GenScatterHierarchy<int, Holder> AtomicInfo;

	std::cout << i << " " << name << std::endl;

	AtomicInfo atom;
	atom.value_ = 1;

	//int j = (static_cast<Holder<int>&>(atom)).value_;
	
	int j = (static_cast<Holder<int>&>(atom)).value_;
	std::cout << j;
	system("pause");
	return 0;
}