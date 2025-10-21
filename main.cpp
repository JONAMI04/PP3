#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include "sqlite3.h"
#include "curl/curl.h"
#include <sstream>

//correo biblioteca.pp3@gmail.com
//pass   B1blioteca

using namespace std;

// Clase Servidor de Correo
class EmailService {
private:
    string smtpServer;
    string smtpUsername;
    string smtpPassword;
    int smtpPort;
    bool debug;

    static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp) {
        string *upload = (string*)userp;
        size_t buffer_size = size * nmemb;

        if(upload->size()) {
            size_t copy_size = min(upload->size(), buffer_size);
            memcpy(ptr, upload->c_str(), copy_size);
            upload->erase(0, copy_size);
            return copy_size;
        }
        return 0;
    }
    //correo biblioteca.pp3@gmail.com
    //pass   B1blioteca

public:
    EmailService(const string& server = "smtp.gmail.com",
                 const string& username = "biblioteca.pp3@gmail.com",
                 const string& password = "B1blioteca",
                 int port = 587,
                 bool debugMode = false)
        : smtpServer(server), smtpUsername(username), smtpPassword(password),
          smtpPort(port), debug(debugMode) {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    ~EmailService() {
        curl_global_cleanup();
    }

    bool enviarEmail(const string& para, const string& asunto, const string& mensaje) {
        CURL *curl;
        CURLcode res = CURLE_OK;
        struct curl_slist *recipients = NULL;

        curl = curl_easy_init();
        if (!curl) {
            cerr << "Error al inicializar cURL" << endl;
            return false;
        }

        // Configurar servidor SMTP
        curl_easy_setopt(curl, CURLOPT_URL, ("smtp://" + smtpServer + ":" + to_string(smtpPort)).c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, smtpUsername.c_str());

        // Agregar destinatario
        recipients = curl_slist_append(recipients, para.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        // Configurar autenticación
        curl_easy_setopt(curl, CURLOPT_USERNAME, smtpUsername.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, smtpPassword.c_str());

        // Para servidores que requieren STARTTLS (puerto 587)
        if (smtpPort == 587) {
            curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
        }

        // Construir el mensaje completo del email
        stringstream emailData;
        emailData << "To: " << para << "\r\n"
                  << "From: Biblioteca <" << smtpUsername << ">\r\n"
                  << "Subject: " << asunto << "\r\n"
                  << "Content-Type: text/plain; charset=utf-8\r\n"
                  << "\r\n"
                  << mensaje;

        string emailStr = emailData.str();

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl, CURLOPT_READDATA, &emailStr);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)emailStr.size());

        // Configuración adicional de seguridad
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Solo para testing, en producción usar 1L
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // Solo para testing, en producción usar 2L

        if (debug) {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }

        // Enviar el email
        res = curl_easy_perform(curl);

        // Limpiar
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            cerr << "Error al enviar email: " << curl_easy_strerror(res) << endl;
            return false;
        }

        cout << "Email enviado exitosamente a: " << para << endl;
        return true;
    }

    /*
    // Metodo para configurar credenciales después de la construcción
    void configurarCredenciales(const string& username, const string& password) {
        smtpUsername = username;
        smtpPassword = password;
    }*/
};


// Clase para manejar la base de datos
class DatabaseManager {
private:
    sqlite3* db;
    string dbPath;

public:
    //ubicacion de la base de datos "C:\\Users\\nahue\\Downloads\\biblioteca.db"
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

    bool actualizarValoracionPrestamo(int idPrestamo, int valoracion) {
        string sql = "UPDATE prestamos SET Valoracion = " + to_string(valoracion) +
                    ", Estado = 'Devuelto' WHERE ID_Prestamo = " +
                    to_string(idPrestamo) + ";";
        return ejecutarSQL(sql);
    }

    vector<vector<string>> obtenerPrestamosPorValoracion(int tipoPublicacion, int valoracionMinima) {
        string sql = "SELECT * FROM prestamos WHERE Tipo_Publicacion = " +
                    to_string(tipoPublicacion) + " AND Valoracion >= " +
                    to_string(valoracionMinima) + " AND Valoracion > 0;";
        return ejecutarConsulta(sql);
    }

    vector<vector<string>> obtenerPrestamosSinValorar(int idUsuario) {
        string sql = "SELECT * FROM prestamos WHERE ID_Usuario = " +
                    to_string(idUsuario) + " AND Estado = 'Devuelto' AND Valoracion = 0;";
        return ejecutarConsulta(sql);
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

    // Metodo para Ejecutar Consultas con Retorno de Datos
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

    // Crear Tablas si no Existen
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

        // Tabla de préstamos
        string sql_prestamos =
            "CREATE TABLE IF NOT EXISTS prestamos ("
            "ID_Prestamo INTEGER PRIMARY KEY AUTOINCREMENT,"
            "ID_Usuario INTEGER,"
            "ID_Publicacion INTEGER,"
            "Tipo_Publicacion INTEGER," // 0=Tesis, 1=Libro, 2=Revista
            "Fecha_Prestamo TEXT,"
            "Fecha_Devolucion TEXT,"
            "Estado TEXT,"
            "Valoracion INTEGER DEFAULT 0," // Nuevo campo: 0 = sin valorar, 1-5 = estrellas
            "FOREIGN KEY(ID_Usuario) REFERENCES usuarios(ID_Usuario)"
            ");";
        ejecutarSQL(sql_prestamos);

        cout << "Tablas verificadas/creadas correctamente." << endl;
    }

