#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// ������� ��� ����������� ����
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

// ������� ������������� ����������
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

// ������� ��������� ������
void linearSearch(int arr[], int n) {
    int target, found = 0;
    printf("������� ����� ��� ������: ");
    scanf("%d", &target);

    printf("������� �� ��������: ");
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            printf("%d ", i);
            found = 1;
        }
    }

    if (!found) {
        printf("����� �� �������");
    }
    printf("\n");
}

// ������� ������ �������
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

    printf("������������� ���������� � ������������ ������\n\n");

    // ����� ������ �����
    printf("�������� ������ ���������� �������:\n");
    printf("1 - ���� �������\n");
    printf("2 - ��������� ���������\n");
    printf("��� �����: ");
    scanf("%d", &choice);

    // ���� ������� �������
    printf("������� ���������� ���������: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("������: ���������� ��������� ������ ���� �������������!\n");
        return 1;
    }

    // ��������� ������
    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("������ ��������� ������!\n");
        return 1;
    }

    // ���������� �������
    if (choice == 1) {
        printf("������� %d ���������:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
    }
    else {
        printf("������� ������ ������� ���������: ");
        scanf("%d", &min_val);
        printf("������� ������� ������� ���������: ");
        scanf("%d", &max_val);

        if (min_val >= max_val) {
            printf("������: ������ ������� ������ ���� ������ �������!\n");
            free(arr);
            return 1;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = rand() % (max_val - min_val + 1) + min_val;
        }
    }

    // ����� ��������� �������
    printf("\n�������� ������:\n");
    printArray(arr, n);

    // ����� � ����������������� �������
    printf("\n������ ��������� ����� � ����������������� �������? (1 - ��, 0 - ���): ");
    scanf("%d", &search_choice);
    if (search_choice == 1) {
        linearSearch(arr, n);
    }

    // ���������� �������
    heapSort(arr, n);

    // ����� ���������������� �������
    printf("\n��������������� ������:\n");
    printArray(arr, n);

    // ������������ ������
    free(arr);
    return 0;
}