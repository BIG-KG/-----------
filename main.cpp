#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "dbl_linked_list_const.h"
#include "dbl_linked_list_funcs.h"



/* !!!! ATTENTION: This functions does not check the correctness of the list data. !!!!
        This functions is only for internal use.
        Before use, check list with: "CHECK_LIST(list, ...)" */
static int find_space(dbl_linked_list_t *list);
static int set_next_free_markers (int startNum, int endNum, dbl_linked_list_t *list);

int main()
{
    printf("start\n");
    dbl_linked_list_t test_list;
    list_inicialisator (&test_list);
    dump (test_list);

    add_after (-1, 256, &test_list);

    printf( "next %d    prev %d\n", test_list.nextArray[1], test_list.prevArray[1] );
    add_after (0, 512, &test_list);
    dump (test_list);

    add_before (-1, 128, &test_list);
    dump (test_list);

    add_before (2, 64, &test_list);
    dump (test_list);

    add_before (-1, 32, &test_list);
    add_after  (-1, 16, &test_list);
    printf("\n\n\n");
    dump (test_list);
    list_delete_element(4, &test_list);
    dump (test_list);
    add_before (-1, 8, &test_list);
    dump (test_list);

    //add_before (-1, 64, &test_list);
    printf("3data = %d=n", list_look(2, &test_list));
    // printf ("value = %lld\n", test_list.dataArray[1] );
    // printf ("333value = %lld\n", list_look(0, &test_list) );
    // printf ("444value = %lld\n", list_look(1, &test_list) );
    printf ("end\n");

    return 0;
}

int list_inicialisator (dbl_linked_list_t *list)
{
    if (!list)
    {
        printf ("ERROR: NULL pointer in inicialisator function.");
        return NULL_PNTR;
    }

    if ( list->initialisated == true)
    {
        printf ("ERROR: list is already initialized.");
        return DOUBLE_INICIALISE_LIST;
    }
    list->initialisated = true;


                      /*The zeroth element is not filled, so the required size is one larger.*/
    int64_t* tmprPntr0 = (int64_t *)calloc ( DATA_ARRAY_BASE_SIZE + 1, sizeof(int64_t) );
    if (tmprPntr0     == NULL)
    {
        printf("ERROR: no space in RAM to make new list.");
        return NO_RAM_SPACE;
    }
    list->dataArray = tmprPntr0;


                      /*The zeroth element is not filled, so the required size is one larger.*/
    int *tmprPntr1 = (int *)calloc ( DATA_ARRAY_BASE_SIZE + 1, sizeof(int) );
    if (tmprPntr1 == NULL)
    {
        printf ("ERROR: no space in RAM to make new list.");
        free (list->dataArray);
        list->initialisated = false;
        return NO_RAM_SPACE;
    }
    list->nextArray = tmprPntr1;


                      /*The zeroth element is not filled, so the required size is one larger.*/
         tmprPntr1 = (int *)calloc ( DATA_ARRAY_BASE_SIZE + 1, sizeof(int) );
    if (tmprPntr1 == NULL)
    {
        printf ("ERROR: no space in RAM to make new list.");
        free (list->dataArray);
        free (list->nextArray);
        list->initialisated = false;
        return NO_RAM_SPACE;
    }
    list->prevArray = tmprPntr1;

    list->capacity  = DATA_ARRAY_BASE_SIZE;
    set_next_free_markers (1, DATA_ARRAY_BASE_SIZE, list);
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

    if (list->dataArray)
    {
        free(list->dataArray);
    }

    if (list->nextArray)
    {
        free(list->nextArray);
    }

    if (list->prevArray)
    {
        free(list->prevArray);
    }

    list->capacity = 0;
    list->numOfElm = 0;

    return 0;
}

