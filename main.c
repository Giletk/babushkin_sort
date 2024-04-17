#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Сортировка Бабушкина - псевдоалгоритм сортировки. Для реализации
// этого алгоритма необходимо использовать другой, действительно
// работающий алгоритм сортировки.

// Структура, содержащая в себе два числа. При делении меньшего на большее получается 
// число Бабушкина 
struct babushkin {
    long long int big, small;
    // Количество знаков после запятой
    long long int digits;
};

// Функция для вывода массива
void print_array(int *arr, int length) {
    
    // Печать элементов массивов с учетом фиксированной ширины чисел
    for (int i = 0; i < length; i++) {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

// Функция для нахождения наибольшего общего делителя (НОД)
long long int gcd(long long int a, long long int b) {
    long long int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для упрощения дроби
void simplify_fraction(long long int *numerator, long long int *denominator) {
    long long int divisor = gcd(*numerator, *denominator);
    *numerator /= divisor;
    *denominator /= divisor;
}

// Вспомогательная функция сортировки. Я использую сортировку пузырьком.
void bubble_sort(int *arr, const int size) {
    int i, j, temp;
    // делаем size проходов по массиву, в результате каждого
    //получаем 1 отсортированный элемент
    for (i = 0; i < size-1; i++)
        // Перемещаем элемент на кго конечную позицию.
        // Не проверяем уже отсортированные элементы.
        for (j = 0; j < size - i - 1; j++) {
            // Если текущий элемент меньше предыдущего, меняем их местами. 
            if (arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
}

// Функция для переноса значений из одного массива в другой
void copy_array(const int *arr1, int *arr2, const int size) {
    // Поэлементно копируем элементы из одного массива в другой
    for (int i = 0; i < size; i++)
        arr2[i] = arr1[i];
}


// Функция для получения числа Бабушкина из массива
struct babushkin get_babushkin_number(int *arr, const int size) {
    // n-ричное представление числа Бабушкина
    int babushkin_arr[size];

    // дробное представление числа Бабушкина
    double babushkin_frac = 0;

    // Само число Бабушкина
    long long int babushkin_num = 0;

    // Структура с двумя искомыми числами
    struct babushkin bnums;
    bnums.big = 0;
    bnums.small = 0;
    bnums.digits = 0;

    // итераторы
    int i, j;

    // массив, в котороый будет записан отсортированный изначальный массив
    long int sorted_arr[size];

    copy_array(arr, (int*)sorted_arr, size);
    bubble_sort((int*)sorted_arr, size);

    // Теперь сравним все элементы в сортированном и изначальном массивах,
    // чтобы выразить число Бабушкина в n-ричной форме
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++) 
            if (sorted_arr[j] == arr[i]) {
                // Разряд i числа Бабушкина равен позиции j в сортированном массиве.
                babushkin_arr[i] = j;
                // Чтобы не было дубликатов, меняем сортированное значение
                // на несуществующее значение
                // Придумать действительно несуществующее значение
                sorted_arr[j] = LONG_MAX;
                break;
            }
    printf("Массив Бабушкина (вычисление):");
    print_array(babushkin_arr, size);

    // Перевод числа Бабушкина в десятичную систему счисления
    for (i = size - 1; i > -1; i--) {
        babushkin_num += babushkin_arr[i] * pow(size, size - 1 - i);
        // Проверка на переполнение
        if (babushkin_num < 0){
            printf("Ошибка переполнения! Число Бабушкина слишком большое\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("Макс long long:  %lld\n", LONG_LONG_MAX);
    printf("Число Бабушкина: %lld\n", babushkin_num);
    babushkin_frac = babushkin_num;

    // Получаем дробь Бабушкина, попутно вычисляя количество знаков после запятой
    while (babushkin_frac > 1) {
        babushkin_frac /= 10;
        bnums.digits += 1;
    }

    bnums.big = pow(10, bnums.digits);
    bnums.small = babushkin_num;
    // Проверка на переполнение
    if (bnums.big < 0){
        printf("Ошибка переполнения! Знаменатель дроби Бабушкина слишком большой\n");
        exit(EXIT_FAILURE);
    }
    simplify_fraction(&bnums.small, &bnums.big);
    printf("Дробь Бабушкина: %lld/%lld\n", bnums.small, bnums.big);
    return bnums;
}

// Функция для сортировки массива с использованием числа Бабушкина.
void sort_with_babushkin_number(int *arr, const int size, const struct babushkin bnums) {
    
    // Создаем пустой массив для отсортированных элементов.
    int result_arr[size];
    // Массив с номерамми позиций в сортированном массиве.
    int babushkin_arr[size];
    // Получаем число Бабушкина из частного двух чисел.
    double babufer = pow(10, bnums.digits);
    babufer *= (double)bnums.small;
    babufer /= (double)bnums.big;
    long long int babushkin_num = (long long int)babufer;
    //Итератор
    int i;

    
    i = 0;
    // Если число Бабушкина имеет ведущий ноль, то определим его здесь.
    // Если нет - его перезапишет следующий цикл
    babushkin_arr[0] = 0; 
    // Перевод числа бабушкина из десятичной в n-ричную систему счисления.
    // Пока число больше нуля, продолжаем делить на основание системы счисления.
    while (babushkin_num > 0) {
        babushkin_arr[size - i - 1] = babushkin_num % size;
        babushkin_num /= size;
        i++;
    }
    printf("Массив Бабушкина (сортировка):");
    print_array(babushkin_arr, size);
    // Перебираем массив с числом бабушкина в n-ричной форме и перемещаем
    // несортированные элементы на места, определяемые каждым разрядом этого числа.
    // Получаем отсортированный массив. 
    for (i = 0; i < size; i++) 
        result_arr[babushkin_arr[i]] = arr[i];

    copy_array(result_arr, arr, size);
    return;
}

void print_arrays(int *arr1, int *arr2, int length) {
    // Определение максимальной длины числа в массиве
    int max_length = 0;
    for (int i = 0; i < length; i++) {
        int len = snprintf(NULL, 0, "%d", arr1[i]); // Получаем длину числа
        if (len > max_length) {
            max_length = len;
        }
    }

    printf("\n%*s\t \t%*s\n\n", max_length, "До", max_length, "После");
    
    // Печать элементов массивов с учетом фиксированной ширины чисел
    for (int i = 0; i < length; i++) {
        printf("%*d\t|\t%*d\n", max_length, arr1[i], max_length, arr2[i]);
    }
}


int main() {
    // Длина массива
    int size;
    // итератор
    int i;
    
    FILE *file = fopen("D:\\Learning\\ALG\\ALG_lab_1\\source\\input.txt", "r");
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    // Считывание размера массива и зфайла
    fscanf(file, "%d", &size);
    printf("Размер массива: %d\n", size);
    // Сортруемый массив
    int arr[size];

    // Чтение элементов массива из файла
    i = 0;
    while (fscanf(file, "%d", &arr[i]) != EOF) {
        i++;
    }

    fclose(file);

    // Вычисляем число Бабушкина
    struct babushkin bnums = get_babushkin_number(arr, size);

    
    int old_arr[size];
    copy_array(arr, old_arr, size);

    // Сортируем массив с использованием числа Бабушкина
    sort_with_babushkin_number(arr, size, bnums);

    // Выводим исходный и отсортированный массив для сравнения
    print_arrays(old_arr, arr, size);

    return 0;
}
