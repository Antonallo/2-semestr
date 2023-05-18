#include <iostream>


namespace lab_2
{
	class String 
	{
	private:
		char* m_str;
		size_t m_size;
	public:
		// Дефолтный конструктор
		String() : m_str(nullptr), m_size(0) {};

		// Конструктор копирования
		String(const String& other) : m_str(nullptr), m_size(other.m_size) {
			if (m_size > 0) {
				m_str = new char[m_size];
				for (size_t i = 0; i < m_size; ++i) {
					m_str[i] = other.m_str[i];
				}
			}
		}

		//Базовый конструктор
		String(const char* s) {
			m_size = strlen(s);
			m_str = new char[m_size + 1];
			strcpy(m_str, s);
		}

		// Оператор присваивания копированием
		String& operator=(const String& other) {
			if (this != &other) {
				if (m_str) {
					delete[] m_str;
					m_str = nullptr;
				}
				m_size = other.m_size;
				if (m_size > 0) {
					m_str = new char[m_size];
					for (size_t i = 0; i < m_size; ++i) {
						m_str[i] = other.m_str[i];
					}
				}
			}
			return *this;
		}

		// Деструктор
		~String() {
			if (m_str) {
				delete[] m_str;
				m_str = nullptr;
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
			if (m_str) {
				for (size_t i = 0; i < old_size; ++i) {
					new_buffer[i] = m_str[i];
				}
				delete[] m_str;
			}
			for (size_t i = old_size; i < m_size; ++i) {
				new_buffer[i] = other.m_str[i - old_size];
			}
			m_str = new_buffer;
			return *this;
		}

		// Оператор [] – чтение и изменение элемента
		char& operator[](size_t index) {
			if (index >= m_size) {
				throw std::out_of_range("Index is out of range");
			}
			return m_str[index];
		}

		int length() const {
			return m_size;
		}

		int find(char c) const {
			for (int i = 0; i < m_size; ++i) {
				if (m_str[i] == c)
					return i;
			}
			return -1;
		}

		bool operator<(const String& s) const {
			int i = 0;
			while (m_str[i] != '\0' && s.m_str[i] != '\0') {
				if (m_str[i] < s.m_str[i])
					return true;
				else if (m_str[i] > s.m_str[i])
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
			while (m_str[i] != '\0' && s.m_str[i] != '\0') {
				if (m_str[i] != s.m_str[i])
					return false;
				i++;
			}
			return true;
		}

		friend std::ostream& operator<<(std::ostream& os,  String& s) {
		    const char* c = s.c_str();
			for (size_t i = 0; i < s.m_size; i++) {
				os << c[i];
			}

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
			return m_str[index];
		}

	    const char* c_str() const {
			return m_str;
		}
	};
}

int main() 
{
	lab_2::String s;
	std::cin >> s;
	std::cout << s;
	return 0;
}