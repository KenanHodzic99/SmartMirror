# -*- coding: utf-8 -*-
import tkinter as tk
from tkinter import font
import time
import urllib.request
import json
from threading import Thread
from PIL import Image, ImageTk
import serial
import io

class Window(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)               
        self.master = master

def update_timeText():
    current = time.strftime("%H:%M")
    seconds = time.strftime(":%S")
    currentDate=time.strftime("%a %e %B, %Y")

    brojPodataka = 2
    arduinoDataList = [0]*brojPodataka
    
    for i in range(0,brojPodataka):
        arduinoData = str(ser.readline())
        if arduinoData[2:5]=='100':
            arduinoDataList[i]='100'
        else:
            if(i==3):
                arduinoDataList[i] = arduinoData[2:8]
            else:            
                arduinoDataList[i] = arduinoData[2:4]

    homeTemperature = arduinoDataList[0] + '°C'
    homeHumidity = arduinoDataList[1] + '%'

    homeTemperatureIcon = ImageTk.PhotoImage(Image.open("/home/pi/Desktop/weatherIcons/HomeTemperature.png"))
    homeHumidityIcon = ImageTk.PhotoImage(Image.open("/home/pi/Desktop/weatherIcons/HomeHumidity.png"))

    timeText1.configure(text=current, fg='white', background='black')
    timeText1.grid(row=0,column=0, sticky='NW', padx=15, pady=15)

    timeText2.configure(text=seconds, fg='white', background='black')
    timeText2.grid(row=0, column=1, pady=25, sticky='NW')

    Date.configure(text=currentDate, fg='white', background='black')
    Date.grid(row=0, column=0, columnspan=3, sticky='NW', padx=20, pady=140, rowspan=2)

    arduinoTemp.configure(image=homeTemperatureIcon, text=homeTemperature, fg='white', background='black')
    arduinoTemp.image = homeTemperatureIcon
    arduinoTemp.grid(row=0, column=4, sticky='NE', padx=(0,325), pady=175)

    arduinoHumi.configure(image=homeHumidityIcon, text=homeHumidity, fg='white', background='black')
    arduinoHumi.image = homeHumidityIcon
    arduinoHumi.grid(row=0, column=4, sticky='NE', padx=(0,220), pady=175)
    
    root.after(1000, update_timeText)

def update_Weather():
    temperatureData = weatherData["main"]["temp"]
    temperature = " " + str(int(temperatureData)) + "°C"

    maxTemperatureData = weatherData["main"]["temp_max"]
    minTemperatureData = weatherData["main"]["temp_min"]
    humidityData = weatherData["main"]["humidity"]
    windSpeedData = weatherData["wind"]["speed"]

    humidity = " " + str(int(humidityData)) + "%"
    windSpeed = " " + str(int(windSpeedData)) + " m/h"
    
    weather = weatherData["weather"]
    nestedList = weather[0]
    iconPictureCode =  nestedList["icon"]
    iconPicPath = "/home/pi/Desktop/weatherIcons/"+iconPictureCode+".png"

    iconPicture = ImageTk.PhotoImage(Image.open(iconPicPath))
    windIcon = ImageTk.PhotoImage(Image.open("/home/pi/Desktop/weatherIcons/wind.png"))
    humidityIcon = ImageTk.PhotoImage(Image.open("/home/pi/Desktop/weatherIcons/humidity.png"))

    weatherTemperatureIcon.configure(image=iconPicture,text=temperature, fg='white', background='black' )
    weatherTemperatureIcon.image = iconPicture
    weatherTemperatureIcon.grid(row=0, column=4, sticky='NE', padx=(420,232), pady=15)

    weatherWindSpeed.configure(image=windIcon, text=windSpeed, fg='white', background='black')
    weatherWindSpeed.image = windIcon
    weatherWindSpeed.grid(row=0, column=4, sticky='NE', padx=(0,325), pady=125)

    weatherHumidity.configure(image=humidityIcon, text=humidity, fg='white', background='black')
    weatherHumidity.image = humidityIcon
    weatherHumidity.grid(row=0, column=4, sticky='NE', padx=(0,225), pady=125)

    root.after(150000, update_Weather)

root = tk.Tk()
w = root.winfo_screenwidth()
h = root.winfo_screenheight()
root.geometry("%dx%d+0+0"%(w,h))
root.overrideredirect(1)
root.configure(background='black')
root.title('Smart Mirror')
root.grid_columnconfigure(1, minsize=100)
root.grid_columnconfigure(0, minsize=275)

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.1)

arduinoTemp = tk.Label(root, text="", font=("Roboto Condensed", 15), image="", compound=tk.LEFT)
arduinoHumi = tk.Label(root, text="", font=("Roboto Condensed", 15), image="", compound=tk.LEFT)

timeText1 = tk.Label(root, text="", font=("Opinio", 70, "bold"))
timeText2 = tk.Label(root, text="", font=("Opinio", 35, "bold"))
Date=tk.Label(root, text="", font=("Roboto Condensed", 18))

weatherAPI=urllib.request.urlopen("https://api.openweathermap.org/data/2.5/weather?q=Mostar,070&APPID=d9c3aca43db397f6c24189c7c52948f9&units=metric")
weatherResponse=weatherAPI.read().decode("utf-8")
weatherData=json.loads(weatherResponse)

weatherTemperatureIcon=tk.Label(root, text="", font=("Roboto Condensed", 76), image="", compound=tk.LEFT)
weatherWindSpeed=tk.Label(root, text="", font=("Roboto Condensed", 15), image="", compound=tk.LEFT)
weatherHumidity=tk.Label(root, text="", font=("Roboto Condensed", 15), image="", compound=tk.LEFT)

Thread(target=update_Weather).start()
Thread(target=update_timeText).start()

app = Window(root)
root.mainloop()