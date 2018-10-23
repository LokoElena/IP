#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

#include "../include/encryptolib.h"
#include "../include/cryptolib.h"
#include "../include/extralib.h"
#include "../include/hashtab.h"

#define NUMBER_CARDS 52
#define MAXINT 512000

struct card {
    char mast[10]; // Масть карты
    char name[10];  // Ранг карты
    unsigned long long int start_card;
};

void gen_cd(unsigned long long int *c, unsigned long long int *d, unsigned long long int p){
    unsigned long long int res[3];
    while(1) {
        *c = (rand() % (p - 4)) + 2;
        euclid(p - 1, *c, res);
        if(res[0] == 1){
            if(res[2] < 0){
                *d = res[2] + (p - 1);
                break;
            } else {
                *d = res[2];
                break;
            }
        }
    }
}

void swap_card(unsigned long long int *a, unsigned long long int *b) {
    long long int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void mental_poker(unsigned long long int number_players)
{
    if(number_players > 23){
        printf("[ERROR] Reached maximum players\n");
        return;
    }

    struct card player_cards[number_players][2];
    unsigned long long int p;
    generate_prime_number(0, MAXINT, &p);

    // c and d для каждого игрока
    FILE *file_cd = fopen("cd", "w+");
    if (file_cd == NULL) {
        printf("[ERROR] File doesn't exist!\n");
        return;
    }
    unsigned long long c, d;
    for(int i = 0; i < number_players; i++) {
        gen_cd(&c, &d, p);
	      fprintf(file_cd, "%lld %lld ", c, d);
        c = d = 0;
    }

    FILE *file_list_cards = fopen("card", "r");
    if (file_list_cards == NULL) {
        printf("[ERROR] File doesn't exist!\n");
        return;
    }
    struct card deck[NUMBER_CARDS];
    unsigned long long int u[NUMBER_CARDS];
    for(int i = 0; i < NUMBER_CARDS; i++) {
        fscanf(file_list_cards, "%s", deck[i].mast);
        fscanf(file_list_cards, "%s", deck[i].name);
        deck[i].start_card = i + 2;
        u[i] = i + 2;
    }
    fclose(file_list_cards);

    fclose(file_cd);
    file_cd = fopen("cd", "r");
    if (file_cd == NULL) {
        printf("[ERROR] File doesn't exist!\n");
        return;
    }
    //считываем с и d
    unsigned long long int c_r[number_players], d_r[number_players];
    for(int i = 0; i < number_players; i++) {
    	c_r[i] = d_r[i] = 0;
    	fscanf(file_cd, "%lld", &c_r[i]);
    	fscanf(file_cd, "%lld", &d_r[i]);
    }
    //кодируем карты
    for(int i = 0; i < number_players; i++){
        for (int j = 0; j < NUMBER_CARDS; j++) {
    	     expmod_func(u[j], c_r[i], p, &u[j]);
        }
        int rand_card;
	//перемешиваем
        for(int j = 0; j < NUMBER_CARDS; j++) {
            rand_card = rand() % NUMBER_CARDS;
            swap_card(&u[j], &u[rand_card]);
        }
    }

    unsigned long long int current_number_cards = NUMBER_CARDS;
    for(int i = 0; i < number_players; i++) {
        int rand_card;
        for(int j = 0; j < 2; j++) {
            rand_card = rand() % current_number_cards;
            for(int k = 0; k < number_players; k++) {
                if (i != k) {
        	    //декодируем
                    expmod_func(u[rand_card], d_r[k], p, &u[rand_card]);
                }
            }
            //своя карта
            expmod_func(u[rand_card], d_r[i], p, &u[rand_card]);
            for(int k = 0; k < NUMBER_CARDS; k++) {
                if (deck[k].start_card == u[rand_card]) {
                    player_cards[i][j] = deck[k];
                    u[rand_card] = u[current_number_cards - 1];
                    current_number_cards--;
                    k = NUMBER_CARDS;
                }
            }
        }//мешаем карты
        for(int j = 0; j < current_number_cards; j++) {
            rand_card = rand() % current_number_cards;
            swap_card(&u[j], &u[rand_card]);
        }
    }
    //вывод

    printf("\n[SYSTEM] Cards on the board!\n");
    for(int j = 0, rand_card; j < 5; j++) {
        rand_card = rand() % current_number_cards;
        for(int k = 0; k < number_players; k++)
            expmod_func(u[rand_card], d_r[k], p, &u[rand_card]);
        for(int k = 0; k < NUMBER_CARDS; k++)
            if (deck[k].start_card == u[rand_card]) {
                printf("%s %s\n", deck[k].name, deck[k].mast);
                u[rand_card] = u[current_number_cards - 1];
                current_number_cards--;
                k = NUMBER_CARDS;
            }
    }
    printf("\n");
    for(int i = 0; i < number_players; i++) {
        printf("Player %d:\n", i + 1);
        printf("%s %s\n",
               player_cards[i][0].name,
               player_cards[i][0].mast);
        printf("%s %s\n",
               player_cards[i][1].name,
               player_cards[i][1].mast);
        printf("\n");
    }
    printf("Widow: %llu cards\n", current_number_cards);
    fclose(file_cd);
}

int main()
{
    srand(time(NULL));
    unsigned long long int play;
    scanf("%llu", &play);
    mental_poker(play);
    return 0;
}
