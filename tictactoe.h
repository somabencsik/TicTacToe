#include <stdio.h>

#define ROWS 12
#define COLS 18

void drawMap(int place, char* signs)
{
	int pipeAt = 6;
	int dashAt = 4;
	int currNum = 0;
	for (int y = 1; y < ROWS; ++y)
	{
		for (int x = 1; x < COLS; ++x)
		{
			if ( (x + (6 * (x % 6) )) % 3 == 0 && x % 6 != 0 &&
			     (y + (4 * (y % 4) )) % 2 == 0 && y % 4 != 0 )
			{
				if (place == -1 || signs[currNum] == 'E')
					printf("%d", currNum);
				else
					printf("%c", signs[currNum]);
				currNum += 1;
			}
			else if (x % pipeAt == 0)
			{
				printf("|");
			}
			else
			{
				if (y % dashAt == 0 )
				{
					printf("-");
				}
				else
				{
					printf(" ");
				}
			}
		}
		printf("\n");
	}
}

int checkForSame(char* signs)
{
	char first = signs[0];
	for (int i = 1; i < 3; ++i)
	{
		if (signs[i] != first || signs[i] == 'E')
			return 0;
	}

	return 1;
}

int checkWin(char* signs)
{
	// Check horizontal win
	int i = 0;
	for (i; i < 9; ++i)
	{
		char temp[3];
		int tempIdx = 0;
		int j = i;
		for (j; j < i + 3; ++j)
		{
			temp[tempIdx] = signs[j];
			++tempIdx;	
		}
		i = --j;
		if ( checkForSame(temp) )
			return 1;
	}
	// Check vertical win
	i = 0;
	for (i; i < 3; ++i)
	{
		char temp[3];
		int tempIdx = 0;
		int j = i;
		for (j; j < i + 7; j = j + 3)
		{
			temp[tempIdx] = signs[j];
			++tempIdx;
		}
		if ( checkForSame(temp) )
			return 1;
	}

	// Check diagonal win
	char firstDiagonal[3];
	firstDiagonal[0] = signs[0];
	firstDiagonal[1] = signs[4];
	firstDiagonal[2] = signs[8];
	if ( checkForSame(firstDiagonal) )
		return 1;
	char secondDiagonal[3];
	secondDiagonal[0] = signs[2];
	secondDiagonal[1] = signs[4];
	secondDiagonal[2] = signs[6];
	if ( checkForSame(secondDiagonal) )
		return 1;

	// Check if draw
	i = 0;
	for (i; i < 9; ++i)
	{
		if (signs[i] == 'E')
			return 0;
	}
	
	return -1;
}

void play(void)
{
	char signs[9];
	for (int i = 0; i < 9; ++i)
	{
		signs[i] = 'E';
	}
	printf("\e[1;1H\e[2J");
	drawMap(-1, signs);

	while(1)
	{
		int choice;
		printf("Player 1: ");
		scanf("%d", &choice);
		signs[choice] = 'O';
		printf("\e[1;1H\e[2J"); // Clear Terminal/Console
		drawMap(choice, signs);

		if ( checkWin(signs) == 1 )
		{
			printf("Player 1 has won!\n");
			break;
		}
		else if ( checkWin(signs) == -1 )
		{
			printf("Draw!\n");
			break;
		}

		printf("Player 2: ");
		scanf("%d", &choice);
		signs[choice] = 'X';
		printf("\e[1;1H\e[2J"); // Clear Terminal/Console
		drawMap(choice, signs);

		if ( checkWin(signs) == 1 )
		{
			printf("Player 2 has won!\n");
			break;
		}
		else if ( checkWin(signs) == -1 )
		{
			printf("Draw!\n");
			break;
		}
	}
}
