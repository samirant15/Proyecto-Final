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


int leer(vehiculo **car);

int main()
{
    vehiculo carBuffer;
    vehiculo **car;
    car = new vehiculo*[0];

    fstream archivo("file.dat", ios::in|ios::out|ios::app);
    if(!archivo.is_open())
    {
        cout << "No se puede abrir el archivo " << endl;
        return -1;
    }
    int n = 0;
    int i=leer(car)+1;
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
    printf("\n---------------------------------------------------\n");
    for(int k=0; k<i+1; k++)
    {
        printf("\n*Carro #%d:\n", k+1);
        printf("\nvelocidad: ");
        cout << car[k]->velocidad;
        printf("\ntipo: ");
        cout << car[k]->tipo;
    }
    printf("\n---------------------------------------------------\n");
}

int leer(vehiculo **car)
{
    vehiculo carBuffer;
    ifstream archivo("file.dat");
    if(!archivo.is_open())
    {
        cout << "No se puede abrir el archivo " << endl;
        return 0;
    }
    archivo.seekg(0, ios::end);
    int total;
    total = (archivo.tellg()/sizeof(vehiculo))+1;
    if(total==0)
        return -1;
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

