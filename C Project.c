/* Assignment: Final Project
Student: Dvir Dishi 316604529
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
typedef enum { False, True } boolean;
typedef struct//
{
	char name[30];
	int sign;
} Player;

int** BuildBoard(int** board, int* rows, int* colums);//������� ����� ��� ��� ����� ������� ����� ����� ������ �������
void PrintBoard(int** board, int rows, int colums);//������� ������� ��� ��� ������� ����� ��
Player PlayerInfo(Player* pPlayer, int i);//���� �������
boolean ValidCol(int* num, int colums);//����� �������
boolean FullCol(int j, int** board);//����� �� ������ ������� ����
void Game(Player* pPlayer, int** board, int rows, int colums);//����� ����� ���� ���� ��� ������ �������� ������ ���� ����� ������ ������
boolean IsTaken(int** board, int i, int j);//�� ������ ������� �������� ��� �����
int validName(char str[]);//�� ��� ����� �� ����� ��� ���� ������ �� ��� ������
void FreeAll(Player* pPlayer, int** board, int rows, int colums);//������� ������� �� �� ������� ������ ����� �������
boolean IsWinner(int** board, int i, int j, int rows, int column);//������� ������ ����� ���� ����� ����� �� �� ��������� �������� ������� ����� ���� ����� �� ������

int main()
{
	Player* pPlayer = NULL;
	pPlayer = (Player*)malloc(2 * sizeof(Player));//����� ���� �� ����� ����� 2 �� ���� ���� ������ ��� �� �2 ������
	int** board = 0;
	int rows = 0, colums = 0;
	for (int i = 0; i < 2; i++)//������ ����� �� ��� ������
	{
		printf("Please enter player number %d first name:", i + 1);
		PlayerInfo(&(pPlayer[i]), i);
	}
	board = BuildBoard(board, &rows, &colums);
	PrintBoard(board, rows, colums);
	Game(pPlayer, board, rows, colums);
	FreeAll(pPlayer, board, rows, colums);
	return 0;
}

int** BuildBoard(int** board, int* rows, int* colums)//������� ����� �� �������
{
	printf("Please enter the size of the board:\n");
	printf("Rows:");
	scanf("%d", rows);
	while (*rows < 4)//�� ����� ���� �4 ����� ������ ���
	{
		printf("wrong rows board's size please try again:");
		scanf("%d", rows);
	}
	printf("Colums:");
	scanf("%d", colums);
	while (*colums < 4)//�� ����� ���� �4 ������ ������ ���
	{
		printf("wrong colums board's size please try again:");
		scanf("%d", colums);
	}
	board = (int**)malloc((*rows) * sizeof(int*));//����� ���� ����� ������� ����� �� ������� �������
	if (board == NULL)
	{
		printf("Error\n");
		return 0;
	}
	for (int i = 0; i < *rows; i++)//����� ������ �� �� ���� �� ���� ������ ����� ��� ������� 
	{
		board[i] = (int*)malloc((*colums) * sizeof(int));//����� ���� ����� ������� ��� �����\����� ��� ������ �� ������� �������
		if (board[i] == NULL)
		{
			printf("Error\n");
			return 0;
		}
	}
	for (int i = 0; i < (*rows); i++)//���� �� ������ ������� �������� ���� 
	{
		for (int j = 0; j < (*colums); j++)//���� �� �� �����
		{
			board[i][j] = 0;//������ �����
		}
	}
	printf("\n");
	return board;
}

void PrintBoard(int** board, int rows, int colums)
{
	for (int i = 0; i < rows; i++)
	{
		if (board[i][0] == 1 || board[i][0] == 2 || board[i][0] == 0)//�� ����� ������ ������ ������� �����
		{
			printf("(%d)-->", i + 1);//������ �� ���� �����
			printf("|");//���� ��� ������
		}
		for (int j = 0; j < colums; j++)
		{
			printf("%d|", board[i][j]);//������ �� ���� ����� ���� ��� ����
		}
		printf("\n");
		printf("      ");//����� ������ ������ ������ ���� ������
		for (int k = 0; k < (2 * colums) + 1; k++)//���� ��� �� ���� ����� ���� ����� �� �� ������� �� ������� ���� ������ ��� �����
		{
			printf("-");
		}
		printf("\n");
	}
}

boolean ValidCol(int* num, int colums)
{
	if (*num >= 1 && *num <= colums)//�� ���� ������ �� ����� �����
	{
		return True;
	}
	printf("\n");
	printf("Wrong colum. please try again: ");//������ ��� ��� ����
	scanf("%d", num);
	return ValidCol(num, colums);//������ �������� ����� ��������� �� ���� ���� ������� ��� �����
}

Player PlayerInfo(Player* pPlayer, int i)//����� ����� �� �� ����, �� ���� ����� �����
{
	char name[30];
	scanf("%s", name);
	while (validName(name) == 0)//�� ��� �� ���� �� ���� ��� ���� ����� ����� ����� ������ ���
	{
		printf("Bad name. Try again:");
		scanf("%s", name);
	}
	strcpy(pPlayer->name, name);
	pPlayer->sign = i + 1;//���� �����
	printf("your sign in the board is %d\n", pPlayer->sign);
}

boolean FullCol(int j, int** board)
{
	if (board[0][j] == 0)//�� ����� ����� ������� ��� ������� ���
		return False;
	return True;
}

void Game(Player* pPlayer, int** board, int rows, int colums)
{
	boolean won = False;//����� �� �� ������ ������� ������ �� �� flag ����� ���� 
	int selection, turn = 0, sign = 0;
	while (turn != rows*colums && won == False)//������ ������� ���� ���� ������ ��������� ����� �� ��� ��� �� ����
	{
		printf("Please enter the colum you want enter your disk to:");//������ ������� ����� ����� ����� ��� ���� ������ �� �������
		scanf("%d", &selection);
		if (turn % 2 == 0)//�� ���� ���� ��� �� ���� �� ��� ����� ������ ������ ���� �����
			sign = pPlayer[0].sign;
		else//�� ���� ���� ��� ���� �� ��� ����� ������ ���� ���� �����
			sign = pPlayer[1].sign;
		while (ValidCol(&selection, colums) == False)//�� ��� ������ ������ �� ����� ����� ������ ������ ������ ����� ���� ��� ����
		{
			printf("The colum is out of range please try again.\n");
			scanf("%d", &selection);
		}

		while (FullCol(selection - 1, board) == True)//�� ��� ������� ���� ������ ���� ����� ��� ���� ������ �� �� ������� ����� ����� ����� ����
		{
			printf("The colum is full, please choose another one.\n");
			scanf("%d", &selection);
		}

		for (int i = rows - 1; i >= 0; i--)//����� ���� ������ ������� �� �������
		{
			if ((IsTaken(board, i, selection - 1) == True) && (FullCol(selection - 1, board) == False))//�� ������ ����� �� ������ ���� ��� ������ ����� �� ���� ����� ���� ��� �����
				continue;
			else//���� ������� �� ������� �� ���� ���� ��� ������
			{
				board[i][selection - 1] = sign;
				break;//������� �������
			}
		}
		for (int i = 0; i < rows; i++)//���� �� ������ ����
		{
			for (int j = 0; j < colums; j++)//���� �� ������� ����
			{
				won = IsWinner(board, i, j, rows, colums);//������ ��� ����� ���� �� ������ ������ ���� �� ����� ������ ����� ������
				if (won == True)//�� �� ��� ������� ������ �� �����
					break;
			}//���� ����� ����� �� ������ ��� ���� ��� ��������� ��� �������
			if (won==True)
				break;
		}
		PrintBoard(board, rows, colums);//������� �� ���� ���� �������� ������� �� ��������
		turn++;//��� ����� ���
	}
	if (won == True)//�� ����� ������ ����� �����
	{
		if (sign == 1)//�� ������� ������� ������� ��� �� ����� ������ ������� ����� �����
			printf("The winner is the first player:%s\n", pPlayer[0].name);
		else//�� ������� ������� ������� ��� �� ����� ���� ������� ����� �����
			printf("The winner is the second player:%s\n", pPlayer[1].name);
	}
	else//���� �� ��� �� ���� ��� ����
		printf("\nTie");
	return;
}

boolean IsTaken(int** board, int i, int j)
{
	if (board[i][j] == 0)//�� ����� ������ ��� �� ����� ������� ���
		return False;
	return True;
}

boolean IsWinner(int** board, int i, int j, int rows, int column) 
{
	if (board[i][j] == 0)
		return False;

	// Check for LEFT (������� ������ �� ����� ������ �����)
	if (j - 3 >= 0) 
	{
		if (board[i][j] == board[i][j - 1] && board[i][j] == board[i][j - 2] && board[i][j] == board[i][j - 3])
			return True;
	}

	// Check for RIGHT (������� ������ �� ����� ������ �����)
	if (j + 3 < column)
	{
		if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3])
			return True;
	}

	// Check for TOP (������� ������ �� ������ ���� ����)
	if (i - 3 >= 0) 
	{
		if (board[i][j] == board[i - 1][j] && board[i][j] == board[i - 2][j] && board[i][j] == board[i - 3][j])
			return True;
	}


	// Check for BOTTOM (������� ������ �� ������ ���� ���)
	if (i + 3 < rows) 
	{
		if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j])
			return True;
	}


	// Check for TOP - LEFT (������� ������ �� ������� ����� �����)
	if (j - 3 >= 0 && i - 3 >= 0)
	{
		if (board[i][j] == board[i - 1][j - 1] && board[i][j] == board[i - 2][j - 2] && board[i][j] == board[i - 3][j - 3])
			return True;
	}

	// Check for TOP - RIGHT (������� ������ �� ������� ����� �����)
	if (j + 3 < column  && i - 3 >= 0)
	{
		if (board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2] && board[i][j] == board[i - 3][j + 3])
			return True;
	}


	// Check for  BOTTOM - LEFT (������� ������ �� ������� ���� �����)
	if (j - 3 >= 0 && i + 3 < rows)
	{
		if (board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] && board[i][j] == board[i + 3][j - 3])
			return True;
	}


	// Check for BOTTOM - RIGHT (������� ������ �� ������� ���� �����)
	if (j + 3 < column && i + 3 < rows)
	{
		if (board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3])
			return True;
	}

	return False;//���� ������� ��� ����� �� ���� ������
}

int validName(char str[])//������� ������ �� ��� ���� �� ��
{
	if (str[0] >= 'a' && str[0] <= 'z')//�� ���� ������� ��� ��� ��� ���� �� ������� ���� �� ����
	{
		return 0;
	}
	for (int i = 1; str[i] != '\0'; i++)
	{
		if (!(str[i] >= 'a' && str[i] <= 'z'))//�� ���� ���� ������� ��� �� ������� �� ����� ��� �� ��� ��� �� �� ����� 0 ����� ���� �� ���� 
		{
			return 0;
		}
	}
	return 1;//�� �� ������ �������� ���� ���� �� ������� 1
}

void FreeAll(Player* pPlayer, int** board, int rows, int colums)
{
	for (int i = 0; i < rows; i++)//����� ������ �� �� ���� �� ���� ������ ����� ��� ������� 
	{
		free(board[i]);//������� �� ����� ��� ������� ����� ����
	}
	free(board);//������� �� �� ������ �� ���� ����
	free(pPlayer);//������� �� ������ ������ �����
}
