typedef struct s_map
{
    int     rows;
    int     cols;
    char    empty_char;
    char    obstacle_char;
    char    full_char;
    char    **map;
    int     **dp;
}           t_map;