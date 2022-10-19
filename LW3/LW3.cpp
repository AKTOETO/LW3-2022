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
void randomize_array(T* arr, int low, int high)
{
	for (int i = low; i <= high; i++)
	{
		arr[i] = rand_num(MIN_VALUE, MAX_VALUE);
	}
}

// печать массива в поток
template<typename T>
void print_arr(
	T* arr,					// массив
	int low = 0,			// индекс, с которого начинается вывод
	int high = 1,			// индекс, на котром кончается вывод
	ostream& stream = cout	// поток вывода
)
{
	// вывод элементов массива
	for (int i = low; i <= high; i++)
	{
		stream << arr[i] << ' ';
	}
	stream << '\n';
}

// чтение массива
void read_arr(int* arr, int low, int high)
{
	for (int i = low; i <= high; i++)
	{
		cin >> arr[i];
	}
}

//======================//
//	CОРТИРОВКА ВЫБОРОМ	//
//======================//

void selection_sort(int* arr, int low, int high)
{
	// проходимся по всем элементам массива
	// кроме последнего он уже будет в
	// нужном порядке, когда мы дойдем до него
	for (int i = low; i < high; i++)
	{
		// индекс наименьшего элемента
		int smallestIndex = i;

		// ищем еще более меньший элемент,
		// чем под индексом smallestIndex
		for (int j = i + 1; j <= high; j++)
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
		print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
	}
}

//======================//
//	БЫСТРАЯ СОРТИРОВКА	//
//======================//

// функция перераспределяющая элементы 
int partition(int* arr, int low, int high)
{
#ifdef EVERY_STEP_PRINT
	cout << "\nлевый: " << low << " правый: " << high << " partition: \n";
	cout << "\tдо изменений: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT

	// опорный элемент
	int pivot = arr[high];

	// индекс, в которм в конце алгоритма
	// окажется опорный элемент
	int out_pivot_ind = low;

	for (int i = low; i < high; i++)
	{
		// если текущий элемент меньше опорного
		if (arr[i] <= pivot)
		{
			// меняем местами текущий элемент 
			// и элемент под индексом out_ind
			swap(arr[out_pivot_ind++], arr[i]);
			// если нужна пошаговая печать
#ifdef EVERY_STEP_PRINT
			cout << "\t" << setfill(' ') << setw(5) << i << " индекс: ";
			print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
		}
	}

	// ставим опорный элемент в позицию out_ind
	swap(arr[out_pivot_ind], arr[high]);

	// если нужна пошаговая печать
#ifdef EVERY_STEP_PRINT
	cout << "\tпосле измен.: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
	return out_pivot_ind;
}

// быстрая сортировка
void quick_sort(int* arr, int low, int high)
{
	// если минимальный индекс меньше максимального
	if (low < high)
	{
		// переставляем элементы относительно 
		// определенного индекса, возвращаем
		// этот индекс
		int pivot_ind = partition(arr, low, high);

		// переставляем левую часть массива
		// относительно индекса ключевого элемента
		quick_sort(arr, low, pivot_ind - 1);

		// переставляем правую часть массива
		// относительно индекса ключевого элемента
		quick_sort(arr, pivot_ind + 1, high);

		// если нужна пошаговая печать
#ifdef EVERY_STEP_PRINT
		cout << "\nлевый: " << low << " правый: " << high << " quick sort: ";
		print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	// для теста сортировки
	int* arr;
	int size;

	//cin >> size;
	size = 15;

	arr = new int[size];

	//read_arr(arr, size);

	randomize_array(arr,0, size);
	print_arr(arr, 0, size);
	selection_sort(arr, 0,size);
	//quick_sort(arr, 0, size - 1);

	cout << setfill('=') << setw(30) << '\n';

	print_arr(arr, 0, size);
}