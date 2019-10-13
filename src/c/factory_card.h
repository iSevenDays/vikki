//
//  factory_card.h
//  vikki
//
//  Created by Anton Sokolchenko on 10/11/19.
//

#ifndef factory_card_h
#define factory_card_h

#include <stdio.h>
#include "uicard.h"


/// Create card and transfer ownership of the title and text
/// @param title title of the card
/// @param text text of the card
/// @param card_icon card icon
struct confirmation_card *create_card(char *title, char *text, enum card_icon card_icon);


/// Free the card
/// @param card card
void destroy_confirmation_card(struct confirmation_card* card);
#endif /* factory_card_h */
