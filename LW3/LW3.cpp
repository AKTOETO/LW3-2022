/***********************************************************************\
*                    кафедра № 304 2 курс 3 семестр информатика			*
*-----------------------------------------------------------------------*
*	Project type : solution												*
*	Project name : matrix												*
*	File name    : matrix.cpp											*
*	Language     : c/c++												*
*	Programmers  : Плоцкий Б.А. Раужев Ю. М.							*
*	Created      :  19/10/22											*
*	Last revision:  24/10/22											*
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
#include <chrono>

using namespace std;

/********************************
*			ДЛЯ КОНСОЛИ			*
********************************/

// убрать комментарий, если нужна
// пошаговая печать массивов
// РАСКОММЕНТИРОВАТЬ ДЛЯ ПЕРВОГО ЭТАПА
#define EVERY_STEP_PRINT

// количество таблиц в консоли
#define NUMB_OF_TABLES 5

// заполнение len элементов элементом symb
#define OUT_W(symb, len) fixed << setfill(symb) << setw(len)

/********************************
*			ДЛЯ МАССИВА			*
********************************/

#ifdef EVERY_STEP_PRINT
// ЕСЛИ НУЖНА ПЕЧАТЬ КАЖДОГО ШАГА
// минимальное и максимальное значение
// для чисел в массиве
#define MIN_VALUE 10
#define MAX_VALUE 20

// минимальный и максимальный
// размер массива
#define MIN_ARR_SIZE 10
#define MAX_ARR_SIZE 15

#else
// ЕСЛИ НЕ НУЖНА ПЕЧАТЬ КАЖДОГО ШАГА
// минимальное и максимальное значение
// для чисел в массиве
#define MIN_VALUE 10
#define MAX_VALUE 20000

// минимальный и максимальный
// размер массива
#define MIN_ARR_SIZE 1000
#define MAX_ARR_SIZE 500000
#endif

/********************************
*	ДЛЯ ПОСЛЕДОВАТЕЛЬНОСТЕЙ		*
********************************/

// шаг чисел при генерации последовательности
#define STEP 1

// максимальное значение при генерации чисел
// для упорядоченных последовательностей
#define MAX_GENERATE MAX_VALUE

// необходима для хранения значений 
// сравнений и перемещений
struct help_data
{
	unsigned long long num_of_comp;	// число сравнений
	unsigned long long num_of_swap;	// число перемещений
};

// тип данных TTIME
typedef chrono::milliseconds TTIME;

/****************************************************************
*              П Р О Т О Т И П Ы   Ф У Н К Ц И Й                *
****************************************************************/

/****************************************************************
*         В С П О М О Г А Т Е Л Ь Н Ы Е  Ф У Н К Ц И Й          *
****************************************************************/

// возвращение случайного значения из 
// интервала (min, max)
template<typename T = int>
T rand_num(T min, T max);

// копирование массива
template<typename T = int>
void copy_arr(
	T* source,	// источник данных
	T* target,	// место копирования данных
	int low,	// индекс начального элемента
	int high	// индекс элемента после последнего
);

// печать массива в поток
template<typename T = int>
void print_arr(
	T* arr,					// массив
	int low = 0,			// индекс, с которого начинается вывод
	int high = 1,			// индекс, на котром кончается вывод
	ostream& stream = cout	// поток вывода
);

// ввод и проверка значений
template<typename T = int>
T input_and_check(T _min, T _max,
	const char* welcome_str, const char* err_str);

/****************************************************************
*	Г Е Н Е Р А Ц И Я   П О С Л Е Д О В А Т Е Л Ь Н О С Т Е Й	*
****************************************************************/

// упорядочная функция по возрастанию
template<typename T = int>
void f1(T* arr, int low, int high);

// упорядочная функция по убыванию
template<typename T = int>
void f2(T* arr, int low, int high);

// рандомизация значений массива
template<typename T = int>
void randomize_array(T* arr, int low, int high);

// чтение массива
template<typename T = int>
void read_arr(T* arr, int low, int high);

