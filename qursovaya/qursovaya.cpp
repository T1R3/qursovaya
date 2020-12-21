// qursovaya.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <locale.h>

FILE* fp1;
void menu() {
    printf("1. Создать случайный неориентированный взвешенный граф\n");
    printf("2. Создать случайный ориентированный взвешенный граф\n");
    printf("3. Ввести данные неориентированного взвешенного графа вручную\n");
    printf("4. Ввести данные ориентированного взвешенного графа вручную\n");
    printf("5. Выход\n\n");
}

void CreateNeOr(int** G, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            if (i < j) {
                if (rand() % 100 > 50) {
                    G[i][j] = rand() % 15;
                }
                else {
                    G[i][j] = 0;
                }
                G[j][i] = G[i][j];
            }
        }
    }
}

void CreateOr(int** G, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            if (i < j) {
                if (rand() % 100 > 50) {
                    G[i][j] = rand() % 10;
                    if (rand() % 100 > 50)
                       G[j][i] = 0;
                    else
                        G[j][i] = G[i][j];
                }
                else
                    if (rand() % 100 > 50) {
                        G[j][i] = rand() % 10;
                        G[i][j] = 0;
                    }
                    else {
                        G[i][j] = 0;
                        G[j][i] = 0;
                    }
            }
        }
}

void CreateRuchNeor(int** G, int n, int temp) {
    for (int i = 0; i < n; i++)
    {
        G[i][i] = 0;
        for (int j = i + 1; j < n; j++) {
            printf("Введите расстояние %d - %d: ", i + 1, j + 1);
            scanf("%d", &temp);
            G[i][j] = temp;
            G[j][i] = temp;
        }
    }
}

void CreateRuchOr(int** G, int n, int temp) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            else {
                printf("Введите расстояние %d - %d: ", i + 1, j + 1);
                scanf("%d", &temp);
                G[i][j] = temp;
            }
        }
    }
}

void PrintGraph(int** G, int n) {
    printf("   ");
    for (int i = 0; i < n; i++) {
        printf("%4d", i + 1);
        fprintf(fp1, "%5d", i + 1);
    }
    printf("\n\n");
    fprintf(fp1, "\n\n");
    for (int i = 0; i < n; i++) {
        printf("%3d", i + 1);
        fprintf(fp1, "%3d", i + 1);
        for (int j = 0; j < n; j++) {

            printf("%4d", G[i][j]);
            fprintf(fp1, "%5d", G[i][j]);
        }
        printf("\n");
        fprintf(fp1, "\n");
    }
    printf("\n");
}

void init(int** G, int n, int* minrast, int* posew) {
    for (int i = 0; i < n; i++) {
        minrast[i] = 10000;
        posew[i] = -1;       //вершины помечаются непосещенными
    }
}

void dijkstra(int** G, int start_index, int n, int min, int s, int* posew, int* minrast, int temp) {
    minrast[start_index] = 0;
    do {
        min = 10000;
        s = 10000;
        for (int i = 0; i < n; i++) {
            if ((posew[i] == -1) && (minrast[i] < min)) {   // Если вершину ещё не обошли и вес меньше min
                min = minrast[i];
                s = i;
            }
        }

        if (s != 10000) {
            for (int i = 0; i < n; i++) {
                if (G[s][i] > 0) {
                    temp = min + G[s][i];       // Добавляем найденный минимальный вес к текущему весу вершины
                    if (temp < minrast[i]) {    // сравниваем с текущим минимальным весом вершины
                        minrast[i] = temp;
                    }
                }

            }
            posew[s] = 0;                       //вершина помечается посещенной
        }
    } while (s < 10000);
    printf("\nКратчайшие расстояния от вершины %d до остальных вершин\n", start_index+1);
    fprintf(fp1, "\nКратчайшие расстояния от вершины %d до остальных вершин\n", start_index + 1);
    for (int i = 0; i < n; i++) {
        printf("%7d ", minrast[i]);
        fprintf(fp1, "%7d ", minrast[i]);
    }
}

