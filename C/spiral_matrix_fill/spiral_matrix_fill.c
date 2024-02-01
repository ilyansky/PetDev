#include <stdio.h>
#include <stdlib.h>

void spiral(int **matr, int m, int n);
void output(int **matr, int m, int n);

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    // Выделение памяти
    int **matr = malloc(m * sizeof(int *));
    int *val = malloc(m * n * sizeof(int));
    for (int i = 0; i < m; i++) matr[i] = val + i * n;

    spiral(matr, m, n);
    output(matr, m, n);

    // Освобождение памяти
    free(val);
    free(matr);

    return 0;
}

void spiral(int **matr, int m, int n) {
    int num = 1;
    char dir = 'r';
    int i_r = 0, j_r = 0, r = 0;
    int i_d = 0, j_d = n, d = 1;
    int i_l = m, j_l = n, l = 1;
    int u = 1, i_u = m, j_u = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (num - 1 == m * n) break;
            if (dir == 'r') {
                if (j_r + r <= n - r - 1) {
                    matr[i_r + r][j_r + r] = num;
                    j_r++;
                    num++;

                } else {
                    dir = 'd';
                    j_r = 0;
                    r++;
                }
            } else if (dir == 'd') {
                if (i_d + d <= m - d) {
                    matr[i_d + d][j_d - d] = num;
                    i_d++;
                    num++;
                } else {
                    dir = 'l';
                    i_d = 0;
                    d++;
                }
            } else if (dir == 'l') {
                if (j_l - l - 1 >= l - 1) {
                    matr[i_l - l][j_l - l - 1] = num;
                    j_l--;
                    num++;

                } else {
                    dir = 'u';
                    j_l = n;
                    l++;
                }
            } else if (dir == 'u') {
                if (i_u - u - 1 >= u) {
                    matr[i_u - u - 1][j_u + u - 1] = num;
                    i_u--;
                    num++;
                } else {
                    dir = 'r';
                    i_u = m;
                    u++;
                }
            }
        }
    }
}

void output(int **matr, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) printf("%-5d", matr[i][j]);
        printf("\n");
    }
}
