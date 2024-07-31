import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report
from joblib import dump

# 데이터 생성
np.random.seed(42)

n_samples = 1000

# 카페, 레스토랑 데이터 생성
cafe_rest_noise = np.random.uniform(25, 35, n_samples)
cafe_rest_brightness = np.random.uniform(60, 90, n_samples)
cafe_rest = np.column_stack((cafe_rest_noise, cafe_rest_brightness))

# 바 데이터 생성
bar_noise = np.random.uniform(-10, 5, n_samples)
bar_brightness = np.random.uniform(10, 40, n_samples)
bar = np.column_stack((bar_noise, bar_brightness))

# 술집 데이터 생성
pub_noise = np.random.uniform(10, 20, n_samples)
pub_brightness = np.random.uniform(40, 60, n_samples)
pub = np.column_stack((pub_noise, pub_brightness))

# 클럽 데이터 생성
club_noise = np.random.uniform(15, 25, n_samples)
club_brightness = np.random.uniform(70, 100, n_samples)
club = np.column_stack((club_noise, club_brightness))

# 데이터 합치기
X = np.vstack((cafe_rest, bar, pub, club))
y = np.array([0]*n_samples + [1]*n_samples + [2]*n_samples + [3]*n_samples)  # 0: 여름, 1: 겨울, 2: 평온, 3: 비

# 데이터프레임으로 변환
data = pd.DataFrame(X, columns=['noiseerature', 'brightness'])
data['Atmosphere'] = y

# 학습 데이터와 테스트 데이터로 분리
X_train, X_test, y_train, y_test = train_test_split(data[['noiseerature', 'brightness']], data['Atmosphere'], test_size=0.2, random_state=42)

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
dump(best_model, 'optimized_Atmosphere_classifier_model.joblib')

# 예측 및 결과 출력
y_pred = best_model.predict(X_test)
print(classification_report(y_test, y_pred, target_names=['cafe_rest', 'bar', 'pub', 'club']))

# 최적 하이퍼파라미터 출력
print("Best Hyperparameters:", grid_search.best_params_)
