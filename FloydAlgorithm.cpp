#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#define ARRAY_SIZE 9

struct Cord
{
	int x;
	int y;
};

int **Inicialize(void)
{
	int tmp[ARRAY_SIZE][ARRAY_SIZE] = {
		{-1, 5, MAXINT, MAXINT, MAXINT, MAXINT, MAXINT, 10, MAXINT},
		{5, -1, 45, 45, MAXINT, MAXINT, MAXINT, 25, MAXINT},
		{MAXINT, 45, -1, 53, MAXINT, 50, MAXINT, MAXINT, MAXINT},
		{MAXINT, 45, 53, -1, 26, MAXINT, MAXINT, MAXINT, 55},
		{MAXINT, MAXINT, MAXINT, 26, -1, 61, MAXINT, MAXINT, 10},
		{MAXINT, MAXINT, 50, MAXINT, 61, -1, 73, MAXINT, 87},
		{MAXINT, MAXINT, MAXINT, MAXINT, MAXINT, 73, -1, 42, MAXINT},
		{10, 25, MAXINT, MAXINT, MAXINT, MAXINT, 42, -1, MAXINT},
		{MAXINT, MAXINT, MAXINT, 55, 10, 87, MAXINT, MAXINT, -1}
	};

	int **tmp_matrix = new int *[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; i++) {
		tmp_matrix[i] = new int[ARRAY_SIZE];
		for (int k = 0; k < ARRAY_SIZE; k++) tmp_matrix[i][k] = tmp[i][k];
	}
	return tmp_matrix;
}

void PrintMatrix(int **matrix, int len)
{
	printf("     ");
	for (int i = 0; i < len; i++)
		printf("%3i  ", i + 1);
	printf("\n\n");

	for (int i = 0; i < len; i++)
	{
		printf("%3i  ", i + 1);
		for (int k = 0; k < len; k++)
			if (matrix[i][k] == -1) printf("  _  ");
			else if (matrix[i][k] == MAXINT) printf(" INF ");
			else printf("%3i  ", matrix[i][k]);
		printf("\n\n");
	}
}

void Floyt(int **matrix)
{
	for (int k = 0; k < ARRAY_SIZE; k++)
	{
		int **p = new int*[ARRAY_SIZE];
		for (int a = 0; a < ARRAY_SIZE; a++) p[a] = new int[ARRAY_SIZE];
		for (int i = 0; i < ARRAY_SIZE; i++)
			for (int j = 0; j < ARRAY_SIZE; j++)
			{
				if (i == j) p[i][j] = -1;
				else if ((i == k) || (j == k)) p[i][j] = matrix[i][j];
				else
				{
					int a = 0;

					if (matrix[i][k] == MAXINT) a = MAXINT;
					else if (matrix[k][j] == MAXINT) a = MAXINT;
					else a = matrix[i][k] + matrix[k][j];

					if (a < matrix[i][j]) p[i][j] = a;
					else p[i][j] = matrix[i][j];
				}
			}
		for (int i = 0; i < ARRAY_SIZE; i++)
			for (int j = 0; j < ARRAY_SIZE; j++)
				matrix[i][j] = p[i][j];

		free(p);
	}
}

void PrintTour(int **matrix, int **new_matrix, int town, int *way)
{
	int sum = LengthOfShortestWay(matrix, way);
	for (int j = 0; j < ARRAY_SIZE - 1; j++)
		if ((matrix[way[j]][way[j + 1]] == MAXINT) || (matrix[way[j]][way[j + 1]] < 0)) printf("%i(INF) -> ", way[j] + 1, matrix[way[j]][way[j + 1]]);
		else printf("%i(%3i) -> ", way[j] + 1, matrix[way[j]][way[j + 1]]);

	if (sum != MAXINT) printf("%i | %i\n", way[ARRAY_SIZE - 1] + 1, sum);
	else printf("%i | There is no way\n", way[ARRAY_SIZE - 1] + 1);
}

int *ShortestWay(int **matrix, int v)
{
	bool a[ARRAY_SIZE] = { false };
	int *res = new int[ARRAY_SIZE];
	int index = v;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		Cord min = { -1, MAXINT };
		a[index] = true;
		for (int j = 0; j < ARRAY_SIZE; j++)
			if ((min.y > matrix[index][j]) && (matrix[index][j] >= 0) && (a[j] != true))
			{
				min.y = matrix[index][j];
				min.x = j;
			}
		res[i] = index;
		index = min.x;

	}
	return res;
}

int LengthOfShortestWay(int **matrix, int *way)
{
	int sum = 0;

	for (int j = 0; j < ARRAY_SIZE - 1; j++)
	{
		int a = matrix[way[j]][way[j + 1]];
		if (a == MAXINT)
		{
			sum = MAXINT;
			break;
		}
		else sum += a;
	}

	return sum;
}

void MinimumTour(int **matrix, int **new_matrix)
{
	int *res = NULL;
	int min_sum = MAXINT;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		int *way = ShortestWay(new_matrix, i);
		int sum = LengthOfShortestWay(matrix, way);

		PrintTour(matrix, new_matrix, way[0], way);

		if (min_sum > sum)
		{
			min_sum = sum;
			res = way;
		}
	}
	printf("\n\nThis is minimum tour: ");
	PrintTour(matrix, new_matrix, res[0], res);
	printf("\n\n");
}


int main(void)
{
	int **matrix = Inicialize();
	int **new_matrix = Inicialize();

	PrintMatrix(matrix, ARRAY_SIZE);
	Floyt(new_matrix);
	printf("-------------------------------------------------\n\n");
	PrintMatrix(new_matrix, ARRAY_SIZE);

	MinimumTour(matrix, new_matrix);

	system("pause");
	free(matrix);
	free(new_matrix);
	return 0;
}