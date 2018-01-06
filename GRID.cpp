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

void Grid::get_ebc()
{
	int i;
	n_ebc=raw_grid(n_nodes+n_elements+1,0);
	node_ebc.zeros(n_ebc,1);
	val_ebc.zeros(n_ebc,1);
	for (i=0; i<n_ebc; i++)
	{
		node_ebc=raw_grid(i+1+n_nodes+n_elements+1,0);
		val_ebc(i,0)=raw_grid(i+1+n_nodes+n_elements+1,1);
	}
	
}


void Grid::get_nbc()
{
	int i;
	n_nbc=raw_grid(n_nodes+n_elements+1+n_ebc+1,0);
	node_nbc.zeros(n_nbc,1);
	val_nbc.zeros(n_nbc,1);
	for (i=0; i<n_nbc; i++)
	{
		node_nbc(i,0)=raw_grid(i+1+n_nodes+n_elements+1+n_ebc,0);
		val_nbc(i,0)=raw_grid(i+1+n_nodes+n_elements+1+n_ebc,1);
	}
	
}

 

int Grid::get_nele()
{
	return n_elements;
}

soln::soln(Grid input_grid) //soln constructor 
{
	sol_grid=input_grid;
}

soln::~soln() //soln destructor
{
}

void soln::get_K_mat()
{
//sol_grid is the grid object for this scope
	mat ELK;
	mat ELKRHS;
	mat psi; 
	psi.zeros(sol_grid.NPE,1);
	double xi;
	double eta;
	int en;
	int ngpxi;
	int ngpeta;
	//int j;
	K_mat.zeros(sol_grid.n_nodes,sol_grid.n_nodes); //initializing K
	RHS.zeros(sol_grid.n_nodes,1); // initialzing RHS
	
	
	for(en=0; en<sol_grid.n_elements; en++)
	{
		//initializing element and RHS matricies with zeros
			ELK.zeros(sol_grid.NPE,sol_grid.NPE);
			ELKRHS.zeros(sol_grid.NPE,1);
		for(ngpxi=0; ngpxi<sol_grid.NGP; ngpxi++)
		{	
			xi=0.0;			
			for(ngpxi=0; ngpeta<sol_grid.NGP; ngpxi++)
			{
				eta=0.0;				
				psi(0,0)=0.25*(1-xi)*(1-eta);
				psi(1,0)=0.25*(1+xi)*(1-eta);
				psi(2)=0.25*(1+xi)*(1+eta);
				psi(3)=0.25*(1-xi)*(1+eta);			
			}
		}
	
	
	
		
	}
	
	
	
}

int main() // main program interface
{
	std::cout << "this is a test, calm down\n";	
	
	mat A = randu<mat>(4,5);
 	mat B = randu<mat>(4,5);
  
  	cout << A*B.t() << endl;


	quad_msh MESH;
	MESH.open_msh_file();
	cout << "double checking number of elements   " << MESH.get_nele() << "\n";
	MESH.setNPE(4); // Set the number of nodes per element
	MESH.read_connectivity();
	MESH.get_ebc();
	MESH.get_nbc();
	soln solutionX(MESH);
	
	
	
	//soln solve;
	//solve.get_K_mat(MESH.n_nodes);
	
	
	return 0; 
	
}
