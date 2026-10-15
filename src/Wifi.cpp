#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Motor.h"
#include "Config.h"

ESP8266WebServer server(80);

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="vi">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>Điều Khiển Xe Wi-Fi</title>
  <style>
    * { box-sizing: border-box; touch-action: manipulation; user-select: none; }
    body {
      font-family: 'Segoe UI', Roboto, sans-serif;
      background: #121212;
      color: #ffffff;
      margin: 0;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      min-height: 100vh;
    }
    h2 { margin-bottom: 20px; color: #00e676; letter-spacing: 1px; }
    .status-panel {
      background: #1e1e1e;
      padding: 10px 20px;
      border-radius: 20px;
      margin-bottom: 30px;
      font-size: 14px;
      border: 1px solid #333;
    }
    .status-panel span { font-weight: bold; color: #ff9800; }
    .control-pad {
      display: grid;
      grid-template-columns: repeat(3, 90px);
      grid-template-rows: repeat(3, 90px);
      gap: 15px;
      justify-content: center;
    }
    .btn {
      background: #2a2a2a;
      border: 2px solid #333;
      border-radius: 18px;
      color: #fff;
      font-size: 24px;
      display: flex;
      align-items: center;
      justify-content: center;
      cursor: pointer;
      box-shadow: 0 4px 10px rgba(0,0,0,0.5);
      transition: all 0.1s ease;
    }
    .btn:active, .btn.active {
      background: #00e676;
      color: #000;
      box-shadow: 0 0 15px #00e676;
      transform: scale(0.95);
    }
    .btn-stop { background: #d32f2f; border-color: #f44336; }
    .btn-stop:active, .btn-stop.active {
      background: #ff5252;
      color: #fff;
      box-shadow: 0 0 15px #ff5252;
    }
    .up { grid-column: 2; grid-row: 1; }
    .left { grid-column: 1; grid-row: 2; }
    .stop { grid-column: 2; grid-row: 2; }
    .right { grid-column: 3; grid-row: 2; }
    .down { grid-column: 2; grid-row: 3; }
  </style>
</head>
<body>
  <h2>XE ĐIỀU KHIỂN WI-FI</h2>
  <div class="status-panel">
    Trạng thái: <span id="status">DỪNG</span>
  </div>
  <div class="control-pad">
    <button class="btn up" id="btn-tien" onmousedown="send('tien')" onmouseup="send('dung')" ontouchstart="send('tien')" ontouchend="send('dung')">▲</button>
    <button class="btn left" id="btn-trai" onmousedown="send('trai')" onmouseup="send('dung')" ontouchstart="send('trai')" ontouchend="send('dung')">◄</button>
    <button class="btn btn-stop stop" id="btn-dung" onclick="send('dung')">■</button>
    <button class="btn right" id="btn-phai" onmousedown="send('phai')" onmouseup="send('dung')" ontouchstart="send('phai')" ontouchend="send('dung')">►</button>
    <button class="btn down" id="btn-lui" onmousedown="send('lui')" onmouseup="send('dung')" ontouchstart="send('lui')" ontouchend="send('dung')">▼</button>
  </div>
  <script>
    let lastCmd = '';
    const statusText = document.getElementById('status');

    function send(cmd) {
      if (lastCmd === cmd && cmd !== 'dung') return;
      lastCmd = cmd;
      const labels = { 'tien': 'TIẾN', 'lui': 'LÙI', 'trai': 'RẼ TRÁI', 'phai': 'RẼ PHẢI', 'dung': 'DỪNG' };
      statusText.innerText = labels[cmd] || 'DỪNG';
      statusText.style.color = (cmd === 'dung') ? '#ff9800' : '#00e676';
      fetch('/' + cmd).catch(err => console.log('Lỗi gửi lệnh:', err));
    }

    const keyMap = {
      'ArrowUp': 'tien', 'w': 'tien', 'W': 'tien',
      'ArrowDown': 'lui', 's': 'lui', 'S': 'lui',
      'ArrowLeft': 'trai', 'a': 'trai', 'A': 'trai',
      'ArrowRight': 'phai', 'd': 'phai', 'D': 'phai',
      ' ': 'dung'
    };

    document.addEventListener('keydown', (e) => {
      if (keyMap[e.key]) {
        send(keyMap[e.key]);
        const btn = document.getElementById('btn-' + keyMap[e.key]);
        if (btn) btn.classList.add('active');
      }
    });

    document.addEventListener('keyup', (e) => {
      if (keyMap[e.key] && keyMap[e.key] !== 'dung') {
        send('dung');
        const btn = document.getElementById('btn-' + keyMap[e.key]);
        if (btn) btn.classList.remove('active');
      }
    });
  </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void handleTien() {
  motorForward(MOTOR_SPEED);
  server.send(200, "text/plain", "Tien");
}

void handleLui() {
  motorBackward(MOTOR_SPEED);
  server.send(200, "text/plain", "Lui");
}

void handleTrai() {
  motorLeft(MOTOR_SPEED);
  server.send(200, "text/plain", "Trai");
}

void handlePhai() {
  motorRight(MOTOR_SPEED);
  server.send(200, "text/plain", "Phai");
}

void handleDung() {
  motorStop();
  server.send(200, "text/plain", "Dung");
}

void wifiInit() {
  Serial.print("Configuring access point...");
  if (!WiFi.softAP(WIFI, PASSWORD)) {
    Serial.println(" failed");
    return;
  }

  Serial.println(" ready");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/tien", handleTien);
  server.on("/lui", handleLui);
  server.on("/trai", handleTrai);
  server.on("/phai", handlePhai);
  server.on("/dung", handleDung);
  server.begin();
  Serial.println("HTTP server started");
}

void wifiHandleClient() {
  server.handleClient();
}
