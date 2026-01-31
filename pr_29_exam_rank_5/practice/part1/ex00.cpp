#include <iostream>

class Awesome
{
  public:
    Awesome(void) : _n(0) {}
    Awesome( int n ) : _n( n ) {}
    Awesome & operator= (Awesome & a) { _n = a._n; return *this; } // copy assignment operator.
    bool 	operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
    bool 	operator!=( Awesome const & rhs ) const{ return (this->_n != rhs._n); }
    bool 	operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
    bool 	operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
    bool 	operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
    bool 	operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
    int 	get_n() const { return _n; }

  private:
    int _n;
};
std::ostream & operator<<(std::ostream & o, const Awesome &a) { o << a.get_n(); return o; }

	void 	swap(Awesome &a, Awesome &b) {
		Awesome temp = a;
				   a = b;
				   b = temp;	
	}
	int		max(Awesome &a, Awesome &b) {
		int anum = a.get_n();
		int bnum = b.get_n();
		return anum > bnum ? anum : bnum;
	}
	int		min(Awesome &a, Awesome &b) {
		int anum = a.get_n();
		int bnum = b.get_n();
		return anum < bnum ? anum : bnum;
	}

int main(void)
{
	Awesome a(2), b(4);

	swap(a, b);
	std::cout << a << " " << b << std::endl;
	std::cout << max(a, b) << std::endl;
	std::cout << min(a, b) << std::endl;
        return (0);
}
