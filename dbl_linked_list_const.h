const int DATA_ARRAY_BASE_SIZE = 4;
const int LIST_FULL            = -1; // Assigned to the last free element of the list, like "next"
const int ARRAY_INCREASE_STEP  = 2;

enum errors{
    NULL_PNTR = -1,
    NO_RAM_SPACE = -2,
    DOUBLE_INICIALISE_LIST = -3
};

struct node_t
{
    int64_t data = 0;
    int     next = 0;
    int     prev = 0;

};

struct dbl_linked_list_t
{
    bool     initialisated  = false;
    int      numOfElm       = 0;
    node_t  *array          = NULL;
    int      capacity       = 0;
    int      firstFreeCell  = LIST_FULL; //
};
