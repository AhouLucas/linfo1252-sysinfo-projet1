import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


num_threads = np.array([2, 4, 8, 16, 32])

data_philosophe = pd.read_csv('csv/philosophe.csv', header=0)
data_prodcons = pd.read_csv('csv/prodcons.csv', header=0)
data_readerwriter = pd.read_csv('csv/readerwriter.csv', header=0)

mean_philosophe = data_philosophe.mean()
mean_prodcons = data_prodcons.mean()
mean_readerwriter = data_readerwriter.mean()

std_philosophe = data_philosophe.std()
std_prodcons = data_prodcons.std()
std_readerwriter = data_readerwriter.std()



def plot(data, num_threads, title, export=False, filename=None, export_type='png'):
    plt.plot(num_threads, data.mean(), marker='.', label="Mean " + title)
    plt.plot(num_threads, data.std(), marker='.', label="Std " + title)
    plt.xticks(num_threads)
    plt.xlabel('Number of threads')
    plt.ylabel('Time (s)')
    plt.xlim(0, num_threads.max() + 1)
    plt.ylim(0, data.max().max() + 0.2)
    plt.title(title)
    plt.legend()
    plt.grid(linestyle='--', alpha=0.5)

    if export:
        plt.savefig(filename, format=export_type, bbox_inches='tight')

    plt.show()


# Philosophe
plot(data_philosophe, num_threads, "Philosophe", export=True, filename="graphs/philosophe.png")

# ProdCons
plot(data_prodcons, num_threads, "ProdCons")

# ReaderWriter
plot(data_readerwriter, num_threads, "ReaderWriter")
