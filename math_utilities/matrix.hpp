#include <stdio.h>

class Matrix {
    private:
        int nrows, ncols;
        float** data;

        void create(){
            data = new float*[nrows];
            for(int r = 0; r < nrows; r++)
                data[r] = new float[ncols]();
        }

    public:
        Matrix(){}
        Matrix(int rows, int cols){
            nrows = rows;
            ncols = cols;
            create();
        }
        ~Matrix(){
            for(int r = 0; r < nrows; r++)
                delete[] data[r];
            delete[] data;
        }

        void init(){
            for(int r = 0; r < nrows; r++)
                for(int c = 0; c < ncols; c++)
                    data[r][c] = 0;
        }

        void set_size(int rows, int cols){
            nrows = rows;
            ncols = cols;
            create();
        }
        int get_nrows(){
            return nrows;
        }
        int get_ncols(){
            return ncols;
        }

        void set(float value, int row, int col){
            data[row][col] = value;
        }
        void add(float value, int row, int col){
            data[row][col] += value;
        }
        float get(int row, int col){
            return data[row][col];
        }

        void remove_row(int row){
            float** neo_data = new float*[nrows-1];
            for(int i = 0, j = 0; i < nrows; i++)
                if(i != row){
                    neo_data[j++] = data[i];
                }
            delete[] data;
            data = neo_data;
            nrows--;
        }

        void remove_column(int col){
            float** neo_data = new float*[nrows];
            for(int r = 0; r < nrows; r++)
                neo_data[r] = new float[ncols-1];

            for(int r = 0; r < nrows; r++){
                for(int c = 0, j = 0; c < ncols; c++)
                    if(c != col){
                        neo_data[r][j++] = data[r][c];
                    }
            }
            for(int r = 0; r < nrows; r++)
                delete[] data[r];
            delete[] data;
            data = neo_data;
            ncols--;
        }

        void clone(Matrix* other){
            for(int r = 0; r < nrows; r++)
                for(int c = 0; c < ncols; c++)
                    other->set(data[r][c],r,c);
        }

        void show(){
            cout << "[ ";
            for(int r = 0; r < nrows; r++){
                cout << "[ " << data[r][0];
                for(int c = 1; c < ncols; c++){
                    cout << ", " << data[r][c];
                }
                cout << " ] ";
            }
            cout << " ]\n\n";
        }
};
