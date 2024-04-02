#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>

#include "../include/date.h"
#include "../include/users.h"
#include "../include/flights.h"
#include "../include/reservations.h"
#include "../include/passengers.h"
#include "../include/users_catalog.h"
#include "../include/flights_catalog.h"
#include "../include/reservations_catalog.h"
#include "../include/passengers_catalog.h"
#include "../include/menus.h"
#include "../include/pages.h"

int calculateTotalPages(int length, int maxPerPage) {
    return length / maxPerPage + (length % maxPerPage != 0);
}

void printPage(GList * list, int page, int maxPerPage, char * (* toStringFunc) (gpointer)) {
    if (!list) page--;

    system("clear");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("                                       Page %d/%d\n", (page + 1), calculateTotalPages(g_list_length(list), maxPerPage));
    printf("---------------------------------------------------------------------------------------------\n");

    int i;
    GList *current = g_list_nth(list, page * maxPerPage);
    for (i = 0; i < maxPerPage && current; ++i) {
        char * str = toStringFunc(current -> data);
        printf("%d - %s\n", (page * maxPerPage) + i + 1, str);
        free(str);
        current = g_list_next(current);
    }

    printf("---------------------------------------------------------------------------------------------\n");
    printf("        [N] Next Page | [P] Previous Page | [F] First Page | [L] Last Page | [Q] Quit        \n");
    printf("---------------------------------------------------------------------------------------------\n");
}

int getUserInput() {
    int userInput = getchar();
    while(getchar() != '\n');
    return userInput;
}

void handleUserInput(GList * list, int * currentPage, int maxPerPage) {
    int userInput = tolower(getUserInput());
    switch (userInput) {
        case 'n':
            if ((* currentPage + 1) < calculateTotalPages(g_list_length(list), maxPerPage))
                (* currentPage)++;
            break;
        case 'p':
            if (* currentPage > 0)
                (* currentPage)--;
            break;
        case 'f':
            * currentPage = 0;
            break;
        case 'l':
            * currentPage = calculateTotalPages(g_list_length(list), maxPerPage);
            break;
        case 'q':
            * currentPage = -1;
            break;
    }
}

void paginateList(GList * list, char * (* toStringFunc) (gpointer)) {
    int maxPerPage = 40;
    int currentPage = 0;

    while (currentPage != -1) {
        printPage(list, currentPage, maxPerPage, toStringFunc);
        handleUserInput(list, &currentPage, maxPerPage);
    }

    system("clear");
    menuUI();
}

void pages(GList * list, char * (* toStringFunc) (gpointer)) {
    paginateList(list, toStringFunc);
}
