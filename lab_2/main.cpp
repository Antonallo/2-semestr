#include <iostream>


namespace lab_2
{
	class String 
	{
	private:
		char* str;
		size_t m_size;
	public:
		// Базовый конструктор
		String() : str(nullptr), m_size(0) {};

		// Конструктор копирования
		String(const String& other) : str(nullptr), m_size(other.m_size) {
			if (m_size > 0) {
				str = new char[m_size];
				for (size_t i = 0; i < m_size; ++i) {
					str[i] = other.str[i];
				}
			}
		}

		// Оператор присваивания копированием
		String& operator=(const String& other) {
			if (this != &other) {
				if (str) {
					delete[] str;
					str = nullptr;
				}
				m_size = other.m_size;
				if (m_size > 0) {
					str = new char[m_size];
					for (size_t i = 0; i < m_size; ++i) {
						str[i] = other.str[i];
					}
				}
			}
			return *this;
		}

		// Деструктор
		~String() {
			if (str) {
				delete[] str;
				str = nullptr;
				m_size = 0;
			}
		}

		// Операторы + и +=
		String operator+(const String& other) const {
			String result(*this);
			result += other;
			return result;
		}

		String& operator+=(const String& other) {
			const size_t old_size = m_size;
			m_size += other.m_size;
			char* new_buffer = new char[m_size];
			if (str) {
				for (size_t i = 0; i < old_size; ++i) {
					new_buffer[i] = str[i];
				}
				delete[] str;
			}
			for (size_t i = old_size; i < m_size; ++i) {
				new_buffer[i] = other.str[i - old_size];
			}
			str = new_buffer;
			return *this;
		}

		// Оператор [] – чтение и изменение элемента
		char& operator[](size_t index) {
			if (index >= m_size) {
				throw std::out_of_range("Index is out of range");
			}
			return str[index];
		}

		int length() const {
			return m_size;
		}

		int find(char c) const {
			for (int i = 0; i < m_size; ++i) {
				if (str[i] == c)
					return i;
			}
			return -1;
		}

		bool operator<(const String& s) const {
			int i = 0;
			while (str[i] != '\0' && s.str[i] != '\0') {
				if (str[i] < s.str[i])
					return true;
				else if (str[i] > s.str[i])
					return false;
				i++;
			}
			if (m_size < s.m_size)
				return true;
			else
				return false;
		}

		bool operator>(const String& s) const {
			return s < *this;
		}

		bool operator==(const String& s) const {
			if (m_size != s.m_size)
				return false;
			int i = 0;
			while (str[i] != '\0' && s.str[i] != '\0') {
				if (str[i] != s.str[i])
					return false;
				i++;
			}
			return true;
		}

		friend std::ostream& operator<<(std::ostream& os, const String& s) {
			os << s.str;
			return os;
		}

		friend std::istream& operator>>(std::istream& is, String& s) {
			char buffer[1000];
			is >> buffer;
			s = String(buffer);
			return is;
		}

		char& at(size_t index) {
			if (index >= m_size) {
				throw std::out_of_range("Index is out of range");
			}
			return str[index];
		}

		const char* c_str() const {
			return str;
		}
	};
}

int main() 
{
	String s;
	std::cin >> s;
	std::cout << s;
	return 0;
}