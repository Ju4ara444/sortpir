
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

// Функция для создания имени файла с текущей датой и временем
void random_file(char* filename, char* type) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    sprintf(filename, "%s_%04d%02d%02d_%02d%02d%02d.txt",
        type,
        t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec);
}

// Функция для записи массива в файл
void write_file(int arr[], int size, char* type) {
    char filename[100];
    random_file(filename, type);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Не удалось создать файл!\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fprintf(file, "\n");

    fclose(file);
    printf("Массив записан в файл: %s\n", filename);
}

// Функция для сортировки кучи
void fix_heap(int arr[], int size, int i, int up) {
    int big = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (up) {
        if (left < size && arr[left] > arr[big])
            big = left;
        if (right < size && arr[right] > arr[big])
            big = right;
    }
    else {
        if (left < size && arr[left] < arr[big])
            big = left;
        if (right < size && arr[right] < arr[big])
            big = right;
    }

    if (big != i) {
        int temp = arr[i];
        arr[i] = arr[big];
        arr[big] = temp;
        fix_heap(arr, size, big, up);
    }
}

// Основная функция сортировки
void main_sort_heap(int arr[], int size, int up) {
    for (int i = size / 2 - 1; i >= 0; i--)
        fix_heap(arr, size, i, up);

    for (int i = size - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        fix_heap(arr, i, 0, up);
    }
}

// Простой поиск по массиву
void simple_search(int arr[], int size) {
    int num, found = 0;
    printf("Введите число для поиска: ");
    scanf("%d", &num);

    printf("Число найдено на позициях: ");
    for (int i = 0; i < size; i++) {
        if (arr[i] == num) {
            printf("%d ", i + 1);
            found = 1;
        }
    }

    if (!found) {
        printf("не найдено");
    }
    printf("\n");
}

// Быстрый поиск (для отсортированного массива)
void fast_search(int arr[], int size, int up) {
    int num;
    printf("Введите число для поиска: ");
    scanf("%d", &num);

    int start = 0, end = size - 1;
    int found = 0;

    printf("Число найдено на позициях: ");
    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] == num) {
            int i = mid;
            while (i >= 0 && arr[i] == num) {
                printf("%d ", i + 1);
                i--;
            }
            i = mid + 1;
            while (i < size && arr[i] == num) {
                printf("%d ", i + 1);
                i++;
            }
            found = 1;
            break;
        }
        if ((up && arr[mid] < num) || (!up && arr[mid] > num)) {
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }

    if (!found) {
        printf("не найдено");
    }
    printf("\n");
}

// Вывод массива на экран
void show_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Предложение сохранить массив в файл
void save_array(int arr[], int size, char* type) {
    char answer;
    int input = 0;

    do {
        printf("\nСохранить массив в файл? (y/n): ");
        scanf(" %c", &answer);

        while (getchar() != '\n');

        if (answer == 'y' || answer == 'Y') {
            write_file(arr, size, type);
            input = 1;
        }
        else if (answer == 'n' || answer == 'N') {
            input = 1;
        }
        else {
            printf("Ошибка: введите 'y' или 'n'!\n");
        }
    } while (!input);
}

