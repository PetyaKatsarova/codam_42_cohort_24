#include <stdio.h> // stdin, fopen, readline
 #include <stdlib.h>
/*
  ┌──────────┬───────────────────────┬────────────────────────────────────────────────────────────────────────────────────────────────────────┐
  │ Function │       Signature       │                                                Returns                                                 │
  ├──────────┼───────────────────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────┤
  │ fopen    │ FILE *fopen(path,     │ Pointer to the open stream, or NULL on failure (bad path, no permission, etc.) — always check for NULL │
  │          │ mode)                 │                                                                                                        │
  ├──────────┼───────────────────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────┤
  │ fclose   │ int fclose(FILE       │ 0 on success, EOF on failure — rarely checked, but exists                                              │
  │          │ *stream)              │                                                                                                        │
  ├──────────┼───────────────────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────┤
  │          │ int fscanf(FILE       │ The count of successfully matched/assigned conversions (e.g. how many of your %d %c %c %c actually got │
  │ fscanf   │ *stream, format, ...) │  filled in). Returns EOF if it hits end-of-input before converting anything. Always check this equals  │
  │          │                       │ what you expected — it's your only signal a malformed header was actually read                         │
  ├──────────┼───────────────────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────┤
  │ fprintf  │ int fprintf(FILE      │ Number of characters written, or negative on error. You basically never check this in practice         │
  │          │ *stream, format, ...) │                                                                                                        │
  ├──────────┼───────────────────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────┤
  │ fputs    │ int fputs(const char  │ Non-negative on success, EOF on error. Writes the string as-is — unlike puts, it does not add a        │
  │          │ *str, FILE *stream)   │ trailing \n for you                                                                                    │
  ├──────────┼───────────────────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────┤
  │ free     │ void free(void *ptr)  │ Nothing — no return value at all                                                                       │
  └──────────┴───────────────────────┴────────────────────────────────────────────────────────────────────────────────────────────────────────┘

 correctness: fscanf's return value. It's not "did it crash" — it's "how many % conversions actually succeeded,"
 malformed header line detection
  stdin/stdout/stderr are pre-opened FILE * values (streams) we pass as the first arg to fscanf/fprintf/etc.

*/

// 9 . 0 x num of lines, empty char, obstacle, full char
  void free_map(char **map, int rows)
  {
      int i;

      i = 0;
      while (i < rows)
      {
          free(map[i]);
          i++;
      }
      free(map);
  }

  int read_map(FILE *fp, int n, char empty_c, char ost_c, char full_c,
               char ***map_out, int *width_out)
  {
      char **map;
      char *line;
      size_t cap;
      ssize_t len;
      int width;
      int i, j;

      map = malloc(n * sizeof(char *));
      if (!map)
          return (-1);
      width = -1;
      i = 0;
      while (i < n)
      {
          line = NULL;
          cap = 0;
          len = getline(&line, &cap, fp);
          if (len == -1 || line[len - 1] != '\n')
          {
              free(line);
              free_map(map, i);
              return (-1);
          }
          len--;
          line[len] = '\0';
          if (width == -1)
              width = (int)len;
          else if ((int)len != width)
          {
              free(line);
              free_map(map, i);
              return (-1);
          }
          j = 0;
          while (j < width)
          {
              if (line[j] != empty_c && line[j] != ost_c && line[j] != full_c)
              {
                  free(line);
                  free_map(map, i);
                  return (-1);
              }
              j++;
          }
          map[i] = line;
          i++;
      }
      *map_out = map;
      *width_out = width;
      return (0);
  }

  /*
    dp[i][j] = size of the largest all-empty square whose bottom-right
    corner is at (i, j). Classic "maximal square" DP:
      obstacle          -> dp[i][j] = 0
      first row/col     -> dp[i][j] = 1
      otherwise         -> 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
    We only update best on strict '>' so scanning top-to-bottom,
    left-to-right naturally gives the topmost-then-leftmost tie-break
    the subject asks for, with no extra bookkeeping.
  */
  void solve_bsq(char **map, int n, int width, char empty_c, char full_c)
  {
      int **dp;
      int i, j, r, c;
      int best, best_i, best_j, top, left;

      dp = malloc(n * sizeof(int *));
      if (!dp)
          return ;
      i = 0;
      while (i < n)
      {
          dp[i] = malloc(width * sizeof(int));
          i++;
      }
      best = 0;
      best_i = 0;
      best_j = 0;
      i = 0;
      while (i < n)
      {
          j = 0;
          while (j < width)
          {
              if (map[i][j] != empty_c)
                  dp[i][j] = 0;
              else if (i == 0 || j == 0)
                  dp[i][j] = 1;
              else
              {
                  dp[i][j] = dp[i - 1][j];
                  if (dp[i][j - 1] < dp[i][j])
                      dp[i][j] = dp[i][j - 1];
                  if (dp[i - 1][j - 1] < dp[i][j])
                      dp[i][j] = dp[i - 1][j - 1];
                  dp[i][j] = dp[i][j] + 1;
              }
              if (dp[i][j] > best)
              {
                  best = dp[i][j];
                  best_i = i;
                  best_j = j;
              }
              j++;
          }
          i++;
      }
      if (best > 0)
      {
          top = best_i - best + 1;
          left = best_j - best + 1;
          r = top;
          while (r <= best_i)
          {
              c = left;
              while (c <= best_j)
              {
                  map[r][c] = full_c;
                  c++;
              }
              r++;
          }
      }
      i = 0;
      while (i < n)
      {
          free(dp[i]);
          i++;
      }
      free(dp);
  }

  void print_map(char **map, int n)
  {
      int i;

      i = 0;
      while (i < n)
      {
          fputs(map[i], stdout);
          fputs("\n", stdout);
          i++;
      }
  }

  int process_map(FILE *fp)
  {
      int n, width;
      char empty_c, ost_c, full_c;
      char **map;
      char *junk;
      size_t jcap;

      if (fscanf(fp, "%d %c %c %c", &n, &empty_c, &ost_c, &full_c) != 4)
          return (-1);
      if (empty_c == ost_c || empty_c == full_c || ost_c == full_c)
          return (-1);
      if (n < 1)
          return (-1);
      junk = NULL;
      jcap = 0;
      getline(&junk, &jcap, fp);   /* consume rest of header line (its own \n) */
      free(junk);
      if (read_map(fp, n, empty_c, ost_c, full_c, &map, &width) == -1)
          return (-1);
      /* fprintf(stderr, "parsed OK: n=%d width=%d\n", n, width); */
      solve_bsq(map, n, width, empty_c, full_c);
      print_map(map, n);
      free_map(map, n);
      return (0);
  }

  /*
 ./a.out "  9 . o x
   ...........................
   ....o......................
   ............o..............
   ...........................
   ....o......................
   ...............o...........
   ...........................
   ......o..............o.....
   ..o.......o................
   EOF
" 
  */
  int main(int argc, char **argv)
  {
      FILE *fp;
      int i;

      if (argc == 1)
      {
          if (process_map(stdin) == -1)
              fprintf(stderr, "map error\n");
      }
      else
      {
          for (i = 1; i < argc; i++)
          {
              fp = fopen(argv[i], "r");
              if (!fp)
                  fprintf(stderr, "map error\n");
              else
              {
                  if (process_map(fp) == -1)
                      fprintf(stderr, "map error\n");
                  fclose(fp);
              }
              if (argc > 2 && i < argc - 1)
                  fprintf(stdout, "\n");
          }
      }
      return (0);
  }
