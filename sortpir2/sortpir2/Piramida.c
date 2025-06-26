#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

// Функция для перестройки кучи
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

// Функция пирамидальной сортировки
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// Функция линейного поиска
void linearSearch(int arr[], int n) {
    int target, found = 0;
    printf("Введите число для поиска: ");
    scanf("%d", &target);

    printf("Найдено на позициях: ");
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            printf("%d ", i);
            found = 1;
        }
    }

    if (!found) {
        printf("число не найдено");
    }
    printf("\n");
}

// Функция вывода массива
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
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

    int n, choice, min_val, max_val, search_choice;
    int* arr = NULL;

    while (1) {
        system("cls");

        // Выбор режима ввода с проверкой
        while (1) {
            printf("|--ГЛАВНОЕ МЕНЮ--|\n\n");
            printf("Выберите способ заполнения массива:\n");
            printf("1 - Ввод вручную\n");
            printf("2 - Случайная генерация\n");
            printf("3 - Работа с файлами(в процессе)\n");
            printf("0 - Выход из программы\n");
            printf("Ваш выбор: ");
            if (scanf("%d", &choice) != 1) {
                printf("Ошибка: введите число!\n");
                while (getchar() != '\n');
                Sleep(1000);
                system("cls");
                continue;
            }

            if (choice >= 0 && choice <= 2) {
                break;
            }
            else {
                printf("\nОшибка: выберите пункт из меню (0-2)!\n");
                printf("Нажмите любую клавишу для продолжения...");
                while (getchar() != '\n');
                getchar();
                system("cls");
            }
        }

        // Обработка выхода
        if (choice == 0) {
            system("cls");
            printf("\nПрограмма завершена. До свидания!\n");
            break;
        }

        // Ввод размера массива с проверкой
        while (1) {
            printf("Введите количество элементов: ");
            if (scanf("%d", &n) != 1) {
                printf("Ошибка: введите число!\n");
                while (getchar() != '\n');
                continue;
            }

            if (n > 0) {
                break;
            }
            else {
                printf("Ошибка: количество элементов должно быть положительным!\n");
            }
        }

        // Выделение памяти
        arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка выделения памяти!\n");
            return 1;
        }

        // Заполнение массива
        if (choice == 1) {
            printf("Введите %d элементов:\n", n);
            for (int i = 0; i < n; i++) {
                printf("Элемент %d: ", i + 1);
                scanf("%d", &arr[i]);
            }
        }
        else if (choice == 2) {
            // Ввод диапазона с проверкой
            while (1) {
                printf("Введите нижнюю границу диапазона: ");
                scanf("%d", &min_val);
                printf("Введите верхнюю границу диапазона: ");
                scanf("%d", &max_val);

                if (min_val < max_val) {
                    break;
                }
                else {
                    printf("Ошибка: нижняя граница должна быть меньше верхней!\n");
                }
            }

            for (int i = 0; i < n; i++) {
                arr[i] = rand() % (max_val - min_val + 1) + min_val;
            }
        }

        // Вывод исходного массива
        printf("\nИсходный массив:\n");
        printArray(arr, n);

        // Поиск в неотсортированном массиве
        int valid_input = 0;
        do {
            printf("\nХотите выполнить поиск в неотсортированном массиве? (1 - Да, 0 - Нет): ");
            if (scanf("%d", &search_choice) != 1) {
                printf("Ошибка: введите число (0 или 1)!\n");
                while (getchar() != '\n'); 
                continue;
            }

            if (search_choice == 0 || search_choice == 1) {
                valid_input = 1;
            }
            else {
                printf("Ошибка: введите 0 или 1!\n");
            }
        } while (!valid_input);

        if (search_choice == 1) {
            linearSearch(arr, n);
        }

        // Сортировка массива
        heapSort(arr, n);

        // Вывод отсортированного массива
        printf("\nОтсортированный массив:\n");
        printArray(arr, n);

        // Ожидание перед выходом
        printf("\nНажмите Enter для продолжения...");
        while (getchar() != '\n');
        getchar();

        // Освобождение памяти
        free(arr);
    }

    return 0;
}