
struct Contaminantes
{
    double PM25;
    double NO2;
    double SO2;
    double CO;
    double I_low, I_high, AQI_low, AQI_high;
    double sumaConcentraciones;
    double promedio;
};

struct Zonas
{
    char nomZona[50];
    int TotalMediciones;
    int nZonas;
    double cpPM25;
    double cpNO2;
    double cpSO2;
    double cpCO;
    struct Contaminantes contaminantes[20];
};

void menu();
void leercadena(char *cadena, int longitud);
void creatDatZona();
void leerDatZona();
void mostrarContaminante(double contaminante);
double calcularAQI(double C, double I_low, double I_high, double AQI_low, double AQI_high);
double CpPM25(double numMediciones, double sumaConcentraciones, struct Zonas *zona);
double CpNO2(double numMediciones, double sumaConcentraciones, struct Zonas *zona);
double CpSO2(double numMediciones, double sumaConcentraciones, struct Zonas *zona);
double CpCO(double numMediciones, double sumaConcentraciones, struct Zonas *zona);
int findByZoneName(char *name);
void updateZone(struct Zonas *zona, int posicion);
void actualizarZona();
void deleateZona();
double predectContaminante(double contaminante, double temperatura, double humedad, double velocidad);
void predectZona();
