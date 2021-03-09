#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Countries
{
	string name;
	unsigned long long int population;
};
int ReadFile(Countries list[], ifstream& file){
	string CurrentLine;
	int index = 0;
	while (!file.eof()) {
		getline(file, CurrentLine);
		list[index].name = CurrentLine;
		getline(file, CurrentLine);
		list[index].population = stoll(CurrentLine);
		getline(file, CurrentLine);
		index++;
	}
	return index;
}
void WriteList(Countries list[], int N) {
	for (int i = 0; i < N; i++) {
		cout << "\nНазвание страны: " << list[i].name << "\nЧисленность населения: " << list[i].population << endl;
	}
}
void ShellSort(Countries list[], int N) {
	int j;
	Countries replace;
	bool flag;
	for (int step = N / 2; step > 0; step /= 2) {
		for (int i = step; i < N; i++) {
			replace = list[i];
			j = i;
			flag = false;
			while ((j >= step)&&(flag==false)) {
				if (replace.population > list[j-step].population) {
					list[j] = list[j - step];
				}
				else {
					flag = true;
					list[j] = replace;
				}
				j -= step;
			}
			if (flag == false) {
				list[j] = replace;
			}
		}
	}
}
void HoaraSort(Countries list[], int left, int right) {
	Countries replace;
	int i = left, j = right, mid = list[(left + right) / 2].population;
	do {
		while (list[i].population > mid) {
			i++;
		}
		while (list[j].population < mid) {
			j--;
		}
		if (i <= j) {
			replace = list[i];
			list[i] = list[j];
			list[j] = replace;
			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) {
		HoaraSort(list, left, j);
	}
	if (right > i) {
		HoaraSort(list, i, right);
	}
};
void SwitchSortingMethod(Countries list[], int N) {
	int MethodNumber = -1;
	string otvet = "Да";
	while (otvet != "Нет") {
		cout << "\nВведите номер метода быстрой сортировки\n\n0 - метод сортировки Шелла\n1 - метод сортировки Хоара\n\nВаш выбор: ";
		cin >> MethodNumber;
		switch (MethodNumber) {
		case (0):
			ShellSort(list, N);
			cout << "\nМножество отсортированное методом Шелла\n";
			WriteList(list, N);
			break;
		case (1):
			HoaraSort(list,0,N-1);
			cout << "\nМножество отсортированное методом Хоара\n";
			WriteList(list, N);
			break;
		default: cout << "\nВведён не номер метода поиска!\n";
			break;
		}
		cout << "\nХотите продолжить работу программы? (Да/Нет)\n\nВаш ответ: ";
		cin >> otvet;
	}
};
void RecordFile(Countries list[], ofstream& file, int N) {
	for (int i = 0; i < N; i++) {
		file << "Название страны: " << list[i].name << "\nЧисленность населения: " << list[i].population << "\n\n";
	}
};
int main() 
{
	system("chcp 1251");
	ifstream inputfile("F1.txt");
	if (inputfile.is_open()) {
		Countries list[100];
		int quantity = ReadFile(list, inputfile);
		cout << "\nКол-во элемнтов в множестве = " << quantity << "\n\nМножество\n";
		inputfile.close();
		WriteList(list,quantity);
		SwitchSortingMethod(list,quantity);
		ofstream outputfile("F2.txt");
		RecordFile(list, outputfile, quantity);
		outputfile.close();
	}
	else {
		cout << "Ошибка! Не удалось откыть файл F1.txt\n";
	}
	system("pause");
}