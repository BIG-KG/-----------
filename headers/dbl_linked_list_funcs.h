#ifndef DBL_LNKD_FUNKS
#define DBL_LNKD_FUNKS

//int     CHECK_LIST          (dbl_linked_list_t *list, const char *const funckName);
int     add_after           (int targetNum_Users, int64_t addingValue, dbl_linked_list_t *list);
int     add_before          (int targetNum_Users, int64_t addingValue, dbl_linked_list_t *list);
int64_t list_delete_element (int targetNum_Users, dbl_linked_list_t *list)                     ;
int     list_destructor     (dbl_linked_list_t *list)                                          ;
int     list_inicialiser    (dbl_linked_list_t *list)                                          ;
int64_t list_look           (int targetNum_Users, dbl_linked_list_t *list)                     ;
void    consol_dump         (dbl_linked_list_t list)                                           ;
int     list_get_true_num   (int targetNum_Users, dbl_linked_list_t *list)                     ;
int     generate_html       (dbl_linked_list_t *list)                                          ;

#define CHECK_LIST (list) ;                                                                 \
    if (list == NULL )                                                                      \
    {                                                                                       \
        printf("Error: Null pointer to list in function\n");                                \
        return 1;                                                                           \
    }                                                                                       \
                                                                                            \
    if (list->array == NULL)                                                                \
    {                                                                                       \
        printf("Error: Null pointer to next num Array in function\n");                      \
        return 1;                                                                           \
    }                                                                                       \
                                                                                            \
    if (list->numOfElm > list->capacity)                                                    \
    {                                                                                       \
        printf("Error: List overflooat in function\n");                                     \
        return 1;                                                                           \
    }                                                                                       \
                                                                                            \
    if (list->initialisated == false)                                                       \
    {                                                                                       \
        printf("Error: List not initialised in function\n");                                \
        return 1;                                                                           \
    }                                                                                       \



#endif
