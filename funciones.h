#define MAX_DIAS 100

struct Dia {
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

void crearArchivo(char *nombre, int *num_dias);
void leercadena(char *cadena, int longitud);
void addDia(char *nombre, int *num_dias);
void leerDatosZona(char *nombre, int *num_dias, struct Dia dias[]);
//void leerDatosZona(char *nombre);
//void agregarFechasHistoricas(char *nombre);
//double calcularAQI(double NO2, double CO2, double PM25, double SO2, double temperatura, double humedad, double velocidad_aire);