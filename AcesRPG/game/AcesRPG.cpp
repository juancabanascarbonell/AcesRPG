#include "AcesRPG.hpp"

int main()
{
    mainMenu();
    std::cin.get();
    return 0;
}

void mostrarMenu(int opcionSeleccionada)
{

    std::cout << "          ----- Menu de Juego -----         " << std::endl;

    // Imprimir las opciones con la opción seleccionada destacada
    if (opcionSeleccionada == NUEVA_PARTIDA) std::cout << "-> Nueva Partida\n";
    else std::cout << "  Nueva Partida\n";

    if (opcionSeleccionada == CARGAR_PARTIDA) std::cout << "-> Cargar Partida\n";
    else std::cout << "  Cargar Partida\n";

    if (opcionSeleccionada == 2) std::cout << "-> Salir\n";
    else std::cout << "  Salir\n";
}

void mainMenu()
{
    mainTitle();
    bool flagExit = false;
    char tecla;
    int opcionSeleccionada = 0;

    mostrarMenu(NUEVA_PARTIDA);
    do{
        tecla = _getch();

        if (tecla == 72) { // Flecha arriba
            if (opcionSeleccionada > 0) opcionSeleccionada--;

            system("cls");
            mostrarMenu(opcionSeleccionada);
        } 
        else if (tecla == 80) { // Flecha abajo
            if (opcionSeleccionada < 2) opcionSeleccionada++;

            system("cls");
            mostrarMenu(opcionSeleccionada);
        }
        else if (tecla == 13) { // Enter
            switch (opcionSeleccionada) {
                case 0:
                    std::cout << "Iniciando Nueva Partida...\n";
                    // Aquí puedes llamar a la función para nueva partida
                    break;
                case 1:
                    std::cout << "Cargando Partida...\n";
                    // Aquí puedes llamar a la función para cargar partida
                    break;
                case 2:
                    std::cout << "Saliendo...\n";
                    // Aquí puedes llamar a la función para configuración
                    break;
            }
        }


    }while(!flagExit);
}

void mainTitle()
{
    SetConsoleOutputCP(CP_UTF8);

    titulo();
    Sleep(2000);
   
    jump(5);
}

void titulo()
{
    std::cout << u8"        ▄████████  ▄████████    ▄████████    ▄████████         ▄████████    ▄███████▄    ▄██████▄  \n";
    std::cout << u8"        ███    ███ ███    ███   ███    ███   ███    ███        ███    ███   ███    ███   ███    ███ \n";
    std::cout << u8"        ███    ███ ███    █▀    ███    █▀    ███    █▀         ███    ███   ███    ███   ███    █▀  \n";
    std::cout << u8"        ███    ███ ███         ▄███▄▄▄       ███              ▄███▄▄▄▄██▀   ███    ███  ▄███        \n";
    std::cout << u8"        ▀███████████ ███        ▀▀███▀▀▀     ▀███████████      ▀▀███▀▀▀▀▀   ▀█████████▀  ▀▀███ ████▄ \n";
    std::cout << u8"         ███    ███ ███    █▄    ███    █▄           ███      ▀███████████   ███          ███    ███\n";
    std::cout << u8"         ███    ███ ███    ███   ███    ███    ▄█    ███        ███    ███   ███          ███    ███\n";
    std::cout << u8"         ███    █▀  ████████▀    ██████████  ▄████████▀         ███    ███  ▄████▀        ████████▀ \n";
    std::cout << u8"                                                                ███    ███                           \n";
}

inline void jump(int n){for(int i=0; i<n; i++) std::cout << std::endl;}

int iniciarPartida(Partida game)
{
    //baraja

    while(game.cartasRest() != 0)
    {
        game.
    }
}

Partida::Partida(Usuario user, std::string filename = "game1.txt") : user{user}
{
    //volcar fichero en memoria
}

inline const int Partida::rondaActual() const noexcept{return ronda;}
inline const int Partida::cartasRest() const noexcept{return cartasRestantes;}
inline const std::vector<Carta> Partida::cartasSala() const noexcept{return sala;}
inline const Carta Partida::topMonton() const noexcept{return monton.top();}
inline const Carta Partida::armaActual() const noexcept{return arma;}
const void Partida::verSala() noexcept{
    for(auto it = sala.begin(); it != sala.end(); it++){
        std::cout << *it;
    }
}

void Partida::nuevaSala()
{
    //Una sala solo se rellena si hay 1 carta
    if(sala.size()!= 1){
        throw std::runtime_error("Error: Relleno de sala inválido");
    }else{
        int i = 0;
    
        //Mientras haya cartas en la baraja y no hayan 4 cartas en la sala
        while(cartasRestantes != 0 && i != 3){
            sala.push_back(baraja.front());
            baraja.pop();
            --cartasRestantes;
            ++i;
        }

        ++ronda;
        user.addRonda(ronda);
        saludUsada = false;
    }
}

inline void Partida::descartarMonton(){
    while(!monton.empty()) monton.pop();
    arma = Carta();
}

void Partida::usarCarta(auto it){
    bool flagValid = true;
    switch(*it.paloCarta()){
        case CORAZON:
            if(saludUsada){
                throw usoInvalido("\n\nYa has usado una poción de salud!\n\n");
                flagValid = false;
            }else{
                addSalud(*it);
            }
        break;

        case DIAMANTE:
            nuevaArma(*it);
        break;
    
        default: //Trébol o Pica
            addMonstruo(*it);
    }

    if(flagValid){
        sala.erase(it);
        sala.shrink_to_fit();

        if(sala.size() == 1) nuevaSala(); //check caso de ganador?
    }
}

inline void Partida::nuevaArma(Carta arma) noexcept{
    descartarMonton();
    Partida::arma = arma;
}
inline void Partida::addMonstruo(Carta monstruo){
    monton.push(monstruo);
}


Usuario::Usuario(std::string nombre) : nomUsuario{nombre}, maxRonda{0}, partidasJugadas{0}, rondasJugadas{0} {}

inline const std::string Usuario::nombre() const noexcept {return nomUsuario;}
inline const int Usuario::ronda_maxima() const noexcept {return maxRonda;}
inline const int Usuario::partidas_jugadas() const noexcept {return partidasJugadas;}
inline const int Usuario::partidas_ganadas() const noexcept {return partidasGanadas;}
inline const int Usuario::rondas_jugadas() const noexcept {return rondasJugadas;}

inline void Usuario::addRonda(int nRonda) noexcept
{
    rondasJugadas++;
    if(nRonda > maxRonda) maxRonda = nRonda;
}


Carta::Carta(int cat = NULO, int palo = NULO) : carta{cat, palo} {}

inline const int Carta::categCarta() const noexcept{return carta.first;}
inline const int Carta::paloCarta() const noexcept{return carta.second;}

std::ostream& operator<<(std::ostream& os, const Carta& c)
{
    std::string s;

    switch(c.paloCarta()){
        case PICA:
            s = "Pica";
        break;

        case CORAZON:
            s = "Corazón";
        break;
        
        case DIAMANTE:
            s = "Diamante";
        break;

        case TREBOL:
            s = "Trébol";
        break;

        default:
            os << "Carta Nula";
            return os;
    }

    os << c.categCarta() << " de " << s;
    return os;
}






