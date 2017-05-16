#include "main.h"
#include "Hash.h"
#include "Random.h"

#include <iostream>
#include <thread>
#include <csignal>
#include <unistd.h>

using namespace std;

static hash_t target;           // Хэш, коллизию для которого надо найти
static uint_fast64_t counter;   // Счётчик посчитанных хэшей для статистики
static bool done;               // Флаг остановки вычислений

// Обработчик сигналов ОС
void signalHandler(int signum)
{
	cout << "\nSignal (" << signum << ") received" << endl;
	if (signum == SIGTRAP)
		cout << "Hashes tested: " << counter << endl;
	else
		done = true;
}

// Поиск коллизии по хэшу заданной строки
void bruteforce()
{
	Random rnd;             // ГПСЧ для заполнения буфера
	Buffer buffer;          // Буфер, заполняемый рандомными числами
	do
	{
		if (done)           // Если нашли коллизию где-то в другом потоке,
			return;         // Завершаем поток
		
		rnd.fill(&buffer);                     // Рандомно заполняем буфер
		counter++;
	}
	// Считаем хэш от буфера и проверяем на совпадение с требуемым
	while (target != Hash::calc(buffer.buf));   // Повторяем, пока хэши не совпадут
	
	// Нашли коллизию, сообщим об этом
	done = true;            // Установим флаг, чтобы завершить остальные потоки
	cout << endl << "Found collision: ";
	buffer.print();         // Выводим рандомный буфер, который привёл к коллизии
}

// Поиск коллизии по таблицам
void findPair()
{
	Random rnd;             // ГПСЧ для заполнения буфера
	// Таблицы "паролей" и их "подделок"
	Table *left  = new Table[TABLE_SIZE];
	Table *right = new Table[TABLE_SIZE];
	do
	{
		// Генерация таблиц
		for (size_t i = 0; i < TABLE_SIZE; ++i)
		{
			if (done)
				break;
			
			// Генерируем пароль и его подделку
			rnd.fill(&(left[i].b));
			rnd.fill(&(right[i].b));
			
			// Считаем хэши от них
			left[i].h = Hash::calc(left[i].b.buf);
			right[i].h = Hash::calc(right[i].b.buf);
			
			counter += 2;
		}
		
		// Поиск коллизии по таблицам
		for (size_t i = 0; i < TABLE_SIZE; ++i)
			for (size_t j = 0; j < TABLE_SIZE; ++j)
			{
				if (done)       // Если нашли коллизию где-то в другом потоке,
				{
					delete left, right; // Освобождаем память
					return;             // Завершаем поток
				}
				
				if (left[i].h == right[j].h)  // Нашли коллизию?
				{
					cout << endl << "Hit" << endl;
					if (left[i].b == right[j].b)    // Если совпали значения буферов,
						continue;                   // То не нашли
					
					// Нашли коллизию, сообщим об этом
					done = true;    // Установим флаг, чтобы завершить остальные потоки
					cout << endl << "Found collision \"hash -> src1 : src2\":" << endl;
					
					Hash::print(left[i].h);
					cout << " -> ";
					
					left[i].b.print();
					cout << " : ";
					
					right[j].b.print();
					cout << endl;
				}
			}
	}
	while (!done);
}

int main()
{
	// Регистрируем обработчики сигналов ОС
	signal(SIGINT, signalHandler);
	signal(SIGTRAP, signalHandler);
	
	int mode = 0;
	cout << "Choose mode:" << endl
	     << "1. Bruteforce" << endl
	     << "2. Find pair by table" << endl
	     << "0. Exit" << endl;
	cin >> mode;
	
	done = false;
	counter = 0;
	
	time_t start;
	thread t[THREAD_COUNT];
	
	switch (mode)
	{
		case 1: // Поиск коллизии по заданной строке
		{
			string str;
			cout << "Enter string to find collision:" << endl;
			cin >> str;
			
			target = Hash::calc((u_char *)str.c_str());
			
			cout << "Target hash: ";
			Hash::println(target);
			cout << "Searching for collision..." << endl;
			
			start = time(0);
			
			for (size_t i = 0; i < THREAD_COUNT; ++i)
				t[i] = thread(bruteforce);
			break;
		}
		case 2: // Поиск коллизии по таблицам "паролей" и их "подделок"
			cout << "Searching for password pair that makes collision..." << endl;
			
			start = time(0);
			
			for (size_t i = 0; i < THREAD_COUNT; ++i)
				t[i] = thread(findPair);
			break;
			
		default:
			return 0;
	}
	
	cout << "PID = " << ::getpid() << endl;
	t[0].join();
	
	printf("\nTime elapsed: %lds\nTotal hashes tested: %ld\n", time(0) - start, counter);
	return 0;
}