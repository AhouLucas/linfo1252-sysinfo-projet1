import matplotlib.pyplot as plt
import numpy as np
import pandas as pd



local_csv = True

if local_csv:
    csv_dir = "local_csv/"
else:
    csv_dir = "csv/"


def plot(plots: list[tuple], num_threads, title, export=False, filename=None, export_type='png', show=True):
    y_max = 0
    for data, label in plots:
        line, = plt.plot(num_threads, data.mean(), label="Mean " + label)
        plt.errorbar(num_threads, data.mean(), yerr=data.std(), fmt='.', color=line.get_color())
        if data.mean().max() >= y_max: y_max = data.mean().max()

    plt.xticks(num_threads)
    plt.xlabel('Number of threads')
    plt.ylabel('Time (s)')
    plt.xlim(0, num_threads.max() + 1)
    plt.ylim(0, y_max + 0.2*y_max)
    plt.title(title)
    plt.legend()
    plt.grid(linestyle='--', alpha=0.5)

    if export:
        if local_csv:
            filename += "_local"
            
        plt.savefig("graphs/" + filename + "." + export_type, format=export_type, bbox_inches='tight')

    if show:
        plt.show()


num_threads = np.array([2, 4, 8, 16, 32])

data_philosophe = pd.read_csv(csv_dir + 'philosophe.csv', header=0)
data_philosophe_tas = pd.read_csv(csv_dir + 'philosophe_tas.csv', header=0)
data_philosophe_tatas = pd.read_csv(csv_dir + 'philosophe_tatas.csv', header=0)

data_prodcons = pd.read_csv(csv_dir + 'prodcons.csv', header=0)
data_prodcons_tas = pd.read_csv(csv_dir + 'prodcons_tas.csv', header=0)
data_prodcons_tatas = pd.read_csv(csv_dir + 'prodcons_tatas.csv', header=0)

data_readerwriter = pd.read_csv(csv_dir + 'readerwriter.csv', header=0)
data_readerwriter_tas = pd.read_csv(csv_dir + 'readerwriter_tas.csv', header=0)
data_readerwriter_tatas = pd.read_csv(csv_dir + 'readerwriter_tatas.csv', header=0)

# Philosophe
plot([(data_philosophe, "philosophe"), (data_philosophe_tas, "philosophe TAS"), (data_philosophe_tatas, "philosophe TATAS")], 
     num_threads, "Philosophe", export=True, filename="philosophe", show=True)

# ProdCons
plot([(data_prodcons, "prod./cons."), (data_prodcons_tas, "prod./cons. TAS"), (data_prodcons_tatas, "prod./cons. TATAS")], 
     num_threads, "Producer / Consumer", export=True, filename="prodcons", show=True)

# ReaderWriter
plot([(data_readerwriter, "reader/writer"), (data_readerwriter_tas, "reader/writer TAS"), (data_readerwriter_tatas, "reader/writer TATAS")], 
     num_threads, "Reader / Writer", export=True, filename="readerwriter", show=True)


## TAS & TATAS Performance
num_threads = np.array([1, 2, 4, 8, 16, 32])

data_tas = pd.read_csv(csv_dir + 'test_and_set_perf.csv', header=0)
data_tatas = pd.read_csv(csv_dir + 'test_and_test_and_set_perf.csv', header=0)

plot([(data_tas, "test & set"), (data_tatas, "test & test & set")], 
     num_threads, "TAS Vs. TATAS", export=True, filename="tas_and_tatas", show=True)