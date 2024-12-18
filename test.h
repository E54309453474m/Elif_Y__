#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 100
#define MAX_NUM 5

typedef struct Room {
    char *description;
    char *items[MAX_NUM];
    int item_count;
    int creature_count;
    char *creatures[MAX_NUM];
    struct Room *forward, *back, *left, *right;
} Room;

typedef struct Player {
    int health;
    int strength;
    char *inventory[MAX_NUM];
    int inventory_count;
} Player;

Room *create_room(const char *desc);
void add_item_and_creature(Room *room1, const char *item, const char *creature);
void connect_rooms(Room *room1, Room *room2, const char *direction);
void move(Room **current_room, const char *direction);
void look(Room *current_room);
void inventory(Player *player);
void pickup(Room *current_room, Player *player);
void attack(Player *player, Room *current_room);
void list_saves();

Room *create_room(const char *desc) {
    Room *room = malloc(sizeof(Room));
    room->description = strdup(desc);
    room->item_count = 0;
    room->creature_count = 0;
    room->forward = room->back = room->left = room->right = NULL;
    return room;
}

void connect_rooms(Room *room1, Room *room2, const char *direction) {
    if (strcmp(direction, "forward") == 0) {
        room1->forward = room2;
        room2->back = room1;
    } else if (strcmp(direction, "back") == 0) {
        room1->back = room2;
        room2->forward = room1;
    } else if (strcmp(direction, "left") == 0) {
        room1->left = room2;
        room2->right = room1;
    } else if (strcmp(direction, "right") == 0) {
        room1->right = room2;
        room2->left = room1;
    }
}

void add_item_and_creature(Room *room1, const char *item, const char *creature) {
    if (item && room1->item_count < MAX_NUM) {
        room1->items[room1->item_count++] = strdup(item);
    }
    if (creature && room1->creature_count < MAX_NUM) {
        room1->creatures[room1->creature_count++] = strdup(creature);
    }
}

void move(Room **current_room, const char *direction) {
    Room *next_room = NULL;
    if (strcmp(direction, "forward") == 0) next_room = (*current_room)->forward;
    else if (strcmp(direction, "back") == 0) next_room = (*current_room)->back;
    else if (strcmp(direction, "left") == 0) next_room = (*current_room)->left;
    else if (strcmp(direction, "right") == 0) next_room = (*current_room)->right;

    if (next_room) {
        *current_room = next_room;
        printf("You moved %s.\n", direction);
    } else {
        printf("You can't go %s.\n", direction);
    }
}

void look(Room *current_room) {
    printf("Room: %s\n", current_room->description);
    if (current_room->item_count > 0) {
        printf("Items here: ");
        for (int i = 0; i < current_room->item_count; i++) {
            printf("%s ", current_room->items[i]);
        }
        printf("\n");
    }
    if (current_room->creature_count > 0) {
        printf("A %s is here!\n", current_room->creatures[current_room->creature_count - 1]);
    }
}

void inventory(Player *player) {
    printf("Inventory:\n");
    for (int i = 0; i < player->inventory_count; i++) {
        printf("- %s\n", player->inventory[i]);
    }
}

void pickup(Room *current_room, Player *player) {
    if (player->inventory_count >= MAX_NUM) {
        printf("Inventory full!\n");
        return;
    }
    if (current_room->item_count > 0) {
        char *item = current_room->items[current_room->item_count - 1];
        player->inventory[player->inventory_count++] = strdup(item);
        printf("You picked up %s.\n", current_room->items[current_room->item_count - 1]);
        if (strcmp(item, "excalibur") == 0) {
            player->strength += 10;
            printf("Your damage power increased by 10.");
        }
        if (strcmp(item, "silver locket") == 0) {
            player->health += 10;
            printf("Your health increased by 10.");
        }
        current_room->item_count--;
    } else {
        printf("Item not found!\n");
    }
}

