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

// для генерации последовательностей
// шаг чисел при генерации последовательности
#define STEP 1
// максимальное значение при генерации чисел
#define MAX_GENERATE MAX_VALUE

// необходима для функций сортировки
struct help_data
{
	int num_of_comp;	// число сравнений
	int num_of_swap;	// число перемещений
};

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
	for (int i = low; i < high; i++)
	{
		arr[i] = rand_num(MIN_VALUE, MAX_VALUE);
	}
}

// копирование массива
template<typename T>
void copy_arr(
	T* arr1,	// источник данных
	T* arr2,	// место копирования данных
	int low,	// индекс начального элемента
	int high	// индекс элемента после последнего
)
{
	for (int i = low; i < high; i++)
	{
		arr2[i] = arr1[i];
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
	for (int i = low; i < high; i++)
	{
		stream << arr[i] << ' ';
	}
	stream << '\n';
}

//***********************************************************//
// Г Е Н Е Р А Ц И Я   П О С Л Е Д О В А Т Е Л Ь Н О С Т Е Й //
//***********************************************************//

// чтение массива
void read_arr(int* arr, int low, int high)
{
	for (int i = low; i < high; i++)
	{
		cin >> arr[i];
	}
}

// упорядочная функция по возрастанию
template<typename T>
void f1(T* arr, int low, int high)
{
	//k, b - коэффициенты прямой
	T k = MAX_GENERATE / (STEP * (high - low + 1));
	T b = 0;
	double x = 0.0; // координата x

	// заполнение массива 
	for (int i = low; i < high; i++, x += STEP)
	{
		arr[i] = k * x + b;
	}
}

// упорядочная функция по убыванию
template<typename T>
void f2(T* arr, int low, int high)
{
	//k, b - коэффициенты прямой
	T k = MAX_GENERATE / (STEP * (high - low + 1));
	T b = 0;
	double x = MAX_GENERATE; // координата x

	// заполнение массива 
	for (int i = low; i < high; i++, x -= STEP)
	{
		arr[i] = k * x + b;
	}
}

// ввод и проверка значений
template<typename T>
T input_and_check(T _min, T _max,
	const char* welcome_str, const char* err_str)
{
	// размер массива
	T num;

	// вывод сообщения
	cout << welcome_str << "\n";
	cin >> num;

	// если было введено не то
	if (num > _max || num < _min) {
		// если была введена не цифра
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		// отчистка консоли
		system("cls");
		cout << err_str << "\n";

		// рекурсивное обращение
		num = input_and_check(_min, _max, welcome_str, err_str);
	}
	return num;
}

//**************************************************************//
//				C О Р Т И Р О В К А   В Ы Б О Р О М				//
//**************************************************************//

void selection_sort(int* arr, int low, int high, help_data& data)
{
#ifdef EVERY_STEP_PRINT
	cout << "\nлевый: " << low << " правый: " << high << " partition: \n";
	cout << "\tдо    изменений: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT

	// проходимся по всем элементам массива
	// кроме последнего он уже будет в
	// нужном порядке, когда мы дойдем до него
	for (int i = low; i < high - 1; i++)
	{
		data.num_of_comp++;

		// индекс наименьшего элемента
		int smallestIndex = i;

		// ищем еще более меньший элемент,
		// чем под индексом smallestIndex
		for (int j = i + 1; j < high; j++)
		{
			data.num_of_comp++;

			// если был найдем элемент,
			// который меньше элемнта под
			// индексом smallestIndex, то
			// обновляем smallestIndex
			data.num_of_comp++;
			if (arr[j] < arr[smallestIndex])
			{
				smallestIndex = j;
			}
		}
		data.num_of_comp++;

		// меняем местами текущий элемент и наименьший 
		data.num_of_swap++;
		swap(arr[i], arr[smallestIndex]);

		// если нужна пошаговая печать
#ifdef EVERY_STEP_PRINT
		cout << "\t" << setfill(' ') << setw(3) << i << " с "
			<< setfill(' ') << setw(2) << smallestIndex << " индекс: ";
		print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
	}
	data.num_of_comp++;
}

//**************************************************************//
//				Б Ы С Т Р А Я   С О Р Т И Р О В К А				//
//**************************************************************//

// функция перераспределяющая элементы 
int partition(int* arr, int low, int high, help_data& data)
{
#ifdef EVERY_STEP_PRINT
	cout << "\nлевый: " << low << " правый: " << high << " partition: \n";
	cout << "\tдо    изменений: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT

	// опорный элемент
	int pivot = arr[high];

	// индекс, в которм в конце алгоритма
	// окажется опорный элемент
	int out_pivot_ind = low;

	for (int i = low; i < high; i++)
	{
		data.num_of_comp++;

		// если текущий элемент меньше опорного
		data.num_of_comp++;
		if (arr[i] <= pivot)
		{
			// меняем местами текущий элемент 
			// и элемент под индексом out_ind
			data.num_of_swap++;
			swap(arr[out_pivot_ind++], arr[i]);
			// если нужна пошаговая печать
#ifdef EVERY_STEP_PRINT
			cout << "\t" << setfill(' ') << setw(3) << i << " с "
				<< setfill(' ') << setw(2) << out_pivot_ind - 1 << " индекс: ";
			print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
		}
	}
	data.num_of_comp++;

	// ставим опорный элемент в позицию out_ind
	data.num_of_swap++;
	swap(arr[out_pivot_ind], arr[high]);
#ifdef EVERY_STEP_PRINT
	cout << "\t" << setfill(' ') << setw(3) << high << " с "
		<< setfill(' ') << setw(2) << out_pivot_ind - 1 << " индекс: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT

	// если нужна пошаговая печать
#ifdef EVERY_STEP_PRINT
	cout << "\tпосле  изменен.: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
	return out_pivot_ind;
}

// быстрая сортировка
void quick_sort(int* arr, int low, int high, help_data& data)
{
	// если минимальный индекс меньше максимального
	data.num_of_comp++;
	if (low < high)
	{
		// переставляем элементы относительно 
		// определенного индекса, возвращаем
		// этот индекс
		int pivot_ind = partition(arr, low, high, data);

		// переставляем левую часть массива
		// относительно индекса ключевого элемента
		quick_sort(arr, low, pivot_ind - 1, data);

		// переставляем правую часть массива
		// относительно индекса ключевого элемента
		quick_sort(arr, pivot_ind + 1, high, data);

		// если нужна пошаговая печать
#ifdef EVERY_STEP_PRINT
		cout << "\nлевый: " << low << " правый: " << high << " quick sort: ";
		print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
	}
}

// функция позволяет увидеть пошаговую работу
// алгоритма сортировки и выводит число сравнений
// и перестановок
void first_part()
{
	// считывание типа последовательности
	int type_of_seq = input_and_check(1, 3,
		"Выберете способ генерации последовательности:\n\
	1. по возрастанию\n\t2. по убыванию\n\t3. случайная\n",
		"Вводимое значение должно быть 1,2 или 3\n"
	);

	int* arr;		// массив для сортировки
	int* arr_deaf;	// массив с изначальной полседовательностью
	int size = 15;	// размер массивов

	arr = new int[size];	// выделение памяти
	arr_deaf = new int[size];	// выделение памяти

	// генерация последовательности в соответствии с вводом
	switch (type_of_seq)
	{
		// по возрастанию
	case 1:
		f1(arr, 0, size);
		break;

		// по убыванию
	case 2:
		f2(arr, 0, size);
		break;

		// случайная
	case 3:
		randomize_array(arr, 0, size);
		break;
	}

	//print_arr(arr, 0, size);

	// копирование массива. необходимо для вывода
	copy_arr(arr, arr_deaf, 0, size);

	// считывание типа алгоритма сортировки
	int type_of_alg = input_and_check(1, 2,
		"Выберете алгоритм сортировки:\n\
	1. выбором\n\t2. быстрая\n",
		"Вводимое значение должно быть 1 или 2\n"
	);

	// количество сравнений и перестановок
	help_data data = { 0,0 };

	// генерация последовательности в соответствии с вводом
	switch (type_of_alg)
	{
		// по возрастанию
	case 1:
		selection_sort(arr, 0, size, data);
		break;

		// по убыванию
	case 2:
		quick_sort(arr, 0, size, data);
		break;
	}

	// вывод результатов
	cout << "\nНачальный массив: ";
	print_arr(arr_deaf, 0, size);

	cout << "Конечный массив: ";
	print_arr(arr, 0, size);

	cout << "Число сравнений: " << data.num_of_comp;
	cout << "\nЧисло пересылок: " << data.num_of_swap;

	// очистка памяти
	delete[] arr;
	delete[] arr_deaf;
}

/****************************************************************
*                Г Л А В Н А Я   Ф У Н К Ц И Я                  *
****************************************************************/

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	first_part();
	//// для теста сортировки
	//int* arr;
	//int size;

	////cin >> size;
	//size = 15;

	//arr = new int[size];


	//help_data data = { 0,0 };

	////генерация последовательности
	////read_arr(arr, 0, size);
	//randomize_array(arr, 0, size);
	////f1(arr, 0, size);
	////f2(arr, 0, size);
	//print_arr(arr, 0, size);

	//// сортировка
	////selection_sort(arr, 0, size, data);
	//quick_sort(arr, 0, size, data);

	//// вывод
	//cout << setfill('=') << setw(30) << '\n';
	//print_arr(arr, 0, size);

	//cout << "число сравнений: " << data.num_of_comp;
	//cout << "\nчисло пересылок: " << data.num_of_swap;
}


/**************** End Of main.cpp File ***************/