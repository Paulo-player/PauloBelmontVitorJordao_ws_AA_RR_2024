import matplotlib.pyplot as plt
import numpy as np

def ler_tempos_de_execucao(arquivo):
    tamanhos = []
    tempos = []

    with open(arquivo, 'r') as file:
        for linha in file:
            partes = linha.split()
            if len(partes) == 2:
                tamanho, tempo = partes
                tamanhos.append(int(tamanho))
                tempos.append(float(tempo))

    return tamanhos, tempos

def plotar_grafico(tamanhos1, tempos1, tamanhos2, tempos2, saida_imagem):
    tamanhos1 = np.array(tamanhos1)
    tempos1 = np.array(tempos1)
    tamanhos2 = np.array(tamanhos2)
    tempos2 = np.array(tempos2)

    plt.figure(figsize=(12, 8))
    plt.plot(tamanhos1, tempos1, marker='o', linestyle='-', color='b', label='MergeSort')
    plt.plot(tamanhos2, tempos2, marker='s', linestyle='-', color='r', label='TimSort')
    # plt.xscale('log')
    # plt.yscale('log')
    plt.xlabel('Tamanho do Arquivo (linhas)')
    plt.ylabel('Tempo de Execução (segundos)')
    plt.title('Tempo de Execução vs Tamanho do Arquivo')
    plt.grid(True, which='both', linestyle='--', linewidth=0.5)
    plt.legend()
    plt.savefig(saida_imagem)
    plt.show()

if __name__ == '__main__':
    arquivo_tempos_merge = 'tempos_de_execucao/tempos_de_execucao.txt'
    arquivo_tempos_timsort = 'tempos_de_execucao/timsort.txt'
    saida_imagem = 'tempos_vs_tamanho_comparativo.png'

    tamanhos_merge, tempos_merge = ler_tempos_de_execucao(arquivo_tempos_merge)
    tamanhos_timsort, tempos_timsort = ler_tempos_de_execucao(arquivo_tempos_timsort)
    
    # Plotar gráfico comparativo
    plotar_grafico(tamanhos_merge, tempos_merge, tamanhos_timsort, tempos_timsort, saida_imagem)
