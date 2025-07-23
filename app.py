import eventlet
eventlet.monkey_patch()

from flask import Flask, render_template, request, jsonify
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app, cors_allowed_origins="*")

press_count = 0

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/press", methods=["POST"])
def register_press():
    global press_count
    press_count += 1
    socketio.emit("update_count", {"count": press_count})
    return jsonify({"message": "Button press registered", "total": press_count})

@app.route("/reset", methods=["POST"])
def reset_counter():
    global press_count
    press_count = 0
    print(press_count)
    socketio.emit("update_count", {"count": press_count})
    return jsonify({"message": "Counter reset"})

@app.route("/count", methods=["GET"])
def get_count():
    return jsonify({"total_presses": press_count})

if __name__ == "__main__":
    socketio.run(app, host="0.0.0.0", port=8000)
