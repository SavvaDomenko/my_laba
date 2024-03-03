#include<iostream>
#include<fstream>
#include<chrono>
#include<time.h>
#include<random>
#include<algorithm>

using namespace std;
//количество точек по x 
const int points = 27;
// массив точек (размеров по х)
const int arrsizes[37] = {100, 200, 300, 400, 500, 600, 700, 800, 900,
							  1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
							  10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,
							  100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000,
							  1000000};

// на рандом заполняем числами
void randomize_array(int arr[], int size, int max)
{
	default_random_engine rng(time(NULL));
	uniform_int_distribution <unsigned > distr(0, max);
	for(int i=0; i<size; i++)
		arr[i] = distr(rng);
}

// простой поиск
int search(int n, int arr[], int size)
{
	for(int i=0; i<size; i++)
	{
		if(arr[i] == n)
			return i;
	}
	return -1; // условие отсутсвия 
}

//бинарный поиск
int bin_search(int n, int arr[], unsigned int size)
{
	int a=0, b=size-1, c = (a+b)/2;

	while(b - a > 1 && size > 1)
	{
		if(arr[c] == n)
			return c;
		else if(arr[c] > n)
			b = c;
		else if(arr[c] < n)
			a = c;

		c = (a + b)/2;

	}
	return -1; // условие отсутсвия 
}

//простой поиск пар
void simple_search(int &index1, int &index2, int arr[], int size, int sum)
{
	bool flag = false;
	for(int i=0; i<size && !flag; i++)
	{
		for(int j=i + 1; j<size && !flag; j++)
		{
			if(arr[i] + arr[j] == sum)
			{
				index1 = i;
				index2 = j;
				flag = true;
                // break;
			}
		}
	}
	cout << index1 << " " << index2 << endl;
}

// поиск по паре с сортированным (улучшенный)
void search2(int &index1, int &index2, int arr[], unsigned int size, int sum)
{
	int i1=0, i2=size-1;
	while(i1 != i2 && size > 1)
	{
		if(arr[i1] + arr[i2] == sum)
		{
			index1 = i1;
			index2 = i2;
            
			break;
		}
		else if(arr[i1] + arr[i2] < sum)
			i1++;
		else if(arr[i1] + arr[i2] > sum)
			i2--;
	}
    cout << arr[i1] << " " << i2 << endl;

}

// ПЕРВОЕ ЗАДАНИЕ
int task1()
{
	auto start = chrono::steady_clock::now(); // начало записи
	auto end = chrono::steady_clock::now(); // конец

	default_random_engine rng(time(NULL)); // в каждый момент разный 

	uniform_int_distribution <unsigned> dist(0, arrsizes[points-1]); // равномерное распределение intов dstr - название переменной 

	ofstream file;
	file.open("data1.csv");

	int* a1 = new int[arrsizes[points-1]];
	int samplesize = 1e3;
	for(int i=0; i<arrsizes[points-1]; i++)
	{
		a1[i] = dist(rng);
	}

	for(int i=0; i<points; i++)
			file << i + 1 << " ";
		file << "\n";

	for(int i=0; i<points; i++)
		file << arrsizes[i] << " ";
	file << "\n";

	//обычный случай простого поиска 
	for (int i = 0; i < points; i++) {
		uniform_int_distribution<int> dstr(0, arrsizes[i]);
		randomize_array(a1, arrsizes[i], arrsizes[i]); // от 0 до N значений N

		start = chrono::steady_clock::now();
		for (int j = 0; j < samplesize; j++) {

			search(dstr(rng), a1, arrsizes[i]);
		}
		end = chrono::steady_clock::now(); //заканчиваем
		file << chrono::duration_cast<chrono::microseconds>(end - start).count()
				<< " ";
	}
	file << "\n";
	//в худшем случае простой поиск (ищет то, чего нет в массиве)
	
	for (int i = 0; i < points; i++) {
		uniform_int_distribution<int> dstr(0, arrsizes[i]);
		randomize_array(a1, arrsizes[i], arrsizes[i]);

		start = chrono::steady_clock::now();
		for (int j = 0; j < samplesize; j++) {
			search(arrsizes[i] + 1, a1, arrsizes[i]);
		}
		end = chrono::steady_clock::now();
		file << chrono::duration_cast<chrono::microseconds>(end - start).count()
				<< " ";
	}
	file << endl;
	sort(a1, a1 + arrsizes[points-1]);
	samplesize = 1e6;

	//бинарный поиск в среднем случае
	for(int i=0; i<points; i++)
	{
		uniform_int_distribution<int> dstr(0, arrsizes[i]);
		start = chrono::steady_clock::now();
		for(int j=0; j<samplesize; j++)
		{
			bin_search(dstr(rng), a1, arrsizes[i]);
		}
		end = chrono::steady_clock::now();
		file << chrono::duration_cast<chrono::microseconds>(end-start).count() << " ";
	}
	file << "\n";
	//бинарный поиск в наихудшем случае
	for(int i=0; i<points; i++)
	{
		uniform_int_distribution<int> dstr(0, arrsizes[i]);
		start = chrono::steady_clock::now();
		for(int j=0; j<samplesize; j++)
		{
			bin_search(-11, a1, arrsizes[i]);
		}
		end = chrono::steady_clock::now();
		file << chrono::duration_cast<chrono::microseconds>(end-start).count() << " ";
	}
	file << "\n";

	file.close();


	return 0;
}

