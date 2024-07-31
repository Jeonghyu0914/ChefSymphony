from joblib import load
import pandas as pd
import genres
import random

def predGenre(temp, humid, noise, bright):
    model1 = load('AI/optimized_Atmosphere_classifier_model.joblib')
    model2 = load('AI/optimized_season_classifier_model.joblib')

    atmo_data = pd.DataFrame([[noise, bright]], columns=['noise', 'brightness'])
    season_data = pd.DataFrame([[temp, humid]], columns=['Temperature', 'Humidity'])

    atmo_pred = model1.predict(atmo_data)
    season_pred = model2.predict(season_data)

    atmo_dict = {0: 'cafe-rest', 1: 'bar', 2: 'pub', 3: 'club'}
    season_dict = {0: 'Summer', 1: 'Winter', 2: 'Mild', 3: 'Rain'}

    atmo = atmo_dict[atmo_pred[0]]
    season = season_dict[season_pred[0]]

    sel_genres = []
    # 예측값에 따른 장르 분류
    
    sel_genres.append(genres.get_genre()[76]) # pop
    sel_genres.append(genres.get_genre()[59]) # k-pop

    if(atmo == "cafe-rest"):
        if(season == "Summer"):
            sel_genres.append(genres.get_genre()[0])
            sel_genres.append(genres.get_genre()[51])
            sel_genres.append(genres.get_genre()[18])
            sel_genres.append(genres.get_genre()[49])
            sel_genres.append(genres.get_genre()[105])
        elif(season == "Winter"):
            sel_genres.append(genres.get_genre()[11])
            sel_genres.append(genres.get_genre()[58])
            sel_genres.append(genres.get_genre()[8])
            sel_genres.append(genres.get_genre()[84])
            sel_genres.append(genres.get_genre()[8])
            sel_genres.append(genres.get_genre()[75])           
        elif(season == "Mild"):
            sel_genres.append(genres.get_genre()[0])
            sel_genres.append(genres.get_genre()[27])
            sel_genres.append(genres.get_genre()[9])
            sel_genres.append(genres.get_genre()[11])
            sel_genres.append(genres.get_genre()[28])
            sel_genres.append(genres.get_genre()[111])  
        elif(season == "Rain"):
            sel_genres.append(genres.get_genre()[85])
            sel_genres.append(genres.get_genre()[93])       
            sel_genres.append(genres.get_genre()[8])
            sel_genres.append(genres.get_genre()[37])    
            sel_genres.append(genres.get_genre()[51])
            sel_genres.append(genres.get_genre()[50])
            sel_genres.append(genres.get_genre()[101])
    elif(atmo == "bar"):
        sel_genres.append(genres.get_genre()[11])
        sel_genres.append(genres.get_genre()[58])
        if(season == "Summer"):
            sel_genres.append(genres.get_genre()[47])
            sel_genres.append(genres.get_genre()[19])       
            sel_genres.append(genres.get_genre()[61])  
        elif(season == "Winter"):
            sel_genres.append(genres.get_genre()[8])  
            sel_genres.append(genres.get_genre()[101])  
            sel_genres.append(genres.get_genre()[26])  
            sel_genres.append(genres.get_genre()[44])  
        elif(season == "Rain"):
            sel_genres.append(genres.get_genre()[85])
            sel_genres.append(genres.get_genre()[93])       
            sel_genres.append(genres.get_genre()[8])
            sel_genres.append(genres.get_genre()[37])    
            sel_genres.append(genres.get_genre()[51])
            sel_genres.append(genres.get_genre()[50])
            sel_genres.append(genres.get_genre()[101])
    elif(atmo == "pub"):
        sel_genres.append(genres.get_genre()[14])  
        sel_genres.append(genres.get_genre()[44])  
        sel_genres.append(genres.get_genre()[73])  
        sel_genres.append(genres.get_genre()[89])  
    elif(atmo == "club"):
        sel_genres.append(genres.get_genre()[80])  
        sel_genres.append(genres.get_genre()[26])  
        sel_genres.append(genres.get_genre()[26])  
        sel_genres.append(genres.get_genre()[26])  
        sel_genres.append(genres.get_genre()[14])  

    genre = sel_genres[random.randint(0, len(sel_genres)-1)]
    print(atmo, season)
    return genre
