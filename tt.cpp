#include <stdio.h>
#include <stdlib.h>

struct List_t {    //  0   1   2   3   4   5   6   7   8   9  10  11  12
    int data[13] = { 111, 10, 20, 30, 40, 50, 60, 70, 80,  0,  0,  0,  0 }; // data || values
    int next[13] = { 0,    2,  3,  4,  5,  6,  7,  8,  0, 10, 11, 12,  0 };
    int prev[13] = { 0,    0,  1,  2,  3,  4,  5,  6,  7,  8, -1, -1, -1 };
    int free = 9;
    int data_size = 13;
};

int main ()
{
    List_t list = {};
    FILE *dot = fopen ( "list.dot", "w" );

    fprintf ( dot, "digraph G { \n"
                   "rankdir = LR;\n"
                   "node [shape = record];\n"
                   " 0 " );
    for ( int i = 0; i < list.data_size; ++i ) {
        fprintf ( dot, "-> %d", i );
    }
    fprintf ( dot, "[arrowsize = 0.0, weight = 10000, color = \"#FFFFFF\"];\n" );
                  // " list [shape = Mrecord, style = filled, fillcolor = lightpink, "
                   //" label = \" data: %d | free: %d \"];)\n", list.data, list.free );
    for ( int i = 0; i < list.data_size; ++i ) {
        fprintf ( dot, "%d [shape = Mrecord, style = filled, fillcolor = lightpink "
                       " label = \"idx: %d | data: %d | next: %d | prev: %d\"];\n ",i, i, list.data[i],
                                                                                          list.next[i],
                                                                                          list.prev[i] );
    }

    for ( int i = 0; i < list.data_size; ++i ) {
        fprintf ( dot, "%d -> %d;\n", i, list.next[i] );
    }


    fprintf ( dot, "}\n" );
    fclose ( dot );

    char dot_cmd[100] = "";
    sprintf(dot_cmd, "dot -T png list.dot -o list%d.png", counter++);
    system ( dot_cmd );
    //system ( "list.png" );

    return 0;
}
