#include <iostream>
#include <cstdio>
#include <fstream>
#include <string.h>

using namespace std;

typedef enum
{
   Carro,
   Camioneta,
   Minibus,
   Camion,
   Emergencia
}TipoVehiculo;

typedef enum
{
    Izquierda,
    Derecha,
    NoGirar
}Girar;

typedef struct
{
    int PosX;
    int PosY;
    TipoVehiculo tipo = Carro;
    int velocidad;
    int Hab_Chofer;
    Girar girar = NoGirar;
    int color; //1=rojo, 2=azul, 3=verde, 4=amarillo
}vehiculo;

typedef enum
{
    CalleVertical,
    CalleHorizontal,
    Hierba,
    Interseccion
}TipoCalle;

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
    TipoCalle tipo = Hierba;
}CalleTile;

int leerVehiculos(vehiculo **car);
int agregarVehiculos(vehiculo **car, int tamAnterior);
int eliminarVehiculo(vehiculo **car, int cant);

int main()
{
    vehiculo **vehiculos;
    vehiculos = new vehiculo*[0];
    int vehiculoCant = 0;
    vehiculoCant = leerVehiculos(vehiculos);
    //vehiculoCant = eliminarVehiculo(vehiculos, vehiculoCant);
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

int eliminarVehiculo(vehiculo **car, int cant)
{
    int eliminar;
    vehiculo carBuffer;
    printf("\n-------------------------------------------------------------------------");
    printf("\n|#\t|\tTipo\t|Velocidad\t|Hab. del chofer|Color\t\t|");
    printf("\n-------------------------------------------------------------------------");
    char tipo[11];
    char color[9];
    for(int i=0; i<cant+1; i++)
    {
        switch(car[i]->tipo)
        {
        case Carro:
            strncpy(tipo, "Carro", 11);
            break;
        case Camioneta:
            strncpy(tipo, "Camioneta", 11);
            break;
        case Minibus:
            strncpy(tipo, "Minibus", 11);
            break;
        case Camion:
            strncpy(tipo, "Camion", 11);
            break;
        case Emergencia:
            strncpy(tipo, "Emergencia", 10);
            break;
        }
        switch(car[i]->color)
        {
        case 1:
            strncpy(color, "Rojo", 9);
            break;
        case 2:
            strncpy(color, "Azul", 9);
            break;
        case 3:
            strncpy(color, "Verde", 9);
            break;
        case 4:
            strncpy(color, "Amarillo", 9);
            break;
        }
        printf("\n|%d\t|%10s\t|%d\t\t|%d\t\t|%9s\t|", i+1, tipo, car[i]->velocidad, car[i]->Hab_Chofer, color);
    }
    printf("\n-------------------------------------------------------------------------");
    do
    {
        printf("\n-Numero del vehiculo a eliminar: ");
        cin >> eliminar;
    }while(eliminar<1||eliminar>(cant+1));

    fstream archivo("file.dat", ios::in|ios::out|ios::trunc);
    if(!archivo.is_open())
    {
        cout << "No se puede abrir el archivo " << endl;
        return -1;
    }

    for(int i=0; i<cant+1; i++)
    {
        carBuffer = *car[i];
        delete car[i];
        if(eliminar!=i+1)
        {
            archivo.write((char*)&carBuffer.tipo, sizeof(carBuffer.tipo));
            archivo.write((char*)&carBuffer.velocidad, sizeof(carBuffer.velocidad));
            archivo.write((char*)&carBuffer.PosX, sizeof(carBuffer.PosX));
            archivo.write((char*)&carBuffer.PosY, sizeof(carBuffer.PosY));
            archivo.write((char*)&carBuffer.Hab_Chofer, sizeof(carBuffer.Hab_Chofer));
            archivo.write((char*)&carBuffer.girar, sizeof(carBuffer.girar));
            archivo.write((char*)&carBuffer.color, sizeof(carBuffer.color));
            archivo.flush();
        }
    }
    archivo.close();
    cant = leerVehiculos(car);
    return cant;
}

int leerVehiculos(vehiculo **car)
{
    vehiculo carBuffer;
    ifstream archivo("file.dat", ios::in|ios::app);
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
    total = (archivo.tellg()/sizeof(vehiculo));
    printf("TOTAL: %d\n\n", total);
    archivo.seekg(0, ios::beg);
    for(int i=0; i<total; i++)
    {
        car[i] = new vehiculo;

        archivo.read((char*)&carBuffer.tipo, sizeof(carBuffer.tipo));
        archivo.read((char*)&carBuffer.velocidad, sizeof(carBuffer.velocidad));
        archivo.read((char*)&carBuffer.PosX, sizeof(carBuffer.PosX));
        archivo.read((char*)&carBuffer.PosY, sizeof(carBuffer.PosY));
        archivo.read((char*)&carBuffer.Hab_Chofer, sizeof(carBuffer.Hab_Chofer));
        archivo.read((char*)&carBuffer.girar, sizeof(carBuffer.girar));
        archivo.read((char*)&carBuffer.color, sizeof(carBuffer.color));

        car[i]->tipo = carBuffer.tipo;
        car[i]->velocidad = carBuffer.velocidad;
        car[i]->PosX = carBuffer.PosX;
        car[i]->PosY = carBuffer.PosY;
        car[i]->Hab_Chofer = carBuffer.Hab_Chofer;
        car[i]->girar = carBuffer.girar;
        car[i]->color = carBuffer.color;

        cout << endl << "#" << i+1 << " " << car[i]->tipo << ", " << car[i]->velocidad;
    }

    archivo.close();
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
    int tipo;
    do
    {
        printf("\nCarro #%d", i+1);
        do
        {
            printf("\nTipo de vehiculo:\n1.Carro\n2.Camioneta\n3.Minibus\n4.Camion\n5.De Emergencia\n\nIngrese el tipo: ");
            cin >> tipo;
            switch(tipo)
            {
            case 1:
                carBuffer.tipo = Carro;
                break;
            case 2:
                carBuffer.tipo = Camioneta;
                break;
            case 3:
                carBuffer.tipo = Minibus;
                break;
            case 4:
                carBuffer.tipo = Camion;
                break;
            case 5:
                carBuffer.tipo = Emergencia;
                break;
            default:
                printf("\nERROR: TIPO NO ENCONTRADO");
                break;
            }
        }while(tipo<1||tipo>5);

        do
        {
            printf("\nColor del vehiculo:\n1.Rojo\n2.Azul\n3.Verde\n4.Amarillo\n\nIngrese el color: ");
            cin >> carBuffer.color;
        }while(carBuffer.color<1||carBuffer.color>4);

        printf("\nHabilidad del chofer(numero entero): ");
        cin >> carBuffer.Hab_Chofer;
        carBuffer.velocidad = carBuffer.Hab_Chofer/10;
        carBuffer.PosX = 0;
        carBuffer.PosY = 0;
        carBuffer.girar = NoGirar;

        archivo.write((char*)&carBuffer.tipo, sizeof(carBuffer.tipo));
        archivo.write((char*)&carBuffer.velocidad, sizeof(carBuffer.velocidad));
        archivo.write((char*)&carBuffer.PosX, sizeof(carBuffer.PosX));
        archivo.write((char*)&carBuffer.PosY, sizeof(carBuffer.PosY));
        archivo.write((char*)&carBuffer.Hab_Chofer, sizeof(carBuffer.Hab_Chofer));
        archivo.write((char*)&carBuffer.girar, sizeof(carBuffer.girar));
        archivo.write((char*)&carBuffer.color, sizeof(carBuffer.color));
        archivo.flush();
        car[i] = new vehiculo;

        car[i]->tipo = carBuffer.tipo;
        car[i]->velocidad = carBuffer.velocidad;
        car[i]->PosX = carBuffer.PosX;
        car[i]->PosY = carBuffer.PosY;
        car[i]->Hab_Chofer = carBuffer.Hab_Chofer;
        car[i]->girar = carBuffer.girar;
        car[i]->color = carBuffer.color;

        printf("\n---------------------------------------------------\n");
        cout << car[i]->tipo << ", " << car[i]->velocidad;
        printf("\n\n**Desea agregar otro?: ");
        cin >> n;
        if(n)
            i++;
    }while(n);

    archivo.close();
    return i;
}
