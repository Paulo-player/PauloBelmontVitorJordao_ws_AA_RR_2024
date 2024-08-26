import os
import random

# Diretório onde os arquivos serão salvos
output_dir = 'entradas'
os.makedirs(output_dir, exist_ok=True)

# Listagem dos tamanhos dos arquivos
sizes = [10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,
         110000,120000,130000,140000,150000,160000,170000,180000,190000,200000]

# Função para gerar arquivos com números aleatórios
def generate_files(sizes):
    for size in sizes:
        filename = os.path.join(output_dir, f'{size}.txt')
        with open(filename, 'w') as file:
            for _ in range(size):
                # Gerar um número aleatório positivo
                number = random.randint(1, size)
                file.write(f'{number}\n')
        print(f'Arquivo {filename} gerado com {size} linhas.')

# Gerar arquivos
generate_files(sizes)