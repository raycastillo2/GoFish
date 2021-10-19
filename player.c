#include "player.h"

int add_card(struct player* target, struct card* new_card){
	struct hand* new_hand = (struct hand*)malloc(sizeof(struct hand));
	if (new_hand  == NULL) {
                        return -1;
        }
	new_hand->top = *new_card;
	new_hand->next = target->card_list;
        target->card_list = new_hand;
	target->hand_size++;
	return 0;
}

int remove_card(struct player* target, struct card* old_card){
	struct hand* curr_card = target->card_list;
	struct hand* saved_card = NULL;
	if (strcmp(curr_card->top.rank, old_card->rank)==0){
		target->card_list = curr_card->next;
		target->hand_size--;
		free(curr_card);
		return 0;
	} 
	while(strcmp(curr_card->top.rank, old_card->rank)!=0){
		if (curr_card->next == NULL){
			return -1;
		}
		saved_card = curr_card;
		curr_card = curr_card->next; 
	}
	saved_card->next = curr_card->next;
	free(curr_card);
	target->hand_size--;
	return 0;
}

char check_add_book(struct player* target){
	struct hand* curr_card = target->card_list;
	for(int i = 0; target->book[i] != '\0'; i++){
                printf("%s", target->book[i]);
        }
        printf("\n");
	while(curr_card != NULL){
		struct hand* curr_card_2 = target->card_list;
	        int val = 0;
		while(curr_card_2 != NULL){
			if(strcmp(curr_card->top.rank, curr_card_2->top.rank)==0){
				val++;
			}
			curr_card_2 = curr_card_2->next;
		}
		if(val == 4){
			for(int i = 0; i < 4; i++){
				remove_card(target, &curr_card->top);
			}
			target->book[target->book_element] = curr_card->top.rank;
			target->book_element++;
			printf("Adding %s to book \n", curr_card->top.rank);
		}
		curr_card = curr_card->next;
	}
	return 0;
}

int search(struct player* target, char rank[2]){
	struct hand* curr_card = target->card_list;
	while(curr_card != NULL) {
		_Bool match = 1;
		for (int i = 0; i < 2; i++) {
			if (curr_card->top.rank[i] != rank[i]) {
				match = 0;
				break;
			}
		}
		if (match) {
			return 1;
		}
		curr_card = curr_card->next;
	}
	return 0;
}

int transfer_cards(struct player* src, struct player* dest, char* rank){
	struct hand* curr_card = src->card_list;
	int count = 0;
        while(curr_card != NULL) {
                _Bool match = 1;
                for (int i = 0; i < 2; i++) {
                        if (curr_card->top.rank[i] != rank[i]) {
                                match = 0;
                                break;
                        }
                }
                if (match) {
			printf("Transferring %s%c\n", curr_card->top.rank, curr_card->top.suit);
                        add_card(dest, &curr_card->top);
                        remove_card(src, &curr_card->top);
                        count++;
                }
                curr_card = curr_card->next;
        }
        return count;
	
}

int game_over(struct player* target){
	if (target->book_element == 7){
		return 1;
	}
	return 0;
}

int reset_player(struct player* target){
	struct hand* curr_card = target->card_list;
	while(curr_card != NULL){
		remove_card(target, &curr_card->top);
	}
	for(int i=0; i < 7; i++){
		target->book[i] = "";
	}
        target->hand_size = 0;
	return 0;
} 

char computer_play(struct player* target){
	if(target->hand_size == 0){
		printf("\nComputer's Turn \nI need a card");
		add_card(target, next_card());
		return 0;
	}
	int num = rand() % target->hand_size;
	struct hand* curr_card = target->card_list;
	for (int i = 0; i < num; i++){
		curr_card = curr_card->next;
	}
	printf("\nComputer's Turn \nDo you have a  %s, \n", curr_card->top.rank);
        if (search(target, curr_card->top.rank) == 0){
                printf("Error - Computer Messed up\n");
                computer_play(target);
        }
        if (search(&user, curr_card->top.rank) == 0){
                if(deck_size() != 0){
                	add_card(target, next_card());
		}else{
                        printf("Deck out of cards\n");
                }
		printf("Aww you dont have that card,\n");
		printf("Computer Book: ");
                check_add_book(target);
        }else{
                printf("I'll be taking that\n ");
                transfer_cards(&user, target, curr_card->top.rank);
		printf("Computer Book: ");
                check_add_book(target);
		printf("And i go again!");
		computer_play(target);
		
        }
        return curr_card->top.rank[0];
}

char user_play(struct player* target){
	printf("\nYour Turn\n");
	 if(target->hand_size == 0){
                printf("You need a card");
                add_card(target, next_card());
                return 0;
        }
	char input[2];
	struct hand* curr_card = target->card_list;
        printf("Your Hand: ");
	while(curr_card != NULL){
		printf("%s%c ", curr_card->top.rank, curr_card->top.suit);
		curr_card = curr_card->next;
        }
	printf("\nWhat do you want? \n");
	while(1){
		scanf("%s", input);
		if(search(target, input) == 1) {
			break;
		}
		printf("Error - Must have at least one card of that rank to play \n Try again \n");
	}
	printf("Searching... ");
	if (search(&computer, input) == 0){
		if(deck_size() != 0){
			printf("Go fish\n");
			add_card(target, next_card());
		}else{
			printf("Deck out of cards\n");
		}
		printf("Your Book: ");
                check_add_book(target);
	}else{
		transfer_cards(&computer, target, input);
		printf("Your Book: ");
                check_add_book(target);
		printf("You go again");
		user_play(target);
	}
	return input[0];
}
	