void attack(Player *player, Room *current_room) {
    if (current_room->creature_count == 0) {
        printf("No creatures to attack here!\n");
        return;
    }
    char *creature = current_room->creatures[current_room->creature_count - 1];
    int creature_health = 0;
    int creature_strength = 0;
    if (strcmp(creature, "cyclop") == 0) {
        creature_health = 20;
        creature_strength = 10;
    }
    if (strcmp(creature, "kerberos") == 0) {
        creature_health = 40;
        creature_strength = 40;
    }
    while (player->health > 0 && creature_health > 0) {
        creature_health -= player->strength;
        if (creature_health <= 0) {
            printf("You defeated the %s!\n", creature);
        }
        player->health -= creature_strength;
        if (player->health <= 0) {
            printf("You were defeated by the %s.\n", creature);
            exit(70);
        }else{
            printf("Your health decreased by %d\n.",creature_strength);
        }
        return;
        
    }
}

void load_game(Player *player, Room **current_room) {
    FILE *file;
    file = fopen("savedgame.txt", "r");
    if (file == NULL) {
        printf("Unable to load the game.\n");
        return;
    }
    fscanf(file, "%d %d %d\n", &player->health, &player->strength, &player->inventory_count);
    for (int i = 0; i < player->inventory_count; i++) {
        char item[100];
        fscanf(file, "%s\n", item);
        player->inventory[i] = strdup(item);
    }
    char description[100];
    fscanf(file, "%s\n", description);
    *current_room = create_room(description);
    fclose(file);
    printf("Game loaded.\n");
}

void save_game(Player *player, Room *current_room) {
    FILE *file;
    file = fopen("savedgame.txt", "w");
    if (file == NULL) {
        printf("Unable to save the game.\n");
        return;
    }
    fprintf(file, "%d %d %d\n", player->health, player->strength, player->inventory_count);
    for (int i = 0; i < player->inventory_count; i++) {
        fprintf(file, "%s\n", player->inventory[i]);
    }
    
    fprintf(file, "%s\n", current_room->description);
    fclose(file);
    printf("Game saved.\n");
}

void list_saves() {
    system("ls saves/");
}

int main() {
    Player player = {50, 30, malloc(MAX_NUM * sizeof(char *)), 0, MAX_NUM};
    Room *rooms[10];
    Room *current_room;

    rooms[0] = create_room("There are two torches illuminating this room.");
    rooms[1] = create_room("A bright room with a glowing sword.");
    rooms[2] = create_room("A dark narrow corridor.");
    rooms[3] = create_room("There is a cyclop in this room.");
    rooms[4] = create_room("A bright room with a silver locket.");
    rooms[5] = create_room("There is a kerberos in this room.");
    connect_rooms(rooms[0], rooms[1], "forward");
    connect_rooms(rooms[1], rooms[2], "right");
    connect_rooms(rooms[2], rooms[3], "forward");
    connect_rooms(rooms[3], rooms[4], "left");
    connect_rooms(rooms[4], rooms[5], "forward");
    current_room = rooms[0];
    add_item_and_creature(rooms[1], "excalibur", NULL);
    add_item_and_creature(rooms[3], NULL, "cyclop");
    add_item_and_creature(rooms[4], "silver locket", NULL);
    add_item_and_creature(rooms[5], NULL, "kerberos");

    char input[MAX_INPUT];
    while (1) {
        printf("\n>Please choose('move 'forward''right''left''back','attack','look','inventory','pickup','list','save','load','exit') \n");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = 0;
        if (strncmp(input, "move", 4) == 0) {
            move(&current_room, input + 5);
        } else if (strcmp(input, "attack") == 0) {
            attack(&player, current_room);
        } else if (strcmp(input, "look") == 0) {
            look(current_room);
        } else if (strcmp(input, "inventory") == 0) {
            inventory(&player);
        } else if (strncmp(input, "pickup", 6) == 0) {
            pickup(current_room, &player);
        } else if (strcmp(input, "list") == 0) {
            list_saves();
        } else if (strcmp(input, "save") == 0) {
            save_game(&player, current_room);
        } else if (strcmp(input, "load") == 0) {
            load_game(&player, &current_room);
        } else if (strcmp(input, "exit") == 0) {
            printf("Exiting the game.\n");
            return 0;
        } else {
            printf("Invalid command.\n");
        }
    }
    return 0;
}