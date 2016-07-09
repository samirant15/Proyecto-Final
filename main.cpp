#include <iostream>
#include <cstdio>
#include <fstream>
#include <string.h>

using namespace std;

typedef struct
{
    int velocidad;
    char tipo[50];
}vehiculo;

typedef enum
{
   Carro,
   Camioneta,
   Minibus,
   Camion,
   Emergencia
}TipoVeh;

typedef enum
{
    Izquierda,
    Derecha,
    NoGirar
}Girar;

typedef enum
{
    calleVertical,
    calleHorizontal,
    curvaH_LL,
    curvaH_LR,
    curvaH_RL,
    curvaH_RR,
    curvaV_UL,
    curvaV_UR,
    curvaV_DL,
    curvaV_DR
}TipoCalle;

typedef struct
{
    int PosX;
    int PosY;
    TipoVeh Veh;
    int velocidad;
    int Hab_Chofer;
}Carro;

typedef struct
{
    int PosX;
    int PosY;
    int TiempoRojo;
    int TiempoAmarillo;
    int TiempoVerde;
}Semaforo;

typedef struct
{
    int PosX;
    int PosY;
    char TipoCalle[10];
}CalleTile;

typedef struct
{
    int PosX;
    int PosY;
}HierbaTile;



int leerVehiculos(vehiculo **car);
int agregarVehiculos(vehiculo **car, int tamAnterior);

int main()
{
    vehiculo **vehiculos;
    vehiculos = new vehiculo*[0];
    int vehiculoCant = 0;
    vehiculoCant = leerVehiculos(vehiculos);
    vehiculoCant = agregarVehiculos(vehiculos, vehiculoCant);

    printf("\n---------------------------------------------------\n");
    for(int k=0; k<vehiculoCant+1; k++)
    {
        printf("\n*Carro #%d:\n", k+1);
        printf("\nvelocidad: ");
        cout << vehiculos[k]->velocidad;
        printf("\ntipo: ");
        cout << vehiculos[k]->tipo;
    }
    printf("\n---------------------------------------------------\n");
}

int leerVehiculos(vehiculo **car)
{
    vehiculo carBuffer;
    ifstream archivo("file.dat");
    if(!archivo.is_open())
    {
        cout << "No se puede abrir el archivo " << endl;
        return 0;
    }
    archivo.seekg(0, ios::end);
    if(archivo.tellg() == 0)
    {
        cout << "Vacio" << endl;
        return -1;
    }
    int total;
    total = (archivo.tellg()/sizeof(vehiculo))+1;
    printf("TOTAL: %d\n\n", total);
    archivo.seekg(0, ios::beg);
    for(int i=0; i<total; i++)
    {
        car[i] = new vehiculo;
        archivo.read((char*)&carBuffer.tipo, sizeof(carBuffer.tipo));
        archivo.read((char*)&carBuffer.velocidad, sizeof(carBuffer.velocidad));
        strncpy(car[i]->tipo, carBuffer.tipo, 50);
        car[i]->velocidad = carBuffer.velocidad;
        cout << endl << "#" << i+1 << " " << car[i]->tipo << ", " << car[i]->velocidad;
    }
    return total-1;
}

int agregarVehiculos(vehiculo **car, int tamAnterior)
{
    vehiculo carBuffer;
    fstream archivo("file.dat", ios::in|ios::out|ios::app);
    if(!archivo.is_open())
    {
        cout << "No se puede abrir el archivo " << endl;
        return -1;
    }
    int n = 0;
    int i=tamAnterior+1;
    do
    {
        printf("\nCarro #%d", i+1);
        printf("\nvelocidad: ");
        cin >> carBuffer.velocidad;
        printf("tipo: ");
        cin >> carBuffer.tipo;
        archivo.write((char*)&carBuffer.tipo, sizeof(carBuffer.tipo));
        archivo.write((char*)&carBuffer.velocidad, sizeof(carBuffer.velocidad));
        archivo.flush();
        car[i] = new vehiculo;
        strncpy(car[i]->tipo, carBuffer.tipo, 50);
        car[i]->velocidad = carBuffer.velocidad;
        printf("\n---------------------------------------------------\n");
        cout << car[i]->tipo << ", " << car[i]->velocidad;
        printf("\n\n**Desea agregar otro?: ");
        cin >> n;
        if(n)
            i++;
    }while(n);

    return i;
}
