
/**
 Esta función calcula el jacobiano local para un elemento tetraédrico en 3D. El jacobiano es la medida 
 de cómo una función cambia según cambian sus entradas. En este caso, las entradas son las coordenadas 
 de los vértices del tetraedro. El valor de retorno es el determinante de la matriz del jacobiano.*/
float calculate_local_jacobian(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4){
    float J = x3*y2*z1 - x4*y2*z1 - x2*y3*z1 + x4*y3*z1 + x2*y4*z1 - x3*y4*z1 - x3*y1*z2 + x4*y1*z2 + x1*y3*z2 - x4*y3*z2 - x1*y4*z2 + x3*y4*z2 + x2*y1*z3 - x4*y1*z3 - x1*y2*z3 + x4*y2*z3 + x1*y4*z3 - x2*y4*z3 - x2*y1*z4 + x3*y1*z4 + x1*y2*z4 - x3*y2*z4 - x1*y3*z4 + x2*y3*z4;
    return ((J==0)?0.000001:J);
}

/**
 * Calcula el volumen local de un tetraedro en 3D.
 *
 * Esta función calcula el volumen de un tetraedro arbitrario definido por cuatro puntos en el espacio 3D.
 * Los puntos son pasados como coordenadas (x, y, z).
 * Si el volumen calculado es 0, la función devuelve un valor muy pequeño para evitar divisiones por cero en cálculos posteriores.

 * Volumen del tetraedro. Si el volumen es 0, devuelve 0.000001.
 */
float calculate_local_volume(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4){
    float V = abs((x1*(y2*z3 + y3*z4 + y4*z2) - y1*(x2*z3 + x3*z4 + x4*z2) + z1*(x2*y3 + x3*y4 + x4*y2)) - (x1*(y3*z4 + y4*z3 + y2*z4) - y1*(x3*z4 + x4*z3 + x2*z4) + z1*(x3*y4 + x4*y3 + x2*y4)))/6;
    return ((V==0)?0.000001:V);
}




/**
 * Calcula la matriz B para un elemento tetraédrico en 3D.
 *
 * Esta función calcula la matriz B para un elemento tetraédrico en 3D. 
 * La matriz B contiene las derivadas de las funciones de forma con respecto a las coordenadas baricéntricas xi, eta, y zeta.
 * Para un elemento tetraédrico, estas derivadas son constantes.
 *
 *  B Matriz B a calcular.
 */
void calculate_B(Matrix* B){
    B->set_size(4,4);
    B->set(-1,0,0);  B->set(1,0,1);  B->set(0,0,2);  B->set(0,0,3);
    B->set(-1,1,0);  B->set(0,1,1);  B->set(1,1,2);  B->set(0,1,3);
    B->set(-1,2,0);  B->set(0,2,1);  B->set(0,2,2);  B->set(1,2,3);
    B->set(-1,3,0);  B->set(0,3,1);  B->set(0,3,2);  B->set(1,3,3);
}


/**
 *  Calcula la matriz local A para un elemento tetraédrico en 3D.
 *
 * Esta función calcula la matriz local A para un elemento tetraédrico en 3D. 
 * La matriz A se calcula a partir de las coordenadas de los nodos del elemento.
 *
 * Matriz local A a calcular.
 */
void calculate_local_A(Matrix* A, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4){
    A->set_size(4,4);

    A->set(y3-y1, 0, 0);   A->set(x1-x3, 0, 1);   A->set(z1-z3, 0, 2);
    A->set(y1-y2, 1, 0);   A->set(x2-x1, 1, 1);   A->set(z2-z1, 1, 2);
    A->set(y2-y4, 2, 0);   A->set(x4-x2, 2, 1);   A->set(z4-z2, 2, 2);
    A->set(y4-y3, 3, 0);   A->set(x3-x4, 3, 1);   A->set(z3-z4, 3, 2);
}

