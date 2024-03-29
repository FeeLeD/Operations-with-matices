// CPractice2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math.h"
#include "iostream"
#include "time.h"

using namespace std;

void show_array(int array[3][3])
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}

void fill_array(int array[3][3])
{
	cout << endl;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> array[i][j];
		}
	}
}

void matrix_addition(int first_array[3][3], int second_array[3][3])
{
	int result_array[3][3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result_array[i][j] = first_array[i][j] + second_array[i][j];
		}
	}

	show_array(result_array);
}

int solve_element(int first_array[3][3], int second_array[3][3], int string, int column)
{
	int result = 0;
	for (int i = 0; i < 3; i++) {
		result += (first_array[string][i] * second_array[i][column]);
	}
	return result;
}

void matrix_multiplication(int first_array[3][3], int second_array[3][3])
{
	int result_array[3][3];
	int result = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result_array[i][j] = solve_element(first_array, second_array, i, j);
		}
	}
	show_array(result_array);
}

void show_any_array(int **matrix, int dimensionality)
{
	for (int i = 0; i < dimensionality; i++) {
		for (int j = 0; j < dimensionality; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int** matrix_creation(int dimensionality)
{
	int** matrix = new int*[dimensionality];
	for (int count = 0; count < dimensionality; count++)
		matrix[count] = new int[dimensionality];

	for (int i = 0; i < dimensionality; i++) {
		for (int j = 0; j < dimensionality; j++) {
			matrix[i][j] = rand() % 10 + 1;
		}
	}
	return matrix;
}

int solve_minor(int **minor)
{
	int main_sum = 0;
	int side_sum = 0;

	int main_diagonal[3];
	main_diagonal[0] = minor[0][1] * minor[1][2] * minor[2][0];
	main_diagonal[1] = minor[0][0] * minor[1][1] * minor[2][2];
	main_diagonal[2] = minor[1][0] * minor[2][1] * minor[0][2];
	for each (int e in main_diagonal) {
		main_sum += e;
	}

	int side_diagonal[3];
	side_diagonal[0] = minor[0][1] * minor[1][0] * minor[2][2];
	side_diagonal[1] = minor[0][2] * minor[1][1] * minor[2][0];
	side_diagonal[2] = minor[1][2] * minor[2][1] * minor[0][0];
	for each (int e in side_diagonal) {
		side_sum += e;
	}

	int result = main_sum - side_sum;

	return result;
}

int solve_square_determinant(int **minor)
{
	return (minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0]);
}

int** minor_creation(int **matrix, int size, int skip_str, int skip_column)
{
	int new_dimensionality = size - 1;
	int** result_matrix = new int*[new_dimensionality];
	for (int count = 0; count < new_dimensionality; count++) {
		result_matrix[count] = new int[new_dimensionality];
	}
	for (int k = 0, i = 0; i < size; i++, k++) {
		if (i == skip_str) {
			k--;
			continue;
		}
		for (int m = 0, j = 0; j < size; j++, m++) {
			if (j == skip_column) {
				m--;
				continue;
			}
			result_matrix[k][m] = matrix[i][j];
		}
	}
	return result_matrix;
}

int find_determinant(int **matrix, int dimensionality)
{
	int determinant = 0;
	int new_size = dimensionality - 1;

	if (dimensionality == 1)
		return matrix[0][0];

	if (dimensionality == 2)
		return solve_square_determinant(matrix);

	int** minor = new int*[new_size];
	for (int count = 0; count < new_size; count++)
		minor[count] = new int[new_size];

	for (int i = 0; i < dimensionality; i++) {
		minor = minor_creation(matrix, dimensionality, 0, i);
		determinant += (pow(-1, i) * matrix[0][i] * find_determinant(minor, new_size));
	}

	return determinant;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	int first_array[3][3];
	int second_array[3][3];

	cout << "Введите элементы первой матрицы: ";
	fill_array(first_array);
	cout << "Введите элементы второй матрицы: ";
	fill_array(second_array);
	cout << "Первая матрица:" << endl;
	show_array(first_array);
	cout << "Вторая матрица:" << endl;
	show_array(second_array);
	cout << "Сумма матриц:" << endl;
	matrix_addition(first_array, second_array);
	cout << "Произведение матриц:" << endl;
	matrix_multiplication(first_array, second_array);

	cout << "Введите размерность матрицы: ";
	int dimensionality;
	cin >> dimensionality;

	int** matrix = new int*[dimensionality];
	for (int count = 0; count < dimensionality; count++)
		matrix[count] = new int[dimensionality];

	matrix = matrix_creation(dimensionality);

	show_any_array(matrix, dimensionality);
	cout << "Определитель матрицы равен: " << find_determinant(matrix, dimensionality) << endl;
}

