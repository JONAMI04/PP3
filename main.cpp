#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "sqlite3.h"
#include <memory>
using namespace std;

// Clase para manejar la base de datos
class DatabaseManager {
private:
    sqlite3* db;
    string dbPath;

public:
    DatabaseManager(const string& path = "C:\\Users\\nahue\\Downloads\\biblioteca.db") : db(nullptr), dbPath(path) {
        if (abrirDB(dbPath)) {
            cout << "Base de datos abierta exitosamente: " << dbPath << endl;
            crearTablasSiNoExisten();
        } else {
            cerr << "Error: No se pudo abrir la base de datos en: " << dbPath << endl;
        }
    }

    ~DatabaseManager() {
        if (db) {
            sqlite3_close(db);
        }
    }

    bool abrirDB(const string& nombreDB) {
        int resultado = sqlite3_open(nombreDB.c_str(), &db);
        if (resultado != SQLITE_OK) {
            cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << endl;
            return false;
        }
        return true;
    }

    bool ejecutarSQL(const string& sql) {
        char* errorMsg = nullptr;
        int resultado = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMsg);

        if (resultado != SQLITE_OK) {
            cerr << "Error SQL: " << errorMsg << endl;
            sqlite3_free(errorMsg);
            return false;
        }
        return true;
    }

    // Método para ejecutar consultas con retorno de datos
    vector<vector<string>> ejecutarConsulta(const string& sql) {
        vector<vector<string>> resultados;
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            int columnas = sqlite3_column_count(stmt);

            while (sqlite3_step(stmt) == SQLITE_ROW) {
                vector<string> fila;
                for (int i = 0; i < columnas; i++) {
                    const char* valor = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                    fila.push_back(valor ? valor : "");
                }
                resultados.push_back(fila);
            }
            sqlite3_finalize(stmt);
        }
        return resultados;
    }

    // Crear tablas basadas en tus archivos CSV
    void crearTablasSiNoExisten() {
        // Tabla de libros
        string sql_libros =
            "CREATE TABLE IF NOT EXISTS libros ("
            "ID_Libro INTEGER PRIMARY KEY,"
            "Titulo TEXT NOT NULL,"
            "Anio TEXT,"
            "Editorial TEXT,"
            "Nombre_Autor TEXT,"
            "Apellido_Autor TEXT,"
            "Genero TEXT,"
            "Cantidad_Total INTEGER,"
            "Cantidad_Disponible INTEGER"
            ");";
        ejecutarSQL(sql_libros);

        // Tabla de revistas
        string sql_revistas =
            "CREATE TABLE IF NOT EXISTS revista ("
            "ID_Revista INTEGER PRIMARY KEY,"
            "Titulo TEXT NOT NULL,"
            "Anio TEXT,"
            "Mes INTEGER,"
            "Nro_Publicacion INTEGER,"
            "Editorial TEXT,"
            "Genero TEXT,"
            "Cantidad_Total INTEGER,"
            "Cantidad_Disponible INTEGER"
            ");";
        ejecutarSQL(sql_revistas);

        // Tabla de tesis
        string sql_tesis =
            "CREATE TABLE IF NOT EXISTS tesis ("
            "ID_Tesis INTEGER PRIMARY KEY,"
            "Titulo TEXT NOT NULL,"
            "Anio INTEGER,"
            "Universidad TEXT,"
            "Carrera TEXT,"
            "Nombre_Autor TEXT,"
            "Apellido_Autor TEXT,"
            "Cantidad_Total INTEGER,"
            "Cantidad_Disponible INTEGER"
            ");";
        ejecutarSQL(sql_tesis);

        // Tabla de usuarios
        string sql_usuarios =
            "CREATE TABLE IF NOT EXISTS usuarios ("
            "ID_Usuario INTEGER PRIMARY KEY,"
            "Nombre_Usuario TEXT,"
            "Apellido_Usuario TEXT,"
            "DNI_Usuario TEXT,"
            "Direccion TEXT,"
            "Telefono TEXT,"
            "Mail TEXT"
            ");";
        ejecutarSQL(sql_usuarios);

        cout << "Tablas verificadas/creadas correctamente." << endl;
    }

    // Métodos para insertar datos
    bool insertarLibro(int id, const string& titulo, const string& anio, const string& editorial,
                      const string& nombre_autor, const string& apellido_autor, const string& genero,
                      int cantidad_total, int cantidad_disponible) {
        string sql = "INSERT INTO libros (ID_Libro, Titulo, Anio, Editorial, Nombre_Autor, Apellido_Autor, Genero, Cantidad_Total, Cantidad_Disponible) "
                    "VALUES (" + to_string(id) + ", '" + titulo + "', '" + anio + "', '" + editorial + "', '" +
                    nombre_autor + "', '" + apellido_autor + "', '" + genero + "', " +
                    to_string(cantidad_total) + ", " + to_string(cantidad_disponible) + ");";
        return ejecutarSQL(sql);
    }

    bool insertarRevista(int id, const string& titulo, const string& anio, int mes, int nro_publicacion,
                        const string& editorial, const string& genero, int cantidad_total, int cantidad_disponible) {
        string sql = "INSERT INTO revista (ID_Revista, Titulo, Anio, Mes, Nro_Publicacion, Editorial, Genero, Cantidad_Total, Cantidad_Disponible) "
                    "VALUES (" + to_string(id) + ", '" + titulo + "', '" + anio + "', " + to_string(mes) + ", " +
                    to_string(nro_publicacion) + ", '" + editorial + "', '" + genero + "', " +
                    to_string(cantidad_total) + ", " + to_string(cantidad_disponible) + ");";
        return ejecutarSQL(sql);
    }

    bool insertarTesis(int id, const string& titulo, int anio, const string& universidad, const string& carrera,
                      const string& nombre_autor, const string& apellido_autor, int cantidad_total, int cantidad_disponible) {
        string sql = "INSERT INTO tesis (ID_Tesis, Titulo, Anio, Universidad, Carrera, Nombre_Autor, Apellido_Autor, Cantidad_Total, Cantidad_Disponible) "
                    "VALUES (" + to_string(id) + ", '" + titulo + "', " + to_string(anio) + ", '" + universidad + "', '" +
                    carrera + "', '" + nombre_autor + "', '" + apellido_autor + "', " +
                    to_string(cantidad_total) + ", " + to_string(cantidad_disponible) + ");";
        return ejecutarSQL(sql);
    }

    bool insertarUsuario(int id, const string& nombre, const string& apellido, const string& dni,
                        const string& direccion, const string& telefono, const string& mail) {
        string sql = "INSERT INTO usuarios (ID_Usuario, Nombre_Usuario, Apellido_Usuario, DNI_Usuario, Direccion, Telefono, Mail) "
                    "VALUES (" + to_string(id) + ", '" + nombre + "', '" + apellido + "', '" + dni + "', '" +
                    direccion + "', '" + telefono + "', '" + mail + "');";
        return ejecutarSQL(sql);
    }

    // Métodos para consultar datos
    vector<vector<string>> obtenerTodosLosLibros() {
        return ejecutarConsulta("SELECT * FROM libros;");
    }

    vector<vector<string>> obtenerTodasLasRevistas() {
        return ejecutarConsulta("SELECT * FROM revista;");
    }

    vector<vector<string>> obtenerTodasLasTesis() {
        return ejecutarConsulta("SELECT * FROM tesis;");
    }

    vector<vector<string>> obtenerTodosLosUsuarios() {
        return ejecutarConsulta("SELECT * FROM usuarios;");
    }

    // Método para escapar comillas simples en SQL
    string escaparSQL(const string& texto) {
        string resultado = texto;
        size_t pos = 0;
        while ((pos = resultado.find("'", pos)) != string::npos) {
            resultado.replace(pos, 1, "''");
            pos += 2;
        }
        return resultado;
    }
};

