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

enum OPCIONES {NUEVA_PARTIDA, CARGAR_PARTIDA, SALIR};
enum PALOS {PICA, CORAZON, DIAMANTE, TREBOL};
enum CATEG {NULO, NA, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, JOTA, REINA, REY, AS};

class Usuario
{
public:
    Usuario(std::string nombre);
    Usuario(std::string filename);

    const std::string nombre() const noexcept {return nomUsuario;}
    const int ronda_maxima() const noexcept {return maxRonda;}
    const int partidas_jugadas() const noexcept {return partidasJugadas;}
    const int partidas_ganadas() const noexcept {return partidasGanadas;}
    const int rondas_jugadas() const noexcept {return rondasJugadas;}

    void addRonda(int) noexcept;

    //Por ahora no hace falta constructores adicionales
private:
    std::string nomUsuario;
    int maxRonda, partidasJugadas, partidasGanadas, rondasJugadas;
};

class Carta
{
public:
    Carta(int cat, int palo);
    const int paloCarta() const noexcept;
    const int categCarta() const noexcept;
    

private:
    std::pair<int, int> carta; //first: categoria second: palo
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
    const void verSala() noexcept;


    void nuevaSala();
    void descartarMonton();
    void usarCarta(auto);

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
    int salud, ronda, cartasRestantes;
    bool saludUsada;
    Carta arma;

    std::vector<Carta> sala; //Cartas presentes en la mesa durante la ronda
    std::queue<Carta> baraja;
    std::stack<Carta> monton; //Montón sobre en el que eliminas monstruos (bottom: arma, top: monstruo cuya vida <= que el sig)
    
    void nuevaArma(Carta arma) noexcept;
    void addMonstruo(Carta monstruo);
    void addSalud(Carta salud) noexcept;


};










void mainMenu();

//FUNCIONES DE TITULO PRINCIPAL

void mainTitle();
void titulo();

//FUNCIONES DE E/S

void jump(int n);


#endif // _ACESRPG_HPP_