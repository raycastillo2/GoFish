#include "deck.h"

int shuffle() {
	char suits[4] = {'S', 'H', 'D', 'C'};
	char* ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	int index = 0;  
	for (int i = 0; i < 4; i++) {
 		for (int j = 0; j < 13; j++) {
			struct card curr_card;
			curr_card.suit = suits[i];
			curr_card.rank = ranks[j];
			deck_instance.list[index] = curr_card;
			index++;
		}
	}
	for (int i = 0; i < 52; i++) {
		int rnum = rand() % 52;
		struct card shuffle = deck_instance.list[i];
		deck_instance.list[i] = deck_instance.list[rnum];
		deck_instance.list[rnum] = shuffle;
	}
	deck_instance.top_card = 0;
	return 0;
}

int deal_player_cards(struct player* target) {
	target->card_list = NULL;
	target->hand_size = 0;
	for (int i = 0; i < 7; i++) {
		struct hand* next_hand = (struct hand*)malloc(sizeof(struct hand));
		if (next_hand  == NULL) {
                	return -1;
        	}	
		next_hand->top = *next_card(); 
		next_hand->next = target->card_list;
		target->card_list = next_hand;
		target->hand_size++;
	}
	target->book_element = 0; 
	return 0;
}

struct card* next_card() {
	struct card* next_card = &(deck_instance.list[deck_instance.top_card]);
	deck_instance.top_card++;
	return next_card;
}

size_t deck_size() {
	return 52 - deck_instance.top_card;
}