int add_after (int targetNum_Users, int64_t addingValue, dbl_linked_list_t *list)
{
    int right_list  = 0;
    int nexttargNum = 0;
    int targetNum   = 0;
    int freeSp      = 0;

    if (  (  right_list = CHECK_LIST(list, "add_after")  )  )
    {
        return right_list;
    }

    if (targetNum_Users + 1> list->numOfElm)
    {
        printf("ERROR: too large num argument in funck add_after\n");
        return -121231;  //Обязательно заменить на enum
    }



    for (int i = 0; i < targetNum_Users + 1; i ++)
    {
       targetNum = list->nextArray[targetNum];
    }
    nexttargNum = list->nextArray[targetNum];

    freeSp = find_space(list);
    if (freeSp < 0)
    {
        printf("ERROR: no ram space\n");
        return NO_RAM_SPACE;
    }

    list->nextArray[targetNum]   = freeSp;
    list->prevArray[freeSp]      = targetNum;
    list->prevArray[nexttargNum] = freeSp;
    list->nextArray[freeSp]      = nexttargNum;

    list->numOfElm ++;
    list->dataArray[freeSp]      = addingValue;

    return 0;
}

int add_before (int targetNum_Users, int64_t addingValue, dbl_linked_list_t *list)
{
    int right_list  = 0;
    int prevTargNum = 0;
    int targetNum   = 0;
    int freeSp      = 0;

    if (  (  right_list = CHECK_LIST(list, "add_before")  )  )
    {
        printf("stop");
        return right_list;
    }

    if (targetNum_Users + 1  > list->numOfElm)
    {
        printf("ERROR: too large num argument in funck add_before\n");
        return 121231;  //Обязательно заменить на enum
    }



    for (int i = 0; i < targetNum_Users + 1; i ++)
    {
       targetNum = list->nextArray[targetNum];
    }
    prevTargNum = list->prevArray[targetNum];

    freeSp = find_space(list);
    if (freeSp < 0)
    {
        printf("ERROR: no ram space\n");
        return NO_RAM_SPACE;
    }


    list->nextArray[prevTargNum] = freeSp;
    list->prevArray[freeSp]      = prevTargNum;
    list->prevArray[targetNum]   = freeSp;
    list->nextArray[freeSp]      = targetNum;

    list->numOfElm ++;
    list->dataArray[freeSp]      = addingValue;

    return 0;
}

int CHECK_LIST (dbl_linked_list_t *list, const char *const funckName)
{
    if (list == NULL )
    {
        printf("Error: Null pointer to list in function %s\n", funckName);
        return 1;
    }

    if (list->nextArray == NULL)
    {
        printf("Error: Null pointer to next num Array in function %s\n", funckName);
        return 1;
    }

    if (list->dataArray == NULL)
    {
        printf("Error: Null pointer to data Array in function %s\n", funckName);
        return 1;
    }

    if (list->prevArray == NULL)
    {
        printf("Error: Null pointer to prev num Array in function %s\n", funckName);
        return 1;
    }

    if (list->numOfElm > list->capacity)
    {
        printf("Error: Null list overflooat in function %s\n", funckName);
        return 1;
    }

    if (list->initialisated == false)
    {
        printf("Error: Null list not initialised in function %s\n", funckName);
        return 1;
    }

    return 0;
}

/* !!!! ATTENTION: This function does not check the correctness of the list data. !!!!
        This function is only for internal use.
        Before use, check list with: "CHECK_LIST(list, ...)" */
int find_space(dbl_linked_list_t *list)
{
    if (list->firstFreeCell == LIST_FULL)
    {
        int newCapacity = list->capacity * ARRAY_INCREASE_STEP;

                        /*The zeroth element is not filled, so the required size is one larger.*/
        int64_t *tmprPntr0 = (int64_t *)realloc (list->dataArray,
                                                    (newCapacity + 1) * sizeof(int64_t) );
        int     *tmprPntr1 = (int     *)realloc (list->nextArray,
                                                    (newCapacity + 1) * sizeof(int    ) );
        int     *tmprPntr2 = (int     *)realloc (list->prevArray,
                                                    (newCapacity + 1) * sizeof(int    ) );

        if (tmprPntr0 == NULL || tmprPntr1 == NULL || tmprPntr2 == NULL)
        {
            if (tmprPntr0 != NULL) free(tmprPntr0);
            if (tmprPntr1 != NULL) free(tmprPntr1);
            if (tmprPntr2 != NULL) free(tmprPntr2);

            return NO_RAM_SPACE;
        }

        list->dataArray = tmprPntr0;
        list->nextArray = tmprPntr1;
        list->prevArray = tmprPntr2;

        set_next_free_markers(list->capacity, newCapacity, list);
        list->firstFreeCell = list->capacity;
        list->capacity = newCapacity;
    }

    int free = list->firstFreeCell;
    list->firstFreeCell = list->nextArray[free];
    return free;
}