//функция измерения времени работы другой функции
template<typename T>
TTIME measure_time(
	T* arr,				// исходный массив
	int size,			// размер массива
	help_data& data,	//количество сравнений и премещений
	void(*sort_funcs)(
		T* arr,			// массив
		int low,		// индекс, с которого начинается вывод
		int high,		// индекс, на котром кончается вывод
		help_data& data	// количество сравнений и премещений
		)
);

// создание массива с помощю определенной функции
template<typename T>
void generate_arr(
	T*& arr,			// массив
	int size,			// размер массива
	int ind_of_gen_func	// индекс функции генерации массива
);

// сортирует, выводит массив
template<typename T>
void draw_table(
	T* arr,			// массив
	int size,			// размер массива
	int ind_of_gen_func	// индекс функции генерации массива
);
/****************************************************************
*				C О Р Т И Р О В К А   В Ы Б О Р О М				*
****************************************************************/

template<typename T = int>
void selection_sort(
	T* arr,			// массив
	int low,		// индекс, с которого начинается вывод
	int high,		// индекс, на котором кончается вывод
	help_data& data	// количество сравнений и премещений
);

/****************************************************************
*				Б Ы С Т Р А Я   С О Р Т И Р О В К А				*
****************************************************************/

// функция перераспределяющая элементы 
template<typename T = int>
int partition(
	T* arr,			// массив
	int low,		// индекс, с которого начинается вывод
	int high,		// индекс, на котром кончается вывод
	help_data& data	// количество сравнений и премещений
);

// быстрая сортировка
// не работает с массивом, 
// размер которого >= 4000
template<typename T = int>
void quick_sort(
	T* arr,			// массив
	int low,		// индекс, с которого начинается вывод
	int high,		// индекс, на котром кончается вывод
	help_data& data	// количество сравнений и премещений
);

// быстрая сортировка, которая
// работает с большими размерами массивов
template<typename T = int>
void improved_quick_sort(
	T* arr,			// массив
	int low,		// индекс, с которого начинается вывод
	int high,		// индекс, на котром кончается вывод
	help_data& data	// количество сравнений и премещений
);

/****************************************************************
*				О С Н О В Н Ы Е   Ф У Н К Ц И И 				*
****************************************************************/


// функция позволяет увидеть пошаговую работу
// алгоритма сортировки и выводит число сравнений
// и перестановок
void first_part();

// функция генерирует массивы разными размерами
// и сортирует их двумя алгоритмами сортировки
void second_part();

/****************************************************************
*					   К О Н С Т А Н Т Ы						*
****************************************************************/

// массив функций генерации последовательности
template<typename T = int>
void(*gen_funcs[])(T* arr, int low, int high) =
{
	f1,
	f2,
	randomize_array,
	read_arr
};

// названия функций генерации
const char gen_f_names[4][12] = {
	"возрастание",
	"убывание",
	"случайная",
	"чтение"
};

// массив функций сортировки
template<typename T = int>
void(*sort_funcs[])(T* arr, int low, int high, help_data& data) =
{
	selection_sort,
	//quick_sort
	improved_quick_sort
};

// названия функций сортировки
const char sort_f_names[2][8] = {
	"выбором",
	"быстрая"
};

/****************************************************************
*                Г Л А В Н А Я   Ф У Н К Ц И Я                  *
****************************************************************/

int main()
{
	// установка русского языка в консоли
	setlocale(LC_ALL, "ru");

	// инициализация генератора случайных чисел
	srand(time(NULL));

	// выполнение первого этапа
	first_part();

	// выполнение второго этапа
	second_part();

	return 0;
}

/****************************************************************
*              Р Е А Л И З А Ц И Я   Ф У Н К Ц И Й              *
****************************************************************/

/****************************************************************
*         В С П О М О Г А Т Е Л Ь Н Ы Е  Ф У Н К Ц И Й          *
****************************************************************/

// возвращение случайного значения из 
// интервала (min, max)
template<typename T = int>
T rand_num(T min, T max)
{
	return rand() % (max - min) + min;
}

