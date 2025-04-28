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
    bool flagValidCard = false;

    //game ya está inicializada
    if(game.rondaActual() == 0){
        system("cls");
        std::cout << "Una nueva aventura comienza...\n\nPreparate." << std::endl;
        Sleep(3000);
    }else{
        system("cls");
        std::cout << "La aventura continua...";
        Sleep(3000);
    }

    while(game.cartasRest() != 0)
    {
        system("cls");
        std::cout << "Ronda " << game.rondaActual() << "\n\n";
        
        flagValidCard = false;
        while(!flagValidCard){
            try{

            }catch(const Partida::usoInvalido& e){
                
            }


        }


    }
}


    //PARTIDA

Partida::Partida(Usuario user, std::string filename = "game1.txt") : user{user}
{
    //volcar fichero en memoria
}

inline const int Partida::rondaActual() const noexcept{return ronda;}
inline const int Partida::cartasRest() const noexcept{return cartasRestantes;}
inline const std::vector<Carta> Partida::cartasSala() const noexcept{return sala;}
inline const Carta Partida::topMonton() const noexcept{return monton.top();}
inline const Carta Partida::armaActual() const noexcept{return arma;}
inline const int Partida::saludActual() const noexcept{return salud;}
const void Partida::verSala() noexcept{
    for(auto it = sala.begin(); it != sala.end(); it++){
        std::cout << *it << " ";
    }
}
inline const bool Partida::salaVacia() const noexcept{return sala.empty();}
inline const void Partida::verStats() noexcept{
    std::cout << "Salud: " << salud << "\nArma: " << arma;
}
inline const std::string Partida::ultimoMsg() const noexcept{return lastMessage;}

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

    lastMessage = "Se ha añadido una nueva arma: " +
}

inline void Partida::addMonstruo(Carta monstruo){
    
    //El siguiente monstruo a combatir ha de ser menor que el tope del montón
    if(monton.top().categCarta() > monstruo.categCarta()){
        monton.push(monstruo);
    }else{ //Si el monstruo es menor o igual, se descarta y se recibe todo el daño
        salud -= monstruo.categCarta();
    }
}

inline void Partida::addSalud(Carta salud) noexcept{
    Partida::salud += salud.categCarta();
    if(Partida::salud > 20) Partida::salud = 20;
}

void Partida::inicializarBaraja() noexcept{
    
    while(!baraja.empty()) baraja.pop();
    
    std::vector<Carta> vectCartas;
    bool flagCartas = false;
    for (int palo = 0; palo < 4; ++palo) {  // Recorrer los palos
        for (int categoria = 2; categoria <= 13; ++categoria) {  // Recorrer las categorías de 2 a K (13)
            // Excluir ases y figuras (J, Q, K) de Corazón y Diamante
            if ((palo == CORAZON || palo == DIAMANTE) && (categoria == 1 || categoria >= 11)) {
                continue;  // Excluir el As (1) y figuras (J, Q, K)
            }
            // Crear la carta y añadirla a la baraja
            vectCartas.push_back(Carta(categoria, palo));
        }
    }

    /* for(auto it = vectCartas.begin() ; it != vectCartas.end() ; it++){
        std::cout << *it << std::endl;
    } */

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vectCartas.begin(), vectCartas.end(), g);

    for(auto it = vectCartas.begin(); it != vectCartas.end() ; it++){
        baraja.push(*it);
    }
}

void Partida::huir(){
    if(huidasRestantes == 0){
        throw usoInvalido("\n\nNo te quedan huidas restantes!\n\n");
    }else{
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(sala.begin(), sala.end(), g);

        //Devuelve la sala al fondo de la baraja sin un orden particular
        for(auto it = sala.rend() ; it != sala.rbegin() ; it++){
            baraja.push(*it);
            sala.pop_back();
        }

        nuevaSala();
        huidasRestantes--;
    }
}

inline void Partida::addMensaje(std::string s){lastMessage = s;}

    //USUARIO

Usuario::Usuario(std::string nombre) : nomUsuario{nombre}, maxRonda{0}, partidasJugadas{0}, rondasJugadas{0} 
{
    //Crear fichero de usuario nuevo
}

Usuario::Usuario()
{
    //Cargar fichero de usuario a memoria
}


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


    //CARTA

Carta::Carta(int cat = NULO, int palo = NULO) : carta{cat, palo} {}

inline const int Carta::categCarta() const noexcept{return carta.first;}
inline const int Carta::paloCarta() const noexcept{return carta.second;}
const std::string Carta::verCarta() const noexcept{
    std::string s;
    std::string palo = nombresPalos[carta.first];

    if(carta.first == 0 && carta.second == 0){
        s = "Carta Nula";
    }else{
        if(carta.first < JOTA){
            s = carta.first + " de " + palo;
        }else{
            std::string categ;

            categ = nombresFiguras[carta.first - 11];
            s = categ + " de " + palo;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Carta& c)
{
    std::string palo = nombresPalos[c.categCarta()];
    const Carta nula;
    if(c == nula){
        os << "Carta Nula";
    }else{
        if(c.categCarta() < JOTA){
            os << c.categCarta() << " de " << palo;
        }else{
            std::string categ;

            categ = nombresFiguras[c.categCarta() - 11];
            os << categ << " de " << palo;
        }
    }

    return os;
} 

inline const bool operator==(const Carta& c1, const Carta& c2){
    return c1.categCarta() == c2.categCarta() && c1.paloCarta() == c2.paloCarta();
}