int64_t list_look (int targetNum_Users, dbl_linked_list_t *list)
{
    int right_list = 0;
    int targetNum  = 0;

    if (  (  right_list = CHECK_LIST(list, "list_look")  )  )  return right_list;

    if (targetNum_Users + 1> list->numOfElm)
    {
        printf("ERROR: too large num argument in funck look\n");
    }

    for (int i = 0; i < targetNum_Users + 1; i ++)
    {
        targetNum = list->nextArray[targetNum];
    }

    return list->dataArray[targetNum];
}

void dump (dbl_linked_list_t list)
{
    printf("\nnum:  ");
    for(int i = 0; i < list.capacity; i ++)
    {
        printf("%4d  ", i);
    }

    printf("\ndata: ");
    for(int i = 0; i < list.capacity; i ++)
    {
        printf("%4d  ", list.dataArray[i]);
    }

    printf("\nnext: ");
    for(int i = 0; i < list.capacity; i ++)
    {
        printf("%4d  ", list.nextArray[i]);
    }

    printf("\nprev: ");
    for(int i = 0; i < list.capacity; i ++)
    {
        printf("%4d  ", list.prevArray[i]);
    }

    printf("\n\n");
}

int64_t list_delete_element (int targetNum_Users, dbl_linked_list_t *list)
{
    int right_list = 0;
    int targetNum  = 0;

    if (  (  right_list = CHECK_LIST(list, "list_look")  )  )  return right_list;

    if (targetNum_Users + 1> list->numOfElm)
    {
        printf("ERROR: too large num argument in funck add_after\n");
        return -121231;  //Обязательно заменить на enum
    }

    for (int i = 0; i < targetNum_Users + 1; i ++)
    {
       targetNum = list->nextArray[targetNum];
    }

    list->dataArray[targetNum] = 0;
    list->numOfElm --;

    list->nextArray[ list->prevArray[targetNum] ] = list->nextArray[targetNum];
    list->prevArray[ list->nextArray[targetNum] ] = list->prevArray[targetNum];

    list->prevArray[targetNum] = 0;
    list->nextArray[targetNum] = 0;

    list->nextArray[targetNum] = list->firstFreeCell;
    list->firstFreeCell = targetNum;

    return list->dataArray[targetNum];
}

/* !!!! ATTENTION: This function does not check the correctness of the list data. !!!!
        This function is only for internal use.
        Before use, check list with: "CHECK_LIST(list, ...)" */
int set_next_free_markers (int startNum, int endNum, dbl_linked_list_t *list)
{
    for(int i = startNum; i < endNum - 1; i ++)
    {
        list->nextArray[i] = (i + 1);
    }

    list->nextArray[endNum - 1] = LIST_FULL;

    return 1;
}

int64_t* list_get_ptr (int targetNum_Users, dbl_linked_list_t *list)
{
    int right_list = 0;
    int targetNum  = 0;

    if (  (  right_list = CHECK_LIST(list, "list_look")  )  )  return right_list;

    if (targetNum_Users + 1> list->numOfElm)
    {
        printf("ERROR: too large num argument in funck look\n");
    }

    for (int i = 0; i < targetNum_Users + 1; i ++)
    {
        targetNum = list->nextArray[targetNum];
    }

    return &list->dataArray[targetNum];
}
