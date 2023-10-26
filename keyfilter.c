#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ROW 42 // maximalni pocet moznych radku adres
#define COL 101 // maximalni pocet moznych znaku v kazdem radku

bool check_possible_characters(char *text) {
    // cyklem for projedu argument text znak po znaku
    for (int i = 0; text[i] != '\0'; i++) {
        // pokud vybrany znak text[i] nepatri do velke nebo male abecedy a neni to mezernik, vratim false
        if (!(text[i] >= 'A' && text[i] <= 'Z') && !(text[i] >= 'a' && text[i] <= 'z') && text[i] != ' ') {
            return false;
        }
    }
    // v pripade, ze vsechny znaky patri do velke nebo male abecedy nebo je to mezera, vratim true
    return true;
}

void upper_case(char *text) {
    // cyklem for projedu argument text znak po znaku
    for (int i = 0; text[i] != '\0'; i++) {
        // pokud vybrany znak text[i] patri do male abecedy, odectu od nej hodnotu 32
        // v ascii tabulce ma totiz kazde velke pismeno o 32 mensi hodnotu nez male pismeno
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] -= 32;
        }
    }
}

void remove_duplicates(char *text) {
    char new_text[COL];
    int new_text_index = 0;
    bool add;
    // cyklem for projedu argument text znak po znaku
    for (int i = 0; text[i] != '\0'; i++) {
        add = true;
        // cyklem for projedu promennou new_text znak po znaku
        for (int j = 0; j < new_text_index; j++) {
            // v pripade, ze promenna new_text jiz obsahuje znak text[i], add nastavim na false
            if (text[i] == new_text[j]) {
                add = false;
                break;
            }
        }
        // pokud je add true, tedy pokud se znak text[i] neshoduje se zadnym znakem z new_text
        // pridam znak text[i] do promenne new_text na index new_text_index a new_text_index zvysim o 1
        if (add) {
            new_text[new_text_index] = text[i];
            new_text[new_text_index + 1] = '\0'; // program obcas pridaval na konec stringu nahodny znak
            new_text_index++;
        }
    }
    // promennou new_text zkopiruju do promenne text pomoci strcpy
    strcpy(text, new_text);
}

void sort_alphabetically(char *text) {
    // cyklem for projedu argument text znak po znaku
    for (int i = 0; text[i] != '\0'; i++) {
        // cyklem for projedu argument text znak po znaku
        for (int j = 0; text[j + 1] != '\0'; j++) {
            // pokud je hodnota znaku text[j] vetsi nez hodnota znaku za nim, znaky vymenim
            if (text[j] > text[j + 1]) {
                char tmp = text[j + 1];
                text[j + 1] = text[j];
                text[j] = tmp;
            }
        }
    }
}

void print_possible_characters(char *text) {
    // pro spravny vystup programu musim z promenne text odstranit duplikaty
    remove_duplicates(text);
    // a seradit podle abecedy
    sort_alphabetically(text);
    // pote muzu vypsat
    printf("Enable: %s\n", text);
}

void check_addresses(char *text) {
    char city[COL];
    char found_city[COL];
    int text_len = strlen(text);
    char possible_characters[ROW]; // uklada vsechny znaky, kteremi muze uzivatel pokracovat v hledani
    int char_index = 0;
    bool add;
    // pomoci cyklu while a funkce fgets projedu kazdy radek souboru ulozeneho v stdin
    // a ulozim jej do promenne city
    while (fgets(city, sizeof(city), stdin) != NULL) {
        // promennou city prevedu na velka pismena
        upper_case(city);
        add = true;
        // cyklem for projedu argument text znak po znaku
        for (int i = 0; text[i] != '\0'; i++) {
            // pokud se znak text[i] neshoduje se znakem city[i], add nastavim na false a cyklus ukoncim pomoci break
            if (text[i] != city[i]) {
                add = false;
                break;
            }
        }
        // pokud je add true, tedy pokud se vsechny znaky argumentu text shoduji s prvnimy n znaky promenne city, kdy n je delka argumentu text,
        // tak pridam znak promenne city s indexem delky argumentu text (tedy znak na indexu o 1 vyssi nez posledni znak argumentu text)
        // do promenne possible_characters s indexem char_index a char_index zvysim o 1
        if (add) {
            possible_characters[char_index] = city[text_len];
            possible_characters[char_index + 1] = '\0'; // program na index 4 z neznameho duvodu obcas prirazoval mezeru
            // do promenne found_city ukladam vzdy posledni mesto, ktere zacina znaky argumentu text
            strcpy(found_city, city);
            char_index++;
        }
    }
    // podle promenne char_index muzu jednoduse spocitat pocet nalezenych schod
    if (char_index == 0) {
        // pokud nebyla nalezena ani jedna shoda, vypisu not found
        printf("Not found\n");
    } else if (char_index == 1) {
        // pokud byla nalezena pouze jedna shoda, vypisu prave to jedine nalezene mesto ulozene v promenne found_city
        printf("Found: %s", found_city);
    } else {
        // jinak vypisu vsechny mozne znaky pomoci funkce print_possible_characters
        print_possible_characters(possible_characters);
    }
}

int main(int argc, char *argv[]) {
    // zjistim, kolik ma program argumentu: pokud ma vice nez 2, program vypise chybove hlaseni a ukonci se
    if (argc > 2) {
        printf("Too many arguments\n");
    // pokud ma program 1 argument, spusti se funkce s prazdnym stringem
    } else if (argc == 1) {
        check_addresses("");
    }
    // Pro pripad kontroly moznych znaku
    /*else if (check_possible_characters(argv[1])) {
        check_addresses(upper_case(argv[1]));
    } else {
        printf("Wrong characters\n");
    }*/
    

    // pokud program nema vice nez 2 argumenty a nema presne 1 argument,
    // tak uvedeny argument prevedu na velka pismena a spustim s nim funkci
    else {
        upper_case(argv[1]);
        check_addresses(argv[1]);
    }

    return 0;
}