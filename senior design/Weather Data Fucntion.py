# This file contains functions for retrieving data from the website 
# openweathermap.org. Using information from it is used in main function 
# to determine different operations. 
# Authors:  Cameron Reynolds, Matthew Bradley, Benjamin Svetlov 
 
import time 
import requests 
from pprint import pprint 
from datetime import datetime 
 
def weather_data(): 
    settings = { 
        'api_key':'56b989a109c1350ccdd345e54bba4465', 
        'zip_code':'28801', 
        'country_code':'us', 
        'temp_unit':'imperial'} #unit can be metric, imperial, or kelvin 
 
    BASE_URL = "http://api.openweathermap.org/data/2.5/weather?appid={0}&zip={1},{2}&units={3}" 
 
    final_url = BASE_URL.format(settings["api_key"],settings["zip_code"],settings["country_code"],settings["temp_unit"]) 
    weather_data = requests.get(final_url).json() 
    if weather_data['cod'] != 200: 
        return 0, 0, 0, 0 
    #pprint(weather_data) 
    for i in range(len(weather_data["weather"])): 
        weather_descr = weather_data["weather"][i]["description"] 
        weather_main = weather_data["weather"][i]["main"] 
    print(weather_main, weather_descr) 
    weather_alert = weather_check(weather_main, weather_descr) 
    wind_speed = weather_data["wind"]["speed"] 
    wind_angle = weather_data["wind"]["deg"] 
    sunrise = datetime.fromtimestamp(weather_data["sys"]["sunrise"]) 
    sunset = datetime.fromtimestamp(weather_data["sys"]["sunset"]) 
    #print("The wind_speed is {} MPH at {} degrees.".format(wind_speed, wind_angle)) 
    #print("Sunrise is at {} and sunset is at {}.".format(sunrise, sunset)) 
    return wind_speed, sunrise, sunset, weather_alert 
 
 
def weather_check(weather_main, weather_descr): 
    if weather_main == 'Clear': 
        print("Its clear sky") 
        return 1 
    if weather_main == 'Rain' or weather_main == 'Thunderstorm' or weather_main == 'Snow': 
        print("Its raining") 
        return 0 
    elif weather_main == 'Clouds' and weather_descr == 'overcast clouds' or weather_descr =='broken clouds': 
        print("Its cloudy") 
        return 0 
    else: 
        print("Everything else weather") 
        return 1
