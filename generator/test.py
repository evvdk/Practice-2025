import matplotlib.pyplot as plt
import pandas as pd

file_path = 'data.txt'

try:
    df = pd.read_csv(file_path, sep='\t', header=None, names=['Time', 'Value'])
    
    plt.figure(figsize=(10, 5))
    plt.plot(df['Time'], df['Value'], marker='o')
    plt.title('График значения функции от времени')
    plt.xlabel('Время')
    plt.ylabel('Значение')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("plot.png")

except Exception as e:
    print(f"Ошибка при обработке файла: {e}")
