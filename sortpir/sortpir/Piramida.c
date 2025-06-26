#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

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

    int n, choice, min_val, max_val, search_choice;
    int* arr = NULL;

    printf("Пирамидальная сортировка с возможностью поиска\n\n");

    // Выбор режима ввода
    printf("Выберите способ заполнения массива:\n");
    printf("1 - Ввод вручную\n");
    printf("2 - Случайная генерация\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);

    // Ввод размера массива
    printf("Введите количество элементов: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Ошибка: количество элементов должно быть положительным!\n");
        return 1;
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
            scanf("%d", &arr[i]);
        }
    }
    else {
        printf("Введите нижнюю границу диапазона: ");
        scanf("%d", &min_val);
        printf("Введите верхнюю границу диапазона: ");
        scanf("%d", &max_val);

        if (min_val >= max_val) {
            printf("Ошибка: нижняя граница должна быть меньше верхней!\n");
            free(arr);
            return 1;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = rand() % (max_val - min_val + 1) + min_val;
        }
    }

    // Вывод исходного массива
    printf("\nИсходный массив:\n");
    printArray(arr, n);

    // Поиск в неотсортированном массиве
    printf("\nХотите выполнить поиск в неотсортированном массиве? (1 - Да, 0 - Нет): ");
    scanf("%d", &search_choice);
    if (search_choice == 1) {
        linearSearch(arr, n);
    }

    // Сортировка массива
    heapSort(arr, n);

    // Вывод отсортированного массива
    printf("\nОтсортированный массив:\n");
    printArray(arr, n);

    // Освобождение памяти
    free(arr);
    return 0;
}