#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//clase publicaciones abstracta
class Publicaciones {
    protected:
            //datos genericos
            static int Total_Publicaciones;
            string Titulo;
            int Anio;
            int Id;
    public:
            //Publicaciones():Titulo(""),Anio(0),Id(0){};
            //constructor
            Publicaciones(string Tit, int Ani, int Id) : Titulo(Tit), Anio(Ani), Id(Id){};
            //metodo virtual puro
            virtual void mostrar() =0;

    //metodo static muestra el contador de publicaciones
    static void total_publicaciones() {
          cout<<"El total de Publicaciones es"<<Total_Publicaciones<<endl;
    };
};
//clases libos, revistas y tesis heredan publicaciones
class Libro : public Publicaciones {
    //datos de los libros
    private:
        string Editorial;
        string Genero;
        string AutorNom;
        string AutorApe;
        int strock; //cantidad de libros por publicaciones
        int disposito;
    public:
        //constructor
        Libro(string tit, int ani, int id, string edi, string gen, string nom, string ape, int sto, int depo): Publicaciones(tit, ani,id), Editorial(edi), Genero(gen), AutorNom(nom),AutorApe(ape), strock(sto), disposito(depo) {
            Total_Publicaciones++;
        };
        //destructor
        ~Libro() {
            Total_Publicaciones--;
        }
        //metodo mostrar
        void mostrar() override {
            cout<<"Libro: "<<Titulo<<endl;
        };
};
class Revista : public Publicaciones {
    //datos de los revistas
private:
    string Editorial;
    string Genero;
    int Numero;
    int Mes_Publicado;
    int strock; //cantidad de revista por publicaciones
    int disposito;
public:
    //constructor
    Revista(string tit, int ani, int id, string edi, string gen, int num, int mes, int sto, int depo): Publicaciones(tit, ani,id), Editorial(edi), Genero(gen), Numero(num),Mes_Publicado(mes), strock(sto),disposito(depo) {
        Total_Publicaciones++;
    };
    //destructor
    ~Revista() {
        Total_Publicaciones--;
    }
    //metodo mostrar
    void mostrar() override {
        cout<<"Revista: "<<Titulo<<endl;
    };
};
class Tesis : public Publicaciones {
    //datos de los tesis
private:
    string Tema;
    string Universidad;
    string Carrera;
    string AutorNom;
    string AutorApe;
    int strock; //cantidad de tesis por publicaciones
    int disposito;
public:
    //constructor
    Tesis(string tit, int ani, int id, string tem, string uni, string carre, string nom, string ape, int tot, int depo):Publicaciones(tit,ani,id),Tema(tem),Universidad(uni),Carrera(carre),AutorNom(nom),AutorApe(ape),strock(tot),disposito(depo){
        Total_Publicaciones++;
    };
    //destructor
    ~Tesis() {
        Total_Publicaciones--;
    }
    //metodo mostrar
    void mostrar() override {
        cout<<"Tesis: "<<Titulo<<endl;
    };
};
//--------------------------------------------------------

//inventario un vector

//iniciar contador de publicaciones
int Publicaciones::Total_Publicaciones = 0;
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code.
        // We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/>
        // breakpoint for you, but you can always add more by pressing
        // <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;
    }

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.