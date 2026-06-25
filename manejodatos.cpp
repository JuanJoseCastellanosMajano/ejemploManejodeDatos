#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Structura que almacena la información de un videojuego
struct VideoJuego
{
    int codigo;
    string nombre;
    string plataforma;
    float precio;
    int stock;
};

// Prototipos de funciones
void crearJuego();
void mostrarVideojuegos();
void buscarJuego();
void actualizarJuego();
void generarReporte();

int main()
{
    int opcion;
        //Menu de toda la vida
    do
    {
        cout << "\n===== INVENTARIO DE VIDEOJUEGOS =====\n";
        cout << "1. Agregar juego\n";
        cout << "2. Mostrar juegos\n";
        // estas opciones son secundarias solo queríamos terminar el código XD
        cout << "3. Buscar juego\n";
        cout << "4. Actualizar juego\n";
        cout << "5. Generar reporte\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            crearJuego();
            break;

        case 2:
            mostrarVideojuegos();
            break;

        case 3:
            buscarJuego();
            break;

        case 4:
            actualizarJuego();
            break;

        case 5:
            generarReporte();
            break;

        case 6:
            cout << "Programa finalizado.\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 6);

    return 0;
}

/*
    FUNCION: crearJuego()

    Solicita los datos de un videojuego y los almacena
    en el archivo inventario.txt.

    Se utiliza ofstream porque estamos escribiendo
    información en un archivo.
*/
void crearJuego()
{
    VideoJuego v;

    cout << "\nCodigo: ";
    cin >> v.codigo;
    // recuerden que el cin.ignore es para utilizar en bucle el getline
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, v.nombre);

    cout << "Plataforma: ";
    getline(cin, v.plataforma);

    cout << "Precio: ";
    cin >> v.precio;

    cout << "Stock: ";
    cin >> v.stock;
 /*
    ios::app permite agregar registros al final
    sin borrar los existentes, sin este estamos sobreescribiendo.
 */
    ofstream archivo("inventario.txt", ios::app);

    if (archivo.is_open())
    {
        archivo << v.codigo << ""
                << v.nombre << ""
                << v.plataforma << ""
                << v.precio << ""
                << v.stock << endl;
        //siempre pongan el .close
        archivo.close();

        cout << "Juego agregado correctamente.\n";
    }
    else
    {
        cout << "Error al abrir el archivo.\n";
    }
}

/*
    FUNCION: mostrarVideojuegos()

    Lee todos los registros almacenados en el archivo
    y los muestra en pantalla.

    Se utiliza ifstream porque solamente se necesita
    leer información.
*/
void mostrarVideojuegos()
{
    // recuerden indicar la dirección del archivo si no está en la misma carpeta
    ifstream archivo("inventario.txt");

    string linea;


    //!algo es la negación de la condición es como la negación en tablas de verdad
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    cout << "\n===== LISTA DE VIDEOJUEGOS =====\n";

    while (getline(archivo, linea))
    {
        cout << linea << endl;
    }
    // siempre pongan el .close X2
    archivo.close();
}

/*
    FUNCION: buscarJuego()

    Busca un videojuego por su código.
*/
void buscarJuego()
{
    int codigoBuscado;
    cout << "\nIngrese el codigo a buscar: ";
    cin >> codigoBuscado;
    // recuerden revisar que el texto o tenga la dirección o esté en la misma carpeta
    ifstream archivo("inventario.txt");
    // si solo tiene el nombre están en la misma carpeta
    VideoJuego v;
    char separador;

    bool encontrado = false;

    while (archivo >> v.codigo >> separador)
    {
        getline(archivo, v.nombre, ';');
        getline(archivo, v.plataforma, ';');
        archivo >> v.precio >> separador >> v.stock;
        archivo.ignore();

        if (v.codigo == codigoBuscado)
        {
            encontrado = true;

            cout << "\nJuego encontrado\n";
            cout << "Codigo: " << v.codigo << endl;
            cout << "Nombre: " << v.nombre << endl;
            cout << "Plataforma: " << v.plataforma << endl;
            cout << "Precio: $" << v.precio << endl;
            cout << "Stock: " << v.stock << endl;

            break;
        }
    }

    if (!encontrado)
    {
        cout << "Juego no encontrado.\n";
    }

    archivo.close();
}

/*
    FUNCION: actualizarJuego()

    Busca un registro por código y actualiza
    sus datos.

    Para hacerlo:
    1. Lee el archivo original.
    2. Crea un archivo temporal.
    3. Copia todos los registros.
    4. Reemplaza el registro encontrado.
*/
void actualizarJuego()
{
    int codigoBuscar;

    cout << "\nCodigo a actualizar: ";
    cin >> codigoBuscar;

    ifstream archivo("inventario.txt");
    ofstream temp("temp.txt");

    VideoJuego v;
    char separador;

    bool encontrado = false;

    while (archivo >> v.codigo >> separador)
    {
        getline(archivo, v.nombre, ';');
        getline(archivo, v.plataforma, ';');
        archivo >> v.precio >> separador >> v.stock;
        archivo.ignore();

        if (v.codigo == codigoBuscar)
        {
            encontrado = true;

            cout << "\nNuevo nombre: ";
            cin.ignore();
            getline(cin, v.nombre);

            cout << "Nueva plataforma: ";
            getline(cin, v.plataforma);

            cout << "Nuevo precio: ";
            cin >> v.precio;

            cout << "Nuevo stock: ";
            cin >> v.stock;
        }

        temp << v.codigo << ";"
             << v.nombre << ";"
             << v.plataforma << ";"
             << v.precio << ";"
             << v.stock << endl;
    }
    // .close no lo olviden
    archivo.close();
    temp.close();

    remove("inventario.txt");
    rename("temp.txt", "inventario.txt");

    if (encontrado)
        cout << "Registro actualizado.\n";
    else
        cout << "Codigo no encontrado.\n";
}

/*
    FUNCION: generarReporte()

    Calcula:
    - Total de videojuegos registrados.
    - Cantidad total en stock.
    - Valor total del inventario.
*/
void generarReporte()
{
    ifstream archivo("inventario.txt");

    VideoJuego v;
    char separador;

    int totalJuegos = 0;
    int stockTotal = 0;
    float valorInventario = 0;

    while (archivo >> v.codigo >> separador)
    {
        getline(archivo, v.nombre, ';');
        getline(archivo, v.plataforma, ';');
        archivo >> v.precio >> separador >> v.stock;
        archivo.ignore();

        totalJuegos++;
        stockTotal += v.stock;
        valorInventario += (v.precio * v.stock);
    }
    // yo les bajaré un punto si a estas alturas no le ponen el .CLOSE
    archivo.close();

    cout << "\n===== REPORTE =====\n";
    cout << "Juegos registrados: " << totalJuegos << endl;
    cout << "Stock total: " << stockTotal << endl;
    cout << "Valor del inventario: $" << valorInventario << endl;
}
