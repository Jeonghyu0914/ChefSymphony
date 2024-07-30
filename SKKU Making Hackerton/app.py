import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import spotipy
from spotipy.oauth2 import SpotifyClientCredentials, SpotifyOAuth
import pandas as pd
import time
import random
import os
from flask import Flask, render_template, request, redirect, session, url_for, jsonify
from flask_cors import CORS
import requests
import genres

client_id = 'f1482fea7e5843668f71fcd44165a9d7'
client_secret = '7ff48d3345304e22be48473760f0fbfc'
redirect_uri = 'http://localhost:8000/callback'

# Spotify OAuth setup
sp_oauth = SpotifyOAuth(client_id, client_secret, redirect_uri, scope='user-read-private user-read-email user-read-playback-state user-modify-playback-state streaming')

# Spotify API authorization
client_credentials_manager = SpotifyClientCredentials(client_id=client_id, client_secret=client_secret)
sp = spotipy.Spotify(client_credentials_manager=client_credentials_manager)

# Firebase database authorization
# cred = credentials.Certificate('/Users/hugh/Documents/GitHub/-CookIoT/SKKU Making Hackerton/firebaseKey.json')
# firebase_admin.initialize_app(cred,{
#     'databaseURL' : 'https://cookiot-test-default-rtdb.firebaseio.com/' 
# }, name = f'{time.time()}')

def get_tracks_by_genre(sp, genre):
    track_ids = []
    """Fetch a list of tracks for the given genre."""
    for i in range(0,1000,50):
        results = sp.search(q=f'genre:"{genre}"', market="KR", type='track', limit=50, offset=i)
        for i, t in enumerate(results['tracks']['items']):
            track_ids.append(t['id'])
    return track_ids

genre = genres.get_genre()[random.randint(0, len(genres.get_genre())-1)]
print(genre)
track_ids = get_tracks_by_genre(sp, genre)
print(len(track_ids))

app = Flask(__name__)
CORS(app)

auth_url = sp_oauth.get_authorize_url()

@app.route('/')
def index():
    auth_url = sp_oauth.get_authorize_url()
    return redirect(auth_url)

@app.route('/callback')
def callback():
    code = request.args.get('code')
    token_info = sp_oauth.get_access_token(code)
    access_token = token_info['access_token']
    print(access_token)

    track_id = track_ids[random.randint(0, len(track_ids)-1)]
    return render_template('index.html', access_token=access_token, track_id=track_id)

@app.route('/new_track')
def new_track():
    track_id = track_ids[random.randint(0, len(track_ids)-1)]
    return jsonify({'track_id': track_id})

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8000, debug=True)