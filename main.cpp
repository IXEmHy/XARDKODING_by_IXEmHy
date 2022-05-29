#include "myalgorithm.h"
#include <Windows.h>
#include <random>
#include <exception>
#include <iomanip>
//#include "Header.h"

//#pragma comment(linker,"/STACK:4194304")

//  fuuny  //
class N
{
protected:
	int data;
	static int size;
public:
	//      TODO	//
	// Constructors //
	N(const int& val) {
		data = val;
		std::cout << "Constructors [Class N]: " << this << tab + '\n' << ++size;
	}
	//virtual void foo() const = 0;
	N() {
		data = 0;
		std::cout << "Constructor [Class N]: " << this << tab << ++size << '\n';
	}

	N(const N& n)
	{
		this->data = n.data;
		std::cout << "Copy constructor [Class N]: " << this << tab << ++size << '\n';
	}
	virtual ~N()
	{
		std::cout << "Destructors [Class N]: " << this << tab << --size << '\n';
	}
	void operator=(const N& N) { data = N.data; std::cout << "operation \"=\" [Class N]: " << this << tab + "\n"; }

	virtual void gun() const { std::cout << "BAM!\n"; }

	friend std::ostream& operator<<(std::ostream& os, 
		const N& a) {
		os << a.data;
		return os;
	}
};

int N::size = 0;
//myround
//double round(double x)
//{
//	return floor(x + 0.5);
//}

class A : public N
{
public:
	A() { std::cout << "Constructors [Class A]: " << this << tab << std::endl; }
	virtual void gun() const override {	std::cout << "BAM!BAM!\n"; }
	~A() { std::cout << "Destructors [Class A]: " << this << tab << data << '\n'; }
};

class myecteption: public std::exception
{
public:
	const char* what() const override
	{
		return "Enterminate error . . .";
	}
};

void foo1() {
	throw myecteption();
}


int32_t main()
{
	/*timer key;
	Рандом диапозон:
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> d(-10, 10);
	int a = d(gen);

	Второй вариант (без диапозона)
	std::random_device rd;  // Для рандомных чисел.
	std::mt19937 mersenne(rd());
	для регулирования вывода кол-во чисел в числе:
	cout << std::setprecision(16);*/

	using std::cout;  using std::endl; using std::cin; // Использование cout, endl, cin
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int arr[]{ 6,4,2,4,5,1 };
	int arr2[5];
	for (auto& el : arr2)
		el = rand() % 10;
	reverse(arr);
	for (auto& el : arr)
		cout << el <<  " ";
	cout << endl;
	sort(arr, 0);
	for (auto& el : arr)
		cout << el << ' ';

	return 0;                                          // Bye!
}