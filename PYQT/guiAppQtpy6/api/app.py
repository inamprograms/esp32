
from flask import Flask
from flask_restx import Api,fields,Resource
import mysql.connector

app = Flask(__name__)
api = Api(app)

def connectWithDb():
    connection = mysql.connector.connect(host = 'localhost',
                                        database = 'esp_data',
                                        user='root',
                                        password = '' ) 

    return connection



updateLedStatus = api.model('UpdateLedStatus',
{
    'led_status' : fields.String,
    'button_status' : fields.String,
    'cnic' : fields.String,
})


@api.route('/send_data')
class send_data(Resource):
    @api.expect(updateLedStatus)
    def patch(self):
        mysql_query = """ UPDATE room1 SET led_status = %s, button_status = %s WHERE cnic = %s """
        bindData  = (api.payload['led_status'],api.payload['button_status'], api.payload['cnic'])
        con = connectWithDb()
        cursor  = con.cursor()
        cursor.execute(mysql_query,bindData)
        con.commit()
        return{"Led status updated " : api.payload['led_status']}


@api.route('/retrieve_data/<string:cnic>')
class receive_data(Resource):
    def get(self,cnic):
        mysql_query = """ SELECT * FROM room1 WHERE cnic = %s """
        connection = connectWithDb()
        cursor = connection.cursor(dictionary=True)
        cursor.execute(mysql_query,(cnic,))
        record = cursor.fetchall()
        for row in record:
           return {"buttonStatus":row['button_status']}
    
if __name__ == '__main__':
    app.run(debug=True, port=5000, host='0.0.0.0')
    