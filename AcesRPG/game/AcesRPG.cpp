#include "AcesRPG.hpp"

int main()
{
    

    mainMenu();
    std::cin.get();
    return 0;
}

Usuario& userLoad()
{
    namespace fs = std::filesystem;
    if(fs::exists(RUTA_USER)){
        Usuario user(cargarDesdeFichero, RUTA_USER);
        std::cout << "Cargando usuario..." << user.nombre();
        Sleep(1000);
        return user;
    }else{
        std::cout << "Eres un nuevo aventurero? Cual es tu nombre?\n\n...";
        std::string nombre;
        std::cin >> nombre;

        system("cls");
        std::cout << "Comienza tu aventura...\n\n\n";
        Sleep(1500);
        std::cout << nombre;

        Usuario user(crearNuevoUsuario, nombre);
        return user;
    }

    
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

Partida& menuCargaPartida(Usuario user)
{
    namespace fs = std::filesystem;

    std::string ruta = "../user/saves"; 
    std::vector<fs::directory_entry> archivos;

    std::cout << "Partidas guardadas:\n\n";

    int index = 1;
    for (const auto& entry : fs::directory_iterator(ruta)) {
        if (entry.is_regular_file()) {
            archivos.push_back(entry);

            auto ftime = entry.last_write_time();
            auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
            );
            std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);

            std::cout << index++ << ". "
                      << entry.path().filename() << " - "
                      << std::put_time(std::localtime(&cftime), "%Y-%m-%d %H:%M:%S")
                      << "\n";
        }
    }

    if (archivos.empty()) {
        std::cout << "No hay partidas guardadas\n";
        Sleep(1000);
        return Partida(user);
    }

    std::cout << "\nIntroduce el número de partida: ";
    int seleccion;
    std::cin >> seleccion;

    if (seleccion < 1 || seleccion > static_cast<int>(archivos.size())) {
        std::cerr << "Selección no válida.\n";
        return 1;
    }

    fs::path archivoSeleccionado = archivos[seleccion - 1].path();
    std::cout << "\nHas seleccionado el archivo: " << archivoSeleccionado.filename() << "\n";

    return 0;
}

void iniciarPartida(Partida game)
{
    bool flagValidCard, flagGuardado = false;
    int opcionSeleccionada = 0;
    char tecla;

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

    while((game.cartasRest() != 0 && game.numMonstruos() != 0) || flagGuardado)
    {
        
        
        do{
            system("cls");
            std::cout << "Ronda " << game.rondaActual() << "\n\n";

            if(!game.ultimoMsg().empty())   std::cout << game.ultimoMsg() << "\n\n";
            
            game.verSala();
            std::cout << "\n";
            mostrarSelectSala(opcionSeleccionada);

            std::cout << "\n\nPulse G para guardar y salir.";

            tecla = _getch();

            if(tecla == 'G' || tecla == 'g'){
                system("cls");
                std::cout << "Guardando partida...";
                //guardarPartida

                flagGuardado = true;
            }else if(tecla == 75){
                if(opcionSeleccionada > 0) opcionSeleccionada--;
            }else if(tecla == 77){
                if(opcionSeleccionada < game.tamSala()) opcionSeleccionada++;
            }

        }while(tecla != 13 || flagGuardado);


        if(!flagGuardado){
            flagValidCard = true;
        
            try{

                game.usarCarta(opcionSeleccionada);
                
            }catch(const Partida::usoInvalido& e){
                game.addMensaje(e.what());
                flagValidCard = false;
            }}

    }

    if(!flagGuardado){
        //winner
    }
}

