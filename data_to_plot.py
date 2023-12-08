import math

import pandas as pd
import matplotlib.pyplot as plt


def create_graphs(df, x_col, y_cols, num_threads_fixed=None, ninput_fixed=None, x_min=None, x_max=None):
    """
    Args:
        df (pd.DataFrame): Il DataFrame contenente i dati.
        x_col (str): Nome della colonna da utilizzare per le ascisse.
        y_cols (list): Lista di nomi delle colonne da utilizzare per le ordinate.
        num_threads_fixed (int): Numero di thread fisso (usato solo se specificato).
        ninput_fixed (int): Numero di input fisso (usato solo se specificato).
        save_path (str): Percorso per salvare i grafici (formato: 'nome_file.png').
        x_min (float): Valore minimo per le ascisse.
        x_max (float): Valore massimo per le ascisse.
    """

    if x_min is not None and x_max is not None:
        df = df[(df[x_col] >= x_min) & (df[x_col] <= x_max)]

    grouped_data = df.groupby(['ROWS', 'COLUMNS'])

    print(grouped_data)

    for (rows, columns), group in grouped_data:
        plt.figure()

        rows_exp = int(math.log10(rows))
        columns_exp = int(math.log10(columns))

        for y_col in y_cols:
            margin_percent = 0.25  # Modifica a seconda delle tue esigenze

            # Calcola i valori minimi e massimi solo all'interno del gruppo corrente
            y_min = group[y_col].min() * (1 - margin_percent)
            y_max = group[y_col].max() * (1 + margin_percent)

            y_range = (y_min, y_max)

            plt.plot(group[x_col], group[y_col])

            plt.title(f'(Matrix 10^{rows_exp} x 10^{columns_exp}) x (Vector 10^{columns_exp})')
            plt.xlabel('Number of threads')
            plt.ylabel(y_col.capitalize())
            plt.ylim(y_range)

            plt.savefig(f'output/plots/plot_{y_col.lower()}_10_{rows_exp}x10_{columns_exp}.png')
            plt.close()


# Esempio di utilizzo con intervallo per le ascisse
csv = pd.read_csv('data.csv')
create_graphs(csv, 'NUM_THREADS', ['TIME', 'SPEEDUP', 'EFFICIENCY'], x_min=1, x_max=8)
