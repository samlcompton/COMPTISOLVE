#include <iostream>
#include <armadillo>

using namespace arma;
//enum MSH_TYPE { tetra_msh, hexa_msh, quad_msh, tri_msh };

class Grid		//declare grid class
{
	protected:
	
		
		int n_elements; // number of elements in the grid
		int n_faces; //the number of faces of the grid
		int n_nodes; //number of nodes in the grid
		double Kx; //thermal conductivity n the X direction
		double Ky; //thermal conductivity in the Y direction 
		double Qdot; // internal heat generation
		int NGP=2; //Number of gauss points to use in quadrature 
		mat raw_grid; //matrix object from arma to hold raw grid input
		Mat<int> nod; //matrix of node
		mat node_xcoord; //vector of node x coordinates
		mat node_ycoord; // vector of node y coordinates 
	public:
		void open_msh_file(); //method to open mesh file 
		void set_dim();
		void read_connectivity();
		int get_nele();
		int NPE;
		void setNPE(int sNPE) {NPE=sNPE;}		
};
//definition of open_msh_file() method

class TwoD_grid : public Grid
{

};

class ThreeD_grid : public Grid
{

};

class tri_msh : public TwoD_grid
{
	public:

};

class quad_msh : public TwoD_grid
{
	public:

};

class hexa_msh : public ThreeD_grid
{
	
};

class tetra_msh : public ThreeD_grid
{
	
};


