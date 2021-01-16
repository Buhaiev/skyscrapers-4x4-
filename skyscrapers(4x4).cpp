// skyscrapers(4x4).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

std::vector<std::array<int, 4>>permutationsVector = {};
int actions = 0;
void permut(std::array<int, 4> nums, int level) {
	if (level < 2) {
		for (int i = level; i < 4; i++) {
			actions++;

			int temp = nums[level];
			nums[level] = nums[i];
			nums[i] = temp;

			permut(nums, level + 1);

			temp = nums[level];
			nums[level] = nums[i];
			nums[i] = temp;
		}
	}
	else if (level == 2) {
		actions++;

		permutationsVector.push_back(nums);

		int temp = nums[2];
		nums[2] = nums[3];
		nums[3] = temp;

		permutationsVector.push_back(nums);

		temp = nums[2];
		nums[2] = nums[3];
		nums[3] = temp;
	}
}

bool lineChecker(std::array<int,4> arr, int clue) {
	int ans = 1;
	int max = arr[0];
	for (int i = 1; i < 4; i++) {
		if (arr[i] > max) {
			ans++;
			max = arr[i];
		}
	}
	/*for (int i = 0; i < 4; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << "    " << ans << " ";*/
	return ans == clue;
}

bool isCorrect(int pos, int clue, std::array<std::array<int, 4>,4> items) {
	std::array<int, 4> arr;
	if (pos < 4) {
		for (int i = 0; i < 4; i++) {
			actions++;
			arr[i] = items[i][pos];
		}
	}
	else if (pos < 8) {
		for (int i = 3; i >= 0; --i) {
			actions++;
			//std::cout<<i<<" ";
			arr[3 - i] = items[pos % 4][i];
		}
	}
	else if (pos < 12) {
		for (int i = 3; i >= 0; --i) {
			actions++;
			//std::cout<<i<<" ";
			arr[3 - i] = items[i][3 - pos % 4];
		}
	}
	else if (pos <= 15) {
		for (int i = 0; i < 4; i++) {
			actions++;
			arr[i] = items[3 - pos % 4][i];
		}
	}
	return lineChecker(arr, clue);
}

bool checkAll(int* clues, std::array<std::array<int, 4>,4> items) {
	for (int i = 0; i < 16; i++) {
		actions++;
		if (clues[i] == 0) continue;
		else if (!(isCorrect(i, clues[i], items))) {
			return false;
		}
	}
	return true;
}

bool checkForUsability(std::array<std::array<int, 4>, 4> arr, int level) {
	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < level-1; j++) {
			for (int k = j + 1; k < level; k++) {
				//actions++;
				if (arr[j][i] == arr[k][i]) {
					return false;
				}
			}
		}

	}
	return true;
}

int main()
{
	int* clues = new int[16]{ 0, 0, 1, 2,
							  0, 2, 0, 0,
							  0, 3, 0, 0,
							  0, 1, 0, 0 };
	std::array<int,4> nums { 1,2,3,4 };
	permut(nums, 0);
	std::cout << actions << std::endl;

	std::array<std::array<int, 4>, 4> myArray;
	for (int i = 0; i < 4; i++) {
		myArray[i] = permutationsVector[0];
	}

	for (int a = 0; a < permutationsVector.size(); a++) {
		actions++;
		myArray[0] = permutationsVector[a];
		for (int b = 0; b < permutationsVector.size(); b++) {
			//actions++;
			myArray[1] = permutationsVector[b];
			if (!checkForUsability(myArray, 2)) continue;
			for (int c = 0; c < permutationsVector.size(); c++) {
				//actions++;
				myArray[2] = permutationsVector[c];
				if (!checkForUsability(myArray, 3)) continue;
				for (int d = 0; d < permutationsVector.size(); d++) {
					//actions++;
					myArray[3] = permutationsVector[d];
					if (checkForUsability(myArray,4)) {
						if (checkAll(clues, myArray)) {
							int** ans = new int*[4];
							for (int i = 0; i < 4; i++) {
								ans[i] = new int[4];
								for (int j = 0; j < 4; j++) {
									ans[i][j] = myArray[i][j];
									std::cout << ans[i][j] << " ";
								}
								std::cout << std::endl;
							}
						}

					}
				}
			}
		}
	}
	std::cout << actions << std::endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
