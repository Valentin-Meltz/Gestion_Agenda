#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module timer-20231031/timer.h"
#include "s_d_list.h"
#include "contact.h"
#include "rendez-vous.h"

int main() {
    int level = 10;

    t_list mylist = Create_list(level);
    int *levels = Create_levels(mylist);
    Add_levels(&mylist, levels);

    Display_All_list_aligne(mylist);

    int val = 324;
    p_cell serachCell = search(mylist, val);

    printf("La valeur trouvé est : %d\n", serachCell->value);
    display_cptRecherche();

    return 0;
}