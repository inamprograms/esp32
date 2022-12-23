
import sys
import mysql.connector
from PyQt6.QtWidgets import QApplication, QWidget,QPushButton,QGridLayout,QLineEdit,QLabel



def connectWithDb():
    connection = mysql.connector.connect(host = 'localhost',
                                        database = 'esp_data',
                                        user='root',
                                        password = '' ) 
    return connection

def get(cnic):
        mysql_query = """ SELECT * FROM room1 WHERE cnic = %s """
        connection = connectWithDb()
       
        cursor = connection.cursor(dictionary=True)
        cursor.execute(mysql_query,(cnic,))
        record = cursor.fetchall()
        for row in record:
           return {"buttonStatus":row['button_status']}

def patch(led_status,cnic,button):
        mysql_query = """ UPDATE room1 SET led_status = %s, button_status = %s WHERE cnic = %s """
        data = (led_status,button,cnic)
        con = connectWithDb()
        cursor  = con.cursor(dictionary=True)
        cursor.execute(mysql_query,data)
        con.commit()
        return{"Led status updated " : led_status}

def button1_post_clicked():



    cnic = line.text()
    button_status = get(cnic)
    button = button_status['buttonStatus']
    if(button == 0):
       led_status = 0
       button = 1
       patch(led_status,cnic,button)
       post_data.setText("CLICK/OFF")
    elif(button == 1):
        led_status = 1
        button = 0
        patch(led_status,cnic,button)
        post_data.setText("CLICK/ON")
    else:
        print("value is expected 1 or 0")
  
    



# def button2_put_clicked():
#     print("Hello World put me")

app = QApplication(sys.argv)

window = QWidget()

post_data = QPushButton(window)
post_data.setText("CLICK")
post_data.move(64,32)
post_data.clicked.connect(button1_post_clicked)
# put_data =QPushButton(window)
# put_data.setText("PUT")
# put_data.move(64,64)
# put_data.clicked.connect(button2_put_clicked)


cnicLabel = QLabel()
cnicLabel.setText('Enter Your CNIC:')
line = QLineEdit()
line.move(80, 20)
line.resize(200, 32)
cnicLabel.move(20, 20)

layout = QGridLayout()
layout.addWidget(cnicLabel,0,0)
layout.addWidget(line,0,1)
layout.addWidget(post_data,0,2)
# layout.addWidget(put_data,0,1)

window.setLayout(layout)

window.show() 


   
app.exec()

sys.exit(app.exec_())





