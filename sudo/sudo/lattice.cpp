#include "lattice.h"
#include<stdlib.h>
#include<iostream>
#include<list>

lattice::lattice()  //we use -1 to represent empty grid in the chess board 
{
	for (int i = 0; i <9; i++) 
	{
		for (int j = 0; j < 9; j++)
		{
			chessboard[i][j] = 0;
		}
	}
	srand(time(NULL));
	for (int iterator = 0; iterator < 9; iterator++)
	{
		for (int block = 1; block <= 3; block++)
		{
			int temp_n = rand() % 9 + 1;		int temp_column = rand() % 9;
			while (!(checkrow(iterator, temp_n) && checkcolumn(temp_column, temp_n) ) )
			{
				temp_n = rand() % 9+1;		temp_column = rand() % 9;
			}
			chessboard[iterator][temp_column] = temp_n;
		}
	}
}

bool lattice::proposition(int i, int j, int n)
{
	return (chessboard[i][j] == n);
}

bool lattice::checkcolumn(int c, int n)
{
	for (int iter = 0; iter < 9; iter++)
	{
		if (chessboard[iter][c] == n)
		{
			return false;
		}
	}
	return true;
}

bool lattice::checkrow(int r, int n)
{
	for (int iter = 0; iter < 9; iter++)
	{
		if (chessboard[r][iter] == n)
		{
			return false;
		}
	}
	return true;
}

void lattice::setgrid(int i, int j, int n,int sheet[][9])
{
	sheet[i][j] = n; 
}

bool lattice::try_number(int r, int c, bool exist_array[9],const int answer_sheet[][9])
{
	memset(exist_array, false, sizeof(bool) * 9);
	for (int i = 0; i < 9; i++)
	{
		if (answer_sheet[r][i] != 0)
		{
			exist_array[answer_sheet[r][i]-1] = true;
		}
		if (answer_sheet[i][c] != 0)
		{
			exist_array[answer_sheet[i][c]-1] = true;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (!exist_array[i])		
			return true;
	}
	return false;	//try failed , return false to parent scope 
}

void lattice::print_my_chessboard()
{
	for (int row = 0; row < 9; row++)
	{
		std::cout << "\t";
		for (int c=0;c<9;c++)
		{
			std::cout << chessboard[row][c] << " ";
		}
		std::cout << std::endl;
	}
}

void lattice::print_my_chessboard(const int sheet[][9]) const 
{
	for (int row = 0; row < 9; row++)
	{
		std::cout << "\t";
		for (int c = 0; c < 9; c++)
		{
			std::cout << sheet[row][c] << " ";
		}
		std::cout << std::endl;
	}
}

void lattice::fillall(int answer_sheet[][9])
{
	//for (int c = 0; c < 9; c++)
	//{
	//	memcpy(&(answer_sheet[c]), &(chessboard[c]), sizeof(int) * 9);	//copy the original matric to the  answer sheet1
	//}
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			answer_sheet[r][c] = chessboard[r][c];
		}
	}

	m_grid_position *temp_grid_pos_ptr=new m_grid_position(0,0);
	m_grid_position *saved_prev_grid_pos_ptr ;		//use this to save the previous grid we have filled 
	m_grid_position *next_grid_position;
	std::list<int>List_possible;	//construct a possible item array to enumerate the answer
	//std::list<int>List_used_member;
	bool exist_array[9] = { false };
	//while((next_EMPTY_grid_pos(temp_grid_pos_ptr,answer_sheet)!=nullptr)&&(try_number())
	temp_grid_pos_ptr = first_EMPTY_grid_pos(answer_sheet);
	saved_prev_grid_pos_ptr = temp_grid_pos_ptr;
	while(temp_grid_pos_ptr!=nullptr)
	{
		    try_number(temp_grid_pos_ptr->get_grid_row() , temp_grid_pos_ptr->get_grid_column(), exist_array, answer_sheet);
			//try to fill the grid 	, Find the number in the candidate number
			
			next_grid_position = next_EMPTY_grid_pos(temp_grid_pos_ptr, answer_sheet);
			List_possible.clear();
			for (int i = 0; i < 9; i++)		//fill the possible array based on the information of "exist_array"
			{
				if (!exist_array[i])
				{
					List_possible.push_back(i + 1);	    //follow the order of least to most ,in the list 
				}
			}
			do
			{
				if (!List_possible.empty())
				{
					setgrid(temp_grid_pos_ptr->get_grid_row(), temp_grid_pos_ptr->get_grid_column(),
						List_possible.back(), answer_sheet);
					List_possible.pop_back();
				}
				else //back to previous array to select another appropriate number
				{
					setgrid(temp_grid_pos_ptr->get_grid_row(), temp_grid_pos_ptr->get_grid_column(),
						0, answer_sheet);		//restore operation

					delete next_grid_position;
					next_grid_position = temp_grid_pos_ptr;
					temp_grid_pos_ptr = saved_prev_grid_pos_ptr;	//restore the iterative position pointer
					try_number(temp_grid_pos_ptr->get_grid_row(), temp_grid_pos_ptr->get_grid_column(), exist_array,
						answer_sheet);
					List_possible.clear();	//remember to clear the share variable;
					for (int i = 0; i < 9; i++)		//fill the possible array based on the information of "exist_array"
					{
						if (!exist_array[i])
						{
							List_possible.push_back(i + 1);	    //follow the order of least to most ,in the list 
						}
					}
					//here, i set a subroutine to judge  whether the process running is a backward operation
					std::list<int>::iterator target_Iterator = List_possible.end();
					target_Iterator--;
					int target_element = answer_sheet[temp_grid_pos_ptr->get_grid_row()][temp_grid_pos_ptr->get_grid_column()];
					while (*target_Iterator != target_element) { target_Iterator--; };
					List_possible.erase(target_Iterator, List_possible.end()--);
					if (!List_possible.empty())   //here, we have met a mathematical problem about sudo, what will happen
					{											//when the possible list still is EMPTY.
						setgrid(temp_grid_pos_ptr->get_grid_row(), temp_grid_pos_ptr->get_grid_column(),
							List_possible.back(), answer_sheet);
						List_possible.pop_back();
					} 
					else
					{
						system("pause");
					}
				}
			} while (!try_number(next_grid_position->get_grid_row(), next_grid_position->get_grid_column(),
				exist_array, answer_sheet));
			if (saved_prev_grid_pos_ptr != temp_grid_pos_ptr)
			{
				delete saved_prev_grid_pos_ptr;
			}
			saved_prev_grid_pos_ptr = temp_grid_pos_ptr;
			temp_grid_pos_ptr = next_grid_position;
			next_grid_position = next_EMPTY_grid_pos(next_grid_position, answer_sheet);
			
	} 

}

