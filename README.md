# alarma-humo-esp8266

Código de prototipo de proyecto IoT para un esp8266 que recibe temperatura de
un sensor DHT22 y activa una alarma si sobrepasa cierta temperatura


## Instalación

1. Descargar las librerías que falten.

2. Configurar datos de red (SSID, contraseña).

3. Subir código al ESP8266.

## Funcionamiento

El circuito del esp se conecta al sensor DHT22 y una luz led que indica la alarma.

Al iniciar el ESP8266, este encenderá el led incorporado y el led de la alarma juntos como señal de que está intentando conectarse a la red WiFi. Una vez conectado, se apagarán ambas luces.

El ESP abrirá un servidor web en el que enviará la temperatura leída y un booleano indicando si se activó la alarma.

La temperatura de alarma esta hardcodeada como 23°C dentro de `loop()` y `handleroot()`.