// ВТОРОЕ ЗАДАНИЕ
void task2()
{
	ofstream file;
	file.open("data2.csv");
	// включаем время
	auto start = chrono::steady_clock::now(); // начало записи
	auto end = chrono::steady_clock::now(); // конец

	default_random_engine rng(time(NULL)); // в каждый момент разный 

	uniform_int_distribution<int> dstr(0, arrsizes[points-1]); // равномерное распределение intов dstr - название переменной 

	int* a1 = new int[arrsizes[points-1]]; // создаю массив 

	// заполняем массив до максимального нужного размера массива
	for(int i=0; i<arrsizes[points-1]; i++)
	{
		a1[i] = dstr(rng);
	}


		for(int i=0; i<points; i++)
				file << i + 1 << " "; // записываем в файл (вписываем номер точки)
			file << "\n";

		for(int i=0; i<points; i++)
			file << arrsizes[i] << " "; // записываем в файл значения по х
		file << "\n";

    

	int samplesize = 10; // количество измерений на одну точку

	// измеряет по каждой точке 
	for(int i=0; i<points; i++)
	{
		int a=0, b=0; // 2 индекса для поиска пары

		uniform_int_distribution<int> temp_dstr(0, arrsizes[i]);
		randomize_array(a1, arrsizes[i], arrsizes[i]*2); // заполняет массив размера N значениям от 0 до 2N (прогон)

		start = chrono::steady_clock::now(); //время начало 

		// измеряет время нескольких поисков (усредняем по количеству значений)
		for(int j=0; j<samplesize; j++)
		{
			int rndnum = temp_dstr(rng) + temp_dstr(rng); //увеличиваем рандом
			cout << "!" << rndnum << "! ";
			simple_search(a, b, a1, arrsizes[i], -1); //temp_dstr(rng) * 4 в среднем
		}
		end = chrono::steady_clock::now(); // конец отчета 
//надо одного
		file << chrono::duration_cast<chrono::microseconds>(end-start).count()/ samplesize << " "; // переводим в микросекунды
	}
	file << "\n";
    samplesize = 1000;

        // file.close();
        // file.open("data2.csv", ios_base::app);
	//сортируем для второго поиска ( для улучшенного)
	std::sort(a1, a1 + arrsizes[points-1]);
    
	for(int i=0; i<points; i++)
	{
		int a=0, b=0;

		uniform_int_distribution<int> temp_dstr(0, arrsizes[i]);
		randomize_array(a1, arrsizes[i], arrsizes[i]*2);

		start = chrono::steady_clock::now();
		for(int j=0; j<samplesize; j++)
			search2(a, b, a1, arrsizes[i], -1); // -1 в худшем
		end = chrono::steady_clock::now();
        file.close();
        file.open("data2.csv", ios_base::app);
		file << chrono::duration_cast<chrono::microseconds>(end-start).count() / samplesize << " ";

	}
    
	file.close(); // закрываем (для чистки)
}

