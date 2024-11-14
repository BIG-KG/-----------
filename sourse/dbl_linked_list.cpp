#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "..\\headers\dbl_linked_list_const.h"
#include "..\\headers\dbl_linked_list_funcs.h"




/* !!!! ATTENTION: This functions does not check the correctness of the list data. !!!!
        This functions is only for internal use.
        Before use, check list with: "CHECK_LIST(list, ...)" */
static int find_space(dbl_linked_list_t *list);
static int set_next_free_markers (int startNum, int endNum, dbl_linked_list_t *list);

// initializer
int list_inicialiser (dbl_linked_list_t *list)
{
    if (!list)
    {
        printf ("ERROR: NULL pointer in inicialisator function.\n");
        return NULL_PNTR;
    }

    if ( list->initialisated == true)
    {
        printf ("ERROR: list is already initialized.\n");
        return DOUBLE_INICIALISE_LIST;
    }
    list->initialisated = true;


                      /*The zeroth element is not filled, so the required size is one larger.*/
    node_t* tmprPntr0 = (node_t *)calloc ( DATA_ARRAY_BASE_SIZE + 1, sizeof(node_t) );
    if (tmprPntr0     == NULL)
    {
        printf("ERROR: no space in RAM to make new list.\n");
        return NO_RAM_SPACE;
    }
    list->array = tmprPntr0;


    list->capacity  = DATA_ARRAY_BASE_SIZE;
    set_next_free_markers (1, DATA_ARRAY_BASE_SIZE + 1, list);
    list->firstFreeCell = 1;

    return 0;
}

int list_destructor (dbl_linked_list_t *list)
{
    if (!list)
    {
        printf ("ERROR: NULL pointer in inicialisator function.");
        return NULL_PNTR;
    }

    list->initialisated = false;

    if (list->array)
    {
        free(list->array);
    }

    list->capacity = 0;
    list->numOfElm = 0;

    return 0;
}

int add_after (int targetNum, int64_t addingValue, dbl_linked_list_t *list)
{
    int nexttargNum = 0;
    int freeSp      = 0;

    CHECK_LIST(list, "add_after");

    if (targetNum >= list->capacity)
    {
        printf("ERROR: too large num argument in funck add_after\n");
        return -121231;  //Обязательно заменить на enum
    }


    freeSp = find_space(list);
    if (freeSp < 0)
    {
        printf("ERROR: No ram space\n");
        return NO_RAM_SPACE;
    }

    nexttargNum  = list->array[targetNum].next;

    list->array[targetNum  ].next  = freeSp     ;
    list->array[freeSp     ].prev  = targetNum  ;
    list->array[nexttargNum].prev  = freeSp     ;
    list->array[freeSp     ].next  = nexttargNum;

    list->numOfElm ++;
    list->array[freeSp     ].data  = addingValue;

    return 0;
}

int add_before (int targetNum, int64_t addingValue, dbl_linked_list_t *list)
{
    int prevTargNum = 0;
    int freeSp      = 0;

    CHECK_LIST(list, "add_before");

    if (targetNum + 1  > list->numOfElm)
    {
        printf("ERROR: too large num argument in funck add_before\n");
        return 121231;  //Обязательно заменить на enum
    }


    prevTargNum  = list->array[targetNum].prev;

    freeSp = find_space(list);
    if (freeSp < 0)
    {
        printf("ERROR: no ram space\n");
        return NO_RAM_SPACE;
    }


    list->array[prevTargNum].next = freeSp     ;
    list->array[freeSp     ].prev = prevTargNum;
    list->array[targetNum  ].prev = freeSp     ;
    list->array[freeSp     ].next = targetNum  ;

    list->numOfElm ++                          ;
    list->array[freeSp     ].data = addingValue;

    return 0;
}

// int CHECK_LIST (dbl_linked_list_t *list, const char *const funckName)
// {
//     if (list == NULL )
//     {
//         printf("Error: Null pointer to list in function %s\n", funckName);
//         return 1;
//     }
//
//     if (list->array == NULL)
//     {
//         printf("Error: Null pointer to next num Array in function %s\n", funckName);
//         return 1;
//     }
//
//     if (list->numOfElm > list->capacity)
//     {
//         printf("Error: List overflooat in function %s\n", funckName);
//         return 1;
//     }
//
//     if (list->initialisated == false)
//     {
//         printf("Error: List not initialised in function %s\n", funckName);
//         return 1;
//     }
//
//     return 0;
// }

