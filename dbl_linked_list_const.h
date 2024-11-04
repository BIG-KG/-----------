const int DATA_ARRAY_BASE_SIZE = 16;
const int LIST_FULL            = -1; // Assigned to the last free element of the list, like "next"

enum errors{
    NULL_PNTR,
    NO_RAM_SPACE,
    DOUBLE_INICIALISE_LIST
};


struct dbl_linked_list_t
{
    bool     initialisated  = false;
    int      numOfElm       = 0;
    int64_t *dataArray      = NULL;
    int     *nextArray      = NULL;
    int     *prevArray      = NULL;
    int      capacity       = 0;
    int      firstFreeCell  = LIST_FULL; //
};
