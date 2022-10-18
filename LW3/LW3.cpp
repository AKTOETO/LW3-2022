/***********************************************************************\
*                    кафедра № 304 2 курс 3 семестр информатика			*
*-----------------------------------------------------------------------*
*	Project type : solution												*
*	Project name : matrix												*
*	File name    : matrix.cpp											*
*	Language     : c/c++												*
*	Programmers  : Плоцкий Б.А. Раужев Ю. М.							*
*	Created      :  19/10/22											*
*	Last revision:  /10/22											*
*	Comment(s)   : Вариант № 1											*
* 																		*
*	Для массива из n элементов выполнить сортировку с помощью двух		*
*	указанных методов для:												*
*		1.	заданной произвольным образом последовательности чисел,		*
*		2.	уже отсортированных последовательностей в возрастающем 		*
*		и убывающем порядке (лучший и худший случаи для					*
*		выполнения сортировки).											*
*																		*
*																		*
\***********************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

// убрать комментарий, если нужна
// пошаговая печать массивов
#define EVERY_STEP_PRINT

// минимальное и максимальное значение
// для чисел в массиве
#define MIN_VALUE 10
#define MAX_VALUE 20

// возвращение случайного значения из 
// интервала (min, max)
template<typename T>
T rand_num(T min, T max)
{
	return rand() % (max - min) + min;
}

// рандомизация значений массива
template<typename T>
void randomize_array(T* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand_num(MIN_VALUE, MAX_VALUE);
	}
}

// печать массива в поток
template<typename T>
void print_arr(T* arr, int size, ostream& stream = cout)
{
	// вывод элементов массива
	for (int i = 0; i < size; i++)
	{
		stream << arr[i] << ' ';
	}
	cout << '\n';
}

// чтение массива
void read_arr(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}
}

//======================//
//	CОРТИРОВКА ВЫБОРОМ	//
//======================//

void selection_sort(int* arr, int size)
{
	// проходимся по всем элементам массива
	// кроме последнего он уже будет в
	// нужном порядке, когда мы дойдем до него
	for (int i = 0; i < size - 1; i++)
	{
		// индекс наименьшего элемента
		int smallestIndex = i;

		// ищем еще более меньший элемент,
		// чем под индексом smallestIndex
		for (int j = i + 1; j < size; j++)
		{
			// если был найдем элемент,
			// который меньше элемнта под
			// индексом smallestIndex, то
			// обновляем smallestIndex
			if (arr[j] < arr[smallestIndex])
			{
				smallestIndex = j;
			}
		}
		// меняем местами текущий элемент и наименьший 
		swap(arr[i], arr[smallestIndex]);

		// если нужна пошаговая печать
#ifdef EVERY_STEP_PRINT
		print_arr(arr, size);
#endif // EVERY_STEP_PRINT
	}
}

//======================//
//	БЫСТРАЯ СОРТИРОВКА	//
//======================//

// функция перераспределяющая элементы 
int partition(int* arr, int low, int high)
{
	int pivot_ind = low;
	for (int i = low; i < high; i++)
	{
		if (arr[i] <= arr[high])
		{
			swap(arr[pivot_ind++], arr[i]);	
		}
		print_arr(arr, 6);
	}
	swap(arr[pivot_ind], arr[high]);

	print_arr(arr, 6);
	cout << "====\n";
	return pivot_ind;
}

// быстрая сортировка
void quick_sort(int* arr, int low, int high)
{
	if (low < high)
	{
		int part = partition(arr, low, high);
		quick_sort(arr, low, part);
		quick_sort(arr, part + 1, high);

		// если нужна пошаговая печать
#ifdef EVERY_STEP_PRINT
		cout << "out: ";
		print_arr(arr, 6);
#endif // EVERY_STEP_PRINT
	}
}

int main()
{
	// для теста сортировки
	int* arr;
	int size;

	cin >> size;

	arr = new int[size];
	
	read_arr(arr, size);

	//randomize_array(arr, size);
	//selection_sort(arr, size);
	quick_sort(arr, 0, size - 1);

	cout << setfill('=') << setw(30) << '\n';

	print_arr(arr, size);
}