// Предложение отсортировать массив
void sort_array(int arr[], int size, int* sorted, int* order) {
    char answer;
    int input = 0;

    do {
        printf("\nОтсортировать массив? (y/n): ");
        scanf(" %c", &answer);

        while (getchar() != '\n');

        if (answer == 'y' || answer == 'Y') {
            int up;
            int sort_input = 0;

            do {
                printf("\nКак сортировать? (1 - по возрастанию, 0 - по убыванию): ");
                scanf("%d", &up);

                while (getchar() != '\n');

                if (up == 0 || up == 1) {
                    main_sort_heap(arr, size, up);
                    *sorted = 1;
                    *order = up;

                    printf("\nМассив после сортировки (%s):\n",
                        up ? "по возрастанию" : "по убыванию");
                    show_array(arr, size);

                    save_array(arr, size, up ? "sorted_up" : "sorted_down");
                    sort_input = 1;
                }
                else {
                    printf("Ошибка: введите 0 или 1!\n");
                }
            } while (!sort_input);

            input = 1;
        }
        else if (answer == 'n' || answer == 'N') {
            input = 1;
        }
        else {
            printf("Ошибка: введите 'y' или 'n'!\n");
        }
    } while (!input);
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    // Заставка
    printf("\n\n");
    printf("  *****************************************************\n");
    printf("  *                                                   *\n");
    printf("  *                                                   *\n");
    printf("  *            |----------------------------|         *\n");
    printf("  *            |                            |         *\n");
    printf("  *            |  ПИРАМИДАЛЬНАЯ СОРТИРОВКА  |         *\n");
    printf("  *            |   С ВОЗМОЖНОСТЬЮ ПОИСКА    |         *\n");
    printf("  *            |                            |         *\n");
    printf("  *            |----------------------------|         *\n");
    printf("  *                                                   *\n");
    printf("  *                                                   *\n");
    printf("  *     Выполнили:                                    *\n");
    printf("  *     студенты группы 24ВВВ3                        *\n");
    printf("  *                                                   *\n");
    printf("  *      Масюк Артём                                  *\n");
    printf("  *      Мамонтов Никита                              *\n");
    printf("  *      Жуков Александр                              *\n");
    printf("  *                                                   *\n");
    printf("  *                                                   *\n");
    printf("  *****************************************************\n");
    printf("\n\n  Загрузка...\n");
    Sleep(2000);

    int size = 0, choice, min, max, search_type;
    int* arr = NULL;
    int sorted = 0;
    int sort_order = 1;

    while (1) {
        system("cls");

        printf("|=== Главное меню ===|\n\n");
        printf("1 - Ввести массив вручную\n");
        printf("2 - Создать случайный массив\n");
        printf("3 - Найти число в массиве\n");
        printf("0 - Выйти из программы\n");
        printf("Выберите действие: ");

        scanf("%d", &choice);

        if (choice == 0) {
            system("cls");
            printf("\nПрограмма завершена. До свидания!\n");
            break;
        }

        switch (choice) {
        case 1: // Ручной ввод
        case 2: // Случайный массив
        {
            while (1) {
                printf("Введите размер массива: ");
                scanf("%d", &size);

                if (size > 0) break;
                else printf("Ошибка: размер должен быть больше 0!\n");
            }
            if (arr != NULL) {
                free(arr);
            }

            arr = (int*)malloc(size * sizeof(int));
            if (arr == NULL) {
                printf("Ошибка: не удалось выделить память!\n");
                return 1;
            }

            if (choice == 1) {
                printf("Введите %d чисел:\n", size);
                for (int i = 0; i < size; i++) {
                    printf("Элемент %d: ", i + 1);
                    scanf("%d", &arr[i]);
                }
            }
            else {
                printf("Введите минимальное число: ");
                scanf("%d", &min);
                printf("Введите максимальное число: ");
                scanf("%d", &max);

                for (int i = 0; i < size; i++) {
                    arr[i] = rand() % (max - min + 1) + min;
                }
            }

            sorted = 0;
            printf("\nВаш массив:\n");
            show_array(arr, size);

            save_array(arr, size, "array");
            sort_array(arr, size, &sorted, &sort_order);

            printf("\nНажмите Enter чтобы продолжить...");
            getchar();
            getchar();
            break;
        }

        case 3: // Поиск числа
        {
            if (arr == NULL || size == 0) {
                printf("Ошибка: массив не создан! Сначала создайте массив.\n");
                printf("\nНажмите Enter чтобы продолжить...");
                getchar();
                getchar();
                break;
            }

            system("cls");
            printf("|=== Поиск числа ===|\n\n");

            if (size <= 10000) {
                printf("Текущий массив:\n");
                show_array(arr, size);
            }
            else {
                printf("Массив не выводится на экран из-за большого количества элементов (%d элемент.).\n", size);
            }

            printf("\n1 - Обычный поиск (для любого массива)\n");
            printf("2 - Быстрый поиск (только для отсортированного)\n");
            printf("0 - Назад\n");
            printf("Выберите тип поиска: ");

            scanf("%d", &search_type);

            switch (search_type) {
            case 1:
                simple_search(arr, size);
                break;
            case 2:
                if (!sorted) {
                    printf("\nОшибка: массив не отсортирован!\n");
                }
                else {
                    fast_search(arr, size, sort_order);
                }
                break;
            case 0:
                break;
            default:
                printf("Неверный выбор!\n");
            }

            printf("\nНажмите Enter чтобы продолжить...");
            getchar();
            getchar();
            break;
        }

        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            Sleep(1000);
        }
    }

    // Освобождение памяти перед выходом
    if (arr != NULL) {
        free(arr);
    }

    return 0;
}