#include <string.h>

/*
TODO:
console.resize()
console.moveToFirstPlan()
console.moveToLastPlan()

create a banner up to the display window around the console ?
    -> create a cross button to close console

take other special caracters into account like \t
*/

//WORKING ON GUI_CONSOLE
struct Terminal
{
    int8_t status;

    //size of window
    int width, height;
    int x_pose, y_pose;

    // BUFFER
    char buffer[500];

    const Font* font;
    Color font_color;
    Color background_color;
} Terminal_default = {0, -1, -1};

typedef struct Terminal Console;

//add a new entry to the buffer
//when there is a new entry and buffer !empty
//we add the \n character to the buffer
void console_addNewEntryToBuffer(Console* cmd, const char* txt)
{
    //at each new entry we add the ending line character
    if (strlen(cmd->buffer) != 0)
    {
        strcat(cmd->buffer, "\n");
    }

    // then we add the new entry
    strcat(cmd->buffer, txt);
}


/**
 * @Brief console_howManyLinesItTakes compute the number of lines
 *        a txt is taking in the console
 * @params cmd the console
 * @params txt the text
  */
uint8_t console_howManyLinesItTakes(const Console* cmd, const char* txt)
{
    if (cmd->width > 0)
    {
        //computing number of carriage returns
        uint8_t carriage_return_nbr = 0;
        int i = 0;
        while (txt[i] != '\0')
        {
            if (txt[i] == '\n')
            {
                ++carriage_return_nbr;
            }
            ++i;
        }

        //if there is not carriage_return then we just work on the txt
        if ( carriage_return_nbr == 0 )
        {
            return (1 + (gui_getFontTextWidth(txt) / cmd->width) );
        }
        else //if not then we have to work on each part of the txt
        {
            int nbr_of_too_large_lines = 0;
            // int nbr_of_too_large_lines = 1; //there is at least one line

            //iterating through txt
            int j=0;
            while (txt[j] != '\0')
            {
                //copying each txt character into a tmp_str
                //unitl we meet a carriage_return
                char tmp_str [200];
                int i = 0;
                while (txt[i] != '\n')
                {
                    tmp_str[i++] = txt[j++];
                }

                //then check if tmp_str can be written into one line
                // nbr_of_too_large_lines += 1 + (gui_getFontTextWidth(tmp_str) / cmd->width);
                nbr_of_too_large_lines += (gui_getFontTextWidth(tmp_str) / cmd->width);
            }

            printf("carriage_return_nbr: %d\n", carriage_return_nbr);
            printf("nbr_of_too_large_lines: %d\n", nbr_of_too_large_lines);
            return (1 + carriage_return_nbr + nbr_of_too_large_lines);
        }
    }
    else
        printf("Error: console_howManyLinesItTakes: Console width has a wrong value (%d).\n",cmd->width);

    return 0;
}









////////////////////////////////////////////////////////////////////////////////
//NOT STABLE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
void console_write(Console*, const char*);

//kinda constructor
//TODO: fonctions createContext? display? hide?
void console_open(Console *cmd, const int x, const int y)
{
    if (cmd->status == 1) //cmd is already opened
    {
        printf("Error: console_open: the current console is already opened.\n");
    }
    else
    {
        gui_setFont(cmd->font);
        gui_setPenColor(cmd->font_color);
        gui_setBrushColor(cmd->background_color);

        cmd->x_pose = x;
        cmd->y_pose = y;
        gui_drawFillRect(cmd->x_pose, cmd->y_pose, cmd->width, cmd->height);

        cmd->buffer[0] = '\0';
        cmd->status = 1;

        // console_write(cmd, "Terminal successfully opened!");
    }
}

//closing the Console
void console_close(Console *cmd)
{
    if (cmd->status == 0) //cmd is already closed
    {
        printf("Error: console_open: the current console is already closed.\n");
    }
    else
    {
        cmd->status = 0;
    }
}

/**
 * @Brief console_treatNewMessage verify if the message is longer than the console width
 *                                if not then add split the message
 */
void console_treatNewMessage(const Console* cmd, char* txt)
{
    //if txt is taking more than 1 line
    if (console_howManyLinesItTakes(cmd, txt) > 1)
    {
        //TODO: maybe there will be more than one \n to add
        //so we have to adapt the size of txt resize
        // printf("\n\n\nTODO: Regler le probleme du character parasite a été temporairement réglé avec NEW_STR[strlen(txt) + nbr_of_lines_2_add + 10]\n\n\n");
        char new_str [strlen(txt) + 10];

        //it's a counter taking care of non go over the cmd width
        int counter = 0;

        int
        i = 0,
        j = 0;
        while (txt[i] != '\0')
        {
            counter += gui_getFontWidth(txt[i]);

            //if the txt has a \n character, add the carriage_return character
            if (txt[i] == '\n')
            {
                new_str[j] = '\n';
                counter = 0;
                ++i;
            }
            else //else we continue to evaluate the lenth of the message
            {
                //if we are at the edge of the screen then we add '\n' in new_str
                if (counter > cmd->width)
                {
                    //adding a carriage return to the new_str
                    new_str[j] = '\n';
                    counter = 0;  //reseting the counter
                }
                else    //else we just copy the txt to new_str
                {
                    new_str[j] = txt[i];
                    ++i;
                }
            }
            ++j;
        }

        //at the end of you copy the new_str in the txt
        strcpy(txt, new_str);
    }

    // else we just do nothing and continue our lives
}

