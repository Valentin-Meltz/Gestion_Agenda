#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "module timer-20231031/timer.h"
#include "s_d_list.h"
#include "contact.h"
#include "rendez-vous.h"
#include "Users.h"


int main() {
    l_contact MyContactList = CreateL_contact();
    Load_contact(&MyContactList);
    DisplayAllContact(MyContactList);
    return 0;
}