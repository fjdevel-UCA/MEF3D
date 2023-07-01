class Node {
    private:
        int ID;
        float x_coordinate;
        float y_coordinate;
        float z_coordinate;// Agregamos la coordenada z para el problema 3D

    public:
        Node(int identifier, float x_value, float y_value,float z_value){
            ID = identifier;
            x_coordinate = x_value;
            y_coordinate = y_value;
            z_coordinate = z_value;// Inicializamos la coordenada z
        }

        void set_ID(int identifier){
            ID = identifier;
        }
        int get_ID(){
            return ID;
        }
        // Los métodos set y get se mantienen igual, solo agregamos los correspondientes a z

        void set_x_coordinate(float x_value){
            x_coordinate = x_value;
        }
        float get_x_coordinate(){
            return x_coordinate;
        }

        void set_y_coordinate(float y_value){
            y_coordinate = y_value;
        }
        float get_y_coordinate(){
            return y_coordinate;
        }
        void set_z_coordinate(float z_value){
            z_coordinate = z_value;
        }
        float get_z_coordinate(){
            return z_coordinate;
        }
};
