#pragma once
#include<vector>
#include<ctime>

class m_grid_position
{
public:
	m_grid_position();
	m_grid_position(int r, int c);
	void set_the_grid_position(int arg_row, int arg_column);
	m_grid_position * Grid_pos();
	int get_grid_row();
	int get_grid_column();
private:
	int row;
	int column;

};

class lattice
{
public:
	lattice();  //used to generate a random chessboard contains enough random number
	bool proposition(int i, int j, int n);
    void setgrid(int r, int c, int n,int sheet[][9]);

	void print_my_chessboard();
	void print_my_chessboard(const int sheet[][9]) const ;
	void fillall(int answer_sheet[][9]);
	int chessboard[9][9];
	//std::vector<int[3][3]>motherboard;
private:
	bool checkrow(int r, int n);
	bool checkcolumn(int c, int n);
	bool isEmpty(int r, int c, const int sheet[][9])const ;
	bool try_number(int r, int c, bool exist_array[9], const int answer_sheet[][9]);
	m_grid_position * next_EMPTY_grid_pos(m_grid_position *cur_Pos, const int sheet[][9]);
	m_grid_position *first_EMPTY_grid_pos(const int sheet[][9]);
};