void winner(Partida game)
{
    
std::cout << " ▄█     █▄     ▄████████         ▄█    █▄       ▄████████  ▄█    █▄     ▄████████         ▄████████       ▄█     █▄   ▄█  ███▄▄▄▄   ███▄▄▄▄      ▄████████    ▄████████"; 
std::cout << "███     ███   ███    ███        ███    ███     ███    ███ ███    ███   ███    ███        ███    ███      ███     ███ ███  ███▀▀▀██▄ ███▀▀▀██▄   ███    ███   ███    ███"; 
std::cout << "███     ███   ███    █▀         ███    ███     ███    ███ ███    ███   ███    █▀         ███    ███      ███     ███ ███▌ ███   ███ ███   ███   ███    █▀    ███    ███"; 
std::cout << "███     ███  ▄███▄▄▄           ▄███▄▄▄▄███▄▄   ███    ███ ███    ███  ▄███▄▄▄            ███    ███      ███     ███ ███▌ ███   ███ ███   ███  ▄███▄▄▄      ▄███▄▄▄▄██▀"; 
std::cout << "███     ███ ▀▀███▀▀▀          ▀▀███▀▀▀▀███▀  ▀███████████ ███    ███ ▀▀███▀▀▀          ▀███████████      ███     ███ ███▌ ███   ███ ███   ███ ▀▀███▀▀▀     ▀▀███▀▀▀▀▀  "; 
std::cout << "███     ███   ███    █▄         ███    ███     ███    ███ ███    ███   ███    █▄         ███    ███      ███     ███ ███  ███   ███ ███   ███   ███    █▄  ▀███████████"; 
std::cout << "███ ▄█▄ ███   ███    ███        ███    ███     ███    ███ ███    ███   ███    ███        ███    ███      ███ ▄█▄ ███ ███  ███   ███ ███   ███   ███    ███   ███    ███"; 
std::cout << " ▀███▀███▀    ██████████        ███    █▀      ███    █▀   ▀██████▀    ██████████        ███    █▀        ▀███▀███▀  █▀    ▀█   █▀   ▀█   █▀    ██████████   ███    ███"; 
std::cout << "                                                                                                                                                             ███    ███"; 

game.winner();
Sleep(3000);

}

void mostrarSelectSala(int opcionSeleccionada)
{
    //Si opcionSeleccionada == 0 -> 0 saltos

    for(int i = 0; i<opcionSeleccionada; i++) std::cout << "    ";

    std::cout << "^";
}


    //PARTIDA

Partida::Partida(Usuario user, std::string filename = "game1.txt") : user{user} , filename{filename}
{
    std::ifstream fp(filename);
    std::string temp, tempCarta1, tempCarta2;

    std::getline(fp, temp, '-');
    ronda = std::stoi(temp);                //ronda
    std::getline(fp, temp, '-');
    salud = std::stoi(temp);                //salud
    std::getline(fp, temp, '-');
    cartasRestantes = std::stoi(temp);      //cartasRestantes
    std::getline(fp, temp, '-');
    monstruosRestantes = std::stoi(temp);   //monstruosRestantes
    std::getline(fp, temp, '-');
    huidasRestantes = std::stoi(temp);      //huidasRestantes
    std::getline(fp, temp);
    saludUsada = std::stoi(temp);           //saludUsada(bool)

    std::getline(fp, lastMessage);          //lastMessage

    int i = 0;
    size_t pos;

    std::getline(fp, temp);
    if(temp != "-"){
        tempCarta1 = temp.substr(0, pos);
        tempCarta2 = temp.substr(pos);
        arma = Carta(std::stoi(tempCarta1), std::stoi(tempCarta2));
    }

    std::getline(fp, temp);

    while(temp != "---"){
        pos = temp.find('_');
        tempCarta1 = temp.substr(0, pos);
        tempCarta2 = temp.substr(pos);
        sala[i] = Carta(std::stoi(tempCarta1), std::stoi(tempCarta2));

        std::getline(fp, temp);
    }

    std::getline(fp, temp);
    while(temp != "---"){
        pos = temp.find('_');
        tempCarta1 = temp.substr(0, pos);
        tempCarta2 = temp.substr(pos);
        monton.push(Carta(std::stoi(tempCarta1), std::stoi(tempCarta2)));
    }

    std::getline(fp, temp);
    while(temp != "---"){
        pos = temp.find('_');
        tempCarta1 = temp.substr(0, pos);
        tempCarta2 = temp.substr(pos);
        baraja.push(Carta(std::stoi(tempCarta1), std::stoi(tempCarta2)));
    }

    fp.close();
}

inline const int Partida::rondaActual() const noexcept{return ronda;}
inline const int Partida::cartasRest() const noexcept{return cartasRestantes;}
inline const std::vector<Carta> Partida::cartasSala() const noexcept{return sala;}
inline const Carta Partida::topMonton() const noexcept{return monton.top();}
inline const Carta Partida::armaActual() const noexcept{return arma;}
inline const int Partida::saludActual() const noexcept{return salud;}
const void Partida::verSala() noexcept{
    for(auto it = sala.begin(); it != sala.end(); it++){
        std::cout << *it << "    ";
    }
}
inline const bool Partida::salaVacia() const noexcept{return sala.empty();}
inline const void Partida::verStats() noexcept{
    std::cout << "Salud: " << salud << "\nArma: " << arma;
}
inline const std::string Partida::ultimoMsg() const noexcept{return lastMessage;}
inline const int Partida::tamSala() const noexcept{return sala.size();}
inline const int Partida::numMonstruos() const noexcept {
    return std::count_if(sala.begin(), sala.end(), [](const Carta& c) {
        return c.paloCarta() == TREBOL || c.paloCarta() == PICA;
    });
}
inline const void Partida::winner() noexcept{user.winner();}

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