void remove_element(char* array, const int index, const int array_length)
{
    int i;
    for(i = index; i < array_length - 1; ++i)
        array[i] = array[i + 1];
}

//verifying if the message is heighter than the console height
//if the buffer DEPASSE then we forget the buffer
void console_verifyBufferHeight(Console* cmd)
{
    //si il n'y a plus de ligne disponible alors on coupe le nombre de lignes pour que ça passe
    printf("console_verifyBufferHeight: console_howManyLinesItTakes: %d\n", console_howManyLinesItTakes(cmd, cmd->buffer));

    const uint8_t nbr_max_line_in_cmd = cmd->height / cmd->font->height;
    printf("nbr_max_line_in_cmd: %d\n", nbr_max_line_in_cmd);

    //if there is too much text then we will have to cut the text
//    int counter = 0;
    // while ( console_howManyLinesItTakes(cmd, cmd->buffer)-counter > nbr_max_line_in_cmd )
    while ( console_howManyLinesItTakes(cmd, cmd->buffer) > nbr_max_line_in_cmd )
    {
        printf("current nbr of lines: %d\n", console_howManyLinesItTakes(cmd, cmd->buffer));

        // char bumped_txt [strlen(cmd->buffer)];

        //iterate through the buffer until we go over the first line
        // int i = 0;
        // while ( cmd->buffer[i] != '\n' )
        // {
        //     printf("cmd->buffer: %c\n", cmd->buffer[i]);
        //     ++i;
        // }
        // printf("i: %d\n", i);





        // int for_counter;
        // for(for_counter = 0; for_counter < i; ++for_counter)
        // {
        //     printf("for_counter: %d\n", for_counter);
        //     cmd->buffer[for_counter] = cmd->buffer[for_counter + 1];
        // }

        // int iterate = 0;
        // while ( cmd->buffer[iterate] != '\0' )
        // {
        //     printf("after: %c\n", cmd->buffer[iterate++]);
        // }


        // ++counter;


        // int line_is_suppr = 0;

        // int i = 0;
        // int j = 0;
        // while ( cmd->buffer[i] != '\0')
        // {
        //     if (line_is_suppr == 1)
        //     {
        //         bumped_txt[j] = cmd->buffer[i];
        //         ++j;
        //     }
        //     else
        //     {
        //         if (cmd->buffer[i] == '\n') line_is_suppr = 1;
        //     }
        //     ++i;
        // }

    //     strcpy(cmd->buffer, bumped_txt);

    }
    // if not then we continue to live our lives

}

//write something in the console
//start a new line
void console_write(Console* cmd, const char* txt)
{
    //TODO: if (cmd_is_not_open){ "CERR NONONON"}
    if (cmd->status == 0)
    {
        printf("Error: console_write: the current console is already opened.\n");
    }
    else
    {
        //copy the txt to another to zork on it
        char txt_2_work_on[strlen(txt)];
        strcpy(txt_2_work_on, txt);

        // printf("current text: %s\n", txt);
        // console_treatNewMessage(cmd, txt_2_work_on);
        // printf("console_treatNewMessage: %s\n", txt_2_work_on);

        console_addNewEntryToBuffer(cmd, txt_2_work_on);
        printf("\n\n");
        printf("lines of txt: %d\n", console_howManyLinesItTakes(cmd, txt_2_work_on) );
        printf("\n\n");
        printf("lines of buffer: %d\n", console_howManyLinesItTakes(cmd, cmd->buffer) );
        // printf("\nbuffer: %s\n", cmd->buffer );

        // console_verifyBufferHeight(cmd);
        // printf("console_howManyLinesItTakes: %d\n", console_howManyLinesItTakes(cmd, cmd->buffer) );


        // // char src[] = "hi";
        // // // char dest[6] = "abcdef"; // no null terminator
        // // char dest[100]; // no null terminator
        // // strncpy(dest, src, 2);
        // // gui_drawText(cmd->x_pose, cmd->font->height+cmd->y_pose, dest);

        //reset display
        gui_drawFillRect(cmd->x_pose, cmd->y_pose, cmd->width, cmd->height);


        //NOW DIPSLAY THE TEXT
        char new_str[100];
        int i = 0;
        int j = 0;
        int line_index = 0;
        while ( cmd->buffer[i] != '\0' )
        {
            new_str[j] = cmd->buffer[i];

            if (cmd->buffer[i+1] == '\n' || cmd->buffer[i+1] == '\0')
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
            }
        }



    }





    // FOR DEBUG
    //then write then the line
    // gui_drawText(cmd->x_pose, cmd->y_pose, cmd->buffer);


    //si le texte a afficher dépasse alors on le découpe
    // const size_t lenth = strlen(txt);
    // // if (txt.nombre_of_characters*cmd->font.letters.width < cmd->width){
    // if (1){
    //     gui_drawText(0, 0, "trop grand");
    // }

    //bump all the line before
    //static int max_of_line = cmd->width / cmd->font.height;
    // if (we have max_of_line){ on efface le premier elts du buffer et on le remplace par TXT}

    //then refresh screen and write the all buffer !
}