    // Metodos para Insertar Datos
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

    bool insertarPrestamo(int id_usuario, int id_publicacion, int tipo_publicacion,
                     const string& fecha_prestamo, const string& fecha_devolucion,
                     const string& estado, int valoracion = 0) {
        string sql = "INSERT INTO prestamos (ID_Usuario, ID_Publicacion, Tipo_Publicacion, Fecha_Prestamo, Fecha_Devolucion, Estado, Valoracion) "
                    "VALUES (" + to_string(id_usuario) + ", " + to_string(id_publicacion) + ", " +
                    to_string(tipo_publicacion) + ", '" + fecha_prestamo + "', '" + fecha_devolucion +
                    "', '" + estado + "', " + to_string(valoracion) + ");";
        return ejecutarSQL(sql);
    }

    bool actualizarEstadoPrestamo(int idPrestamo, const string& nuevoEstado) {
        string sql = "UPDATE prestamos SET Estado = '" + nuevoEstado +
                    "' WHERE ID_Prestamo = " + to_string(idPrestamo) + ";";
        return ejecutarSQL(sql);
    }

    // Metodos para Consultar Datos
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

    vector<vector<string>> obtenerPrestamosUsuario(int id_usuario) {
        return ejecutarConsulta("SELECT * FROM prestamos WHERE ID_Usuario = " + to_string(id_usuario) + ";");
    }

    vector<vector<string>> obtenerTodosLosPrestamos() {
        return ejecutarConsulta("SELECT * FROM prestamos;");
    }

    vector<vector<string>> obtenerPrestamosPorUsuarioYEstado(int idUsuario, const string& estado) {
        string sql = "SELECT * FROM prestamos WHERE ID_Usuario = " +
                    to_string(idUsuario) + " AND Estado = '" + estado + "';";
        return ejecutarConsulta(sql);
    }

    bool actualizarDisponibilidad(int tipo, int id, int nueva_cantidad) {
        string tabla;
        if (tipo == 0) tabla = "tesis";
        else if (tipo == 1) tabla = "libros";
        else if (tipo == 2) tabla = "revista";
        else return false;

        string sql = "UPDATE " + tabla + " SET Cantidad_Disponible = " + to_string(nueva_cantidad) +
                    " WHERE ID_" + (tipo == 0 ? "Tesis" : (tipo == 1 ? "Libro" : "Revista")) + " = " + to_string(id) + ";";
        return ejecutarSQL(sql);
    }

    // Solucion Comillas Simples en SQL
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

// Clase Publicaciones abstracta
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
//Creo Que no Hace Falta
    static void cargarDatosDesdeCSV() {
        cout << "Funcion para cargar datos desde CSV (a implementar)" << endl;
    }
};

// Inicializar miembros static
int Publicaciones::Total_Publicaciones = 0;
static void mostrarPublicaciones() {
    Publicaciones::total_publicaciones();
}
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
                               AutorNom, AutorApe, Genero,
                               stock, disponibles);
    }

    int getDisponibles() const { return disponibles; }

    void setDisponibles(int disp) { disponibles = disp; }
};

// Clase Revista
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
                                Numero, Editorial, Genero, stock,
                                disponibles);
    }

    int getDisponibles() const { return disponibles; }

    void setDisponibles(int disp) { disponibles = disp; }
};

// Clase Tesis
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
                              Carrera, AutorNom, AutorApe,
                              stock, disponibles);
    }

    int getDisponibles() const { return disponibles; }

    void setDisponibles(int disp) { disponibles = disp; }
};

//Clase Prestamo
class Prestamo {
private:
    int idPrestamo;
    int idUsuario;
    int idPublicacion;
    int tipoPublicacion; // 0=Tesis, 1=Libro, 2=Revista
    string fechaPrestamo;
    string fechaDevolucion;
    string estado;
    int valoracion; // Nuevo 0, prestado 1 a 5
    static DatabaseManager db;

public:
    Prestamo(int idUser, int idPub, int tipoPub, const string& fechaPrest = "",
             const string& fechaDev = "", const string& est = "Activo",
             int val = 0)
        : idUsuario(idUser), idPublicacion(idPub), tipoPublicacion(tipoPub),
          fechaPrestamo(fechaPrest), fechaDevolucion(fechaDev), estado(est),
          valoracion(val) {
        idPrestamo = 0;
    }

    bool guardarEnDB() {
        if (db.insertarPrestamo(idUsuario, idPublicacion, tipoPublicacion,
                               fechaPrestamo, fechaDevolucion, estado,
                               valoracion)) {
            // Obtener el ID generado automáticamente
            auto resultado = db.ejecutarConsulta("SELECT last_insert_rowid();");
            if (!resultado.empty()) {
                idPrestamo = stoi(resultado[0][0]);
            }
            return true;
                               }
        return false;
    }

    static vector<vector<string>> obtenerHistorialUsuario(int idUsuario) {
        return db.obtenerPrestamosUsuario(idUsuario);
    }

