#ifndef DBL_LNKD_FUNKS
#define DBL_LNKD_FUNKS

int     CHECK_LIST         (dbl_linked_list_t *list, const char *const funckName);
int     add_after          (int targetNum_Users, int64_t addingValue, dbl_linked_list_t *list);
int     add_before         (int targetNum_Users, int64_t addingValue, dbl_linked_list_t *list);
int     list_destructor    (dbl_linked_list_t *list);
int     list_inicialisator (dbl_linked_list_t *list);
int64_t list_look          (int targetNum_Users, dbl_linked_list_t *list);
void    dump               (dbl_linked_list_t list);


#endif
