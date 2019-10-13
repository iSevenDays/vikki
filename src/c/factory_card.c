//
//  factory_card.c
//  vikki
//
//  Created by Anton Sokolchenko on 10/11/19.
//

#include "factory_card.h"
#include <stdlib.h>

struct confirmation_card *create_confirmation_card(char *title, char *text, enum card_icon card_icon) {
	struct confirmation_card *card = malloc(sizeof *card);
	card->title = title;
	card->text = text;
	card->top_icon = card_icon;

	return card;
}

void destroy_confirmation_card(struct confirmation_card* card) {
	free(card->title);
	free(card->text);
	free(card);
}
