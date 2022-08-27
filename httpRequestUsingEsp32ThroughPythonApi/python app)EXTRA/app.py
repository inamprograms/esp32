
from flask import Flask
from flask_restx import Resource, Api, fields
import mysql.connector

app = Flask(__name__)
api = Api(app)


def connectionWithDb():
    connection = mysql.connector.connect(host='localhost',
                                         database='esp_data',
                                         user='root',
                                         password='')
    return connection


post_data= api.model('MYDATA',
{
    'temperature': fields.String,
    'humidity': fields.String,
    'led_status': fields.String,
    'btn_status': fields.String,
    'cnic': fields.String,
})
put_data= api.model('MYDATA_TO_UPDATE',
{
    'temperature': fields.String,
    'humidity': fields.String,
    'led_status': fields.String,
    'btn_status': fields.String,
    'cnic': fields.String,
})

# updateTemperature= api.model('UpdateTemp',
# {
#     'cnic' : fields.String,
#     'temperature' :  fields.String
# })

# updateHumidity = api.model('UpdateHumidity',
# {
#     'cnic' : fields.String,
#     'humidity' : fields.String,
# })
# updateLedStatus = api.model('UpdateLedStatus',
# {
#     'cnic' : fields.String,
#     'led_status' : fields.String,
# })

updateBtnStatus = api.model('UpdateBtnStatus',
{
    'cnic' : fields.String,
    'btn_status' : fields.String,
})




@api.route('/get_data/<string:cnic>') #<string:cnic>
class HelloWorld(Resource):
    def get(self,cnic):
        mysql_query = """ SELECT * from room1 WHERE cnic = %s"""
        # bindData = api.payload['cnic']
        con = connectionWithDb()
        cursor = con.cursor(dictionary = True) #dictionary = true
        cursor.execute(mysql_query,(cnic,))
        record = cursor.fetchall()
        # dict = record
        dict = record[0]
        # print(record)
        return {'Temperature ' : dict['temperature']}
    


@api.route('/send_data')
class send_data_class(Resource):
    @api.expect(post_data)
    def post(self):

        mysql_query = """ INSERT into room1(temperature,humidity,led_status,btn_status,user_cnic) VALUES (%s,%s,%s,%s,%s) """
        bindata = (api.payload['temperature'],api.payload['humidity'],api.payload['led_status'],api.payload['btn_status'],api.payload['cnic'])
        connection_01 = connectionWithDb()
        cursor = connection_01.cursor()
        cursor.execute(mysql_query, bindata)
        connection_01.commit()
        return {'this is temperature value ': api.payload['temperature']}

    @api.expect(put_data)
    def put(self):
        mysql_query = """ UPDATE room1 SET temperature = %s , humidity = %s, led_status = %s , btn_status = %s WHERE cnic = %s """
        bindData = (api.payload['temperature'],api.payload['humidity'],api.payload['led_status'], api.payload['btn_status'], api.payload['cnic'])
        con = connectionWithDb()
        cursor = con.cursor()
        cursor.execute(mysql_query,bindData)
        con.commit()
        return {"Data updated successfully ": api.payload['temperature']}

    # @api.expect(updateTemperature)
    def patch(self):
        mysql_query = """ UPDATE room1 SET temperature = %s WHERE cnic = %s """
        bindData = (api.payload['temperature'], api.payload['cnic'])
        con = connectionWithDb()
        cursor = con.cursor()
        cursor.execute(mysql_query,bindData)
        con.commit()
        return{"Temperature updated " : api.payload['temperature']}

    # @api.expect(updateHumidity)
    def patch(self):
        mysql_query = """ UPDATE room1 SET humidity = %s WHERE cnic = %s """
        bindData  = (api.payload['humidity'], api.payload['cnic'])
        con = connectionWithDb()
        cursor  = con.cursor()
        cursor.execute(mysql_query,bindData)
        con.commit()
        return{"Huidity updated " : api.payload['humidity']}
    
    # @api.expect(updateLedStatus)
    def patch(self):
        mysql_query = """ UPDATE room1 SET led_status = %s WHERE cnic = %s """
        bindData  = (api.payload['led_status'], api.payload['cnic'])
        con = connectionWithDb()
        cursor  = con.cursor()
        cursor.execute(mysql_query,bindData)
        con.commit()
        return{"Led status updated " : api.payload['led_status']}

    @api.expect(updateBtnStatus)
    def patch(self):
        mysql_query = """ UPDATE room1 SET btn_status = %s WHERE cnic = %s """
        bindData  = (api.payload['btn_status'], api.payload['cnic'])
        con = connectionWithDb()
        cursor  = con.cursor()
        cursor.execute(mysql_query,bindData)
        con.commit()
        return{"Button status updated " : api.payload['btn_status']}


if __name__ == '__main__':
    app.run(debug=True, port=5000, host='0.0.0.0')
    
