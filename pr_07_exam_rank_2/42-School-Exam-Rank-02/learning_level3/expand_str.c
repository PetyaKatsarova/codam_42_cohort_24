#include <unistd.h>



int main(int argc, char **argv)
{
    int i = 0;
    int flag = 0;
    if (argc == 2)
    {
        if (argv[1] == "")
        {
            write(1, "\n", 1);
            return (0);
        }
        while (argv[1][i] == ' ' || argv[1][i] == '\t')
            i++;
        while (argv[1][i])
        {
            if (argv[1][i] == ' ' || argv[1][i] == '\t')
                flag = 1;
            if (!(argv[1][i] == ' ' || argv[1][i] == '\t'))
            {
                if (flag == 1)
                    write(1, "   ", 3);
                flag = 0;
                write(1, &argv[1][i], 1);
            }
            i++;
        }
        
    }
    write(1, "\n", 1);
    return (0);
}