int main() {
    int num, min = NULL, s = NULL;
    int** G;	// указатель на указатель на строку элементов
    int* minrast, *posew, start_index;
    int n, temp = NULL, start = NULL, save;
    setlocale(LC_ALL, "rus");

    
    while (true) {
        system("cls");
        menu();

        printf("Введите номер операции: ");
        scanf("%d", &num);

        if (num == 1) {
            system("cls");
            printf("Введите размер графа: ");
            scanf("%d", &n);

            G = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++) {
                G[i] = (int*)malloc(n * sizeof(int));
            }
            minrast = (int*)malloc(n * sizeof(int));
            posew = (int*)malloc(n * sizeof(int));
            fp1 = fopen("Результаты случайный неор. взвеш. граф.txt", "w");
            CreateNeOr(G, n);
            PrintGraph(G, n);
            printf("Введите номер вершины, с которой хотите начать обход: ");
            scanf("%d", &start_index);
            while (start_index < 1 || start_index > n) {
                printf("Требуемая вершина отсутствует. Введите данные корректно:");
                scanf("%d", &start_index);
            }
            start_index--;
            init(G, n, minrast, posew);
            dijkstra(G, start_index, n, min, s, posew, minrast, temp);
            fclose(fp1);
            printf("\nДля продолжения нажмите любую кнопку...");
            for (int i = 0; i < n; i++) {
                free(G[i]);
            }
            free(G);
            free(minrast);
            free(posew);
            getchar();
            getchar();
        }

        if (num == 2) {
            system("cls");
            printf("Введите размер графа: ");
            scanf("%d", &n);

            G = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++) {
                G[i] = (int*)malloc(n * sizeof(int));
            }
            minrast = (int*)malloc(n * sizeof(int));
            posew = (int*)malloc(n * sizeof(int));
            fp1 = fopen("Результаты случайный ор. взвеш. граф.txt", "w");
            CreateOr(G, n);
            PrintGraph(G, n);
            printf("Введите номер вершины, с которой хотите начать обход: ");
            scanf("%d", &start_index);
            while (start_index < 1 || start_index > n) {
                printf("Требуемая вершина отсутствует. Введите данные корректно:");
                scanf("%d", &start_index);
            }
            start_index--;
            init(G, n, minrast, posew);
            dijkstra(G, start_index, n, min, s, posew, minrast, temp);
            fclose(fp1);
            printf("\nДля продолжения нажмите любую кнопку...");
            for (int i = 0; i < n; i++) {
                free(G[i]);
            }
            free(G);
            free(minrast);
            free(posew);
            getchar();
            getchar();
        }

        if (num == 3) {
            system("cls");
            printf("Введите размер графа: ");
            scanf("%d", &n);

            G = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++) {
                G[i] = (int*)malloc(n * sizeof(int));
            }
            minrast = (int*)malloc(n * sizeof(int));
            posew = (int*)malloc(n * sizeof(int));

            fp1 = fopen("Результаты ручной неор. взвеш. граф.txt", "w");
            CreateRuchNeor(G, n, temp);
            PrintGraph(G, n);
            printf("Введите номер вершины, с которой хотите начать обход: ");
            scanf("%d", &start_index);
            while (start_index < 1 || start_index > n) {
                printf("Требуемая вершина отсутствует. Введите данные корректно:");
                scanf("%d", &start_index);
            }
            start_index--;
            init(G, n, minrast, posew);
            dijkstra(G, start_index, n, min, s, posew, minrast, temp);
            fclose(fp1);
            printf("\nДля продолжения нажмите любую кнопку...");
            for (int i = 0; i < n; i++) {
                free(G[i]);
            }
            free(G);
            free(minrast);
            free(posew);
            getchar();
            getchar();
        }

        if (num == 4) {
            system("cls");
            printf("Введите размер графа: ");
            scanf("%d", &n);

            G = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++) {
                G[i] = (int*)malloc(n * sizeof(int));
            }
            minrast = (int*)malloc(n * sizeof(int));
            posew = (int*)malloc(n * sizeof(int));

            fp1 = fopen("Результаты ручной ор. взвеш. граф.txt", "w");
            CreateRuchOr(G, n, temp);
            PrintGraph(G, n);
            printf("Введите номер вершины, с которой хотите начать обход: ");
            scanf("%d", &start_index);
            while (start_index < 1 || start_index > n) {
                printf("Требуемая вершина отсутствует. Введите данные корректно:");
                scanf("%d", &start_index);
            }
            start_index--;
            init(G, n, minrast, posew);
            dijkstra(G, start_index, n, min, s, posew, minrast, temp);
            fclose(fp1);
            printf("\nДля продолжения нажмите любую кнопку...");
            for (int i = 0; i < n; i++) {
                free(G[i]);
            }
            free(G);
            free(minrast);
            free(posew);
            getchar();
            getchar();
        }

        if (num == 5) {
            break;
        }
    }
}