    // Metodo para agregar valoración cuando se devuelve el préstamo
    bool agregarValoracion(int val, const string& com = "") {
        if (val < 0 || val > 5) {
            cerr << "Error: La valoración debe estar entre 0 y 5" << endl;
            return false;
        }

        valoracion = val;
        estado = "Devuelto";

        // Actualizar en la base de datos
        string sql = "UPDATE prestamos SET Valoracion = " + to_string(valoracion) +
                    ", Estado = 'Devuelto' WHERE ID_Prestamo = " +
                    to_string(idPrestamo) + ";";
        return db.ejecutarSQL(sql);
    }

    // Getters
    int getIdPrestamo() const { return idPrestamo; }
    int getValoracion() const { return valoracion; }
    int getIdUsuario() const { return idUsuario; }
    int getIdPublicacion() const { return idPublicacion; }
    int getTipoPublicacion() const { return tipoPublicacion; }
    string getFechaPrestamo() const { return fechaPrestamo; }
    string getFechaDevolucion() const { return fechaDevolucion; }
    string getEstado() const { return estado; }
    void setIdPrestamo(int id) { idPrestamo = id; }

    static Prestamo* obtenerPorId(int idPrestamo) {
        auto resultados = db.ejecutarConsulta(
            "SELECT * FROM prestamos WHERE ID_Prestamo = " + to_string(idPrestamo));

        if (resultados.empty()) {
            return nullptr;
        }

        auto& prestamoData = resultados[0];

        // Crear el objeto Prestamo
        Prestamo* prestamo = new Prestamo(
            stoi(prestamoData[1]),  // ID_Usuario
            stoi(prestamoData[2]),  // ID_Publicacion
            stoi(prestamoData[3]),  // Tipo_Publicacion
            prestamoData[4],        // Fecha_Prestamo
            prestamoData[5],        // Fecha_Devolucion
            prestamoData[6],        // Estado
            stoi(prestamoData[7])  // Valoracion
        );

        // Establecer el ID del préstamo
        prestamo->idPrestamo = stoi(prestamoData[0]);

        return prestamo;
    }
};

DatabaseManager Prestamo::db;

// Clase Usuario
class Usuario {
private:
    int ID_Usuario;
    string Nombre_Usuario;
    string Apellido_Usuario;
    string DNI_Usuario;
    string Direccion;
    string Telefono;
    string Mail;
    static DatabaseManager db;
    static EmailService emailService;

public:
    Usuario(int id, const string& nombre, const string& apellido, const string& dni,
            const string& direccion, const string& telefono, const string& mail)
        : ID_Usuario(id), Nombre_Usuario(nombre), Apellido_Usuario(apellido),
          DNI_Usuario(dni), Direccion(direccion), Telefono(telefono), Mail(mail) {}

    // Metodo estático para configurar el servicio de email
    static void configurarEmailService(const string& username, const string& password,
                                     const string& server = "smtp.gmail.com",
                                     int port = 587) {
        emailService = EmailService(server, username, password, port, true); // debug=true para desarrollo
    }

    // Guardar usuario en la base de datos
    bool guardarEnDB() {
        return db.insertarUsuario(ID_Usuario, Nombre_Usuario, Apellido_Usuario, DNI_Usuario, Direccion, Telefono, Mail);
    }

    // Realizar préstamo
    bool realizarPrestamo(int idPublicacion, int tipoPublicacion) {
        // Obtener fecha actual
        time_t now = time(0);
        tm* ltm = localtime(&now);
        string fechaPrestamo = to_string(1900 + ltm->tm_year) + "-" +
                              to_string(1 + ltm->tm_mon) + "-" +
                              to_string(ltm->tm_mday);

        // Calcular fecha de devolución (15 días después)
        tm fechaDev = *ltm;
        fechaDev.tm_mday += 15;
        mktime(&fechaDev);
        string fechaDevolucion = to_string(1900 + fechaDev.tm_year) + "-" +
                                to_string(1 + fechaDev.tm_mon) + "-" +
                                to_string(fechaDev.tm_mday);

        // Crear y guardar préstamo
        Prestamo prestamo(ID_Usuario, idPublicacion, tipoPublicacion, fechaPrestamo, fechaDevolucion);
        if (prestamo.guardarEnDB()) {
            // Obtener título de la publicación para la notificación
            string titulo = "Publicación ID: " + to_string(idPublicacion);
            string sql;

            if (tipoPublicacion == 1)
                sql = "SELECT Titulo FROM libros WHERE ID_Libro = " + to_string(idPublicacion);
            else if (tipoPublicacion == 2)
                sql = "SELECT Titulo FROM revista WHERE ID_Revista = " + to_string(idPublicacion);
            else if (tipoPublicacion == 0)
                sql = "SELECT Titulo FROM tesis WHERE ID_Tesis = " + to_string(idPublicacion);

            auto resultado = db.ejecutarConsulta(sql);
            if (!resultado.empty()) {
                titulo = resultado[0][0];
            }

            string recomendacion = generarRecomendacion();
            enviarNotificacion(titulo, 15, recomendacion, false); // false = no es recordatorio

            return true;
        }
        return false;
    }