// копирование массива
template<typename T = int>
void copy_arr(
	T* source,	// источник данных
	T* target,	// место копирования данных
	int low,	// индекс начального элемента
	int high	// индекс элемента после последнего
)
{
	for (int i = low; i < high; i++)
	{
		target[i] = source[i];
	}
}

// печать массива в поток
template<typename T = int>
void print_arr(
	T* arr,			// массив
	int low,		// индекс, с которого начинается вывод
	int high,		// индекс, на котром кончается вывод
	ostream& stream	// поток вывода
)
{
	// вывод элементов массива
	for (int i = low; i < high; i++)
	{
		stream << arr[i] << ' ';
	}
	stream << '\n';
}

// ввод и проверка значений
template<typename T = int>
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

//функция измерения времени работы другой функции
template<typename T>
TTIME measure_time(
	T* arr,
	int size,
	help_data& data,
	void(*sort_funcs)(
		T* arr,
		int low,
		int high,
		help_data& data
		)
)
{
	// начало отсчета времени
	auto begin = chrono::steady_clock::now();

	// вызов функции сортировки
	sort_funcs(arr, 0, size, data);

	// конец отсчета времени
	auto end = chrono::steady_clock::now();

	return chrono::duration_cast<TTIME>(end - begin);
}

// создание массива с помощю определенной функции
template<typename T>
void generate_arr(T*& arr, int size, int ind_of_gen_func)
{
	// удаление массива
	if (arr != nullptr)
		delete[] arr;

	// выделение памяти
	arr = new T[size];

	// генерация последовательности
	gen_funcs<T>[ind_of_gen_func](arr, 0, size);
}

// сортирует, выводит массив
template<typename T>
void draw_table(T* arr, int size, int ind_of_gen_func)
{
	// количество сравнений и перестановок
	help_data data = { 0,0 };

	// отрисовка шапки таблицы
	cout << OUT_W('_', 84) << '\n';
	cout << "|_ф._генерации_|_ф._сортировки_|_размер_|_время_(мс)_|__сравнения__|_перестановки_|\n";

	// сортировка и вывод таблицы
	for (int ind_of_sort_func = 0; ind_of_sort_func < 2; ind_of_sort_func++)
	{
		// создание копии массива
		T* arr_copy = new T[size];
		copy_arr(arr, arr_copy, 0, size);

		// измерение времени работы функции
		TTIME elapsed_time = measure_time(arr_copy, size, data, sort_funcs<T>[ind_of_sort_func]);

		// вывод строки таблицы
		cout << "| " << OUT_W(' ', 12) << gen_f_names[ind_of_gen_func]
			<< " | " << OUT_W(' ', 13) << sort_f_names[ind_of_sort_func]
			<< " | " << OUT_W(' ', 6) << size
			<< " | " << OUT_W(' ', 10) << elapsed_time.count()
			<< " | " << OUT_W(' ', 11) << data.num_of_comp
			<< " | " << OUT_W(' ', 12) << data.num_of_swap
			<< " |\n";
		data = { 0,0 };

		delete[] arr_copy;
	}
	cout << OUT_W('-', 84) << '\n';
}

/****************************************************************
*	Г Е Н Е Р А Ц И Я   П О С Л Е Д О В А Т Е Л Ь Н О С Т Е Й	*
****************************************************************/

// упорядочная функция по возрастанию
template<typename T = int>
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
template<typename T = int>
void f2(T* arr, int low, int high)
{
	//k, b - коэффициенты прямой
	T k = MAX_GENERATE / (STEP * (high - low + 1));
	T b = 0;
	double x = high - low - 1; // координата x

	// заполнение массива 
	for (int i = low; i < high; i++, x -= STEP)
	{
		arr[i] = x * k + b;
	}
}

// рандомизация значений массива
template<typename T = int>
void randomize_array(T* arr, int low, int high)
{
	for (int i = low; i < high; i++)
	{
		arr[i] = rand_num(MIN_VALUE, MAX_VALUE);
	}
}

// чтение массива
template<typename T = int>
void read_arr(T* arr, int low, int high)
{
	for (int i = low; i < high; i++)
	{
		cin >> arr[i];
	}
}

