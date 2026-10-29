#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <ctime>

template <typename T>
class dynamic_array
{
public:
	T* array;
	int size;
	int capacity;

	dynamic_array()
	{
		size = 0;
		capacity = 1;
		array = new T[capacity];
	}

	void push_back(T number)
	{
		if (size < capacity)
		{
			array[size] = number;
			size += 1;
		}
		else if (size == capacity)
		{
			capacity *= 2;
			T* temp_array = new T[capacity];
			for (int i = 0; i < size; i++)
			{
				temp_array[i] = array[i];
			}
			delete[] array;
			array = temp_array;
			array[size] = number;
			size += 1;
		}

	}

	T& operator[](int index)
	{
		if (index < 0 || index >= size)
		{
			throw std::out_of_range("Zly index");
		}
		return array[index];
	}

	void clear()
	{
		delete[] array;
		size = 0;
		capacity = 1;
		array = new T[capacity];
	}

	void bubble_sort()
	{
		for (int j = 0; j < size - 1; j++)
		{
			for (int i = 0; i + 1 < size; i++)
			{
				if (array[i] > array[i + 1])
				{
					T temp = array[i];
					array[i] = array[i + 1];
					array[i + 1] = temp;
				}
			}
		}

	}

	~dynamic_array()
	{
		delete[] array;
	}
};

int main()
{
	{
		dynamic_array<int> s;
		s.push_back(1);
		s.push_back(2);
		s.push_back(3);
		s.push_back(4);
		s.push_back(5);
		std::cout << s[0] << "  " << std::endl;
		s[0] = 42;
		std::cout << s[0] << "  " << std::endl;

		std::cout << "Pred Size: " << s.size << "  Capacity: " << s.capacity << std::endl;
		for (int i = 0; i < s.size; i++)
		{
			std::cout << s.array[i] << "  ";
		}
		std::cout << "\n";
		s.clear();
		std::cout << "Po Size: " << s.size << "  Capacity: " << s.capacity << std::endl;
		s.push_back(100);
		std::cout << "Dodalem element Size: " << s.size << "  Capacity: " << s.capacity << std::endl;
		std::cout << s.array[0] << "  " << std::endl;

		dynamic_array<int> v;
		v.push_back(5);
		v.push_back(2);
		v.push_back(4);
		v.push_back(1);
		v.push_back(3);

		std::cout << "Przed bubble sort: " << "\n";
		for (int i = 0; i < v.size; i++)
		{
			std::cout << v.array[i] << "  ";
		}
		v.bubble_sort();
		std::cout << "\nPo bubble sort: " << "\n";
		for (int i = 0; i < v.size; i++)
		{
			std::cout << v.array[i] << "  ";
		}
		std::cout << "\n\n";
	}

	int num_elements = 1000;
	for (int i = 0; i < 11; i++)
	{
		std::cout << "\n";
		std::cout << "Rozmiar: " << num_elements << std::endl;
		{
			dynamic_array<int> f;
			double max_time = 0.0;
			for (int i = 0; i < num_elements; i++)
			{
				clock_t element_start = clock();
				f.push_back(i);
				clock_t element_end = clock();
				double element_time = (element_end - element_start) / (double)CLOCKS_PER_SEC;
				if (element_time > max_time)
				{
					max_time = element_time;
					std::cout << "Nowy rekord: iteracja " << i + 1 << ", czas: " << max_time * 1e3 << " ms" << std::endl;
				}
			}
		}

		{
			dynamic_array<int> k;
			clock_t start = clock();
			for (int i = 0; i < num_elements; i++)
			{
				k.push_back(i);
			}
			clock_t end = clock();
			double time = (end - start) / (double)CLOCKS_PER_SEC;
			std::cout << "Czas calkowity: " << time * 1e3 << " ms " << std::endl;

			double amortized_time = time / num_elements;
			std::cout << "Czas zamortyzowany: " << amortized_time * 1e9 << " ns " << std::endl;
		}
		num_elements *= 2;
	}

	return 0;
}