#include"lattice.h"
#include<iostream>
//#include<list>
int main()
{
	lattice lat1;
	lat1.print_my_chessboard();
	int answer_sheet[9][9];
	std::cout <<std:: endl;
	lat1.fillall(answer_sheet);
	std::cout << "after we fill the answer sheet \n\n";
	lat1.print_my_chessboard(answer_sheet);
	//std::list<int> li;
	//li.push_back(10);
	//li.push_back(20);
	//li.push_back(30);

	//std::list<int>::iterator test_Iter = li.end();
	//test_Iter--;
	//std::cout << "the last element in the list is" << *test_Iter << std::endl;

	
	
//	std::cout << "\n" << 17 / 9;
	std::cin.get();
}