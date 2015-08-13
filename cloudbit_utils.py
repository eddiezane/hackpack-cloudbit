import requests
import os

device_id = os.environ.get('DEVICE_ID')
auth_token = os.environ.get('LITTLEBITS_AUTH_TOKEN')

cloudbit_url = 'https://api-http.littlebitscloud.cc/devices/' + device_id + \
               '/output'

char_map = {
    'a': 3,
    'b': 6,
    'c': 9,
    'd': 12,
    'e': 15,
    'f': 18,
    'g': 21,
    'h': 24,
    'i': 27,
    'j': 30,
    'k': 33,
    'l': 36,
    'm': 39,
    'n': 42,
    'o': 45,
    'p': 48,
    'q': 51,
    'r': 54,
    's': 57,
    't': 60,
    'u': 63,
    'v': 66,
    'w': 69,
    'x': 72,
    'y': 75,
    'z': 78,
    ' ': 81,
    '.': 84,
    '!': 87,
    '?': 90,
    'EOC': 93,  # End of Character value
    'EOF': 96  # End of String value
}


def send_message(message):

    for index, char in enumerate(message.lower()):
        post_data = {'percent': char_map[char], 'duration_ms': -1}
        r = requests.post(cloudbit_url, data=post_data,
                          headers={'Authorization': 'Bearer ' + auth_token})
        import time
        time.sleep(1)
        print "Request sent: " + r.text

        if index == len(message) - 1:
            post_data = {'percent': char_map['EOF'], 'duration_ms': -1}
        else:
            post_data = {'percent': char_map['EOC'], 'duration_ms': -1}

        r = requests.post(cloudbit_url, data=post_data,
                          headers={'Authorization': 'Bearer ' + auth_token})
        print "Request sent: " + r.text