    // Calcular días restantes de préstamo
    int calcularDiasRestantes(const string& fechaDevolucion) {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        // Convertir fecha de devolución a time_t
        tm fechaDev = {};
        sscanf(fechaDevolucion.c_str(), "%d-%d-%d", &fechaDev.tm_year, &fechaDev.tm_mon, &fechaDev.tm_mday);
        fechaDev.tm_year -= 1900;
        fechaDev.tm_mon -= 1;
        time_t tiempoDev = mktime(&fechaDev);

        // Calcular diferencia en días
        double diferencia = difftime(tiempoDev, now);
        return static_cast<int>(diferencia / (60 * 60 * 24));
    }

    // Enviar notificación por email
    void enviarNotificacion(const string& tituloPublicacion, int diasRestantes,
                           const string& recomendacion, bool esRecordatorio = true) {
        string asunto, mensaje;
        if (esRecordatorio) {
            asunto = "Recordatorio de préstamo - " + tituloPublicacion;
            mensaje = "Hola " + Nombre_Usuario + " " + Apellido_Usuario + ",\n\n"
                     "Te recordamos que el préstamo de '" + tituloPublicacion + "'\n"
                     "tiene " + to_string(diasRestantes) + " días restantes para su devolución.\n\n";
        } else {
            asunto = "Confirmación de nuevo préstamo - " + tituloPublicacion;
            mensaje = "Hola " + Nombre_Usuario + " " + Apellido_Usuario + ",\n\n"
                     "Confirmamos tu préstamo de '" + tituloPublicacion + "'\n"
                     "Fecha de devolución: en " + to_string(diasRestantes) + " días.\n\n";
        }
        if (!recomendacion.empty()) {
            mensaje += recomendacion + "\n\n";
        }
        mensaje += "Saludos cordiales,\nBiblioteca";

        // Enviar email real
        bool exito = emailService.enviarEmail(Mail, asunto, mensaje);

        if (exito) {
            cout << "Notificación enviada por email a: " << Mail << endl;
        } else {
            cout << "Error al enviar email a: " << Mail << " (mostrando en consola)" << endl;
            // Fallback: mostrar en consola
            cout << "\n=== NOTIFICACIÓN (FALLBACK) ===" << endl;
            cout << "Para: " << Mail << endl;
            cout << "Asunto: " << asunto << endl;
            cout << "Mensaje: " << mensaje << endl;
            cout << "==============================\n" << endl;
        }
    }

    // Generar recomendación basada en historial
    string generarRecomendacion() {
        auto historial = Prestamo::obtenerHistorialUsuario(ID_Usuario);
        map<string, int> generosFrecuentes;
        map<string, int> autoresFrecuentes;

        // Analizar géneros y autores de préstamos anteriores con valoraciones altas
        for (const auto& prestamo : historial) {
            int tipo = stoi(prestamo[3]);
            int idPub = stoi(prestamo[2]);
            int valoracion = stoi(prestamo[7]); // Nueva columna de valoración

            // Solo considerar préstamos con buena valoración (4-5 estrellas)
            if (valoracion >= 4) {
                string sql;
                if (tipo == 1) { // Libro
                    sql = "SELECT Genero, Nombre_Autor, Apellido_Autor FROM libros WHERE ID_Libro = " + to_string(idPub);
                } else if (tipo == 2) { // Revista
                    sql = "SELECT Genero FROM revista WHERE ID_Revista = " + to_string(idPub);
                }

                auto resultado = db.ejecutarConsulta(sql);
                if (!resultado.empty() && !resultado[0][0].empty()) {
                    string genero = resultado[0][0];
                    generosFrecuentes[genero]++;

                    // Para libros, también considerar autores
                    if (tipo == 1 && resultado.size() > 2) {
                    string autor = resultado[0][1] + " " + resultado[0][2];
                        autoresFrecuentes[autor]++;
                    }
                }
            }
        }

        // Buscar recomendación basada en género favorito
        if (!generosFrecuentes.empty()) {
            string generoFavorito;
            int maxFrecuencia = 0;
            for (const auto& par : generosFrecuentes) {
                if (par.second > maxFrecuencia) {
                    maxFrecuencia = par.second;
                    generoFavorito = par.first;
                }
            }

            // Buscar libro del mismo género que no haya sido prestado antes
            string sql = "SELECT l.Titulo, l.Nombre_Autor, l.Apellido_Autor "
                        "FROM libros l "
                        "WHERE l.Genero = '" + generoFavorito + "' "
                        "AND l.Cantidad_Disponible > 0 "
                        "AND l.ID_Libro NOT IN ("
                        "SELECT p.ID_Publicacion FROM prestamos p WHERE p.ID_Usuario = " + to_string(ID_Usuario) + " AND p.Tipo_Publicacion = 1"
                        ") LIMIT 1;";

            auto recomendacion = db.ejecutarConsulta(sql);
            if (!recomendacion.empty()) {
                return "Basado en tu interés en " + generoFavorito +
                       ", te recomendamos: '" + recomendacion[0][0] +
                       "' de " + recomendacion[0][1] + " " + recomendacion[0][2];
            }
        }

        // Si no hay historial con valoraciones, recomendar novedades
        string sql = "SELECT Titulo, Nombre_Autor, Apellido_Autor FROM libros "
                    "WHERE Cantidad_Disponible > 0 "
                    "ORDER BY Anio DESC LIMIT 1";
        auto novedad = db.ejecutarConsulta(sql);
        if (!novedad.empty()) {
            return "Te recomendamos nuestra novedad: '" + novedad[0][0] +
                   "' de " + novedad[0][1] + " " + novedad[0][2];
        }

        return "Te recomendamos explorar nuestras novedades literarias.";
    }