/****************************************************************
*				C О Р Т И Р О В К А   В Ы Б О Р О М				*
****************************************************************/

template<typename T = int>
void selection_sort(T* arr, int low, int high, help_data& data)
{
#ifdef EVERY_STEP_PRINT
	cout << "\tдо    изменений: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT

	// проходимся по всем элементам массива
	// кроме последнего, он уже будет в
	// нужном порядке, когда мы дойдем до него
	for (int i = low; i < high - 1; i++)
	{
		// индекс наименьшего элемента
		int smallestIndex = i;

		// ищем еще более меньший элемент,
		// чем под индексом smallestIndex
		for (int j = i + 1; j < high; j++)
		{
			// если был найден элемент,
			// который меньше элемента под
			// индексом smallestIndex, то
			// обновляем smallestIndex
			data.num_of_comp++;
			if (arr[j] < arr[smallestIndex])
			{
				smallestIndex = j;
			}
		}

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
}

/****************************************************************
*				Б Ы С Т Р А Я   С О Р Т И Р О В К А				*
****************************************************************/

// функция перераспределяющая элементы 
template<typename T = int>
int partition(T* arr, int low, int high, help_data& data)
{
#ifdef EVERY_STEP_PRINT
	cout << "\nлевый: " << low << " правый: " << high << " partition: \n";
	cout << "\tдо    изменений: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT

	// индекс, в которм в конце алгоритма
	// окажется опорный элемент
	int out_pivot_ind = low;

	// опорный элемент
	T pivot = arr[high - 1];

	for (int i = low; i < high - 1; i++)
	{

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
			cout << "\t" << setfill(' ') << setw(3) << i - low << " с "
				<< setfill(' ') << setw(2) <<
				(out_pivot_ind == 0 ? out_pivot_ind : out_pivot_ind - 1) - low
				<< " индекс: ";
			print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
		}
	}

	// ставим опорный элемент в позицию out_pivot_ind
	data.num_of_swap++;
	swap(arr[out_pivot_ind], arr[high - 1]);

	// пошаговая печать
#ifdef EVERY_STEP_PRINT
	cout << "\t" << setfill(' ') << setw(3) << high - 1 << " с "
		<< setfill(' ') << setw(2) <<
		(out_pivot_ind == 0 ? out_pivot_ind : out_pivot_ind)
		<< " индекс: ";
	print_arr(arr, low, high);

	cout << "\tпосле  изменен.: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
	return out_pivot_ind;
}

