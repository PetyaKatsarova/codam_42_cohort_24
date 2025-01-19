#include <unistd.h>
#include <stdio.h>

// int main(int argc, char **argv)
// {
//     int i;
//     char moved;
//     if (argc == 2)
//     {
//         i = 0;
//         while (argv[1][i])
//         {
//             char c = argv[1][i];
//             if (c >= 'a' && c <= 'z')
//             {
//                 if (c+13 > 'z')
//                     moved = 'a' + (c + 13 - 'z' - 1);
//                 else
//                     moved = c+13;
//             }
//             else if ( c >= 'A' && c <= 'Z')
//             {
//                  if (c+13 > 'Z')
//                  {
//                     moved = 'A' + (c + 13 - 'Z' - 1);
//                     printf("moved in A: %c", moved);
//                  }
                    
//                 else
//                     moved=c+13;
//             } else
//                 moved = c;
//             write(1, &moved, 1);
//             i++;
//         }
//     }
//     write(1, "\n", 1);
//     return (0);
// }

// shorter
int main(int argc, char **argv)
{
    int i = 0;
    char c;
    if (argc == 2)
    {
        while (argv[1][i])
        {
            c = argv[1][i];
            if (c >= 'a' && c <= 'z')
                c = (c - 'a' + 13) % 26 + 'a';
            else if (c >= 'A' && c <= 'Z')
                c = (c - 'A' + 13) % 26 + 'A';
            write(1, &c, 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}