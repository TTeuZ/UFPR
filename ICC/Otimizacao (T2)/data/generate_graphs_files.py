import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

files = ['cache', 'flops', 'mem', 'time']
y_labels = ['Data Cache Miss Ratio', 'MFLOPS/s', 'MBytes/s', 'Tempo (ms)']
titles = ['Taxa de Miss Ratio', 'Flops por Segundo', 'Largura de Memória', 'Tempo de Execução']

for i in range(0, 4): 
    df = pd.read_csv('./csvs/' + files[i] + '.csv')
    plt.figure(figsize=(7, 4.5))
    ax = df.set_index('matrix_size').plot(marker='o', color=['red', 'forestgreen', 'royalblue', 'darkorange'])
    ax.set(yscale='log')
    ax.set_ylabel(y_labels[i])
    ax.set_xlabel('Tamanho da Matriz')
    ax.set_title(titles[i])
    plt.grid()
    plt.savefig('./images/' + files[i] + '.svg', bbox_inches='tight')