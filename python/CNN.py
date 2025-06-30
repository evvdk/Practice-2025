import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Model
from tensorflow.keras.layers import Input, Conv1D, Dropout, Flatten, Dense
import matplotlib.pyplot as plt
import tensorflow as tf
import tf2onnx
import onnx

timesteps = 100
features = 1

def generate_data(n_samples=1000):
    X = []
    Y = []
    for _ in range(n_samples):
        t = np.linspace(0, 10, timesteps)
        f = np.sin(t) + np.random.normal(0, 0.1, size=t.shape)
        
        idx = np.random.randint(20, 80)
        f[idx:] += 2.0
        
        x_sample = f.reshape(-1, 1)
        y_sample = np.zeros(timesteps)
        y_sample[idx] = 1
        X.append(x_sample)
        Y.append(y_sample)
    return np.array(X), np.array(Y)

X, Y = generate_data(1000)

def visualize(X, Y, save_path="plot.png"):
    t = np.linspace(0, 10, timesteps)
    plt.figure(figsize=(10, 5))
    plt.plot(t, X[0].squeeze(), label='Сигнал')
    plt.plot(t, Y[0] * np.max(X[0]), 'r--', label='Метка перехода')
    plt.title('Пример')
    plt.xlabel('Время')
    plt.ylabel('Амплитуда')
    plt.legend()
    plt.grid(True)
    plt.savefig(save_path)

#Игра в имитацию нормальных графиков - так себе получется
visualize(X,Y)

#Сама моделька
input_layer = Input(shape=(timesteps, features), name='model_input')

x = Conv1D(filters=32, kernel_size=5, activation='relu')(input_layer)
x = Dropout(0.2)(x)
x = Conv1D(filters=64, kernel_size=5, activation='relu')(x)
x = Dropout(0.2)(x)
x = Flatten()(x)

output_layer = Dense(timesteps, activation='sigmoid', name='model_output')(x)

model = Model(inputs=input_layer, outputs=output_layer)

model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
model.summary()

model.fit(X, Y, epochs=10, batch_size=32, validation_split=0.2)

# Конвертация в ONNX
spec = [tf.TensorSpec((None, 100, 1), tf.float32, name="input")]
onnx_model, _ = tf2onnx.convert.from_keras(model, input_signature=spec, opset=15)
onnx.save(onnx_model, "model.onnx")


#Тест
predictions = model.predict(X[:5])

# Пример: извлечение времени начала перехода
for i, pred in enumerate(predictions):
    transition_points = np.where(pred > 0.5)[0]
    print(f"Sample {i}: transition starts at t[{transition_points}]")
