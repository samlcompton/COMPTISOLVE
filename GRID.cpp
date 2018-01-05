// Declaration of a class, grid

#include <iostream>
#include <armadillo>
#include <fstream>
#include <istream>
#include <string>
using namespace arma;
using namespace std;
	
class Grid		//declare grid class
{
	double n_elements;
	int n_faces;
	mat raw_grid;
	char ch;
	//mat input_mesh;
	public:
	void open_msh_file();
	
};
//definition of open_msh_file() method
void Grid::open_msh_file()
{
	raw_grid.load("FEM_HT_input.csv");
	raw_grid.print();
	n_elements=raw_grid(0,0);
	cout <<"number of elements:   " << n_elements << "\n";
	 		
}


int main() // main program interface
{
	std::cout << "this is a test, calm down\n";	
	
	mat A = randu<mat>(4,5);
 	mat B = randu<mat>(4,5);
  
  	cout << A*B.t() << endl;

	Grid main_grid;
	main_grid.open_msh_file();

	return 0; 
	
}
