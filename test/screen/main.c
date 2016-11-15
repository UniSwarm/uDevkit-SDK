#include "modules.h"
#include "board.h"
#include "archi.h"

#include <stdio.h>
#include <stdint.h>

#include "pictures.h"
#include "fonts.h"

#include <gui/widget.h>


//WORKING ON GUI_CONSOLE
typedef struct
{
    //size of window
    int width;
    int heigth;
    int x_pose, y_pose;
    // BUFFER
    // char* buffer;
    char buffer[200];

    Font* font;
    Color font_color;
    Color background_color;

} Console;

void console_write(Console *cmd, const char*);

//kinda constructor
//TODO: fonctions createContext? display? hide?
void console_open(Console *cmd, int x , int y)
{
    gui_setFont(cmd->font);
    gui_setPenColor(cmd->font_color);
    gui_setBrushColor(cmd->background_color);

    //create a banner up to the dipqlay window ?
    gui_drawFillRect(x, y, cmd->width, cmd->heigth);

    cmd->x_pose = x;
    cmd->y_pose = y;
    memset(cmd->buffer, 0, 200);
    cmd->buffer[0] = '\0';

    console_write(cmd, "Terminal successfully opened!");

    //TEST with a looooong text
    // console_write(cmd, "Terminal successfully opened! BONJOURerefefefefefefefefef");
}



//closing the terminal
void console_close(Console *cmd){}

//add a new entry to the buffer
void console_addEntry(Console* cmd, const char* txt)
{
    //we add the new text to the buffer
    if(cmd->buffer[0] == '\0')
    {
        gui_drawText(0, 0, "buffer is empty"); //DEBUG
        strcat(cmd->buffer, txt);
    }
    else
    {
        gui_drawText(0, 0, "buffer is not empty"); //DEBUG
        strcat(cmd->buffer, "\n");  //at each new entry we add the ending line character
        strcat(cmd->buffer, txt);   //then we add the new entry
    }

    //verifying if the new entry is not longer than the terminal width
    // char* new_str;
    // if( strlen(txt)*cmd->font->letters[0]->width > cmd->width )
    // {
    //     gui_drawText(0, 40, "TOO LONG"); //DEBUG

    //     int i = 0;
    //     int j = 0;
    //     while( txt[i] != '\0' )
    //     {
    //         if( strlen(txt)*cmd->font->letters[0]->width > )
    //         new_str[j] = txt[i];
            
    //     }
    // }
}

//write something in the console
//start a new line
void console_write(Console* cmd, const char* txt)
{
    //TODO: if(cmd_is_not_open){ "CERR NONONON"}

    console_addEntry(cmd, txt);

    printf("%s\n", cmd->buffer);

    // char src[] = "hi";
    // // char dest[6] = "abcdef"; // no null terminator
    // char dest[100]; // no null terminator
    // strncpy(dest, src, 2);
    // gui_drawText(cmd->x_pose, cmd->font->height+cmd->y_pose, dest);


    //NOW DIPSLAY THE TEXT
    char new_str[100];
    int i = 0;
    int j = 0;
    int line_index = 0;
    while( cmd->buffer[i] != '\0' )
    {
        new_str[j] = cmd->buffer[i];

        if( cmd->buffer[i+1] == '\n' || cmd->buffer[i+1] == '\0')
        {
            gui_drawText(cmd->x_pose, cmd->font->height*(line_index++)+cmd->y_pose, new_str);
            memset(new_str, 0, 100);
            j=0;
            ++i;
        }
        else
        {
            ++j;
            ++i;
        //     gui_drawText(cmd->x_pose, cmd->font->height*(line_index++)+cmd->y_pose, "yo");
        }


    }








    // FOR DEBUG 
    //then write then the line
    // gui_drawText(cmd->x_pose, cmd->y_pose, cmd->buffer);


    //si le texte a afficher dépasse alors on le découpe
    // const size_t lenth = strlen(txt);
    // // if(txt.nombre_of_characters*cmd->font.letters.width < cmd.width){ 
    // if(1){
    //     gui_drawText(0, 0, "trop grand");
    // }

    //bump all the line before
    //static int max_of_line = cmd.width / cmd->font.heigth;
    // if(we have max_of_line){ on efface le premier elts du buffer et on le remplace par TXT}

    //then refresh screen and write the all buffer !
}

int main(void)
{
    unsigned int i,j;
    char buff[101];
    size_t size;

    sysclock_setClock(120000000);
    board_init();

    // a6 init
    a6_init();

    gui_init();
    gui_fillScreen(Gui_Blue2);

    //display an image
    gui_dispImage(0, 0, &picture);

    gui_setPenColor(Gui_Yellow);
    gui_setBrushColor(0x2965);

    //initialize touch
    // ssize_t response = 42;
    // response = ar1000_init();
    // response = ar1000_enable_touch();

    //WORKING ON GUI_CONSOLE
    Console cmd;
    cmd.width = 300;
    cmd.heigth = 100;
    cmd.font = &core12b;
    cmd.font_color = Gui_White;
    cmd.background_color = Gui_Black;
    console_open(&cmd, 50, 50);
    console_write(&cmd, "bonjour");
    console_write(&cmd, "bab");
    console_write(&cmd, "prout");
    console_write(&cmd, "caca");




    /*gui_drawFillRect(50, 50, 50, 50);

    for(i=51;i<100;i++)
        gui_drawPoint(50, i);

    gui_setBrushColor(Yellow);
    gui_drawFillRect(51, 51, 50, 50);

    gui_setBrushColor(Blue);
    gui_drawFillRect(52, 52, 50, 50);

    gui_drawLine(50, 50, 420, 270);
    gui_drawLine(50, 270, 420, 50);*/





    //Drawing text
    gui_setFont(&core12b);
    gui_drawText(100, 100, "It seems to work !!! <3");
    gui_setFont(&core18b);
    gui_drawText(100, 150, "It seems to work !!! <3");

    //widget_addButton(50, 200, 150, 50);

    //displaying ar1000 responses
    // gui_drawText(100, 150, "response: ");
    // char to_disp[100];
    // sprintf(to_disp, "%d", response);
    // gui_drawText(200, 150, to_disp);

    while(1)
    {
        for(j=0;j<10;j++) for(i=0;i<65000;i++);

        size = a6_read(buff, 100);
        if(size>0)
        {
            gui_drawTextRect(188, 273, 282, 30, buff, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);
        }
    }

    return 0;
}
