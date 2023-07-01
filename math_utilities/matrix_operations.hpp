#include <cmath>

#include "vector.hpp"
#include "matrix.hpp"
//Multiplica una matriz M por un escalar y guarda el resultado en la matriz R.

void product_scalar_by_matrix(float scalar, Matrix* M, int n, int m, Matrix* R){
    for(int r = 0; r < n; r++)
        for(int c = 0; c < m; c++)
            R->set(scalar*M->get(r,c),r,c);
}
//Multiplica una matriz M por un vector V y guarda el resultado en el vector R.
void product_matrix_by_vector(Matrix* M, Vector* V, int n, int m, Vector* R){
    for(int r = 0; r < n; r++){
        float acc = 0;
        for(int c = 0; c < n; c++)
            acc += M->get(r,c)*V->get(c);
        R->set(acc,r);
    }
}
//product_matrix_by_matrix: Multiplica una matriz A por otra matriz B y guarda el resultado en la matriz R.
void product_matrix_by_matrix(Matrix* A, Matrix* B, Matrix* R){
    int n = A->get_nrows(), m = A->get_ncols(), p = B->get_nrows(), q = B->get_ncols();
    if(m == p){
        R->set_size(n,q);
        R->init();
        
        for(int r = 0; r < n; r++)
            for(int c = 0; c < q; c++)
                for(int i = 0; i < m; i++)
                    R->add(A->get(r,i)*B->get(i,c),r,c);
    }else{
        cout << "Incompatibilidad de dimensiones al multiplicar matrices.\n\nAbortando...\n";
        exit(EXIT_FAILURE);
    }
}

//determinant: Calcula el determinante de una matriz M. Para matrices de tamaño 1x1, 2x2, 3x3 y 4x4, 
//la función implementa la fórmula directamente. Para matrices de tamaño mayor, utiliza la función auxiliar determinant_auxiliar.

float determinant(Matrix* M);
//determinant_auxiliar: Una función auxiliar para calcular el determinante de una matriz de tamaño mayor a 4x4. Usa la definición
 //recursiva del determinante basada en los cofactores.
 
float determinant_auxiliar(Matrix* M) {
    int n = M->get_ncols();
    float acc = 0;

    if (n == 1) {
        return M->get(0, 0);
    }

    for (int c = 0; c < n; c++) {
        Matrix clon(n - 1, n - 1);
        for (int i = 1; i < n; i++) {
            for (int j = 0, col = 0; j < n; j++) {
                if (j != c) {
                    clon.set(M->get(i, j), i - 1, col);
                    col++;
                }
            }
        }
        acc += pow(-1, c) * M->get(0, c) * determinant(&clon);
    }

    return acc;
}

float determinant(Matrix* M) {
    float ans;
    switch (M->get_ncols()) {
        case 1:
            ans = M->get(0, 0);
            break;
        case 2:
            ans = M->get(0, 0) * M->get(1, 1) - M->get(0, 1) * M->get(1, 0);
            break;
        case 3:
            ans = M->get(0, 0) * M->get(1, 1) * M->get(2, 2) - M->get(0, 0) * M->get(1, 2) * M->get(2, 1) - M->get(0, 1) * M->get(1, 0) * M->get(2, 2) + M->get(0, 1) * M->get(1, 2) * M->get(2, 0) + M->get(0, 2) * M->get(1, 0) * M->get(2, 1) - M->get(0, 2) * M->get(1, 1) * M->get(2, 0);
            break;
        case 4:
            ans = M->get(0, 0) * M->get(1, 1) * M->get(2, 2) * M->get(3, 3) +
                  M->get(0, 0) * M->get(1, 2) * M->get(2, 3) * M->get(3, 1) +
                  M->get(0, 0) * M->get(1, 3) * M->get(2, 1) * M->get(3, 2) +
                  M->get(0, 1) * M->get(1, 0) * M->get(2, 3) * M->get(3, 2) +
                  M->get(0, 1) * M->get(1, 2) * M->get(2, 0) * M->get(3, 3) +
                  M->get(0, 1) * M->get(1, 3) * M->get(2, 2) * M->get(3, 0) +
                  M->get(0, 2) * M->get(1, 0) * M->get(2, 1) * M->get(3, 3) +
                  M->get(0, 2) * M->get(1, 1) * M->get(2, 3) * M->get(3, 0) +
                  M->get(0, 2) * M->get(1, 3) * M->get(2, 0) * M->get(3, 1) +
                  M->get(0, 3) * M->get(1, 0) * M->get(2, 2) * M->get(3, 1) +
                  M->get(0, 3) * M->get(1, 1) * M->get(2, 0) * M->get(3, 2) +
                  M->get(0, 3) * M->get(1, 2) * M->get(2, 1) * M->get(3, 0) -
                  M->get(0, 0) * M->get(1, 1) * M->get(2, 3) * M->get(3, 2) -
                  M->get(0, 0) * M->get(1, 2) * M->get(2, 1) * M->get(3, 3) -
                  M->get(0, 0) * M->get(1, 3) * M->get(2, 2) * M->get(3, 1) -
                  M->get(0, 1) * M->get(1, 0) * M->get(2, 2) * M->get(3, 3) -
                  M->get(0, 1) * M->get(1, 2) * M->get(2, 3) * M->get(3, 0) -
                  M->get(0, 1) * M->get(1, 3) * M->get(2, 0) * M->get(3, 2) -
                  M->get(0, 2) * M->get(1, 0) * M->get(2, 3) * M->get(3, 1) -
                  M->get(0, 2) * M->get(1, 1) * M->get(2, 0) * M->get(3, 3) -
                  M->get(0, 2) * M->get(1, 3) * M->get(2, 1) * M->get(3, 0) -
                  M->get(0, 3) * M->get(1, 0) * M->get(2, 1) * M->get(3, 2) -
                  M->get(0, 3) * M->get(1, 1) * M->get(2, 2) * M->get(3, 0) -
                  M->get(0, 3) * M->get(1, 2) * M->get(2, 0) * M->get(3, 1);
            break;
        default:
            ans = determinant_auxiliar(M);
            break;
    }
    return ans;
}
//get_minor: Obtiene el menor de la matriz M eliminando la fila r y la columna c.
float get_minor(Matrix* M, int n, int r, int c){
    Matrix clon(n,n);
    M->clone(&clon);

    //M.show(); clon.show();

    clon.remove_row(r);
    clon.remove_column(c);

    //clon.show();

    return determinant(&clon);
}
//conjugate_matrix: Calcula la matriz de cofactores de la matriz M y guarda el resultado en la matriz C.
void conjugate_matrix(Matrix* M, int n, Matrix* C){
    for(int r = 0; r < n; r++)
        for(int c = 0; c < n; c++)
            C->set(pow(-1,r+c)*get_minor(M,n,r,c),r,c);
}
//transpose: Transpone la matriz M y guarda el resultado en la matriz T.
void transpose(Matrix* M, int n, int m, Matrix* T){
    for(int r = 0; r < n; r++)
        for(int c = 0; c < m; c++)
            T->set(M->get(r,c),c,r);
}

