#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

// ������� ��� ����������� ���� (� ���������� ������� ����������)
void heapify(int arr[], int n, int i, int ascending) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (ascending) {
        // ���������� �� ����������� (������������ ����)
        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;
    }
    else {
        // ���������� �� �������� (����������� ����)
        if (left < n && arr[left] < arr[largest])
            largest = left;

        if (right < n && arr[right] < arr[largest])
            largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest, ascending);
    }
}

// ������� ������������� ���������� � ������� �����������
void heapSort(int arr[], int n, int ascending) {
    // ���������� ���� (�������������� ������)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, ascending);

    // ���� �� ������ ��������� �������� �� ����
    for (int i = n - 1; i >= 0; i--) {
        // ���������� ������� ������ � �����
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // �������� heapify �� ����������� ����
        heapify(arr, i, 0, ascending);
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

    // ��������
    printf("\n\n");
    printf("  *****************************************************\n");
    printf("  *                                                   *\n");
    printf("  *                                                   *\n");
    printf("  *            |----------------------------|         *\n");
    printf("  *            |                            |         *\n");
    printf("  *            |  ������������� ����������  |         *\n");
    printf("  *            |   � ������������ ������    |         *\n");
    printf("  *            |                            |         *\n");
    printf("  *            |----------------------------|         *\n");
    printf("  *                                                   *\n");
    printf("  *                                                   *\n");
    printf("  *     ���������:                                    *\n");
    printf("  *     �������� ������ 24���3                        *\n");
    printf("  *                                                   *\n");
    printf("  *      ����� ����                                  *\n");
    printf("  *      �������� ������                              *\n");
    printf("  *      ����� ���������                              *\n");
    printf("  *                                                   *\n");
    printf("  *                                                   *\n");
    printf("  *****************************************************\n");
    printf("\n\n  ��������...\n");
    Sleep(2000);

    int n, choice, min_val, max_val, search_choice, sort_order;
    int* arr = NULL;

    while (1) {
        system("cls");

        // ����� ������ ����� � ���������
        while (1) {
            printf("|--������� ����--|\n\n");
            printf("�������� ������ ���������� �������:\n");
            printf("1 - ���� �������\n");
            printf("2 - ��������� ���������\n");
            printf("3 - ������ � �������(� ��������)\n");
            printf("0 - ����� �� ���������\n");
            printf("��� �����: ");
            if (scanf("%d", &choice) != 1) {
                printf("������: ������� �����!\n");
                while (getchar() != '\n');
                Sleep(1000);
                system("cls");
                continue;
            }

            if (choice >= 0 && choice <= 2) {
                break;
            }
            else {
                printf("\n������: �������� ����� �� ���� (0-2)!\n");
                printf("������� ����� ������� ��� �����������...");
                while (getchar() != '\n');
                getchar();
                system("cls");
            }
        }

        // ��������� ������
        if (choice == 0) {
            system("cls");
            printf("\n��������� ���������. �� ��������!\n");
            break;
        }

        // ���� ������� ������� � ���������
        while (1) {
            printf("������� ���������� ���������: ");
            if (scanf("%d", &n) != 1) {
                printf("������: ������� �����!\n");
                while (getchar() != '\n');
                continue;
            }

            if (n > 0) {
                break;
            }
            else {
                printf("������: ���������� ��������� ������ ���� �������������!\n");
            }
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
                printf("������� %d: ", i + 1);
                scanf("%d", &arr[i]);
            }
        }
        else if (choice == 2) {
            // ���� ��������� � ���������
            while (1) {
                printf("������� ������ ������� ���������: ");
                scanf("%d", &min_val);
                printf("������� ������� ������� ���������: ");
                scanf("%d", &max_val);

                if (min_val < max_val) {
                    break;
                }
                else {
                    printf("������: ������ ������� ������ ���� ������ �������!\n");
                }
            }

            for (int i = 0; i < n; i++) {
                arr[i] = rand() % (max_val - min_val + 1) + min_val;
            }
        }

        // ����� ��������� �������
        printf("\n�������� ������:\n");
        printArray(arr, n);

        // ����� � ����������������� �������
        int valid_input = 0;
        do {
            printf("\n������ ��������� ����� � ����������������� �������? (1 - ��, 0 - ���): ");
            if (scanf("%d", &search_choice) != 1) {
                printf("������: ������� ����� (0 ��� 1)!\n");
                while (getchar() != '\n');
                continue;
            }

            if (search_choice == 0 || search_choice == 1) {
                valid_input = 1;
            }
            else {
                printf("������: ������� 0 ��� 1!\n");
            }
        } while (!valid_input);

        if (search_choice == 1) {
            linearSearch(arr, n);
        }

        // ����� ������� ����������
        valid_input = 0;
        do {
            printf("\n�������� ������� ���������� (1 - �� �����������, 0 - �� ��������): ");
            if (scanf("%d", &sort_order) != 1) {
                printf("������: ������� ����� (0 ��� 1)!\n");
                while (getchar() != '\n');
                continue;
            }

            if (sort_order == 0 || sort_order == 1) {
                valid_input = 1;
            }
            else {
                printf("������: ������� 0 ��� 1!\n");
            }
        } while (!valid_input);

        // ���������� �������
        heapSort(arr, n, sort_order);

        // ����� ���������������� �������
        printf("\n��������������� ������ (%s):\n", sort_order ? "�� �����������" : "�� ��������");
        printArray(arr, n);

        // �������� ����� �������
        printf("\n������� Enter ��� �����������...");
        while (getchar() != '\n');
        getchar();

        // ������������ ������
        free(arr);
    }

    return 0;
}