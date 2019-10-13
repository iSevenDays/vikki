//
//  uicard.h
//  vikki
//
//  Created by Anton Sokolchenko on 10/11/19.
//

#ifndef uicard_h
#define uicard_h


enum card_icon {
	REMINDER,
	NOTE,
};
struct confirmation_card {
	char *title;
	char *text;
	enum card_icon top_icon;
};

#endif /* uicard_h */
