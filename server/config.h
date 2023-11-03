#ifndef __CONFIG_H__
#define __CONFIG_H__

// Tempo de Atualização da velocidade (em milissegundos), isso evita que flutuações no valor
// valor da leitura do potenciômetro sejam enviadas repetidamente para os trens.
// Se o trem estiver demorando a responder aos comandos, tente diminuir este valor.
#define UPDATE_SPEED_EVERY_MS       (100)

// Resolução da leitura do sensor (valores entre 1 e 8 são aceitos).
// Se a resolução é pequena, existem poucas velocidades, mas é fácil de controlar.
// Se a resolução é alta, existem muitas velocidades, mas é dificil controlar.
#define SPEED_RESOLUTION_BITS       (5)

// Tempo (milissegundos) para que um botão seja considerado pressionado/solto. Valores aceitos variam de 0 a 1000.
// Se este valor é muito pequeno, pode ser difícil controlar os leds devido a flutuações nos valores de leitura.
// Se este valor é muito grande, o botão deve ser pressionado por bastante tempo para que uma alteração seja feita.
#define DEBOUNCE_DELAY_MS           (50)

#endif