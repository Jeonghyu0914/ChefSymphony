import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report
from joblib import dump

# 데이터 생성
np.random.seed(42)

n_samples = 1000

# 여름 데이터 생성
summer_temp = np.random.uniform(25, 35, n_samples)
summer_humidity = np.random.uniform(60, 90, n_samples)
summer = np.column_stack((summer_temp, summer_humidity))

# 겨울 데이터 생성
winter_temp = np.random.uniform(-10, 5, n_samples)
winter_humidity = np.random.uniform(10, 40, n_samples)
winter = np.column_stack((winter_temp, winter_humidity))

# 평온 데이터 생성
mild_temp = np.random.uniform(10, 20, n_samples)
mild_humidity = np.random.uniform(40, 60, n_samples)
mild = np.column_stack((mild_temp, mild_humidity))

# 비 데이터 생성
rain_temp = np.random.uniform(15, 25, n_samples)
rain_humidity = np.random.uniform(70, 100, n_samples)
rain = np.column_stack((rain_temp, rain_humidity))

# 데이터 합치기
X = np.vstack((summer, winter, mild, rain))
y = np.array([0]*n_samples + [1]*n_samples + [2]*n_samples + [3]*n_samples)  # 0: 여름, 1: 겨울, 2: 평온, 3: 비

# 데이터프레임으로 변환
data = pd.DataFrame(X, columns=['Temperature', 'Humidity'])
data['Season'] = y

# 학습 데이터와 테스트 데이터로 분리
X_train, X_test, y_train, y_test = train_test_split(data[['Temperature', 'Humidity']], data['Season'], test_size=0.2, random_state=42)

# 하이퍼파라미터 그리드 설정
param_grid = {
    'n_estimators': [50, 100, 200],
    'max_depth': [None, 10, 20, 30],
    'min_samples_split': [2, 5, 10],
    'min_samples_leaf': [1, 2, 4]
}

# Grid Search 설정
grid_search = GridSearchCV(estimator=RandomForestClassifier(random_state=42), param_grid=param_grid, cv=3, n_jobs=-1, verbose=2)
grid_search.fit(X_train, y_train)

# 최적 하이퍼파라미터로 모델 학습
best_model = grid_search.best_estimator_

# 모델 저장
dump(best_model, 'optimized_season_classifier_model.joblib')

# 예측 및 결과 출력
y_pred = best_model.predict(X_test)
print(classification_report(y_test, y_pred, target_names=['Summer', 'Winter', 'Mild', 'Rain']))

# 최적 하이퍼파라미터 출력
print("Best Hyperparameters:", grid_search.best_params_)
