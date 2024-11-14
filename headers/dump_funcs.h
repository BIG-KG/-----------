#ifndef   DUMP_FUNCK
#define   DUMP_FUNK

int   generate_html              (dbl_linked_list_t *list, char *picture_name, char *html_name);
char *generate_png_real_location (dbl_linked_list_t *list)                                     ;
void  text_dump                  (dbl_linked_list_t *xlist, FILE *dump_file)                   ;
char *generate_png               (dbl_linked_list_t *list, int dumpNum)                        ;


#endif