    // Verificar préstamos próximos a vencer
    void verificarPrestamosProximos() {
        auto prestamos = Prestamo::obtenerHistorialUsuario(ID_Usuario);

        for (const auto& prestamo : prestamos) {
            if (prestamo[6] == "Activo") { // Estado activo
                int diasRestantes = calcularDiasRestantes(prestamo[5]); // Fecha_Devolucion

                if (diasRestantes <= 3 && diasRestantes > 0) {
                    // Obtener título de la publicación
                    string titulo = "Publicación ID: " + prestamo[2];
                    int tipo = stoi(prestamo[3]);
                    int idPub = stoi(prestamo[2]);

                    string sql;
                    if (tipo == 1) sql = "SELECT Titulo FROM libros WHERE ID_Libro = " + to_string(idPub);
                    else if (tipo == 2) sql = "SELECT Titulo FROM revista WHERE ID_Revista = " + to_string(idPub);
                    else if (tipo == 0) sql = "SELECT Titulo FROM tesis WHERE ID_Tesis = " + to_string(idPub);

                    auto resultado = db.ejecutarConsulta(sql);
                    if (!resultado.empty()) {
                        titulo = resultado[0][0];
                    }

                    string recomendacion = generarRecomendacion();
                    enviarNotificacion(titulo, diasRestantes, recomendacion);
                }
            }
        }
    }

    // Mostrar información del usuario
    void mostrarInformacion() {
        cout << "\n=== INFORMACIÓN DEL USUARIO ===" << endl;
        cout << "ID: " << ID_Usuario << endl;
        cout << "Nombre: " << Nombre_Usuario << " " << Apellido_Usuario << endl;
        cout << "DNI: " << DNI_Usuario << endl;
        cout << "Dirección: " << Direccion << endl;
        cout << "Teléfono: " << Telefono << endl;
        cout << "Email: " << Mail << endl;

        // Mostrar préstamos activos
        auto prestamos = Prestamo::obtenerHistorialUsuario(ID_Usuario);
        cout << "Préstamos activos: ";
        int activos = 0;
        for (const auto& prestamo : prestamos) {
            if (prestamo[6] == "Activo") activos++;
        }
        cout << activos << endl;
    }

    // Getters
    int getId() const { return ID_Usuario; }
    string getNombre() const { return Nombre_Usuario; }
    string getApellido() const { return Apellido_Usuario; }
    string getMail() const { return Mail; }

    // Metodo estático para obtener usuario por ID
    static Usuario* obtenerPorId(int id) {
        auto resultados = db.ejecutarConsulta("SELECT * FROM usuarios WHERE ID_Usuario = " + to_string(id));
        if (resultados.empty()) return nullptr;

        return new Usuario(stoi(resultados[0][0]), resultados[0][1], resultados[0][2],
                          resultados[0][3], resultados[0][4], resultados[0][5], resultados[0][6]);
    }
};

DatabaseManager Usuario::db;
EmailService Usuario::emailService;