// Clase publicaciones abstracta
class Publicaciones {
protected:
    static int Total_Publicaciones;
    string Titulo;
    int Anio;
    int Id;
    int Tipo; // Tesis=0  Libros=1    Revistas=2
    static DatabaseManager db;

public:
    Publicaciones(string Tit, int Ani, int Id, int tipo) :
        Titulo(Tit), Anio(Ani), Id(Id), Tipo(tipo) {
        Total_Publicaciones++;
    };

    virtual ~Publicaciones() {
        Total_Publicaciones--;
    }

    virtual void mostrar() = 0;
    virtual bool guardarEnDB() = 0;

    // Getters
    string getTitulo() const { return Titulo; }
    int getAnio() const { return Anio; }
    int getId() const { return Id; }
    int getTipo() const { return Tipo; }

    static void total_publicaciones() {
        cout << "El total de Publicaciones es: " << Total_Publicaciones << endl;
    }

    static void cargarDatosDesdeCSV() {
        cout << "Función para cargar datos desde CSV (a implementar)" << endl;
    }
};

// Inicializar miembros static
int Publicaciones::Total_Publicaciones = 0;
DatabaseManager Publicaciones::db;

// Clase Libro
class Libro : public Publicaciones {
private:
    string Editorial;
    string Genero;
    string AutorNom;
    string AutorApe;
    int stock;
    int disponibles;

public:
    Libro(string tit, int ani, int id, string edi, string gen,
          string nom, string ape, int sto, int disp) :
        Publicaciones(tit, ani, id, 1), Editorial(edi), Genero(gen),
        AutorNom(nom), AutorApe(ape), stock(sto), disponibles(disp) {};

