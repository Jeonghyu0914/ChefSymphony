import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

#Firebase database 인증 및 앱 초기화
cred = credentials.Certificate('/Users/hugh/Documents/GitHub/-CookIoT/SKKU Making Hackerton/firebaseKey.json')
firebase_admin.initialize_app(cred,{
    'databaseURL' : 'https://cookiot-test-default-rtdb.firebaseio.com/' 
})

ref = db.reference() #db 위치 지정, 기본 가장 상단을 가르킴
ref.update({'이름' : '김철수'}) #해당 변수가 없으면 생성한다.
