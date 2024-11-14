#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

#include "..\\headers\dbl_linked_list_const.h"
#include "..\\headers\dbl_linked_list_funcs.h"
#include "..\\headers\dump_funcs.h"

const int FILE_NAME_SIZE = 64;

char *generate_png (dbl_linked_list_t *list, int dumpNum)
{
    char        txt_file [FILE_NAME_SIZE] = {};
    static char png_file [FILE_NAME_SIZE] = {};

    sprintf (txt_file,  "dump_picture%d.txt", dumpNum);
    sprintf (png_file,  "dump_picture%d.png", dumpNum);

    FILE *dot_file = fopen(txt_file, "w");

    fprintf (dot_file, "digraph G {\n\trankdir = LR\n");
    //printf("capasity = %d", list->capacity);

    //fprintf (dot_file, "\tfree_node [fillcolor = lightgreen, style=\"rounded, filled\" shape=Mrecord; label = \" FREE \"]; \n ");

    for (int i = 0; i <= list->capacity; i++)
    {
        fprintf (dot_file, "\tnode%d [shape=Mrecord, style=\"rounded, filled\" label = \"  %d | data = %d | next = %d | prev = %d  \"]; \n", i, i,
                                                        list->array[i].data,
                                                        list->array[i].next,
                                                        list->array[i].prev );
    }

    fprintf(dot_file, "\tnode0 [fillcolor=lightblue]\n", free);


    fprintf (dot_file,"\n");
    int j = list->array[0].next;
    //fprintf (dot_file, "\tnode%d ->node%d [ weight=100, color=white ];\n", 0, j);

    do{
        fprintf(dot_file, "\tnode%d ->node%d [ weight=100, color=white ];\n", j, list->array[j].next);
        j = list->array[j].next;
    }while (j != 0)


    fprintf (dot_file,"\n");
    j = list->array[0].next;
    {
        fprintf(dot_file, "\tnode%d ->node%d [color=blue ];\n", j, list->array[j].next);
        j = list->array[j].next;
    }while (j != 0)


    fprintf (dot_file,"\n");
    int k = list->array[0].prev;
    fprintf (dot_file, "\tnode%d ->node%d [color=red ];\n", 0, k);
    while (k != 0)
    {
        fprintf(dot_file, "\tnode%d ->node%d [color=red];\n", k, list->array[k].prev);
        k = list->array[k].prev;
    }
    printf("end cicles\n");


    //fprintf (dot_file,"\n\tedge[color=green]\n");
    int free = list->firstFreeCell                                 ;
    if (free != -1)
    {
        fprintf (dot_file, "\tnode%d[fillcolor=lightgreen]\n", free)   ;
        fprintf (dot_file, "\tfree_node -> node%d  [weight=0]\n", free);
    }

    while( list->array[free].next != -1 && free != -1)
    {
        printf("test free = %d\n", free);
        fprintf (dot_file, "\tnode%d[fillcolor=lightgreen]\n", list->array[free].next)    ;
        fprintf (dot_file, "\tnode%d ->node%d [weight=0]\n", free, list->array[free].next);
        free = list->array[free].next;
        printf("end test free = %d", free);
    }

    printf("end cicles2\n");
    fprintf(dot_file, "}");



    fclose(dot_file)          ;
    char cmd_command[128] = "";
    sprintf (cmd_command, "dot -Tpng %s -o %s", txt_file, png_file);
    printf("syst\n");
    system (cmd_command);

    //generate_html(list, png_file, html_file);

    return png_file;
}


