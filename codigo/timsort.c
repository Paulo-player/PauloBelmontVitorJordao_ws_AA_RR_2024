#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_LENGTH 256
#define INPUT_DIR "entradas"
#define OUTPUT_DIR "tempos_de_execucao"
#define RUN 32

// Função para usar Insertion Sort em uma parte do array
void insertionSort(int arr[], int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= l && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Função para mesclar dois subarrays
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

// Função para ordenar o array usando TimSort
void timSort(int arr[], int n) {
    // Ordenar pequenas partes usando InsertionSort
    for (int i = 0; i < n; i += RUN) {
        int end = i + RUN - 1 < n - 1 ? i + RUN - 1 : n - 1;
        insertionSort(arr, i, end);
    }

    // Mesclar partes
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? left + 2 * size - 1 : n - 1;

            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

// Função para ler números de um arquivo
int *readNumbers(const char *filename, int *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Não foi possível abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int capacity = 1000;
    int *arr = (int *)malloc(capacity * sizeof(int));
    *size = 0;

    while (fscanf(file, "%d", &arr[*size]) != EOF) {
        (*size)++;
        if (*size >= capacity) {
            capacity *= 2;
            arr = (int *)realloc(arr, capacity * sizeof(int));
        }
    }

    fclose(file);
    return arr;
}

// Função para gravar o tempo de execução
void writeExecutionTime(const char *filename, int size, double time_spent) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Não foi possível abrir o arquivo de resultados");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d %f\n", size, time_spent);
    fclose(file);
}

int main() {
    // Criar diretório de resultados
    system("mkdir -p " OUTPUT_DIR);

    // Arquivos de entrada
    const char *files[] = {
        "entradas/10000.txt", 
        "entradas/20000.txt", 
        "entradas/30000.txt", 
        "entradas/40000.txt", 
        "entradas/50000.txt", 
        "entradas/60000.txt", 
        "entradas/70000.txt", 
        "entradas/80000.txt", 
        "entradas/90000.txt", 
        "entradas/100000.txt",
        "entradas/110000.txt", 
        "entradas/120000.txt", 
        "entradas/130000.txt", 
        "entradas/140000.txt", 
        "entradas/150000.txt", 
        "entradas/160000.txt", 
        "entradas/170000.txt", 
        "entradas/180000.txt", 
        "entradas/190000.txt", 
        "entradas/200000.txt",
    };

    int num_files = sizeof(files) / sizeof(files[0]);

    // Criar/abrir arquivo de resultados
    char results_file[MAX_LINE_LENGTH];
    snprintf(results_file, sizeof(results_file), "%s/timsort.txt", OUTPUT_DIR);
    FILE *results = fopen(results_file, "w");
    if (!results) {
        perror("Não foi possível criar o arquivo de resultados");
        return EXIT_FAILURE;
    }
    fclose(results);

    // Processar cada arquivo
    for (int i = 0; i < num_files; i++) {
        int size;
        int *arr = readNumbers(files[i], &size);

        clock_t start = clock();
        timSort(arr, size);
        clock_t end = clock();

        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        writeExecutionTime(results_file, size, time_spent);

        free(arr);
        printf("Arquivo %s processado.\n", files[i]);
    }

    printf("Todos os arquivos foram processados. Resultados salvos em %s.\n", results_file);

    return EXIT_SUCCESS;
}