/* !!!! ATTENTION: This function does not check the correctness of the list data. !!!!
        This function is only for internal use.
        Before use, check list with: "CHECK_LIST(list, ...)" */
static int find_space(dbl_linked_list_t *list)
{
    if (list->firstFreeCell == LIST_FULL)
    {
        int newCapacity = list->capacity * ARRAY_INCREASE_STEP;

                        /*The zeroth element is not filled, so the required size is one larger.*/
        node_t *tmprPntr0 = (node_t *)realloc (list->array,
                                                    (newCapacity + 1) * sizeof(node_t) );

        if ( tmprPntr0 == NULL )
        {
            return NO_RAM_SPACE;
        }
        list->array = tmprPntr0;

        set_next_free_markers(list->capacity, newCapacity + 1, list);
        list->firstFreeCell = list->capacity;
        list->capacity = newCapacity;
    }

    int free = list->firstFreeCell;
    list->firstFreeCell = list->array[free].next;
    return free;
}

int64_t list_look (int targetNum_Users, dbl_linked_list_t *list)
{
    int targetNum  = 0;

    CHECK_LIST(list, "list_look");

    if (targetNum_Users + 1> list->numOfElm)
    {
        printf("ERROR: too large num argument in funck look\n");
    }

    for (int i = 0; i < targetNum_Users + 1; i ++)
    {
        targetNum = list->array[targetNum].next;
    }

    return list->array[targetNum].data;
}

void consol_dump (dbl_linked_list_t list)
{
    printf("\nnum:  ");
    for(int i = 0; i <= list.capacity; i ++)
    {
        printf("%4d  ", i);
    }

    printf("\ndata: ");
    for(int i = 0; i <= list.capacity; i ++)
    {
        printf("%4d  ", list.array[i].data);
    }

    printf("\nnext: ");
    for(int i = 0; i <= list.capacity; i ++)
    {
        printf("%4d  ", list.array[i].next);
    }

    printf("\nprev: ");
    for(int i = 0; i <= list.capacity; i ++)
    {
        printf("%4d  ", list.array[i].prev);
    }

    printf("\n\n");
}

int64_t list_delete_element (int targetNum_Users, dbl_linked_list_t *list)
{
    int targetNum = 0;

    CHECK_LIST(list, "list_look");

    if (targetNum_Users + 1> list->numOfElm)
    {
        printf("ERROR: too large num argument in funck add_after\n");
        return -121231;  //Обязательно заменить на enum
    }

    for (int i = 0; i < targetNum_Users + 1; i ++)
    {
       targetNum = list->array[targetNum].next;
    }

    list->array[targetNum].data = 0;
    list->numOfElm --              ;

    list->array[ list->array[targetNum].prev ].next = list->array[targetNum].next;
    list->array[ list->array[targetNum].next ].prev = list->array[targetNum].prev;

    list->array[targetNum].prev = 0;
    list->array[targetNum].next = 0;

    list->array[targetNum].next = list->firstFreeCell;
    list->firstFreeCell = targetNum                  ;

    return 0;
}

/* !!!! ATTENTION: This function does not check the correctness of the list data. !!!!
        This function is only for internal use.
        Before use, check list with: "CHECK_LIST(list, ...)" */
static int set_next_free_markers (int startNum, int endNum, dbl_linked_list_t *list)
{
    for(int i = startNum; i < endNum - 1; i ++)
    {
        list->array[i].next = (i + 1);
        list->array[i].data = 0;
        list->array[i].prev = 0;
    }

    list->array[endNum - 1].data = 0;
    list->array[endNum - 1].prev = 0;
    list->array[endNum - 1].next = LIST_FULL;

    return 1;
}

int list_get_true_num (int targetNum_Users, dbl_linked_list_t *list)
{
    int targetNum = 0;
    CHECK_LIST(list, "list_look");

    if (targetNum_Users + 1> list->numOfElm)
    {
        printf("ERROR: too large num argument in funck look\n");
    }

    for (int i = 0; i < targetNum_Users + 1; i ++)
    {
        targetNum = list->array[targetNum].next;
    }

    return targetNum;
}
