
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

post_put_data = api.model('POST/PUT_DATA',
{
    'cnic' : fields.String,
    'temperature' : fields.String,
    'humidity' : fields.String,
    'led_status' : fields.String,
    'btn_status' : fields.String,
})

updateLedStatus = api.model('UpdateLedStatus',
{
    'led_status' : fields.String,
    'cnic' : fields.String,
})
deleteUser = api.model('DeleteUserDate',
{
    'cnic' : fields.String,
})

@api.route('/send_data')
class send_data(Resource):

    @api.expect(post_put_data)
    def post(self):
        mysql_query = """ INSERT into room1(temperature,humidity,led_status,btn_status,user_cnic) VALUES (%s,%s,%s,%s,%s)"""
        bindData = (api.payload['temperature'],api.payload['humidity'],api.payload['led_status'],api.payload['btn_status'],api.payload['cnic'])
        connection = connectWithDb()
        cursor = connection.cursor()
        cursor.execute(mysql_query,bindData)
        connection.commit()
       
        return {"Data inserted successfully ": api.payload['temperature']}
    
    @api.expect(post_put_data)
    def put(self):
        mysql_query = """ UPDATE room1 SET temperature = %s , humidity = %s, led_status = %s , btn_status = %s WHERE user_cnic = %s """
        bindData = (api.payload['temperature'],api.payload['humidity'],api.payload['led_status'], api.payload['btn_status'], api.payload['cnic'])
        con = connectWithDb()
        cursor = con.cursor()
        cursor.execute(mysql_query,bindData)
        con.commit()
        return {"Data updated successfully ": api.payload['temperature']}
    @api.expect(updateLedStatus)
    def patch(self):
        mysql_query = """ UPDATE room1 SET led_status = %s WHERE user_cnic = %s """
        bindData  = (api.payload['led_status'], api.payload['cnic'])
        con = connectWithDb()
        cursor  = con.cursor()
        cursor.execute(mysql_query,bindData)
        con.commit()
        return{"Led status updated " : api.payload['led_status']}
    @api.expect(deleteUser)
    def delete(self):
        mysql_query = """ DELETE FROM room1 WHERE user_cnic = %s """
        bindData  = (api.payload['cnic'])
        con = connectWithDb()
        cursor  = con.cursor()
        cursor.execute(mysql_query,(bindData,))  # mysql.connector.errors.ProgrammingError: Could not process parameters: str(3540173791210), it must be of type list, tuple or dict
        con.commit()
        return{"Led status updated " : api.payload['cnic']}

if __name__ == '__main__':
    app.run(debug=True, port=5000, host='0.0.0.0')
    