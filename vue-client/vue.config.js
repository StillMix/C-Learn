const { defineConfig } = require("@vue/cli-service");
module.exports = defineConfig({
  transpileDependencies: true,
});

module.exports = {
  // Базовый путь для собранного приложения
  publicPath: process.env.NODE_ENV === "production" ? "./" : "/",

  // Настройки для разработки
  devServer: {
    port: 8080,
    // Разрешаем доступ с любого IP (важно для тестирования на устройствах в сети)
    host: "0.0.0.0",
    // Другие настройки разработки
    headers: {
      "Access-Control-Allow-Origin": "*",
    },
  },
};
