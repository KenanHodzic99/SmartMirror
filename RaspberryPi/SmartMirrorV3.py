import tkinter
import io
from tkinter import font
import tkinter as tk
import time
import urllib.request
import json
import socket
from threading import Thread
import base64
import png

socket.getaddrinfo('localhost', 8080)


class Window(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)               
        self.master = master

def update_timeText():
    current = time.strftime("%H:%M")
    seconds = time.strftime(":%S")
    currentDate=time.strftime("%a %e %B, %Y")
    timeText1.configure(text=current, fg='white', background='black')
    timeText1.grid(row=0,column=0, sticky='NW', padx=15, pady=15)
    timeText2.configure(text=seconds, fg='white', background='black')
    timeText2.grid(row=0, column=1, pady=17, sticky='NW')
    Date.configure(text=currentDate, fg='white', background='black')
    Date.grid(row=0, column=0, columnspan=3, sticky='NW', padx=20, pady=124, rowspan=2)
    root.after(1000, update_timeText)

def update_Weather():
    temperatureData = weatherData["main"]["temp"]
    temperature = int(temperatureData) , "°C"
    weather = weatherData["weather"]
    List1 = weather[0]
    pictureCode = List1["icon"]
    picUrl = "http://openweathermap.org/img/w/"+pictureCode+".png"
    print(picUrl)
    pictureData = urllib.request.urlopen(picUrl).read()
    pictureB64 = base64.encodebytes(pictureData)
    picture = tk.PhotoImage(data=pictureB64)
    weatherIcon.configure(image=picture)
    weatherIcon.grid(row=3)
    weatherTemperature.configure(text=temperature, fg='white', background='black')
    weatherTemperature.grid(row=3, column=2)
    root.after(100000, update_Weather)

root = tk.Tk()
root.configure(background='black')
root.title('Smart Mirror')
timeText1 = tk.Label(root, text="", font=("Opinio", 90, "bold"))
timeText2 = tk.Label(root, text="", font=("Opinio", 45, "bold"))
Date=tk.Label(root, text="", font=("Roboto Condensed", 24))
weatherAPI=urllib.request.urlopen("https://api.openweathermap.org/data/2.5/weather?q=Mostar,070&APPID=d9c3aca43db397f6c24189c7c52948f9&units=metric")
weatherData=json.load(weatherAPI)
weatherTemperature=tk.Label(root, text="", font=("Roboto Condensed", 24))
weatherIcon=tk.Label(root, image="")
Thread(target=update_Weather).start()
Thread(target=update_timeText).start()
app = Window(root)
root.mainloop()
