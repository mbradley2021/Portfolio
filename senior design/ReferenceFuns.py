# This file contains reference functions use to main to retrieve certain data, 
# compare LDR values, multiple motor moves, and timing functions. 
# Authors:  Cameron Reynolds, Matthew Bradley, Benjamin Svetlov 
 
import time 
from datetime import datetime 
import adafruit_dht #get_temp 
import board #get_temp, get_LDR 
import busio #get_LDR 
import digitalio #get_LDR 
import adafruit_mcp3xxx.mcp3008 as MCP #get_LDR 
from adafruit_mcp3xxx.analog_in import AnalogIn #get_LDR 
from TempHum_Thingspeak import * 
from Motor_Reference_Functions import * 
 
 
spi = busio.SPI(clock=board.SCK, MISO=board.MISO, MOSI=board.MOSI) 
cs = digitalio.DigitalInOut(board.D4) 
mcp = MCP.MCP3008(spi, cs) 
 
#_________________________________________________________________ 
#Temperature reading function 
dht = adafruit_dht.DHT22(board.D26) 
def get_temp(): 
    temp_C = dht.temperature 
    temp_F = temp_C * (9 / 5) + 32 
    return temp_F 
 
#_________________________________________________________________ 
#LDR reading function 
def get_LDR(): 
    Left_side = AnalogIn(mcp, MCP.P0) 
    Middle_side = AnalogIn(mcp, MCP.P1) 
    Right_side = AnalogIn(mcp, MCP.P2) 
    return Left_side.value, Right_side.value, Middle_side.value 
 
#__________________________________________________________________ 
# Function for getting LDR values, comparing them, and returns the next case 
# to go into for the state machine.  
Cloud_cover = 5500 
Sunset_value = 9000 
Sunrise_value = 7000 
tolerance = 50 
 
def Compare_LDR(): 
    Left, Right, Third_eye = get_LDR() 
    print("Left is {}, Right is {}, Middle is {}".format(Left, Right, Third_eye)) 
    average = (Left + Right) / 2 
    WriteData_LDR(average, Third_eye) 
     
    if Third_eye > Sunset_value: 
        return 8 
    #elif (Third_eye > Cloud_cover) and (Third_eye < Sunset_value): 
        #return 6 
    elif (average - Third_eye) >= tolerance: 
        print("Third eye is less than Left and Right, move motors") 
        time.sleep(5) 
        return 4 
    elif (average - Third_eye) < tolerance: 
        print("Third eye is equal to average of Left and Right") 
        time.sleep(5) 
         
        return 5 
 
#___________________________________________________________________ 
# 
def Compare_LDR_Sunrise(): 
    Left, Right, Third_eye = get_LDR() 
    print("Before sunrise Left is {}, Right is {}, Middle is {}".format(Left, Right, Third_eye)) 
    average = (Left + Right) / 2 
    #WriteData_LDR(average, Third_eye) 
    if (average - Third_eye) < 200: 
        return 1 
    else: return 0 
     
#___________________________________________________________________ 
# Time reading function.  
def get_timeTest(): 
    now = datetime.now() 
    minute = int(now.strftime("%M")) 
    hour = int(now.strftime("%H")) 
    return hour, minute 
 
#____________________________________________________________________ 
# Funciton for moving all the motors by a step count of 500 
final_position = 21000 
step_count = 500 
step_count7 = 600 
moving_time = 10 
def move_ALLmotors(): 
    position7 = posarms7() 
    WriteData_ActPos(position7) 
    if position7 >= final_position: 
        case = 8 
    else: 
        # Move actuator 7 
        print (" Arm 7 position is: ", position7) 
        arm7move(position7 + step_count7) 
        print("Arm 7 new posistion is: ", (position7 + step_count7)) 
        time.sleep(moving_time) 
         
        # Move actuator 1 
        position1 = posarms1() 
        print (" Arm 1 position is: ", position1) 
        arm1move(position1 + step_count) 
        print("Arm 1 new posistion is: ", (position1 + step_count)) 
        time.sleep(moving_time) 
         
        # Move actuator 0 
        position0 = posarms0() 
        print (" Arm 0 position is: ", position0) 
        arm0move(position0 + step_count) 
        print("Arm 0 new posistion is: ", (position0 + step_count)) 
        time.sleep(moving_time) 
         
        case = 3 
     
    return case 
 
#___________________________________________________________________ 
# Function for the emergency move of actuators. 
Homing_time = 125 
Emergency_time = Homing_time / 2 
Emergency_target = 20000 
def emergency_move(): 
    arm7move(11000) 
    time.sleep(Emergency_time) 
    arm1move(11500) 
    time.sleep(Emergency_time) 
    arm0move(11500) 
    time.sleep(Emergency_time) 
    return 
 
#___________________________________________________________________ 
# Function for honming move of actuators. 
def homing_move(): 
    arm7move(0) 
    time.sleep(Homing_time) 
    arm1move(0) 
    time.sleep(Homing_time) 
    arm0move(0) 
    time.sleep(Homing_time) 
    return 
            
#______________________________________________________________________ 
# Function for checking when 14 minutes has passed based on initial time. 
def fourteen_check(hour1, min1): 
    hour2, min2 = get_timeTest() 
    if hour2 - hour1 == 1: 
        if min1 - min2 == 45: 
            return 1 
    elif hour1 - hour2 == 23: 
        if min1 - min2 == 45: 
            return 2    
    elif hour2 - hour1 == 0: 
        if min2 - min1 == 14: 
            return 1 
    else: 
        return 0 
 
#______________________________________________________________________ 
# Function for checking when 30 minutes has passed based on initial time.  
def thirty_check(hour1, min1): 
    hour2, min2 = get_timeTest() 
    if hour2 - hour1 == 1: 
        if min1 - min2 == 30: 
            return 1 
    elif hour1 - hour2 == 23: 
        if min1 - min2 == 30: 
            return 2 
    elif hour2 - hour1 == 0: 
        if min2 - min1 == 30: 
            return 1 
    else: return 0 