char *generate_png_real_location(dbl_linked_list_t *list, int dumpNum)
{
    char        txt_file [FILE_NAME_SIZE] = {};
    static char png_file [FILE_NAME_SIZE] = {};

    sprintf (txt_file,  "dump_picture_true%d.txt", dumpNum);
    sprintf (png_file,  "dump_picture_true%d.png", dumpNum);

    FILE *dot_file = fopen(txt_file, "w");

    fprintf (dot_file, "digraph G {\n\trankdir = LR; \n\t splines=spline; \n\t nodesep=1; \n\t ranksep=1.2; \n");
    //printf("capasity = %d", list->capacity);

    fprintf (dot_file, "\tfree_node [fillcolor = lightgreen, style=\"rounded, filled\" shape=Mrecord; label = \" FREE \"]; \n ");

    for (int i = 0; i <= list->capacity; i++)
    {
        fprintf (dot_file, "\tnode%d [shape=Mrecord, style=\"rounded, filled\" label = \"  %d | data = %d | next = %d | prev = %d  \"]; \n", i, i,
                                                        list->array[i].data,
                                                        list->array[i].next,
                                                        list->array[i].prev );
    }

    fprintf(dot_file, "\tnode0 [fillcolor=lightblue]\n", free);


    fprintf (dot_file,"\n");
    for (int j = 0; j <= list->capacity - 1; j++)
    {
        fprintf(dot_file, "\tnode%d ->node%d [ color=white ];\n", j, j + 1);
    }


    fprintf (dot_file,"\n");
    int j = list->array[0].next;
    if ( 0 != list->array[list->array[0].next].prev)
    {
        fprintf (dot_file, "\tnode%d ->node%d [ constraint=false, color=red ];\n", 0, j);
        fprintf (dot_file, "\tnode%d ->node%d [ constraint=false, color=red ];\n", 0, j);
    }
    else
    {
        fprintf (dot_file, "\tnode%d ->node%d [ constraint=false, color=green, dir=both, arrowtail=crow ];\n", 0, j);
    }

    while (j != 0)
    {
        if ( j != list->array[list->array[j].next].prev)
        {
            fprintf (dot_file, "\tnode%d ->node%d [ constraint=false, color=red ];\n", j,                   list->array[j].next);
            fprintf (dot_file, "\tnode%d ->node%d [ constraint=false, color=red ];\n", list->array[j].next, j                   );
        }
        else
        {
            fprintf (dot_file, "\tnode%d ->node%d [ constraint=false, color=green, dir=both, arrowtail=crow ];\n", j, list->array[j].next);
        }

        j = list->array[j].next;
    }



    //fprintf (dot_file,"\n\tedge[color=green]\n");
    int free = list->firstFreeCell                                 ;
    if (free != -1){
        fprintf (dot_file, "\tnode%d[fillcolor=lightgreen]\n", free)   ;
    }
    //fprintf (dot_file, "\tfree_node -> node%d  [ constraint=false, weight=0]\n", free);

    while( list->array[free].next != -1 && free != -1 )
    {
        fprintf (dot_file, "\tnode%d[fillcolor=lightgreen]\n", list->array[free].next)    ;
        fprintf (dot_file, "\tnode%d ->node%d [constraint=false]\n", free, list->array[free].next);
        free = list->array[free].next                                                     ;
    }


    fprintf(dot_file, "}");



    fclose(dot_file)          ;
    char cmd_command[128] = "";
    sprintf (cmd_command, "dot -Tpng %s -o %s", txt_file, png_file);

    system (cmd_command);

    //generate_html(list, png_file, html_file);

    return png_file;
}

int generate_html(dbl_linked_list_t *list)
{
    static int  dumpNum = 0                   ;
    char        html_file[FILE_NAME_SIZE] = {};
    printf("start gener\n");
    sprintf (html_file, "dump.html", dumpNum);

    char png_name              [FILE_NAME_SIZE] = "";
    char png_name_true_location[FILE_NAME_SIZE] = "";

    printf("funcs\n");
    strcpy(png_name              , generate_png              (list, dumpNum));
    strcpy(png_name_true_location, generate_png_real_location(list, dumpNum));
    printf("end funcs\n");

    FILE *output_file = NULL;

    if (dumpNum == 0) output_file = fopen(html_file, "w");
    else              output_file = fopen(html_file, "a");

    printf("func2\n");
    text_dump(list, output_file);
    printf("end func2\n");
    fprintf(output_file, "<img src=\"C:/MIPT/dbl_linked_list/%s\">", png_name              );
    fprintf(output_file, "<img src=\"C:/MIPT/dbl_linked_list/%s\">", png_name_true_location);

    fclose(output_file);

    dumpNum ++;

    return 0;
}

void text_dump (dbl_linked_list_t *list, FILE *dump_file)
{
    fprintf(dump_file ,"<pre><br/> num:  ");
    for(int i = 0; i < list->capacity; i ++)
    {
        fprintf(dump_file ,"%4d  ", i);
    }
    fprintf(dump_file ,"\n");

    fprintf(dump_file ,"<br/> data: ");
    for(int i = 0; i < list->capacity; i ++)
    {
        fprintf(dump_file ,"%4d  ", list->array[i].data);
    }
    fprintf(dump_file ,"\n");

    fprintf(dump_file ,"<br/> next: ");
    for(int i = 0; i < list->capacity; i ++)
    {
        fprintf(dump_file ,"%4d  ", list->array[i].next);
    }
    fprintf(dump_file ,"\n");

    fprintf(dump_file ,"<br/> prev: ");
    for(int i = 0; i < list->capacity; i ++)
    {
        fprintf(dump_file ,"%4d  ", list->array[i].prev);
    }
    fprintf(dump_file ,"\n");

    fprintf(dump_file ,"</pre><br/> <br/>");
}
