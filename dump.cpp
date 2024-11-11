#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "dbl_linked_list_const.h"
#include "dbl_linked_list_funcs.h"

int  generate_html (dbl_linked_list_t *list, char *picture_name, char *html_name);
void text_dump     (dbl_linked_list_t *xlist, FILE *dump_file);


char *generate_png (dbl_linked_list_t *list)
{
    static int dumpNum = 0;
    char txt_file [30] = {};
    char png_file [30] = {};
    char html_file[30] = {};

    sprintf (txt_file,  "dump_picture%d.txt", dumpNum);
    sprintf (png_file,  "dump_picture%d.png", dumpNum);
    sprintf (html_file, "dump%d.html",        dumpNum);

    FILE *input_file = fopen(txt_file, "w");

    fprintf (input_file, "digraph G {\n\trankdir = LR\n");
    printf("capasity = %d", list->capacity);
    for (int i = 0; i <= list->capacity; i++)
    {
        fprintf (input_file, "\tnode%d [shape=Mrecord; label = \"  %d | data = %d | next = %d | prev = %d  \"]; \n", i, i,
                                                        list->array[i].data,
                                                        list->array[i].next,
                                                        list->array[i].prev );
    }

    fprintf (input_file,"\n");
    int j = list->array[0].next;
    fprintf (input_file, "\tnode%d ->node%d [ weight=0; color=blue; ]\n", 0, j);
    while (j != 0)
    {
        fprintf(input_file, "\tnode%d ->node%d [ weight=0; color=blue; ]\n", j, list->array[j].next);
        j = list->array[j].next;
    }


    fprintf (input_file,"\n");
    int k = list->array[0].prev;
    fprintf (input_file, "\tnode%d ->node%d [ weight=0; color=red; ]\n", 0, k);
    while (k != 0)
    {
        fprintf(input_file, "\tnode%d ->node%d [ weight=0; color=\"red\"]\n", k, list->array[k].prev);
        k = list->array[k].prev;
    }


    fprintf (input_file,"\n");
    int free = list->firstFreeCell;
    while( list->array[free].next != -1)
    {
        fprintf(input_file, "\tnode%d ->node%d [ weight=0; color=blue; ]\n", free, list->array[free].next);
        free = list->array[free].next;
    }



    fprintf(input_file, "}");

    fclose(input_file);
    char cmd_command[128] = "";
    sprintf (cmd_command, "dot -Tpng %s -o %s", txt_file, png_file);

    system (cmd_command);

    generate_html(list, png_file, html_file);

    return 0;
}

int generate_html(dbl_linked_list_t *list, char *picture_name, char *html_file)
{
    FILE *input_file = fopen(html_file, "w");

    text_dump(list, input_file);

    fprintf(input_file, "<img src=\"C:/MIPT/dbl_linked_list/%s\">", picture_name);

    fclose(input_file);

}

void text_dump (dbl_linked_list_t *list, FILE *dump_file)
{
    fprintf(dump_file ,"<pre><br/> num:  ");
    for(int i = 0; i < list->capacity; i ++)
    {
        fprintf(dump_file ,"%4d  ", i);
    }

    fprintf(dump_file ,"<br/> data: ");
    for(int i = 0; i < list->capacity; i ++)
    {
        fprintf(dump_file ,"%4d  ", list->array[i].data);
    }

    fprintf(dump_file ,"<br/> next: ");
    for(int i = 0; i < list->capacity; i ++)
    {
        fprintf(dump_file ,"%4d  ", list->array[i].next);
    }

    fprintf(dump_file ,"<br/> prev: ");
    for(int i = 0; i < list->capacity; i ++)
    {
        fprintf(dump_file ,"%4d  ", list->array[i].prev);
    }

    fprintf(dump_file ,"</pre><br/> <br/>");
}