    void mostrar() override {
        cout << "=== LIBRO ===" << endl;
        cout << "ID: " << Id << endl;
        cout << "Título: " << Titulo << endl;
        cout << "Autor: " << AutorNom << " " << AutorApe << endl;
        cout << "Editorial: " << Editorial << endl;
        cout << "Género: " << Genero << endl;
        cout << "Año: " << Anio << endl;
        cout << "Stock: " << stock << endl;
        cout << "Disponibles: " << disponibles << endl;
        cout << "=============" << endl;
    };

    bool guardarEnDB() override {
        return db.insertarLibro(Id, Titulo, to_string(Anio), Editorial,
                               AutorNom, AutorApe, Genero, stock, disponibles);
    }
};

// Clase Revista adaptada a tu estructura
class Revista : public Publicaciones {
private:
    string Editorial;
    string Genero;
    int Numero;
    int Mes;
    int stock;
    int disponibles;

public:
    Revista(string tit, int ani, int id, string edi, string gen,
            int num, int mes, int sto, int disp) :
        Publicaciones(tit, ani, id, 2), Editorial(edi), Genero(gen),
        Numero(num), Mes(mes), stock(sto), disponibles(disp) {};

    void mostrar() override {
        cout << "=== REVISTA ===" << endl;
        cout << "ID: " << Id << endl;
        cout << "Título: " << Titulo << endl;
        cout << "Editorial: " << Editorial << endl;
        cout << "Género: " << Genero << endl;
        cout << "Número: " << Numero << endl;
        cout << "Mes: " << Mes << endl;
        cout << "Año: " << Anio << endl;
        cout << "Stock: " << stock << endl;
        cout << "Disponibles: " << disponibles << endl;
        cout << "===============" << endl;
    };

    bool guardarEnDB() override {
        return db.insertarRevista(Id, Titulo, to_string(Anio), Mes,
                                Numero, Editorial, Genero, stock, disponibles);
    }
};

// Clase Tesis adaptada a tu estructura
class Tesis : public Publicaciones {
private:
    string Universidad;
    string Carrera;
    string AutorNom;
    string AutorApe;
    int stock;
    int disponibles;

public:
    Tesis(string tit, int ani, int id, string uni, string carre,
          string nom, string ape, int sto, int disp) :
        Publicaciones(tit, ani, id, 0), Universidad(uni),
        Carrera(carre), AutorNom(nom), AutorApe(ape), stock(sto), disponibles(disp) {};

    void mostrar() override {
        cout << "=== TESIS ===" << endl;
        cout << "ID: " << Id << endl;
        cout << "Título: " << Titulo << endl;
        cout << "Autor: " << AutorNom << " " << AutorApe << endl;
        cout << "Universidad: " << Universidad << endl;
        cout << "Carrera: " << Carrera << endl;
        cout << "Año: " << Anio << endl;
        cout << "Stock: " << stock << endl;
        cout << "Disponibles: " << disponibles << endl;
        cout << "=============" << endl;
    };

    bool guardarEnDB() override {
        return db.insertarTesis(Id, Titulo, Anio, Universidad,
                              Carrera, AutorNom, AutorApe, stock, disponibles);
    }
};

// Sistema de biblioteca mejorado
class SistemaBiblioteca {
private:
    DatabaseManager db;

public:
    void mostrarMenuPrincipal() {
        int opcion;
        do {
            cout << "\n=== SISTEMA DE BIBLIOTECA ===" << endl;
            cout << "1. Gestión de Libros" << endl;
            cout << "2. Gestión de Revistas" << endl;
            cout << "3. Gestión de Tesis" << endl;
            cout << "4. Gestión de Usuarios" << endl;
            cout << "5. Mostrar Todo el Inventario" << endl;
            cout << "6. Cargar Datos de Ejemplo" << endl;
            cout << "7. Salir" << endl;
            cout << "Seleccione una opción: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
                case 1: menuLibros(); break;
                case 2: menuRevistas(); break;
                case 3: menuTesis(); break;
                case 4: menuUsuarios(); break;
                case 5: mostrarTodo(); break;
                case 6: cargarDatosEjemplo(); break;
                case 7: cout << "¡Hasta luego!" << endl; break;
                default: cout << "Opción inválida!" << endl;
            }
        } while (opcion != 7);
    }

