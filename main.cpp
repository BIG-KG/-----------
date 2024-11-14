#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include ".\\headers\dbl_linked_list_const.h"
#include ".\\headers\dbl_linked_list_funcs.h"

int main()
{
    printf("start\n");
    dbl_linked_list_t test_list;
    list_inicialiser (&test_list);
    consol_dump (test_list);

    add_after (0, 256, &test_list);

    //printf( "next %d    prev %d\n", test_list.nextArray[1], test_list.prevArray[1] );
    add_after (0, 512, &test_list);
    consol_dump (test_list);

    add_before (0, 128, &test_list);
    consol_dump (test_list);
    consol_dump (test_list);

    printf("first free = %d\ncapasity = %d\n", test_list.firstFreeCell, test_list.capacity);
    consol_dump (test_list);


    generate_html(&test_list);

    add_before (0, 64, &test_list);
    consol_dump (test_list);

    add_before (0, 32, &test_list);
    add_after  (0, 16, &test_list);
    printf("\n\n\n");
    consol_dump (test_list);
    list_delete_element(4, &test_list);
    consol_dump (test_list);
    add_before (0, 8, &test_list);
    consol_dump (test_list);

    generate_html(&test_list);

    //add_before (-1, 64, &test_list);
    //printf("3data = %d=n", list_look(2, &test_list));
    //printf ("value = %lld\n", test_list.dataArray[1] );
    //printf ("333value = %lld\n", list_look(0, &test_list) );
    //printf ("444value = %lld\n", list_look(1, &test_list) );
    printf ("true = %d\n", list_get_true_num(1, &test_list ));

    return 0;
}