//cholesky_decomposition: Realiza la descomposición de Cholesky de la matriz M y guarda el resultado en la matriz L.
void cholesky_decomposition(Matrix* M, int n, Matrix* L) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            float sum = 0;
            if (j == i) {
                for (int k = 0; k < j; k++)
                    sum += pow(L->get(j, k), 2);
                L->set(sqrt(M->get(j, j) - sum), j, j);
            } else {
                for (int k = 0; k < j; k++)
                    sum += (L->get(i, k) * L->get(j, k));
                L->set((M->get(i, j) - sum) / L->get(j, j), i, j);
            }
        }
    }
}
//back_substitution: Resuelve el sistema lineal de ecuaciones Ux = y, donde U es una matriz triangular superior, y devuelve el vector solución.
Vector back_substitution(Matrix* U, Vector* y) {
    int n = U->get_nrows();
    Vector x(n);
    for (int i = n - 1; i >= 0; i--) {
        float sum = 0;
        for (int j = i + 1; j < n; j++)
            sum += U->get(i, j) * x.get(j);
        x.set((y->get(i) - sum) / U->get(i, i), i);
    }
    return x;
}
//forward_substitution: Resuelve el sistema lineal de ecuaciones Lb = y, donde L es una matriz triangular inferior, y devuelve el vector solución.
Vector forward_substitution(Matrix* L, Vector* b) {
    int n = L->get_nrows();
    Vector y(n);
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < i; j++)
            sum += L->get(i, j) * y.get(j);
        y.set((b->get(i) - sum) / L->get(i, i), i);
    }
    return y;
}
//calculate_inverse: Calcula la inversa de la matriz M usando la descomposición de Cholesky y la sustitución hacia atrás y hacia adelante. La matriz inversa se guarda en la matriz R.
void calculate_inverse(Matrix* M, int n, Matrix* R) {
    cout << "\t\tCalculating Cholesky Decomposition...\n\n";
    Matrix L(n, n);
    cholesky_decomposition(M, n, &L);

    cout << "\t\tSolving for Y in L * Y = I...\n\n";
    Matrix Y(n, n);
    for (int i = 0; i < n; i++) {
        Vector column(n);
        for (int j = 0; j < n; j++) {
            column.set((i == j) ? 1.0 : 0.0, j);  // Creating identity matrix column by column
        }
        Vector y = forward_substitution(&L, &column);
        for (int j = 0; j < n; j++) {
            Y.set(y.get(j), j, i);
        }
    }

    cout << "\t\tSolving for X in L^T * X = Y...\n\n";
    Matrix L_T(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L_T.set(L.get(j, i), i, j);  // Transposing L manually
        }
    }
    for (int i = 0; i < n; i++) {
        Vector column(n);
        for (int j = 0; j < n; j++) {
            column.set(Y.get(j, i), j);
        }
        Vector x = back_substitution(&L_T, &column);
        for (int j = 0; j < n; j++) {
            R->set(x.get(j), j, i);
        }
    }
}
