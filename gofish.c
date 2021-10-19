#include <stdio.h>
#include "deck.h"

int main(int argc, char* argv[]) {
  	shuffle();
	printf("Starting Game\nDealing Cards\n");
	deal_player_cards(&user);
        deal_player_cards(&computer);
	while(1){
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	  	user_play(&user);
		if(game_over(&user)){
			printf("You Won");
			break;
		}
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	  	computer_play(&computer);
		if(game_over(&computer)){
                        printf("You Lost");
                        break;
                }
	}
	printf("\nDo you want to play again [Y/N]: ");
	char input[1];
	scanf("%s", input);
	if(strcmp(input, "Y") == 0){
		main(1, argv);
	}else{
		return 0;
	}
}
