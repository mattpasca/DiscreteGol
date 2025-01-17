/* This program encodes the state transition for discrete GoL.
 *The matrix representing the grid is implemented as a 2d torus.
 *
 * ISSUES:
 * Where do you define DIM? Maybe define it global here and pass the value through python
 * How do we pass results to python?
 *
 * Compiler: gcc -shared -o state_transition.so -fPIC state_transition.c 
 */
#include <stdlib.h>

int index_wrap(int index, int index_shift){
	return (DIM+(index+index_shift)%DIM)%DIM;
}

int toroidal_wrap(int row, int row_shift, int col, int col_shift){
	return DIM*index_wrap(row, row_shift) + index_wrap(col, col_shift);
}

int* state_transition(int* matrix, int DIM){
        int* result_matrix;
        result_matrix = calloc(DIM*DIM, sizeof(double));
        int living_neighbors;   // count of the living neighbors
        int row, col; // indices to go through each cell
        int row_shift, col_shift; // auxiliary variables to select the neighboring cells
        int wrapped_index;
        living_neighbors = 0;
        for(row=0; row<DIM; ++row){
            for(col=0; col<DIM; ++col){
                for(row_shift=-1; row_shift<2; ++row_shift){
                    for(col_shift=-1; col_shift<2; ++col_shift){
                        wrapped_index = toroidal_wrap(row, row_shift, col, col_shift);
                        living_neighbors += matrix[wrapped_index];
                    }
                }
                living_neighbors -= matrix[DIM*row+col]; //consider only the neighbors
                /* These are the classic rules of Conway's game of life:
                 * living cells die if neighbors are less than 2 or more than 3
                 * dead cells come alive if neighbors are exactly 3.
                 */
                switch(matrix[DIM*row+col]){
                    case 0: result_matrix[DIM*row+col] = (living_neighbors==3)? 1:0; break;
                    case 1: result_matrix[DIM*row+col] = (living_neighbors<2||living_neighbors>3)? 0:1; break;
                }
            }
        }
return result_matrix;

}

void free_matrix(int* matrix){
    free(matrix);
}

/*   __________
 *  |_/_|_/_|_/_|
 *  |_/_|_n_|_/_|
 *  |_/_|_/_|_/_|
 *
 */
