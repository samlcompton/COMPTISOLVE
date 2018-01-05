// Declaration of a class, grid

#include <iostream>
#include <armadillo>
#include <fstream>
#include <istream>
#include <string>
#include "GRID.h"
using namespace arma;
using namespace std;
	
//enum MSH_TYPE { tetra_msh, hexa_msh, quad_msh, tri_msh };

void Grid::open_msh_file()
{
	raw_grid.load("FEM_HT_input.csv"); //arma function for mat object to
	//read in the grid matrix
	raw_grid.print(); // step to print raw grid
	
	n_elements=raw_grid(0,0); //assigns the elements value to the 
	// n_elements attribute of object 
	
	n_nodes=raw_grid(0,1); // assigns the number of nodes value to the 
	// n_nodes attribute of Grid object
	
	Kx=raw_grid(0,2); // assigns the value of the thermal conductivity 
	//in X to the Kx attribute of Grid object
	
	Ky=raw_grid(0,3); // assigns the value of the thermal conductivity in 
	//Y to the Ky attribute of Grid object 
	
	Qdot=raw_grid(0,4); // assigns the value of Qdot term
	
	
	
	cout <<"number of elements:   " << n_elements << "\n";
	cout <<"number of nodes:    " << n_nodes << "\n"; 		
}

void Grid::read_connectivity()
{
	int i;
	int j;
	nod.zeros( n_elements, NPE );
	node_xcoord.zeros( n_nodes, 1);
	node_ycoord.zeros( n_nodes, 1);
	for (i=0; i<n_elements; i++)
	{	
		for (j=0; j<NPE; j++)
		{
			nod(i,j)=raw_grid(i+1,j+1); // read connectivity to mat
		}
	}	
	cout <<"printing connectivity   \n";
	nod.print();
	for (i=0; i<n_nodes; i++)
	{	
		for (j=0; j<NPE; j++)
		{
			node_xcoord(i)=raw_grid(i+1+n_elements,1);
			node_ycoord(i)=raw_grid(i+1+n_elements,2);
		}
	}	
	cout << "printing x coords \n";
	node_xcoord.print();
	cout << "printing y coords \n";
	node_ycoord.print();	
	
	
}

int Grid::get_nele()
{
	return n_elements;
}

int main() // main program interface
{
	std::cout << "this is a test, calm down\n";	
	
	mat A = randu<mat>(4,5);
 	mat B = randu<mat>(4,5);
  
  	cout << A*B.t() << endl;


	tri_msh MESH;
	MESH.open_msh_file();
	cout << "double checking number of elements   " << MESH.get_nele() << "\n";
	MESH.setNPE(4); // Set the number of nodes per element
	MESH.read_connectivity();

	return 0; 
	
}