// быстрая сортировка
// не работает с массивом, 
// размер которого >= 4000
template<typename T = int>
void quick_sort(T* arr, int low, int high, help_data& data)
{
#ifdef EVERY_STEP_PRINT
	cout << "\nлевый: " << low << " правый: " << high << "\n";
	cout << "\tдо    изменений: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
	// если минимальный индекс меньше максимального
	if (low < high)
	{
		// переставляем элементы относительно 
		// определенного индекса, возвращаем
		// этот индекс
		int pivot_ind = partition(arr, low, high, data);

		// переставляем левую часть массива
		// относительно индекса ключевого элемента
		quick_sort(arr, low, pivot_ind, data);

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

// быстрая сортировка, которая
// работает с большими размерами массивов
template<typename T = int>
void improved_quick_sort(T* arr, int low, int high, help_data& data)
{
#ifdef EVERY_STEP_PRINT
	cout << "\nлевый: " << low << " правый: " << high << "\n";
	cout << "\tдо    изменений: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT

	// индекс числа слева от ключевого
	int left = low;
	// индекс числа справа от ключевого
	int right = high - 1;
	// ключевое число
	T key = arr[(left + right) / 2];

	// переставляем элементы в массиве
	while (left <= right)
	{
		// двигаем индекс левого числа вправо
		// если число под левым индексом 
		// меньше ключевого элемента
		while (arr[left] < key)
		{
			data.num_of_comp++;
			left++;
		}
		data.num_of_comp++;

		// двигаем индекс правого числа влево
		// если число под правым индексом 
		// больше ключевого элемента
		while (arr[right] > key)
		{
			data.num_of_comp++;
			right--;
		}
		data.num_of_comp++;

		// если индекс левого числа <= 
		// индексу правого, то меняем
		// значения под этими индексами
		// и сдвигаем иба индекса к центру
		// отрезка (low, high)
		if (left <= right)
		{
			swap(arr[left], arr[right]);
			data.num_of_swap++;
#ifdef EVERY_STEP_PRINT
			cout << "\t" << setfill(' ') << setw(3) << left - low << " с "
				<< setfill(' ') << setw(2) << right - low << " индекс: ";
			print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT
			left++;
			right--;
		}
		data.num_of_comp++;
	}

	// пошаговая печать
#ifdef EVERY_STEP_PRINT
	cout << "\tпосле  изменен.: ";
	print_arr(arr, low, high);
#endif // EVERY_STEP_PRINT

	// если правый индекс не дошел до
	// начала отрезка (low, high)
	if (right > low)
	{
		improved_quick_sort(arr, low, right + 1, data);
	}

	// если левый индекс не дошел до
	// конца отрезка (low, high)
	if (left < high)
	{
		improved_quick_sort(arr, left, high, data);
	}
}

/****************************************************************
*				О С Н О В Н Ы Е   Ф У Н К Ц И И 				*
****************************************************************/

// функция позволяет увидеть пошаговую работу
// алгоритма сортировки и выводит число сравнений
// и перестановок
void first_part()
{
	cout << OUT_W('=', 27) << '\n';
	cout << "||\tПЕРВЫЙ ЭТАП" << "\t||\n";
	cout << OUT_W('=', 27) << '\n';

	// считывание типа последовательности
	int type_of_gen = input_and_check(1, 3,
		"Выберете способ генерации последовательности:\n\
	1. по возрастанию\n\t2. по убыванию\n\t3. случайная\n",
		"Вводимое значение должно быть 1,2 или 3\n"
	);

	int* arr = nullptr;		// массив для сортировки
	int* arr_deaf = nullptr;	// массив с изначальной полседовательностью
	int size = 15;	// размер массивов

	// создание массива с полседовательностью
	generate_arr(arr, size, type_of_gen - 1);

	arr_deaf = new int[size];	// выделение памяти

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
	sort_funcs<int>[type_of_alg - 1](arr, 0, size, data);

	// вывод результатов
	cout << "\nНачальный массив: ";
	print_arr(arr_deaf, 0, size);

	cout << "Конечный  массив: ";
	print_arr(arr, 0, size);

	cout << "Число  сравнений: " << data.num_of_comp << '\n';
	cout << "Число  пересылок: " << data.num_of_swap << "\n\n\n";

	// очистка памяти
	delete[] arr;
	delete[] arr_deaf;
}

// функция генерирует массивы разными размерами
// и сортирует их двумя алгоритмами сортировки
void second_part()
{
	cout << OUT_W('=', 27) << '\n';
	cout << "||\tВТОРОЙ ЭТАП" << "\t||\n";
	cout << OUT_W('=', 27) << '\n';

	// считывание генерирующей функции
	int ind_of_gen_func = input_and_check(1, 4,
		"Введите номер генерирующей функции:\n\
	1. по возрастанию\n\t2. по убыванию\n\t3. случайная\n",
		"Значения должны быть 1, 2 или 3\n"
	);
	// индексы должны начинаться с 0
	ind_of_gen_func--;

	// массив для последовательности
	unsigned int* arr = nullptr;

	// выполняем генерацию массива и
	// выполняем сортировки
	for (
		int size = MIN_ARR_SIZE; size <= MAX_ARR_SIZE;
		size += (MAX_ARR_SIZE - MIN_ARR_SIZE) / (NUMB_OF_TABLES - 1)
		)
	{
		// генерация массива
		generate_arr(arr, size, ind_of_gen_func);

		// печать таблицы
		draw_table(arr, size, ind_of_gen_func);
	}
}

/**************** End Of main.cpp File ***************/