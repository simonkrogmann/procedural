# This script downloads the textures I used for the examples.
# Feel free to replace them.

import urllib.request

images = {
    'capitol_reef.jpg': 'https://unsplash.com/photos/QuRc5m4cBOs/download',
    'bryce_canyon.jpg': 'https://unsplash.com/photos/_-y3WUSFrrQ/download',
}

for name, url in images.items():
    urllib.request.urlretrieve(url, name)
