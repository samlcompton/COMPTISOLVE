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
	int n_cells;
	int n_faces;
	string astring;
	char ch;
	//mat input_mesh;
	public:
	void open_msh_file();
	
};
//definition of open_msh_file() method
void Grid::open_msh_file()
{
	ifstream fin("fem2d_input.csv");
	if (fin.is_open()) 
	{ 
		cout << "argg\n";
		getline(fin,astring,',');
		cout << astring,"\n";
	}

	fin.close();  		
}




		
int main() // main program interface
{
	std::cout << "this is a test, calm down\n";	
	
	mat A = randu<mat>(4,5);
 	mat B = randu<mat>(4,5);
  
  	cout << A*B.t() << endl;

	Grid frustration;
	frustration.open_msh_file();

	return 0; 
	
}