void Partida::usarCarta(int i){
    bool flagValid = true;
    switch(sala[i].paloCarta()){
        case CORAZON:
            if(saludUsada){
                throw usoInvalido("\n\nYa has usado una poción de salud!\n\n");
                flagValid = false;
            }else{
                addSalud(sala[i]);
            }
        break;

        case DIAMANTE:
            nuevaArma(sala[i]);
        break;
    
        default: //Trébol o Pica
            addMonstruo(sala[i]);
    }

    if(flagValid){
        auto it = std::find(sala.begin(), sala.end(), sala[i]);
        sala.erase(it);
        sala.shrink_to_fit();

        if(sala.size() == 1) nuevaSala(); //check caso de ganador?
    }
}

inline void Partida::nuevaArma(Carta arma) noexcept{
    descartarMonton();
    Partida::arma = arma;

    lastMessage = "Se ha añadido una nueva arma: " + arma.verCarta();
}

inline void Partida::addMonstruo(Carta monstruo){
    
    //El siguiente monstruo a combatir ha de ser menor que el tope del montón
    if(monton.top().categCarta() > monstruo.categCarta()){
        monton.push(monstruo);
    }else{ //Si el monstruo es menor o igual, se descarta y se recibe todo el daño
        salud -= monstruo.categCarta();
    }

    monstruosRestantes--;
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

void Partida::guardarPartida()
{
    namespace fs = std::filesystem;

    fs::remove(filename);

    std::ofstream fp(filename);
    if(!fp) throw std::runtime_error("Error: No se ha podido sobreescribir el archivo de guardado");

    fp << ronda << '-' << salud << '-' << cartasRestantes << '-' << monstruosRestantes
    << '-' << huidasRestantes << '-' << salud << '\n';
    
    if(!(arma == Carta())){
        guardarCarta(fp, arma);
    }

    for(auto it = sala.cbegin() ; it != sala.cend() ; it++){
        guardarCarta(fp, *it);
    }

    fp << "---\n";
    std::vector<Carta> tempCartas;

    while(!monton.empty()){
        tempCartas.push_back(monton.top());
        monton.pop();
    }

    for(auto it = tempCartas.begin() ; it != tempCartas.end() ; it++){
        guardarCarta(fp, *it);
    }
    fp << "---\n";

    while(!baraja.empty()){
        guardarCarta(fp, baraja.front());
        baraja.pop();
    }
    
    fp << "---\n";

    fp.clsoe();

}

void guardarCarta(std::ofstream& fp, const Carta& c)
{
    fp << c.categCarta() << '_' << c.paloCarta();
}

    //USUARIO

Usuario::Usuario(CrearNuevoUsuario_t, const std::string& nombre) : nomUsuario{nombre}
{
    std::ofstream fp(RUTA_USER);
    if(!fp){
        throw std::runtime_error("Error: No se ha podido crear el fichero");
    }

    fp << nombre << "-" << 0 << "-" << 0 << "-" << 0 << "-" << 0;

    fp.close();
}

Usuario::Usuario(CargarDesdeFichero_t, const std::string& fichero)
{
    std::ifstream fp(fichero);
    if(!fp){
        throw std::runtime_error("Error: No se ha podido abrir el fichero");
    }
    std::string temp; //string temporal para la conversión de numeros

    std::getline(fp, nomUsuario, '-'); //Nombre

    std::getline(fp, temp, '-');
    partidasJugadas = std::stoi(temp); //partidasJugadas
    std::getline(fp, temp, '-');
    partidasGanadas = std::stoi(temp); //partidasGanadas
    std::getline(fp, temp, '-');
    rondasJugadas = std::stoi(temp); //rondasJugadas
    std::getline(fp, temp);
    maxRonda = std::stoi(temp); //maxRonda

    fp.close();
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
inline void Usuario::winner() noexcept{partidasGanadas++;}

void Usuario::guardarUsuario()
{
    namespace fs = std::filesystem;

    fs::remove(filename);

    std::ofstream fp(filename);

    fp << nomUsuario << '-' << maxRonda << '-' << partidasJugadas << '-' << partidasGanadas << '-' << rondasJugadas;

    fp.close();
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

inline Carta& Carta::operator=(const Carta& c)
{
    if(this != &c){
        carta = std::pair<int,int>(c.categCarta(), c.paloCarta());
    }
}






