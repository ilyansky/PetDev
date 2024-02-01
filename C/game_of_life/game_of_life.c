#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define STR 25
#define COL 80

// 1 - Функция ввода матрцицы
void input_matrix(int matr[STR][COL]);

// 2 - Функция итерации по матрице и отбора исследуемой точки
void update_matrix(int matr1[STR][COL], int matr2[STR][COL]);

// 3 - Функция подсчета соседей
int count_neighbors(int matr1[STR][COL], int i, int j);

// 4 - Функция принятия решения о следующем поколении
int decision(int neighbors, int condition);

// 5 - Функция для переприсваивания матриц
void replace(int matr2[STR][COL], int matr1[STR][COL]);

// 6 - Функция проверяющая статичность поля
int check(int matr1[STR][COL], int matr2[STR][COL]);

// 7 - Функция смены скорости
int change_speed(char control_button, int *flag, int time_mili_sec);

// 8 - Функция на случай пустого поля
int count(int matr[STR][COL]);

// MAIN 
// ---------------------------------------
int main() {
    int matr1[STR][COL];
    int matr2[STR][COL];
    int time_mili_sec = 500;
    int stop = 0;

    input_matrix(matr1);
    if (freopen("/dev/tty", "r", stdin)) initscr();  // Инициализация ncurses
    nodelay(stdscr, true);

    // Основной цикл игры
    while (stop != 1) {
        char control_button = getch();

        if (count(matr1) == 0) {
            stop = 1;
        }

        time_mili_sec = change_speed(control_button, &stop, time_mili_sec);

        usleep(time_mili_sec * 1000);
        clear();
        update_matrix(matr1, matr2);

        if (check(matr1, matr2) == 2000) {
            stop = 1;
        }
        replace(matr2, matr1);
    }

    endwin();  // Выход из ncurses
    return 0;
}
// ---------------------------------------

void input_matrix(int matr[STR][COL]) {
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            scanf("%d", &matr[i][j]);
        }
    }
}

void update_matrix(int matr1[STR][COL], int matr2[STR][COL]) {
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            matr2[i][j] = decision(count_neighbors(matr1, i, j), matr1[i][j]);
            if (matr2[i][j] == 1)
                printw("0");
            else
                printw("-");
        }
        printw("\n");
    }
}

int count_neighbors(int matr1[STR][COL], int i, int j) {
    // Количество соседей
    int sum = 0;
    
    // i и j для координат соседей
    int i_minus = i - 1, j_minus = j - 1, i_plus = i + 1, j_plus = j + 1;
    
    // i и j для координат соседей краевых ячеек
    if (i_minus < 0) i_minus = STR - 1;
    if (j_minus < 0) j_minus = COL - 1;
    if (i_plus > STR - 1) i_plus = i_plus % STR;
    if (j_plus > COL - 1) j_plus = j_plus % COL;

    sum += matr1[i_minus][j_minus];  // Обход соседей по часовой стрелке с левого верхнего угла
    sum += matr1[i_minus][j];
    sum += matr1[i_minus][j_plus];
    sum += matr1[i][j_plus];
    sum += matr1[i_plus][j_plus];
    sum += matr1[i_plus][j];
    sum += matr1[i_plus][j_minus];
    sum += matr1[i][j_minus];

    return sum;
}

int decision(int neighbors, int condition) {
    int next_gen = -1;
    if ((neighbors == 2 || neighbors == 3) && condition == 1) {
        next_gen = 1;
    } else if (neighbors == 3 && condition == 0) {
        next_gen = 1;
    } else {
        next_gen = 0;
    }
    return next_gen;
}

void replace(int matr2[STR][COL], int matr1[STR][COL]) {
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            matr1[i][j] = matr2[i][j];
        }
    }
}

int check(int matr1[STR][COL], int matr2[STR][COL]) {
    int ans = 0;
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            if (matr1[i][j] == matr2[i][j]) ans++;
        }
    }
    return ans;
}

int change_speed(char control_button, int *flag, int time_mili_sec) {
    if (control_button == '1')
        time_mili_sec = 900;
    else if (control_button == '2')
        time_mili_sec = 400;
    else if (control_button == '3')
        time_mili_sec = 70;
    else if (control_button == 'q')
        *flag = 1;

    return time_mili_sec;
}

int count(int matr[STR][COL]) {
    int sum = 0;
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            sum += matr[i][j];
        }
    }
    return sum;
}

