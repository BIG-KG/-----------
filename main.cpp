#include <stdio.h>
#include <stdlib.h>

#include "dbl_linked_list_funcs.h"
#include "dbl_linked_list_const.h"


struct dbl_linked_list_t
{
    bool     initialisated  = false;
    int      numOfElm       = 0;
    int64_t *dataArray      = NULL;
    int     *nextArray      = NULL;
    int     *prevArray      = NULL;
    int      capacity       = 0;
}
/* !!!! ATTENTION: This function does not check the correctness of the list data. !!!!
        This function is only for internal use.
        Before use, check list with: "CHECK_LIST(list, ...)" */
static int find_space(dbl_linked_list_t *list)


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
    int64_t tmprPntr0 = (int64_t)calloc ( DATA_ARRAY_BASE_SIZE + 1, sizeof(int64_t) );
    if (tmprPntr0 == NULL)
    {
        printf("ERROR: no space in RAM to make new list.");
        return NO_RAM_SPACE;
    }
    list->dataArray = tmprPntr0;


                      /*The zeroth element is not filled, so the required size is one larger.*/
    int tmprPntr1 = (int)calloc ( DATA_ARRAY_BASE_SIZE + 1, sizeof(int) );
    if (tmprPntr1 == NULL)
    {
        printf ("ERROR: no space in RAM to make new list.");
        free (list->dataArray);
        list->initialisated = false;
        return NO_RAM_SPACE;
    }
    list->nextArray = tmprPntr1;


                      /*The zeroth element is not filled, so the required size is one larger.*/
        tmprPntr1 = (int)calloc ( DATA_ARRAY_BASE_SIZE + 1, sizeof(int) );
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

    if (  !(  right_list = CHECK_LIST(list, "add_after")  )  )  return right_list;

    if (targetNum_Users + 1> list->numOfElm)
    {
        printf("ERROR: too large num argument in funck add_after");
    }



    for (int i = 0; i < targetNum_Users; i ++)
    {
       targetNum = list->nextArray[targetNum];
    }
    nexttargNum = list->nextArray[targetNum];

    freeSp = find_space(list);
    if (freeSp == 0)
    {
        // increase_space(list);
        ;
    }

    list->nextArray[targetNum]   = freeSp;
    list->prevArray[nexttargNum] = freeSp;

    list->dataArray[freeSp]      = addingValue;

    return 0;
}

int CHECK_LIST(dbl_linked_list_t *list, const char const *funckName)
{
    int rightList = 1;

    if (list == NULL )
    {
        printf("Error: Null pointer to list in function %s", funckName);
        return 1;
    }

    if (list->nextArray == NULL)
    {
        printf("Error: Null pointer to next num Array in function %s", funckName);
        return 1;
    }

    if (list->dataArray == NULL)
    {
        printf("Error: Null pointer to data Array in function %s", funckName);
        return 1;
    }

    if (list->prevArray == NULL)
    {
        printf("Error: Null pointer to prev num Array in function %s", funckName);
        return 1;
    }

    if (list->numOfElm > list->capacity)
    {
        printf("Error: Null list overflooat in function %s", funckName);
        return 1;
    }

    if (list->initialisated == false)
    {
        printf("Error: Null list not initialised in function %s", funckName);
        return 1;
    }

    return 0;
}

/* !!!! ATTENTION: This function does not check the correctness of the list data. !!!!
        This function is only for internal use.
        Before use, check list with: "CHECK_LIST(list, ...)" */
int find_space(dbl_linked_list_t *list)
{
    int free = 1;
    while (  (list->nextArray[free] != 0) && (list->prevArray[free] != 0)
                      && (list->nextArray[0] != free) && (list->prevArray[0] != free)  )
    {
        free = list->nextArray[free];
    }

    return free;
}
