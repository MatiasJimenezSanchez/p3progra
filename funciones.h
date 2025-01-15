struct Dia
{
    int numDia;

    double CO2;
    double SO2;
    double NO2;
    double PM25;

    double temperatura;
    double humedad;
    double velocidad_aire;

    double AQI;
};


void crearArchivo(char* nombre);
void addDia(char* nombre);
void leerDatos(char* nombre);
void mostrarContaminante(double contaminante);