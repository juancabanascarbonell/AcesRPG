#ifndef _ACESRPG_HPP_
#define _ACESRPG_HPP_

#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <string>
#include <stack>
#include <queue>
#include <exception>
#include <algorithm> //find, count...
#include <utility> //pair
#include <random> //shuffle
#include <filesystem> //exists
#include <fstream> //E/S ficheros

#define RUTA_USER "../user/user.txt"

struct CargarDesdeFichero_t {};
struct CrearNuevoUsuario_t {};

inline constexpr CargarDesdeFichero_t cargarDesdeFichero{};
inline constexpr CrearNuevoUsuario_t crearNuevoUsuario{};

enum OPCIONES {NUEVA_PARTIDA, CARGAR_PARTIDA, SALIR};
enum PALOS {PICA, CORAZON, DIAMANTE, TREBOL};
enum CATEG {NULO, NA, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, JOTA, REINA, REY, AS};

const std::string nombresPalos[] = { "Pica", "Corazón", "Diamante", "Trébol" };
const std::string nombresFiguras[] = {"Jota", "Reina", "Rey" , "As"};

class Usuario
{
public:
    Usuario(CrearNuevoUsuario_t, const std::string& nombre);
    Usuario(CargarDesdeFichero_t, const std::string& fichero);

    const std::string nombre() const noexcept;
    const int ronda_maxima() const noexcept;
    const int partidas_jugadas() const noexcept;
    const int partidas_ganadas() const noexcept;
    const int rondas_jugadas() const noexcept;

    void addRonda(int) noexcept;
    void winner() noexcept;

    void guardarUsuario();

    //Por ahora no hace falta constructores adicionales
private:
    std::string nomUsuario;
    int maxRonda, partidasJugadas, partidasGanadas, rondasJugadas;

    std::string filename;
};



class Carta
{
public:
    Carta(int cat, int palo);
    const int paloCarta() const noexcept;
    const int categCarta() const noexcept;
    const std::string verCarta() const noexcept;

    Carta& operator=(const Carta& c);
    
private:
    std::pair<int, int> carta; //first: categoria. second: palo
};



class Partida
{
public:
    Partida(Usuario user, std::string filename); //Vuelca el fichero en memoria

    const int rondaActual() const noexcept;
    const int cartasRest() const noexcept;
    const std::vector<Carta> cartasSala() const noexcept;
    const Carta topMonton() const noexcept;
    const Carta armaActual() const noexcept;
    const int saludActual() const noexcept;
    const void verSala() noexcept;
    const bool salaVacia() const noexcept;
    const void verStats() noexcept;
    const std::string ultimoMsg() const noexcept;
    const int tamSala() const noexcept;
    const int numMonstruos() const noexcept;
    const void winner() noexcept;


    void nuevaSala();
    void descartarMonton();
    void usarCarta(int i);
    void huir();
    void addMensaje(std::string);

    void guardarPartida();


    class usoInvalido : public std::exception {
        private:
            std::string mensaje;  // Almacena el mensaje de error
    
        public:
            // Constructor que recibe un mensaje personalizado
            usoInvalido(const std::string& msg) : mensaje(msg) {}
    
            // Sobrescribe el método what() para devolver el mensaje
            const char* what() const noexcept override {
                return mensaje.c_str();
            }
        };

private:
    Usuario user;
    int ronda, salud, cartasRestantes, monstruosRestantes, huidasRestantes;
    bool saludUsada;
    Carta arma;

    std::string lastMessage;

    std::vector<Carta> sala; //Cartas presentes en la mesa durante la ronda
    std::queue<Carta> baraja;
    std::stack<Carta> monton; //Montón sobre en el que eliminas monstruos (bottom: arma, top: monstruo cuya vida <= que el sig)
    
    void nuevaArma(Carta arma) noexcept;
    void addMonstruo(Carta monstruo);
    void addSalud(Carta salud) noexcept;

    void inicializarBaraja() noexcept;

    std::string filename;
};










void mainMenu();

//FUNCIONES DE TITULO PRINCIPAL

void mainTitle();
void titulo();

//FUNCIONES DE E/S

void jump(int n);

//CARGA PARTIDA

Partida& menuCargaPartida();

//PARTIDA

void iniciarPartida(Partida game);


#endif // _ACESRPG_HPP_
