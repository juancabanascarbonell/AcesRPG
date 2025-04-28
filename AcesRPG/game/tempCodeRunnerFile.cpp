void Partida::inicializarBaraja() noexcept{
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

    for(auto it = vectCartas.begin() ; it != vectCartas.end() ; it++){
        std::cout << *it << std::endl;
    }
}