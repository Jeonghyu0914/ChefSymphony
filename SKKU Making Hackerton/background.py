import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import spotipy
from spotipy.oauth2 import SpotifyClientCredentials
import pandas as pd

client_id = 'f1482fea7e5843668f71fcd44165a9d7'
client_secret = '7ff48d3345304e22be48473760f0fbfc'

# Spotify API authorization
client_credentials_manager = SpotifyClientCredentials(client_id=client_id, client_secret=client_secret)
sp = spotipy.Spotify(client_credentials_manager=client_credentials_manager)

# Firebase database authorization
cred = credentials.Certificate('/Users/hugh/Documents/GitHub/-CookIoT/SKKU Making Hackerton/firebaseKey.json')
firebase_admin.initialize_app(cred,{
    'databaseURL' : 'https://cookiot-test-default-rtdb.firebaseio.com/' 
})

artist_name =[]
track_name = []
track_popularity =[]
artist_id =[]
track_id =[]
for i in range(0,1000,50):
    track_results = sp.search(q='year:2021', type='track', limit=50, offset=i)
    for i, t in enumerate(track_results['tracks']['items']):
        artist_name.append(t['artists'][0]['name'])
        artist_id.append(t['artists'][0]['id'])
        track_name.append(t['name'])
        track_id.append(t['id'])
        track_popularity.append(t['popularity'])

track_df = pd.DataFrame({'artist_name' : artist_name, 'track_name' : track_name, 'track_id' : track_id, 'track_popularity' : track_popularity, 'artist_id' : artist_id})

artist_popularity = []
artist_genres = []
artist_followers =[]
for a_id in track_df.artist_id:
    artist = sp.artist(a_id)
    artist_popularity.append(artist['popularity'])
    artist_genres.append(artist['genres'])
    artist_followers.append(artist['followers']['total'])

print(artist_genres[0])

ref = db.reference() #db 위치 지정, 기본 가장 상단을 가르킴
ref.update({'이름' : '김철수'}) #해당 변수가 없으면 생성한다.
