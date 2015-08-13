from flask import Flask, request
from twilio.twiml import Response

app = Flask(__name__)


@app.route('/sms', methods=['POST'])
def sms_reply():
    message_body = request.form['Body']
    print message_body

    res = Response()
    res.message('Thanks for texting our HackPack! After a bit of '
                'rendering, your message should scroll by on our display '
                'shortly :) To find out how to do stuff this on your own '
                'check out: http://twilio.com')

    return str(res)

if __name__ == '__main__':
    app.run(host='0.0.0.0')
