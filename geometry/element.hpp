class Element {
    private:
        int ID;
        Node* node1;
        Node* node2;
        Node* node3;
        Node* node4;// Agregamos el cuarto nodo para el tetraedro

    public:
        Element (int identifier, Node* first_node, Node* second_node, Node* third_node,Node* four_node){
            ID = identifier;
            node1 = first_node;
            node2 = second_node;
            node3 = third_node;
            node4 = four_node;// Inicializamos el cuarto nodo
        }

        void set_ID(int identifier){
            ID = identifier;
        }
        int get_ID(){
            return ID;
        }
// Los métodos set y get se mantienen igual, solo agregamos los correspondientes al cuarto nodo

        void set_node1(Node* node){
            node1 = node;
        }
        Node* get_node1(){
            return node1;
        }

        void set_node2(Node* node){
            node2 = node;
        }
        Node* get_node2(){
            return node2;
        }

        void set_node3(Node* node){
            node3 = node;
        }
        Node* get_node3(){
            return node3;
        }
        //Agregando set y get del nodo 4
        void set_node4(Node* node){
            node4 = node;
        }
        Node* get_node4(){
            return node4;
        }
};