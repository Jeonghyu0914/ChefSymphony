// Function to initialize the Spotify Web Playback SDK
function initializeSpotifyPlayer(token, trackId, genre) {
  // Create a new Spotify player instance
  const player = new Spotify.Player({
    name: "Web Playback SDK Quick Start Player",
    getOAuthToken: (cb) => {
      cb(token);
    },
  });

  let deviceId = null;

  // Error handling
  player.addListener("initialization_error", ({ message }) =>
    console.error(message)
  );
  player.addListener("authentication_error", ({ message }) =>
    console.error(message)
  );
  player.addListener("account_error", ({ message }) => console.error(message));
  player.addListener("playback_error", ({ message }) => console.error(message));

  // Playback status updates
  player.addListener("player_state_changed", (state) => {
    console.log(state);
  });

  // Ready
  player.addListener("ready", ({ device_id }) => {
    console.log("Ready with Device ID", device_id);
    deviceId = device_id;
    document.getElementById("play-btn").disabled = false;
    document.getElementById("pause-btn").disabled = false;

    // Play the track
    playTrack(deviceId, trackId, token);
  });

  player.addListener("not_ready", ({ device_id }) => {
    console.log("Device ID has gone offline", device_id);
    document.getElementById("play-btn").disabled = true;
    document.getElementById("pause-btn").disabled = true;
  });

  // Connect to the player!
  player.connect();

  // Playback controls
  document.getElementById("play-btn").addEventListener("click", () => {
    player
      .resume()
      .then(() => {
        console.log("Playback resumed!");
      })
      .catch((e) => console.error(e));
  });

  document.getElementById("pause-btn").addEventListener("click", () => {
    player
      .pause()
      .then(() => {
        console.log("Playback paused!");
      })
      .catch((e) => console.error(e));
  });

  // Fetch track details
  async function fetchTrackDetails(accessToken, trackId) {
    const response = await fetch(
      `https://api.spotify.com/v1/tracks/${trackId}`,
      {
        headers: {
          Authorization: `Bearer ${accessToken}`,
        },
      }
    );
    const data = await response.json();
    document.getElementById("genre").textContent = genre;
    document.getElementById("track-title").textContent = data.name;
    document.getElementById("track-artist").textContent = data.artists
      .map((artist) => artist.name)
      .join(", ");
    document.getElementById("track-image").src = data.album.images[0].url;
    document.getElementById("track-link").href = data.external_urls.spotify;
  }

  // Initialize with data passed from Flask
  fetchTrackDetails(token, trackId);

  // Function to play a track
  function playTrack(deviceId, trackId, token) {
    fetch(`https://api.spotify.com/v1/me/player/play?device_id=${deviceId}`, {
      method: "PUT",
      body: JSON.stringify({ uris: [`spotify:track:${trackId}`] }),
      headers: {
        Authorization: `Bearer ${token}`,
        "Content-Type": "application/json",
      },
    })
      .then(() => {
        console.log("Track is playing");
      })
      .catch((e) => console.error(e));
  }

  // Fetch new track
  document
    .getElementById("new-track-btn")
    .addEventListener("click", async () => {
      document.getElementById("track-title").textContent = "Loading...";
      document.getElementById("track-artist").textContent = "";
      const response = await fetch("/new_track");
      const data = await response.json();
      trackId = data.track_id;
      genre = data.genre;
      document.getElementById("track-title").textContent = data.name;
      document.getElementById("track-artist").textContent = data.artists;
      document.getElementById("genre").textContent = genre;
      fetchTrackDetails(token, trackId);
      playTrack(deviceId, trackId, token);
    });
}