bool lattice::isEmpty(int row , int column,const int sheet[][9]) const 
{
	return (sheet[row][column] == NULL) ? true : false ; 
}

m_grid_position* lattice::next_EMPTY_grid_pos(m_grid_position* cur_Pos, const int sheet[][9])
{
	
	int counter = cur_Pos->get_grid_row() * 9 + cur_Pos->get_grid_column();
	int temp_row; int temp_column;
	do {
		counter++;
		temp_row = counter / 9; temp_column = counter % 9;
	} while (!isEmpty(temp_row, temp_column,sheet)&&counter<81);
	if (counter < 81)
	{
		return new m_grid_position(temp_row, temp_column);
	}
	else
		return nullptr;
}

m_grid_position* lattice::first_EMPTY_grid_pos(const int sheet[][9])
{
	int counter = 0;
	int temp_row; int temp_column;
	do {
		temp_row = counter / 9; temp_column = counter % 9;
		counter++;
	} while (!isEmpty(temp_row, temp_column, sheet) && counter < 81);
	if (counter < 81)
	{
		return new m_grid_position(temp_row, temp_column);
	}
	else
		return nullptr;
}



// auxiliary class : position manager in chessboard grid;
m_grid_position::m_grid_position()
{}

m_grid_position::m_grid_position(int r, int c)
{
	row = r;	column = c;
}

void m_grid_position::set_the_grid_position(int arg_row, int arg_column)
{
	column = arg_column; row = arg_row;
}

m_grid_position* m_grid_position::Grid_pos()
{
	return this;
}

int m_grid_position::get_grid_column()
{
	return column;
}

int m_grid_position::get_grid_row()
{
	return row;
}