void swap(int &a, int &b)
{
	int swap = a;
	a = b;
	b = swap;
}

// ЗАДАНИЕ 3
void task3()
{

	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();

	default_random_engine rng(time(NULL));

	ofstream file;
	file.open("data3.csv");
	file << "0 1 2 3 4" << endl; // хернем столбцы (впринципе безразницы)

	int* a1 = new int[arrsizes[points-1]];
	int* indices = new int[arrsizes[points-1]]; // количество поисков каждого элемента 

	int samplesize = (int)1e6;
	//инциализируем для замеров
	for(int i=0; i<points-1; i++)
	{
		geometric_distribution <unsigned > exp(0.01); // для неравномерного распределения 

		uniform_int_distribution <unsigned > lin(0, arrsizes[i]); // для линейного распределение

		for(int j=0; j<arrsizes[i]; j++)
			a1[j] = j; // заполнили по порядку 
		for(int j=0; j<arrsizes[i]; j++)
		{
			swap(a1[j], a1[lin(rng)]);
			indices[j] = 0; // занулили количество поисков
			//cout << a1[j] << " ";
		}
		//cout << endl;


		// простой поиск
		start = chrono::steady_clock::now();
		int index = 0;
		for(int j=0; j<samplesize; j++)
		{
			index = search(exp(rng), a1, arrsizes[i]);
			indices[index]++;

		}
		end = chrono::steady_clock::now();
		file << arrsizes[i] << " " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " ";

		//найденный элемент заменяется первым А
		start = chrono::steady_clock::now();
		for(int j=0; j<samplesize; j++)
		{
			index = search(exp(rng), a1, arrsizes[i]);
			if(index > -1)
			{
				swap(a1[index], a1[0]);
				indices[index]++;
				swap(indices[index], indices[0]);
			}
		}
		end = chrono::steady_clock::now();

		file << chrono::duration_cast<chrono::microseconds>(end - start).count() << " ";

// заполняем и обнуляем
		for(int j=0; j<arrsizes[i]; j++)
			a1[j] = j;
		for(int j=0; j<arrsizes[i]; j++)
		{
			swap(a1[j], a1[lin(rng)]);
			indices[j] = 0;
		}

		//найденный элемент заменяется предыдущим Б
		start = chrono::steady_clock::now();
		for(int j=0; j<samplesize; j++)
		{
			int index = search(exp(rng), a1, arrsizes[i]);
			if(index > 0)
				swap(a1[index], a1[index-1]);
			indices[index]++;
			swap(indices[index], indices[index-1]);
		}
		end = chrono::steady_clock::now();

		file << chrono::duration_cast<chrono::microseconds>(end - start).count() << " ";

		for(int j=0; j<arrsizes[i]; j++)
			a1[j] = j;
		for(int j=0; j<arrsizes[i]; j++)
		{
			swap(a1[j], a1[lin(rng)]);
			indices[j] = 0;
		}

		//найденный элемент заменяется предыдущим, если это более вероятно 
		start = chrono::steady_clock::now();
		for(int j=0; j<samplesize; j++)
		{
			int index = search(exp(rng), a1, arrsizes[i]);
			if(index > 0 && indices[index] > indices[index-1])
			{
				swap(a1[index], a1[index-1]);
				indices[index]++;
				swap(indices[index], indices[index-1]);
			}
			else
				indices[index]++;
		}
		end = chrono::steady_clock::now();

		file << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
}
	file.close();


}

int main()
{
	task2();
}
