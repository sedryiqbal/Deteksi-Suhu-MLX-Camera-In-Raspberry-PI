#Import Library OpenCV
import cv2
import telebot
from smbus2 import SMBus
from mlx90614 import MLX90614
 
bot = telebot.Telebot("5520071826:AAHC6JRQlGkVNjbL1JtLpfBtl0AAo5DW7PA")
ID_TELE = 626351605

#Variable untuk VideoCapture
cap = cv2.VideoCapture(0)
 
#Fungsi untuk membuat frame pengaturan pada video
while(True):
    #Membaca video
    bus = SMBus(1)
    sensor = MLX90614(bus, address=0x5A)
    ret, frame = cap.read()
    print ("suhu sekitar (ambient) :", sensor.get_ambient())
    print ("Suhu objek :", sensor.get_object_1())
    #Menampilkan video
    cv2.imshow('frame',frame)
    
    if (sensor.get_object_1() > 37):
        cv2.imwrite ( 'capture.png' , frame )
        bot.send_photo(ID_TELE, open('foto.jpg',temp))
        bot.send_message(ID_TELE, "Suhu tidak Aman")
        
    #Pengaturan frame
    if cv2.waitKey(1) == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
