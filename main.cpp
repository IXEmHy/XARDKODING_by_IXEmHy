#include "myalgorithm.h"
#include <algorithm>
#include <Windows.h>
//#include <ctime>
#include <random>
//#include "Header.h"

//#pragma comment(linker,"/STACK:4194304")

//  fuuny  //
class N
{
protected:
	int a = 0;
	static int size;
private:
	int n;
public:
	int& getSize() const
	{
		return size;
	}
	//      TODO	//
	// Constructors //
	/*N(const int val) {
		n = val;
		size++;
		std::cout << "Constructors [Class N]: " << this << tab << size << '\n';
	}*/
	//virtual void foo() const = 0;
	N() {
		a = 0;
		n = 0;
		size++;
		std::cout << "Constructors [Class N]: " << this << tab << size << '\n';
	}

	N(const N& n)
	{
		this->n = n.n;
		size++;
		std::cout << "Copy constructor [Class N]: " << this << tab << size << '\n';
	}

	virtual ~N()
	{
		size--;
		std::cout << "Destructors [Class N]: " << this << tab << size << '\n';
	}

	/*void operator=(const N & n)
	{
		this->n = n.n;
		data = n.data;
	}*/

	virtual void get() const
	{
		std::cout << "get_Class_N\n";
	}

	virtual void gun() const
	{
		std::cout << "BAM!\n";
	}
	virtual void good()
	{
		std::cout << "good\n";
	}

	friend std::ostream& operator<<(std::ostream& os, const N& a) {
		os << a.n;
		return os;
	}

	/*bool operator()(const N &n) const { return n.n > 0; }

	friend bool operator==(const N & a, const N & b) { return a.n == b.n; }

	template <class T>
	const N operator+(const T t) const { return N(n + t); }

	const N operator+(const N & t) const { return N(n + t.n); }

	template <class T>
	friend const N operator+(const T t, const N & n) { return n.operator+(t); }*/


	friend class A;

	//END
	//friend int32_t main();
};

int N::size = 0;


class A : public N
{
public:
	A()
	{
		std::cout << "Constructors [Class A]: " << this << tab <<
		++getSize() << std::endl;
	}
	//virtual void foo() const override {};
	virtual void gun() const override
	{
		std::cout << "BAM!BAM!\n";
	}
	virtual void get() const override
	{
		std::cout << "get_Class_A\n";
	}

	~A()
	{
		std::cout << "Destructors [Class A]: " << this << tab << --getSize() << '\n';
	}
};


void foo(N* n)
{
	n->gun();
}

void foo(A* a)
{
	a->gun();
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
	std::mt19937 mersenne(rd());*/

	using std::cout; using std::cin; using std::endl; //Использование cout, endl, cin
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Matrix<int> mat(3, 3);
	mat.arrgs(5, 3, 4);
	mat.getMat();

	return 0;
}