/**
 * Calcula la matriz de rigidez local para un elemento tetraédrico en 3D.
* Esta función calcula la matriz de rigidez local K para un elemento tetraédrico en 3D. 
 * La matriz K se calcula como el producto de la matriz B transpuesta, la matriz A, la matriz B y el jacobiano local J, 
 * todo ello multiplicado por la conductividad térmica k y dividido por el cuadrado del jacobiano.
 * La matriz B es una matriz constante para los elementos tetraédricos, mientras que la matriz A y el jacobiano se calculan a partir de las coordenadas de los nodos del elemento.
 *
 * element_id El ID del elemento para el que se calculará la matriz de rigidez.
 *  M Un puntero a la malla que contiene el elemento.
 *  K Un puntero a la matriz donde se almacenará la matriz de rigidez calculada.
 */
void create_local_K(Matrix* K, int element_id, Mesh* M){
    K->set_size(4,4);

    float k = M->get_problem_data(THERMAL_CONDUCTIVITY);
    float x1 = M->get_element(element_id)->get_node1()->get_x_coordinate(), y1 = M->get_element(element_id)->get_node1()->get_y_coordinate(), z1 = M->get_element(element_id)->get_node1()->get_z_coordinate();
    float x2 = M->get_element(element_id)->get_node2()->get_x_coordinate(), y2 = M->get_element(element_id)->get_node2()->get_y_coordinate(), z2 = M->get_element(element_id)->get_node2()->get_z_coordinate();
    float x3 = M->get_element(element_id)->get_node3()->get_x_coordinate(), y3 = M->get_element(element_id)->get_node3()->get_y_coordinate(), z3 = M->get_element(element_id)->get_node3()->get_z_coordinate();
    float x4 = M->get_element(element_id)->get_node4()->get_x_coordinate(), y4 = M->get_element(element_id)->get_node4()->get_y_coordinate(), z4 = M->get_element(element_id)->get_node4()->get_z_coordinate();
    float Volume = calculate_local_volume(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    float J = calculate_local_jacobian(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);

    Matrix B(4,4), A(4,4);
    calculate_B(&B);
    calculate_local_A(&A, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
/*B.show(); A.show();*/
    Matrix Bt(4,4), At(4,4);
    transpose(&B,4,4,&Bt);
    transpose(&A,4,4,&At);
/*Bt.show(); At.show();*/
    Matrix res1, res2, res3;
    product_matrix_by_matrix(&A,&B,&res1);
    product_matrix_by_matrix(&At,&res1,&res2);
    product_matrix_by_matrix(&Bt,&res2,&res3);
    product_scalar_by_matrix(k*Volume/(J*J),&res3,4,4,K);
}

/**
 * Crea el vector de carga local b para un elemento tetraédrico en 3D.
 *
 * Esta función calcula el vector de carga local b para un elemento tetraédrico en 3D. 
 * El vector b se calcula como el producto de la fuente de calor Q, el volumen del tetraedro y 1/24.
 * Si el jacobiano es cero, se devuelve un valor pequeño para evitar la división por cero en los cálculos posteriores.
 *
 * b Vector de carga local a calcular.
 * element_id ID del elemento para el que se va a calcular el vector b.
 * M Malla que contiene la información del problema y de los elementos.
 */
void create_local_b(Vector* b, int element_id, Mesh* M){
    b->set_size(4);

    float Q = M->get_problem_data(HEAT_SOURCE);
    float x1 = M->get_element(element_id)->get_node1()->get_x_coordinate(), y1 = M->get_element(element_id)->get_node1()->get_y_coordinate(), z1 = M->get_element(element_id)->get_node1()->get_z_coordinate(),
          x2 = M->get_element(element_id)->get_node2()->get_x_coordinate(), y2 = M->get_element(element_id)->get_node2()->get_y_coordinate(), z2 = M->get_element(element_id)->get_node2()->get_z_coordinate(),
          x3 = M->get_element(element_id)->get_node3()->get_x_coordinate(), y3 = M->get_element(element_id)->get_node3()->get_y_coordinate(), z3 = M->get_element(element_id)->get_node3()->get_z_coordinate(),
          x4 = M->get_element(element_id)->get_node4()->get_x_coordinate(), y4 = M->get_element(element_id)->get_node4()->get_y_coordinate(), z4 = M->get_element(element_id)->get_node4()->get_z_coordinate();
    float V = calculate_local_volume(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);

    b->set(Q*V/24,0);
    b->set(Q*V/24,1);
    b->set(Q*V/24,2);
    b->set(Q*V/24,3);

    //cout << "\t\tLocal vector created for Element " << element_id+1 << ": "; b->show(); cout << "\n";
}


/**
 *Crea los sistemas locales para todos los elementos en la malla.
 *
 * Esta función crea las matrices de rigidez local K y los vectores de carga local b para todos los elementos en la malla. 
 * Cada elemento es un tetraedro en 3D, por lo que las matrices K y los vectores b son de tamaño 4.
 *
 * Ks Matrices de rigidez locales para todos los elementos.
 *bs Vectores de carga locales para todos los elementos.
 * num_elements Número de elementos en la malla.
 * M Malla que contiene la información del problema y de los elementos.
 */
void create_local_systems(Matrix* Ks, Vector* bs, int num_elements, Mesh* M){
    for(int e = 0; e < num_elements; e++){
        cout << "\tCreating local system for Element " << e+1 << "...\n\n";
        create_local_K(&Ks[e],e,M);
        create_local_b(&bs[e],e,M);
    }
}

 /* Esta función agrega la matriz de rigidez local de un elemento a la matriz de rigidez global K 
 en las posiciones correspondientes a los índices de los nodos del elemento.*/

void assembly_K(Matrix* K, Matrix* local_K, int index1, int index2, int index3, int index4){
    K->add(local_K->get(0,0),index1,index1);    K->add(local_K->get(0,1),index1,index2);    K->add(local_K->get(0,2),index1,index3);    K->add(local_K->get(0,3),index1,index4);
    K->add(local_K->get(1,0),index2,index1);    K->add(local_K->get(1,1),index2,index2);    K->add(local_K->get(1,2),index2,index3);    K->add(local_K->get(1,3),index2,index4);
    K->add(local_K->get(2,0),index3,index1);    K->add(local_K->get(2,1),index3,index2);    K->add(local_K->get(2,2),index3,index3);    K->add(local_K->get(2,3),index3,index4);
    K->add(local_K->get(3,0),index4,index1);    K->add(local_K->get(3,1),index4,index2);    K->add(local_K->get(3,2),index4,index3);    K->add(local_K->get(3,3),index4,index4);
}
/* Esta función agrega el vector de carga local de un elemento al vector de carga global b 
en las posiciones correspondientes a los índices de los nodos del elemento.*/

void assembly_b(Vector* b, Vector* local_b, int index1, int index2, int index3, int index4){
    b->add(local_b->get(0),index1);
    b->add(local_b->get(1),index2);
    b->add(local_b->get(2),index3);
    b->add(local_b->get(3),index4);
}

/**
 *  Realiza el ensamblaje de las matrices y vectores locales en las matrices y vectores globales.
 *
 * Esta función realiza el ensamblaje de las matrices y vectores locales en las matrices y vectores globales.
 * Para cada elemento de la malla, se obtienen los índices de los nodos del elemento y se utilizan para ensamblar las matrices y vectores locales en las matrices y vectores globales.
 *
 * Matriz global de rigidez a ensamblar.
 * Vector global de cargas a ensamblar.
 * Matrices locales de rigidez.
 * Vectores locales de cargas.
 * Número de elementos en la malla.
 * Malla que contiene la información del problema y de los elementos.
 */
void assembly(Matrix* K, Vector* b, Matrix* Ks, Vector* bs, int num_elements, Mesh* M){
    K->init();
    b->init();

    for(int e = 0; e < num_elements; e++){
        int index1 = M->get_element(e)->get_node1()->get_ID() - 1;
        int index2 = M->get_element(e)->get_node2()->get_ID() - 1;
        int index3 = M->get_element(e)->get_node3()->get_ID() - 1;
        int index4 = M->get_element(e)->get_node4()->get_ID() - 1;

        assembly_K(K, &Ks[e], index1, index2, index3, index4);
        assembly_b(b, &bs[e], index1, index2, index3, index4);
    }
}
// Aplica condiciones de contorno de Neumann a un vector dado.
    // b: Puntero al vector en el que se aplicarán las condiciones.
    // M: Puntero a la malla que contiene las condiciones de contorno de Neumann.

void apply_neumann_boundary_conditions(Vector* b, Mesh* M){
    int num_conditions = M->get_quantity(NUM_NEUMANN);

    for(int c = 0; c < num_conditions; c++){
        Condition* cond = M->get_neumann_condition(c);
        
        int index = cond->get_node()->get_ID() - 1;
        b->add(cond->get_value(), index);
    }
    //cout << "\t\t"; b->show(); cout << "\n";
}
// Agrega una columna a la matriz de la mano derecha (RHS, Right Hand Side) del sistema.
    // K: Puntero a la matriz.
    // b: Puntero al vector donde se añadirá la columna.
    // col: Índice de la columna a añadir.
    // T_bar: Valor de la condición de Dirichlet

void add_column_to_RHS(Matrix* K, Vector* b, int col, float T_bar){
    for(int r = 0; r < K->get_nrows(); r++)
        b->add(-T_bar*K->get(r,col),r);
}
// Aplica las condiciones de contorno de Dirichlet a una matriz y un vector dados.
    // K: Puntero a la matriz en la que se aplicarán las condiciones.
    // b: Puntero al vector en el que se aplicarán las condiciones.
    // M: Puntero a la malla que contiene las condiciones de contorno de Dirichlet.
void apply_dirichlet_boundary_conditions(Matrix* K, Vector* b, Mesh* M){
    int num_conditions = M->get_quantity(NUM_DIRICHLET);
    int previous_removed = 0;

    for(int c = 0; c < num_conditions; c++){
        Condition* cond = M->get_dirichlet_condition(c);
        
        int index = cond->get_node()->get_ID() - 1 - previous_removed;
        float cond_value = cond->get_value();

        //K->show();
        K->remove_row(index);
        //K->show();
        //b->show();
        b->remove_row(index);
        //b->show();

        add_column_to_RHS(K, b, index, cond_value);
        //b->show();

        K->remove_column(index);
        //K->show();

        previous_removed++;
    }
}
 // Resuelve el sistema de ecuaciones lineales.
    // K: Puntero a la matriz de coeficientes del sistema.
    // b: Puntero al vector de términos independientes del sistema.
    // T: Puntero al vector de resultados.

void solve_system(Matrix* K, Vector* b, Vector* T){
    int n = K->get_nrows();
    
    Matrix Kinv(n,n);

    cout << "\tCalculating inverse of global matrix K...\n\n";
    calculate_inverse(K, n, &Kinv);

    cout << "\tPerforming final calculation...\n\n";
    product_matrix_by_vector(&Kinv, b, n, n, T);
}
// Fusiona los resultados con las condiciones de contorno de Dirichlet.
    // T: Puntero al vector de resultados de las ecuaciones.
    // Tf: Puntero al vector final que contendrá la fusión de los resultados con las condiciones de Dirichlet.
    // n: Número total de nodos en la malla.
    // M: Puntero a la malla que contiene las condiciones de contorno de Dirichlet.
void merge_results_with_dirichlet(Vector* T, Vector* Tf, int n, Mesh* M){
    int num_dirichlet = M->get_quantity(NUM_DIRICHLET);

    int cont_dirichlet = 0;
    int cont_T = 0;
    for(int i = 0; i < n; i++){
        if(M->does_node_have_dirichlet_condition(i+1)){
            Condition* cond = M->get_dirichlet_condition(cont_dirichlet);
            cont_dirichlet++;
        
            float cond_value = cond->get_value();

            Tf->set(cond_value,i);
        }else{
            Tf->set(T->get(cont_T),i);
            cont_T++;
        }
    }
}
