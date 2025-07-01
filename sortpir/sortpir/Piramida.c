
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

// ������� ��� �������� ����� ����� � ������� ����� � ��������
void random_file(char* filename, char* type) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    sprintf(filename, "%s_%04d%02d%02d_%02d%02d%02d.txt",
        type,
        t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec);
}

// ������� ��� ������ ������� � ����
void write_file(int arr[], int size, char* type) {
    char filename[100];
    random_file(filename, type);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("�� ������� ������� ����!\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fprintf(file, "\n");

    fclose(file);
    printf("������ ������� � ����: %s\n", filename);
}

// ������� ��� ���������� ����
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

// �������� ������� ����������
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

// ������� ����� �� �������
void simple_search(int arr[], int size) {
    int num, found = 0;
    printf("������� ����� ��� ������: ");
    scanf("%d", &num);

    printf("����� ������� �� ��������: ");
    for (int i = 0; i < size; i++) {
        if (arr[i] == num) {
            printf("%d ", i + 1);
            found = 1;
        }
    }

    if (!found) {
        printf("�� �������");
    }
    printf("\n");
}

// ������� ����� (��� ���������������� �������)
void fast_search(int arr[], int size, int up) {
    int num;
    printf("������� ����� ��� ������: ");
    scanf("%d", &num);

    int start = 0, end = size - 1;
    int found = 0;

    printf("����� ������� �� ��������: ");
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
        printf("�� �������");
    }
    printf("\n");
}

// ����� ������� �� �����
void show_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// ����������� ��������� ������ � ����
void save_array(int arr[], int size, char* type) {
    char answer;
    int input = 0;

    do {
        printf("\n��������� ������ � ����? (y/n): ");
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
            printf("������: ������� 'y' ��� 'n'!\n");
        }
    } while (!input);
}

// ����������� ������������� ������
void sort_array(int arr[], int size, int* sorted, int* order) {
    char answer;
    int input = 0;

    do {
        printf("\n������������� ������? (y/n): ");
        scanf(" %c", &answer);

        while (getchar() != '\n');

        if (answer == 'y' || answer == 'Y') {
            int up;
            int sort_input = 0;

            do {
                printf("\n��� �����������? (1 - �� �����������, 0 - �� ��������): ");
                scanf("%d", &up);

                while (getchar() != '\n');

                if (up == 0 || up == 1) {
                    main_sort_heap(arr, size, up);
                    *sorted = 1;
                    *order = up;

                    printf("\n������ ����� ���������� (%s):\n",
                        up ? "�� �����������" : "�� ��������");
                    show_array(arr, size);

                    save_array(arr, size, up ? "sorted_up" : "sorted_down");
                    sort_input = 1;
                }
                else {
                    printf("������: ������� 0 ��� 1!\n");
                }
            } while (!sort_input);

            input = 1;
        }
        else if (answer == 'n' || answer == 'N') {
            input = 1;
        }
        else {
            printf("������: ������� 'y' ��� 'n'!\n");
        }
    } while (!input);
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

    int size = 0, choice, min, max, search_type;
    int* arr = NULL;
    int sorted = 0;
    int sort_order = 1;

    while (1) {
        system("cls");

        printf("|=== ������� ���� ===|\n\n");
        printf("1 - ������ ������ �������\n");
        printf("2 - ������� ��������� ������\n");
        printf("3 - ����� ����� � �������\n");
        printf("0 - ����� �� ���������\n");
        printf("�������� ��������: ");

        scanf("%d", &choice);

        if (choice == 0) {
            system("cls");
            printf("\n��������� ���������. �� ��������!\n");
            break;
        }

        switch (choice) {
        case 1: // ������ ����
        case 2: // ��������� ������
        {
            while (1) {
                printf("������� ������ �������: ");
                scanf("%d", &size);

                if (size > 0) break;
                else printf("������: ������ ������ ���� ������ 0!\n");
            }
            if (arr != NULL) {
                free(arr);
            }

            arr = (int*)malloc(size * sizeof(int));
            if (arr == NULL) {
                printf("������: �� ������� �������� ������!\n");
                return 1;
            }

            if (choice == 1) {
                printf("������� %d �����:\n", size);
                for (int i = 0; i < size; i++) {
                    printf("������� %d: ", i + 1);
                    scanf("%d", &arr[i]);
                }
            }
            else {
                printf("������� ����������� �����: ");
                scanf("%d", &min);
                printf("������� ������������ �����: ");
                scanf("%d", &max);

                for (int i = 0; i < size; i++) {
                    arr[i] = rand() % (max - min + 1) + min;
                }
            }

            sorted = 0;
            printf("\n��� ������:\n");
            show_array(arr, size);

            save_array(arr, size, "array");
            sort_array(arr, size, &sorted, &sort_order);

            printf("\n������� Enter ����� ����������...");
            getchar();
            getchar();
            break;
        }

        case 3: // ����� �����
        {
            if (arr == NULL || size == 0) {
                printf("������: ������ �� ������! ������� �������� ������.\n");
                printf("\n������� Enter ����� ����������...");
                getchar();
                getchar();
                break;
            }

            system("cls");
            printf("|=== ����� ����� ===|\n\n");

            if (size <= 10000) {
                printf("������� ������:\n");
                show_array(arr, size);
            }
            else {
                printf("������ �� ��������� �� ����� ��-�� �������� ���������� ��������� (%d �������.).\n", size);
            }

            printf("\n1 - ������� ����� (��� ������ �������)\n");
            printf("2 - ������� ����� (������ ��� ����������������)\n");
            printf("0 - �����\n");
            printf("�������� ��� ������: ");

            scanf("%d", &search_type);

            switch (search_type) {
            case 1:
                simple_search(arr, size);
                break;
            case 2:
                if (!sorted) {
                    printf("\n������: ������ �� ������������!\n");
                }
                else {
                    fast_search(arr, size, sort_order);
                }
                break;
            case 0:
                break;
            default:
                printf("�������� �����!\n");
            }

            printf("\n������� Enter ����� ����������...");
            getchar();
            getchar();
            break;
        }

        default:
            printf("�������� �����! ���������� �����.\n");
            Sleep(1000);
        }
    }

    // ������������ ������ ����� �������
    if (arr != NULL) {
        free(arr);
    }

    return 0;
}