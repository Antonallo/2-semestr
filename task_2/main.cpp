#include<iostream>

class DataConverter
{
public:
	template <typename T>
	static void convert(T* source, T* destination, int size)
	{
		const long long* pointer1 = (const long long*)source;
		long long* t_pointer1 = (long long*)destination;
		int m = sizeof(T) * size / sizeof(long long);
		for (int i = 0; i < m; i++) {
			*(t_pointer1++) = *(pointer1++);
		}
		char* pointer2 = (char*)pointer1;
		char* t_pointer2 = (char*)t_pointer1;
		m = (sizeof(T) * size) % sizeof(long long);
		for (int i = 0; i < m; i++)
		{
			*(t_pointer2++) = *(pointer2++);
		}

	}
};
int main()
{
	const int N = 100;
	int mas_a[N] = { 1,2,3,4,5 };
	int mas_b[N] = { 0 };
	DataConverter::convert(mas_a, mas_b, N);
	std::cout << "mas_a: ";
	for (int i = 0; i < N; i++)
	{
		std::cout << mas_a[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "mas_b: ";
	for (int i = 0; i < N; i++)
	{
		std::cout << mas_b[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}