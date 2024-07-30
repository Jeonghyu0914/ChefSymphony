# app.py
from flask import Flask, request, jsonify, render_template

app = Flask(__name__)

# 데이터 변수
data = {"message": "Hello from Python!"}

@app.route('/')
def index():
    return render_template('testIndex.html')

@app.route('/button_click', methods=['POST'])
def button_click():
    # 버튼 클릭을 인식하는 로직
    print("Button clicked")
    return jsonify({"status": "Button clicked successfully"})

@app.route('/get_data', methods=['GET'])
def get_data():
    # Python 데이터를 웹으로 보내는 로직
    return jsonify(data)

if __name__ == '__main__':
    app.run(debug=True)
