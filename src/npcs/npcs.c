/*
** EPITECH PROJECT, 2023
** B-MUL-200-MPL-2-1-myrpg-noa.vanhamme
** File description:
** npcs.c
*/

#include "my.h"

void draw_npc(sfRenderWindow *window, npc_t *npc)
{
    sfRenderWindow_drawSprite(window, npc->sprite, NULL);
}

void draw_npcs(sfRenderWindow *window, npc_t *npcs)
{
    npc_t *current = npcs;

    while (current != NULL) {
        draw_npc(window, current);
        current = current->next;
    }
}

static char *fetch_content(char *filename)
{
    FILE *file = fopen(filename, "r");
    long file_size = 0;
    char *content = NULL;

    if (file != NULL){
        fseek(file, 0, SEEK_END);
        file_size = ftell(file);
        fseek(file, 0, SEEK_SET);
        content = malloc(file_size + 1);
        if (content != NULL){
            fread(content, 1, file_size, file);
            content[file_size] = '\0';
        }
        fclose(file);
        return content;
    }
    return NULL;
}

static void replace_newlines(char *src)
{
    for (int i = 0; src[i] != '\0'; i++)
        if ((src[i] == '\\') && (src[i + 1] == 'n')){
            src[i] = '\n';
            src[i + 1] = ' ';
        }
}

void display_dialog_box(void)
{
    sfRenderWindow_drawRectangleShape(engine()->graphics->window,
        global_game()->dialog_box->box, NULL);
    sfRenderWindow_drawText(engine()->graphics->window,
        global_game()->dialog_box->title, NULL);
    sfRenderWindow_drawText(engine()->graphics->window,
        global_game()->dialog_box->text, NULL);
    sfRenderWindow_display(engine()->graphics->window);
}

static void handle_inputs(void)
{
    sfEvent event;
    bool spaced = false;

    while (sfRenderWindow_pollEvent(engine()->graphics->window, &event) ||
        (!spaced)){
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(engine()->graphics->window);
        if (sfKeyboard_isKeyPressed(sfKeySpace))
            spaced = true;
    }
}

void set_text_on_dialog_box_and_draw(char *title, char *text)
{
    dialog_box_t **box = &global_game()->dialog_box;
    sfVector2f ppos = global_game()->player->position;
    sfVector2f dpos = {ppos.x - 400, ppos.y + 130};

    sfRectangleShape_setPosition((*box)->box, dpos);
    sfText_setPosition((*box)->title, (sfVector2f){dpos.x + 50, dpos.y + 10});
    sfText_setPosition((*box)->text, (sfVector2f){dpos.x + 50, dpos.y + 100});
    replace_newlines(text);
    sfText_setString((*box)->title, title);
    sfText_setString((*box)->text, text);
    display_dialog_box();
    handle_inputs();
    sfSleep(sfMilliseconds(280));
}

static void dialog_npc_next(char **dialog, npc_t *npc, char *content)
{
    char **text = NULL;
    char *name = NULL;

    text = string_to_array(dialog[npc->no_dialog * 2 - 1], "\n:\t");
    if (arr_len(text) % 2 != 0){
        fprintf(stderr, "Error: dialog file is not well formatted\nAre you\
        sure the text file does not ends with a newline?\n");
        return;
    }
    for (int i = 0; text[i] != NULL; i += 2){
        name = ((text[i][0] == 'p') ? "you" : npc->name);
        set_text_on_dialog_box_and_draw(name, text[i + 1]);
    }
    npc->no_dialog += 1;
    free(content);
}

void dialog_npc(npc_t *npc)
{
    char *content = fetch_content(npc->filename);
    int pos = 0;
    char **dialog = NULL;

    if (content == NULL)
        return;
    if (content[pos] == '\0')
        return;
    npc->talked_to = true;
    if (!npc->can_talk && npc->no_dialog > 1)
        npc->no_dialog -= 1;
    dialog = string_to_array(content, "{}");
    if (npc->no_dialog * 2 > (arr_len(dialog))){
        fprintf(stderr, "Error: not enough dialog in file\n");
        npc->no_dialog = arr_len(dialog) / 2;
    }
    dialog_npc_next(dialog, npc, content);
}
