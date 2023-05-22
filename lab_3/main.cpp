#include <iostream>
using namespace std;

namespace lab_3
{
	class Complex 
	{
	private: 
		double m_real, m_imag;
	public:
        Complex() : m_real(0.0), m_imag(0.0)
        {}

        Complex(double a, double b) : m_real(a), m_imag(b)
        {}

        Complex(const Complex& other)
        {
            m_real = other.m_real;
            m_imag = other.m_imag;
        }

        ~Complex()
        {}

        Complex& operator+=(const Complex& other) {
            m_real += other.m_real;
            m_imag += other.m_imag;
            return *this;
        }

        Complex operator+(const Complex& other) const {
            return Complex(m_real + other.m_real, m_imag + other.m_imag);
        }

        Complex& operator*=(const Complex& other) {
            double new_real = m_real * other.m_real - m_imag * other.m_imag;
            double new_imag = m_real * other.m_imag + m_imag * other.m_real;
            m_real = new_real;
            m_imag = new_imag;
            return *this;
        }

        Complex operator*(const Complex& other) const {
            Complex result = *this;
            result *= other;
            return result;
        }

        Complex& operator++() {
            m_real++;
            return *this;
        }

        Complex operator++(int) {
            Complex tmp(*this);
            operator++();
            return tmp;
        }

        friend std::istream& operator >> (std::istream& in, Complex& z)
        {
            in >> z.m_real;
            in >> z.m_imag;

            return in;
        }

        friend std::ostream& operator << (std::ostream& out, Complex& z)
        {
            out << "{ " << z.m_real << " , " << z.m_imag << " }";

            return out;
        }
	};
}

int main() 
{
    lab_3::Complex a(1, 2);
    lab_3::Complex b(3, 4);
    lab_3::Complex c = a + b;
    lab_3::Complex d = a * b;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << c << endl;
    cout << "a * b = " << d << endl;
    a++;
    cout << "a++ = " << a << endl;
    ++b;
    cout << "++b = " << b << endl;
    lab_3::Complex e;
    cout << "Enter complex number (a, b): ";
    cin >> e;
    cout << "You entered " << e << endl;
    return 0;
}