// Menus de Biblioteca adaptar
class SistemaBiblioteca {
private:
    DatabaseManager db;

public:
    void mostrarMenuPrincipal() {
        int opcion;
        do {
            cout << "\n=== SISTEMA DE BIBLIOTECA ===" << endl;
            cout << "1. Gestion de Libros" << endl;
            cout << "2. Gestion de Revistas" << endl;
            cout << "3. Gestion de Tesis" << endl;
            cout << "4. Gestion de Usuarios" << endl;
            cout << "5. Gestion de Prestamos" << endl;
            cout << "6. Mostrar Todo el Inventario" << endl;
            cout << "7. Cargar Datos de Ejemplo" << endl;
            cout << "8. Verificar Notificaciones" << endl;
            cout << "9. Salir" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
                case 1: menuLibros(); break;
                case 2: menuRevistas(); break;
                case 3: menuTesis(); break;
                case 4: menuUsuarios(); break;
                case 5: menuPrestamos(); break;
                case 6: mostrarTodo(); break;
                case 7: cargarDatosEjemplo(); break;
                case 8: verificarNotificaciones(); break;
                case 9: cout << "Hasta luego" << endl; break;
                default: cout << "Opcion inválida!" << endl;
            }
        } while (opcion != 9);
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
                default: cout << "Opcion inválida!" << endl;
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
            cout << "ID: " << libro[0] << " | Título: " << libro[1] << " | Autor: " << libro[4] << " " << libro[5]
                 << " | Disponibles: " << libro[8] << "/" << libro[7] << endl;
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
            cout << "ID: " << libro[0] << " | Título: " << libro[1] << " | Autor: " << libro[4] << " " << libro[5]
                 << " | Disponibles: " << libro[8] << "/" << libro[7] << endl;
        }
    }

    void menuUsuarios() {
        int opcion;
        do {
            cout << "\n=== GESTIÓN DE USUARIOS ===" << endl;
            cout << "1. Agregar Usuario" << endl;
            cout << "2. Mostrar Todos los Usuarios" << endl;
            cout << "3. Buscar Usuario por ID" << endl;
            cout << "4. Mostrar Información de Usuario" << endl;
            cout << "5. Volver al Menú Principal" << endl;
            cout << "Seleccione: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
                case 1: agregarUsuario(); break;
                case 2: mostrarUsuarios(); break;
                case 3: buscarUsuario(); break;
                case 4: mostrarInfoUsuario(); break;
                case 5: break;
                default: cout << "Opcion inválida!" << endl;
            }
        } while (opcion != 5);
    }

    void agregarUsuario() {
        string nombre, apellido, dni, direccion, telefono, mail;
        int id;

        cout << "ID Usuario: "; cin >> id;
        cin.ignore();
        cout << "Nombre: "; getline(cin, nombre);
        cout << "Apellido: "; getline(cin, apellido);
        cout << "DNI: "; getline(cin, dni);
        cout << "Dirección: "; getline(cin, direccion);
        cout << "Teléfono: "; getline(cin, telefono);
        cout << "Email: "; getline(cin, mail);

        Usuario usuario(id, nombre, apellido, dni, direccion, telefono, mail);
        if (usuario.guardarEnDB()) {
            cout << "Usuario agregado exitosamente!" << endl;
        } else {
            cout << "Error al guardar el usuario." << endl;
        }
    }

    void mostrarUsuarios() {
        auto usuarios = db.obtenerTodosLosUsuarios();
        cout << "\n=== LISTA DE USUARIOS ===" << endl;
        for (const auto& usuario : usuarios) {
            cout << "ID: " << usuario[0] << " | Nombre: " << usuario[1] << " " << usuario[2]
                 << " | DNI: " << usuario[3] << " | Email: " << usuario[6] << endl;
        }
    }

    void buscarUsuario() {
        int id;
        cout << "Ingrese ID de usuario a buscar: ";
        cin >> id;

        auto usuario = Usuario::obtenerPorId(id);
        if (usuario) {
            usuario->mostrarInformacion();
            delete usuario;
        } else {
            cout << "Usuario no encontrado." << endl;
        }
    }

    void mostrarInfoUsuario() {
        int id;
        cout << "Ingrese ID de usuario: ";
        cin >> id;

        auto usuario = Usuario::obtenerPorId(id);
        if (usuario) {
            usuario->mostrarInformacion();

            // Mostrar préstamos del usuario
            auto prestamos = db.obtenerPrestamosUsuario(id);
            if (!prestamos.empty()) {
                cout << "\n--- PRÉSTAMOS ---" << endl;
                for (const auto& prestamo : prestamos) {
                    cout << "Publicación ID: " << prestamo[2] << " | Tipo: "
                         << (prestamo[3] == "0" ? "Tesis" : prestamo[3] == "1" ? "Libro" : "Revista")
                         << " | Devolución: " << prestamo[5] << " | Estado: " << prestamo[6] << endl;
                }
            }
            delete usuario;
        } else {
            cout << "Usuario no encontrado." << endl;
        }
    }

    void menuPrestamos() {
        int opcion;
        do {
            cout << "\n=== GESTIÓN DE PRÉSTAMOS ===" << endl;
            cout << "1. Realizar Préstamo" << endl;
            cout << "2. Mostrar Todos los Préstamos" << endl;
            cout << "3. Ver Préstamos de Usuario" << endl;
            cout << "4. Valorar Préstamo Devuelto" << endl; // Nueva opción
            cout << "5. Volver al Menú Principal" << endl;
            cout << "Seleccione: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
                case 1: realizarPrestamo(); break;
                case 2: mostrarPrestamos(); break;
                case 3: verPrestamosUsuario(); break;
                case 4: valorarPrestamo(); break;
                case 5: break;
                default: cout << "Opcion inválida!" << endl;
            }
        } while (opcion != 5);
    }

    void valorarPrestamo() {
        int idPrestamo, valoracion;

        cout << "ID del Préstamo a valorar: ";
        cin >> idPrestamo;

        auto prestamo = Prestamo::obtenerPorId(idPrestamo);
        if (!prestamo) {
            cout << "Préstamo no encontrado." << endl;
            return;
        }

        cout << "Valoración (1-5 estrellas): ";
        cin >> valoracion;
        cin.ignore();

        if (valoracion < 1 || valoracion > 5) {
            cout << "La valoración debe ser entre 1 y 5." << endl;
            delete prestamo;
            return;
        }
        if (prestamo->agregarValoracion(valoracion)) {
            cout << "Valoración registrada exitosamente!" << endl;
        } else {
            cout << "Error al registrar la valoración." << endl;
        }

        delete prestamo;
    }

    void realizarPrestamo() {
        int idUsuario, idPublicacion, tipoPublicacion;

        cout << "ID Usuario: "; cin >> idUsuario;
        cout << "ID Publicación: "; cin >> idPublicacion;
        cout << "Tipo (0=Tesis, 1=Libro, 2=Revista): "; cin >> tipoPublicacion;

        auto usuario = Usuario::obtenerPorId(idUsuario);
        if (usuario) {
            if (usuario->realizarPrestamo(idPublicacion, tipoPublicacion)) {
                cout << "Préstamo realizado exitosamente!" << endl;

                // Actualizar disponibilidad
                string sql;
                if (tipoPublicacion == 1)
                    sql = "SELECT Cantidad_Disponible FROM libros WHERE ID_Libro = " + to_string(idPublicacion);
                else if (tipoPublicacion == 2)
                    sql = "SELECT Cantidad_Disponible FROM revista WHERE ID_Revista = " + to_string(idPublicacion);
                else if (tipoPublicacion == 0)
                    sql = "SELECT Cantidad_Disponible FROM tesis WHERE ID_Tesis = " + to_string(idPublicacion);

                auto resultado = db.ejecutarConsulta(sql);
                if (!resultado.empty()) {
                    int disponibles = stoi(resultado[0][0]);
                    db.actualizarDisponibilidad(tipoPublicacion, idPublicacion, disponibles - 1);
                }
            } else {
                cout << "Error al realizar el préstamo." << endl;
            }
            delete usuario;
        } else {
            cout << "Usuario no encontrado." << endl;
        }
    }

    void mostrarPrestamos() {
        auto prestamos = db.obtenerTodosLosPrestamos();
        cout << "\n=== TODOS LOS PRÉSTAMOS ===" << endl;
        for (const auto& prestamo : prestamos) {
            cout << "ID: " << prestamo[0] << " | Usuario: " << prestamo[1]
                 << " | Publicación: " << prestamo[2]
                 << " | Tipo: " << (prestamo[3] == "0" ? "Tesis" : prestamo[3] == "1" ? "Libro" : "Revista")
                 << " | Préstamo: " << prestamo[4] << " | Devolución: " << prestamo[5]
                 << " | Estado: " << prestamo[6]
                 << " | Valoración: " << (prestamo[7] == "0" ? "Sin valorar" : prestamo[7] + "/5") << endl;
        }
    }

    void verPrestamosUsuario() {
        int idUsuario;
        cout << "ID Usuario: ";
        cin >> idUsuario;

        auto prestamos = db.obtenerPrestamosUsuario(idUsuario);
        if (!prestamos.empty()) {
            cout << "\n=== PRÉSTAMOS DEL USUARIO " << idUsuario << " ===" << endl;
            for (const auto& prestamo : prestamos) {
                cout << "Publicación: " << prestamo[2] << " | Tipo: "
                     << (prestamo[3] == "0" ? "Tesis" : prestamo[3] == "1" ? "Libro" : "Revista")
                     << " | Préstamo: " << prestamo[4] << " | Devolución: " << prestamo[5]
                     << " | Estado: " << prestamo[6] << endl;
            }
        } else {
            cout << "No se encontraron préstamos para este usuario." << endl;
        }
    }

    void verificarNotificaciones() {
        auto usuarios = db.obtenerTodosLosUsuarios();
        cout << "\n=== VERIFICANDO NOTIFICACIONES ===" << endl;

        for (const auto& usuarioData : usuarios) {
            int idUsuario = stoi(usuarioData[0]);
            auto usuario = Usuario::obtenerPorId(idUsuario);
            if (usuario) {
                usuario->verificarPrestamosProximos();
                delete usuario;
            }
        }
        cout << "Verificación completada." << endl;
    }

    void menuRevistas() {
        int opcion;
        do {
            cout << "\n=== GESTIÓN DE REVISTAS ===" << endl;
            cout << "1. Agregar Revistas" << endl;
            cout << "2. Mostrar Todos los Revistas" << endl;
            cout << "3. Buscar Revista por Título" << endl;
            cout << "4. Volver al Menú Principal" << endl;
            cout << "Seleccione: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
                case 1: agregarRevista(); break;
                case 2: mostrarRevistas(); break;
                case 3: buscarRevista(); break;
                case 4: break;
                default: cout << "Opcion inválida!" << endl;
            }
        } while (opcion != 4);
    }

    void agregarRevista() {
        string titulo, editorial, genero;
        int anio, id, stock, disponibles, nro_publicacion, mes;

        cout << "ID: "; cin >> id;
        cin.ignore();
        cout << "Título: "; getline(cin, titulo);
        cout << "Año: "; cin >> anio;
        cin.ignore();
        cout << "Editorial: "; getline(cin, editorial);
        cout << "Género: "; getline(cin, genero);
        cout << "Nro de Publicacion: "; cin >> nro_publicacion;
        cout << "Stock: "; cin >> stock;
        cout << "Mes de Publicacion: "; cin >> mes;
        cout << "Disponibles: "; cin >> disponibles;
        Revista revista(titulo, anio, id, editorial, genero, nro_publicacion, mes, stock, disponibles);
        if (revista.guardarEnDB()) {
            cout << "Revista agregada exitosamente!" << endl;
        } else {
            cout << "Error al guardar la revista." << endl;
        }
    }

    void mostrarRevistas() {
        auto Revistas = db.obtenerTodasLasRevistas();
        cout << "\n=== LISTA DE REVISTAS ===" << endl;
        for (const auto& revista : Revistas) {
            cout << "ID: " << revista[0] << " | Título: " << revista[1] << " | Editorial: " << revista[5] << " Nro " << revista[4]
                 << " | Disponibles: " << revista[8] << "/" << revista[7] << endl;
        }
    }

    void buscarRevista() {
        string titulo;
        cout << "Ingrese título a buscar: ";
        getline(cin, titulo);

        string sql = "SELECT * FROM revista WHERE Titulo LIKE '%" + db.escaparSQL(titulo) + "%';";
        auto resultados = db.ejecutarConsulta(sql);

        cout << "\n=== RESULTADOS DE BÚSQUEDA ===" << endl;
        for (const auto& Revista : resultados) {
            cout << "ID: " << Revista[0] << " | Título: " << Revista[1] << " | Editorial: " << Revista[5] << " Nro " << Revista[4]
                 << " | Disponibles: " << Revista[8] << "/" << Revista[7] << endl;
        }
    }
    void menuTesis() {
        int opcion;
        do {
            cout << "\n=== GESTIÓN DE TESIS ===" << endl;
            cout << "1. Agregar Tesis" << endl;
            cout << "2. Mostrar Todas las Tesis" << endl;
            cout << "3. Buscar Tesis por Título" << endl;
            cout << "4. Volver al Menú Principal" << endl;
            cout << "Seleccione: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
                case 1: agregarTesis(); break;
                case 2: mostrarTesis(); break;
                case 3: buscarTesis(); break;
                case 4: break;
                default: cout << "Opcion inválida!" << endl;
            }
        } while (opcion != 4);
    }

    void agregarTesis() {
        string titulo, universidad, carrera, nom_autor, ape_autor ;
        int anio, id, stock, disponibles;

        cout << "ID: "; cin >> id;
        cin.ignore();
        cout << "Título: "; getline(cin, titulo);
        cout << "Año: "; cin >> anio;
        cin.ignore();
        cout << "Universidad: "; getline(cin, universidad);
        cout << "Carrera: "; getline(cin, carrera);
        cout << "Nombre del Autor: "; getline(cin, nom_autor);
        cout << "Apellido del Autor: "; getline(cin, ape_autor);
        cout << "Stock: "; cin >> stock;
        cout << "Disponibles: "; cin >> disponibles;
        Tesis tesis(titulo, anio, id, universidad, carrera, nom_autor, ape_autor, stock, disponibles);
        if (tesis.guardarEnDB()) {
            cout << "Tesis agregada exitosamente!" << endl;
        } else {
            cout << "Error al guardar la Tesis." << endl;
        }
    }

    void mostrarTesis() {
        auto Tesis = db.obtenerTodasLasTesis();
        cout << "\n=== LISTA DE TESIS ===" << endl;
        for (const auto& tesis : Tesis) {
            cout << "ID: " << tesis[0] << " | Título: " << tesis[1] << " | Autor: " << tesis[4] << " " << tesis[5]
                 << " | Disponibles: " << tesis[8] << "/" << tesis[7] << endl;
        }
    }

    void buscarTesis() {
        string titulo;
        cout << "Ingrese título a buscar: ";
        getline(cin, titulo);

        string sql = "SELECT * FROM tesis WHERE Titulo LIKE '%" + db.escaparSQL(titulo) + "%';";
        auto resultados = db.ejecutarConsulta(sql);

        cout << "\n=== RESULTADOS DE BÚSQUEDA ===" << endl;
        for (const auto& Tesis : resultados) {
            cout << "ID: " << Tesis[0] << " | Título: " << Tesis[1] << " | Autor: " << Tesis[4] << " " << Tesis[5]
                 << " | Disponibles: " << Tesis[8] << "/" << Tesis[7] << endl;
        }
    }

    void mostrarTodo() {
        cout << "\n=== INVENTARIO COMPLETO ===" << endl;

        cout << "\n--- LIBROS ---" << endl;
        auto libros = db.obtenerTodosLosLibros();
        for (const auto& libro : libros) {
            cout << "L" << libro[0] << ": " << libro[1] << " (" << libro[4] << " " << libro[5] << ") - Disp: " << libro[8] << endl;
        }

        cout << "\n--- REVISTAS ---" << endl;
        auto revistas = db.obtenerTodasLasRevistas();
        for (const auto& revista : revistas) {
            cout << "R" << revista[0] << ": " << revista[1] << " - N°" << revista[4] << " - Disp: " << revista[8] << endl;
        }

        cout << "\n--- TESIS ---" << endl;
        auto tesis = db.obtenerTodasLasTesis();
        for (const auto& tesis_item : tesis) {
            cout << "T" << tesis_item[0] << ": " << tesis_item[1] << " (" << tesis_item[3] << ") - Disp: " << tesis_item[8] << endl;
        }

        cout << "\n--- USUARIOS ---" << endl;
        auto usuarios = db.obtenerTodosLosUsuarios();
        for (const auto& usuario : usuarios) {
            cout << "U" << usuario[0] << ": " << usuario[1] << " " << usuario[2] << endl;
        }
    }

    void cargarDatosEjemplo() {
        cout << "Cargando datos de ejemplo..." << endl;

        // Por ahora solo un ejemplo
        db.insertarLibro(100, "Ejemplo de Libro", "2024", "Editorial Ejemplo",
                        "Autor", "Ejemplo", "Ficcion", 5, 3);

        cout << "Datos de ejemplo cargados." << endl;
    }
};

int main() {
    Usuario::configurarEmailService("biblioteca.pp3@gmail.com", "B1blioteca");
    cout << "Iniciando Sistema de Biblioteca..." << endl;
    cout << "Conectando a la base de datos..." << endl;
    //integrar el menu de mati
    SistemaBiblioteca sistema;
    sistema.mostrarMenuPrincipal();

    mostrarPublicaciones();

    return 0;
}