private:
    void menuLibros() {
        int opcion;
        do {
            cout << "\n=== GESTIÓN DE LIBROS ===" << endl;
            cout << "1. Agregar Libro" << endl;
            cout << "2. Mostrar Todos los Libros" << endl;
            cout << "3. Buscar Libro por Título" << endl;
            cout << "4. Volver al Menú Principal" << endl;
            cout << "Seleccione: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
                case 1: agregarLibro(); break;
                case 2: mostrarLibros(); break;
                case 3: buscarLibro(); break;
                case 4: break;
                default: cout << "Opción inválida!" << endl;
            }
        } while (opcion != 4);
    }

    void agregarLibro() {
        string titulo, editorial, genero, autorNom, autorApe;
        int anio, id, stock, disponibles;

        cout << "ID: "; cin >> id;
        cin.ignore();
        cout << "Título: "; getline(cin, titulo);
        cout << "Año: "; cin >> anio;
        cin.ignore();
        cout << "Editorial: "; getline(cin, editorial);
        cout << "Género: "; getline(cin, genero);
        cout << "Autor Nombre: "; getline(cin, autorNom);
        cout << "Autor Apellido: "; getline(cin, autorApe);
        cout << "Stock: "; cin >> stock;
        cout << "Disponibles: "; cin >> disponibles;

        Libro libro(titulo, anio, id, editorial, genero, autorNom, autorApe, stock, disponibles);
        if (libro.guardarEnDB()) {
            cout << "Libro agregado exitosamente!" << endl;
        } else {
            cout << "Error al guardar el libro." << endl;
        }
    }

    void mostrarLibros() {
        auto libros = db.obtenerTodosLosLibros();
        cout << "\n=== LISTA DE LIBROS ===" << endl;
        for (const auto& libro : libros) {
            cout << "ID: " << libro[0] << " | Título: " << libro[1] << " | Autor: " << libro[4] << " " << libro[5] << endl;
        }
    }

    void buscarLibro() {
        string titulo;
        cout << "Ingrese título a buscar: ";
        getline(cin, titulo);

        string sql = "SELECT * FROM libros WHERE Titulo LIKE '%" + db.escaparSQL(titulo) + "%';";
        auto resultados = db.ejecutarConsulta(sql);

        cout << "\n=== RESULTADOS DE BÚSQUEDA ===" << endl;
        for (const auto& libro : resultados) {
            cout << "ID: " << libro[0] << " | Título: " << libro[1] << " | Autor: " << libro[4] << " " << libro[5] << endl;
        }
    }

    void menuRevistas() {
        // Similar a menuLibros pero para revistas
        cout << "Gestión de Revistas (implementación similar a libros)" << endl;
    }

    void menuTesis() {
        // Similar a menuLibros pero para tesis
        cout << "Gestión de Tesis (implementación similar a libros)" << endl;
    }

    void menuUsuarios() {
        // Gestión de usuarios
        cout << "Gestión de Usuarios" << endl;
    }

    void mostrarTodo() {
        cout << "\n=== INVENTARIO COMPLETO ===" << endl;

        cout << "\n--- LIBROS ---" << endl;
        auto libros = db.obtenerTodosLosLibros();
        for (const auto& libro : libros) {
            cout << "L" << libro[0] << ": " << libro[1] << " (" << libro[4] << " " << libro[5] << ")" << endl;
        }

        cout << "\n--- REVISTAS ---" << endl;
        auto revistas = db.obtenerTodasLasRevistas();
        for (const auto& revista : revistas) {
            cout << "R" << revista[0] << ": " << revista[1] << " - N°" << revista[4] << endl;
        }

        cout << "\n--- TESIS ---" << endl;
        auto tesis = db.obtenerTodasLasTesis();
        for (const auto& tesis_item : tesis) {
            cout << "T" << tesis_item[0] << ": " << tesis_item[1] << " (" << tesis_item[3] << ")" << endl;
        }
    }

    void cargarDatosEjemplo() {
        cout << "Cargando datos de ejemplo..." << endl;

        // Aquí podrías cargar datos de tus archivos CSV
        // Por ahora solo un ejemplo
        db.insertarLibro(100, "Ejemplo de Libro", "2024", "Editorial Ejemplo",
                        "Autor", "Ejemplo", "Ficción", 5, 3);

        cout << "Datos de ejemplo cargados." << endl;
    }
};

int main() {
    cout << "Iniciando Sistema de Biblioteca..." << endl;
    cout << "Conectando a la base de datos..." << endl;

    SistemaBiblioteca sistema;
    sistema.mostrarMenuPrincipal();

    return 0;
}