import matplotlib.pyplot as plt
import pandas as pd
import sys

try:
    if len(sys.argv) > 1: 
        file_path = sys.argv[1]
    else: 
        file_path = 'data.txt'

    df = pd.read_csv(file_path, sep='\t', header=None, names=['Time', 'Value'])
    
    plt.figure(figsize=(10, 5))
    plt.plot(df['Time'], df['Value'], marker='o')
    plt.title('График значения функции от времени')
    plt.xlabel('Время')
    plt.ylabel('Значение')
    plt.grid(True)
    plt.tight_layout()

    if len(sys.argv) > 2: 
        png_file = sys.argv[2]
    else:
        png_file = "plot.png"

    plt.savefig(png_file)
    
    print(f"Создан файл {png_file} для файла {file_path}")

except Exception as e:
    print(f"Ошибка при обработке файла: {e}")
