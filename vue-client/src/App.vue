<template>
  <div id="app">
    <header>
      <h1>Vue.js + Qt C++</h1>
      <nav>
        <router-link to="/">Home</router-link> |
        <router-link to="/about">About</router-link>
      </nav>
      <router-view />
    </header>

    <main>
      <div class="card">
        <h2>Обмен данными с C++</h2>
        <p>
          Сообщение от C++: <span class="highlight">{{ messageFromCpp }}</span>
        </p>

        <div class="form-group">
          <label for="userInput">Отправить данные в C++:</label>
          <input
            id="userInput"
            v-model="userInput"
            placeholder="Введите текст..."
          />
          <button @click="sendToCpp">Отправить</button>
        </div>

        <div v-if="processedData" class="result-box">
          <p>Результат обработки: {{ processedData }}</p>
        </div>

        <div v-if="showProgress" class="progress-container">
          <div class="progress-bar" :style="{ width: progress + '%' }"></div>
          <span>{{ progress }}%</span>
        </div>
      </div>

      <div class="card calculator">
        <h2>Калькулятор (использует C++)</h2>
        <div class="form-group">
          <input type="number" v-model.number="num1" placeholder="Число 1" />
          <span>+</span>
          <input type="number" v-model.number="num2" placeholder="Число 2" />
          <button @click="calculate">=</button>
          <span class="result">{{ calculationResult }}</span>
        </div>
      </div>
    </main>
  </div>
</template>

<script>
export default {
  name: "App",
  data() {
    return {
      messageFromCpp: "Загрузка...",
      userInput: "",
      processedData: "",
      progress: 0,
      showProgress: false,
      num1: null,
      num2: null,
      calculationResult: null,
    };
  },
  mounted() {
    // Ожидаем, когда QWebChannel будет доступен
    window.onload = () => {
      if (window.QWebChannel) {
        this.initQtConnection();
      } else {
        // Если QWebChannel не доступен, предположим, что мы в режиме разработки
        console.log(
          "QWebChannel не найден, используем заглушки для разработки"
        );
        this.messageFromCpp = "Режим разработки (без Qt)";
      }
    };
  },
  methods: {
    initQtConnection() {
      // Подключаемся к WebChannel после его доступности
      new window.QWebChannel(window.qt.webChannelTransport, (channel) => {
        // Получаем объект backend из C++
        this.backend = channel.objects.backend;

        // Получаем сообщение из C++
        this.messageFromCpp = this.backend.getMessage();

        // Подписываемся на сигналы от C++
        this.backend.dataChanged.connect((newData) => {
          this.processedData = newData;
        });

        this.backend.progressUpdated.connect((progress) => {
          this.progress = progress;
          if (progress === 100) {
            // Скрываем прогресс-бар через 1 секунду после завершения
            setTimeout(() => {
              this.showProgress = false;
            }, 1000);
          }
        });
      });
    },

    sendToCpp() {
      if (!this.userInput.trim()) return;

      if (this.backend) {
        // Обнуляем предыдущие данные
        this.processedData = "";
        this.progress = 0;
        this.showProgress = true;

        // Отправляем данные в C++
        this.backend.processData(this.userInput);
      } else {
        // Для режима разработки без Qt
        this.processedData = "Режим разработки: " + this.userInput;

        // Эмуляция прогресса
        this.showProgress = true;
        let progress = 0;
        const interval = setInterval(() => {
          progress += 10;
          this.progress = progress;
          if (progress >= 100) {
            clearInterval(interval);
            setTimeout(() => {
              this.showProgress = false;
            }, 1000);
          }
        }, 200);
      }
    },

    calculate() {
      if (this.num1 === null || this.num2 === null) return;

      if (this.backend) {
        // Вызываем метод из C++
        this.calculationResult = this.backend.calculate(this.num1, this.num2);
      } else {
        // Для режима разработки без Qt
        this.calculationResult = this.num1 + this.num2;
      }
    },
  },
};
</script>

<style>
#app {
  font-family: "Roboto", "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  max-width: 800px;
  margin: 0 auto;
  padding: 20px;
  color: #2c3e50;
}

header {
  text-align: center;
  margin-bottom: 30px;
}

h1 {
  color: #4b5eab;
}

.card {
  background: #fff;
  border-radius: 8px;
  box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
  padding: 20px;
  margin-bottom: 20px;
}

.form-group {
  margin: 15px 0;
  display: flex;
  align-items: center;
  flex-wrap: wrap;
  gap: 10px;
}

label {
  margin-right: 10px;
  font-weight: bold;
}

input {
  padding: 8px 12px;
  border: 1px solid #ddd;
  border-radius: 4px;
  flex-grow: 1;
}

button {
  background: #4b5eab;
  color: white;
  border: none;
  padding: 8px 16px;
  border-radius: 4px;
  cursor: pointer;
  transition: background 0.3s;
}

button:hover {
  background: #3a4a8c;
}

.highlight {
  font-weight: bold;
  color: #4b5eab;
}

.result-box {
  background: #f5f7ff;
  padding: 15px;
  border-radius: 4px;
  margin-top: 15px;
  border-left: 4px solid #4b5eab;
}

.progress-container {
  margin-top: 20px;
  background: #eee;
  border-radius: 4px;
  height: 20px;
  position: relative;
  overflow: hidden;
}

.progress-bar {
  height: 100%;
  background: #4b5eab;
  transition: width 0.2s;
}

.progress-container span {
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  text-align: center;
  line-height: 20px;
  color: white;
  font-size: 12px;
  text-shadow: 0 0 2px rgba(0, 0, 0, 0.5);
}

.calculator .form-group {
  display: flex;
  align-items: center;
  gap: 10px;
}

.calculator input {
  width: 80px;
}

.calculator .result {
  font-weight: bold;
  font-size: 18px;
}

@media (max-width: 600px) {
  .form-group {
    flex-direction: column;
    align-items: stretch;
  }

  input,
  button {
    width: 100%;
  }
}
</style>
