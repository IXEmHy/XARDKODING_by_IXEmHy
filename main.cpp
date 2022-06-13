#include "myalgorithm.h"
#include <Windows.h>
#include <random>
#include <exception>
#include <iomanip>

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
	explicit N(const int& val) {
		data = val;
		std::cout << "Constructor [Class N]: " << this << tab << ++size<<'\n';
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
	virtual ~N() { std::cout << "Destructors [Class N]: " << this << tab << --size << '\n'; }
	void operator=(const N& N) { data = N.data; std::cout << "operation \"=\" [Class N]: " << this << tab + "\n"; }

	virtual void gun() const { std::cout << "BAM!\n"; }

	friend std::ostream& operator<<
		(std::ostream& os, const N& a) {
		os << a.data;
		return os;
	}
};
int N::size = 0;
class A : public N
{
public:
	A() { std::cout << "Constructors [Class A]: " << this << tab << std::endl; }
	virtual void gun() const override {	std::cout << "BAM!BAM!\n"; }
	~A() { std::cout << "Destructors [Class A]: " << this << tab << data << '\n'; }
};

class myecteption : public std::exception
{
public:
	const char* what() const override
	{
		return "Enterminate error . . .";
	}
};

void foo1() { throw myecteption(); }

//myround
//double round(double x)
//{
//	return floor(x + 0.5);
//}


class Grand {
public:
	virtual void speak() { std::cout << "Grand speak\n"; };
};

class Superb : public Grand {
public:
	void speak() override { std::cout << "Superb speak\n"; };
	virtual void say() { std::cout << "Superb say\n"; }
};

class Magnificient : public Superb {
public:
	char ch;
	void speak() override { std::cout << "Magnificient speak\n"; }
	void say() override { std::cout << "Magnificient say\n"; }
};



int32_t main()
{
	/*timer key;
	–андом диапозон:
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> d(-10, 10);
	int a = d(gen);

	¬торой вариант (без диапозона)
	std::random_device rd;  // ƒл€ рандомных чисел.
	std::mt19937 mersenne(rd());
	дл€ регулировани€ вывода кол-во чисел в числе:
	cout << std::setprecision(16);
	Grand* pa = new Grand;
	Grand* pb = new Superb;
	Grand* pc = new Magnificient;

	Grand* pe = dynamic_cast<Grand*> (pb);                                   // dynamic_cast<Type*> (px) - если (*px) имеет тип Type или унаследованный от Type, 
	cout << pe << tab + typeid(*pe).name() << '\n';                          // то произойдет преобразование, иначе nullptr
	pe->speak();*/

	using std::cout;  using std::endl; using std::cin; // »спользование cout, endl, cin
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int arr[]{ 7,5,6,8,9,5,2,10,2,3,4,5,6,7,8,9,5,5,5,11,44,554,4,5,3,77,86,5,-5 };
	cout << min_max<int[29]>(arr) << tab << min_max(arr, 0) << endl;
	return 0;                                          // Bye!
}