# Main state machine for sunlight tracking for solar panel system. 
# This state machine has 8 states and uses multiple reference files in order 
# to operate. It also will print out which state it is in and at some points 
# print to which state is going. 
# Authors: Cameron Reynolds, Matthew Bradley, Benjamin Svetlov 
 
from Reference_Functions import * 
from Motor_Reference_Functions import * 
from WeatherData import * 
from TempHum_Thingspeak import * 
 
 
 
# Variables used 
case = 1  
EMERGENCY_flag = 0 
Sunrise_value = 7000 
init_14 = 0 
init_thirty = 0 
SR_timeAlert = 1 
SR_check = 0 
sunrise_time2 = "12:30" 
 
while True: 
# Case 1: Moves actuators to homing position, 0 position, and resets the emergency flag 
    if case == 1: 
        print("In state 1, Homing motors") 
        energizearms() #prime arms 
        homing_move() 
        EMERGENCY_flag = 0 
        case = 8 
    
# Case 2: Retrieves weather data needed for the day, sends temperature and humidity 
#    data to thingspeak website. Is the main comparison for time to start, stop, and 
#    checks for wifi connection.  
    if case == 2: 
        print("In state 2, Send data and retrieve weather info") 
        # Get weather varibales from WeatherData 
        wind_speed, sunrise, sunset, weather_alert = weather_data() 
        sunrise_time=sunrise.time().strftime('%H:%M') 
        sunset_time=sunset.time().strftime('%H:%M') 
        clock_time = time.strftime('%H:%M') 
        # Send data to be logged on ThingSpeak 
        Thingspeak_alert = WriteData() 
        print(sunrise_time, sunset_time, clock_time, Thingspeak_alert, weather_alert) 
         
        if EMERGENCY_flag == 1: 
            print("Move to case 8") 
            case = 8 
        else: 
            if Thingspeak_alert and (sunrise and sunset) == 0: 
                # LDR based case 
                print("Move to case 7") 
                case = 7 
            else:   
                if clock_time < sunrise_time or clock_time > sunset_time: 
                    sunrise_time_hour = int(sunrise.time().strftime('%H')) 
                    clock_time_hour = int(time.strftime('%H')) 
                    print(sunrise_time_hour, clock_time_hour,) 
                    if (sunrise_time_hour - clock_time_hour) == 1 or sunrise_time_hour == clock_time_hour: 
                        SR_timeAlert = 1 
                        print("Move to case 5") 
                        case = 5 
                    else: 
                        print("Move to case 8") 
                        case = 8 
                elif clock_time >= sunrise_time: 
                    # start comparing LDR's 
                    if weather_alert == 0: 
                        print("Move to case 6") 
                        case = 6 
                    elif clock_time >= sunrise_time2: 
                        SR_timeAlert = 0 
                        print("Move to case 3, after full sunrise") 
                        case = 3 
                    else: 
                        print("Move to case 3, before full sunrise") 
                        case = 3 
 
# Case 3: Calls function to check and compare LDR values for controlling motor 
#    movement.   
    if case == 3: 
        if SR_timeAlert == 1: 
            SR_check = Compare_LDR_Sunrise() 
            if SR_check == 1: 
                case = Compare_LDR() 
            else: case = 5 
        else: 
            print("In state 3, Compare LDR") 
            case = Compare_LDR() 
            print("Move to case {}".format(case)) 
         
# Case 4: Move all motors by a step count of 500.     
    if case == 4: 
        print("Motor movement") 
        energizearms() #prime arms 
        case = move_ALLmotors() 
         
# Case 5: Time wait for 14 minutes. 
    if case == 5: 
        print("Sleep state for 14 min") 
        if init_14 == 0: 
            hour_fourteen, min_fourteen = get_timeTest() 
            print("Time to compare for 14 min is {}:{}".format(hour_fourteen, min_fourteen)) 
            init_fourteen = 1 
        while True: 
            alert_fourteen = fourteen_check(hour_fourteen, min_fourteen) 
            if alert_fourteen == 1: 
                print("Alert, 14 minutes") 
                case = 2 
                init_fourteen = 0 
                break 
            elif alert_fourteen == 2:  
                case = 1 
                init_fourteen = 0 
                break 
  
# Case 6: Emergency move for actuators at a postion of 20000 
    if case == 6: 
        print("Emergency State") 
        # Move to middle position for a fixed amount of time.  
        energizearms() 
        if EMERGENCY_flag == 0: 
            emergency_move() 
            EMERGENCY_flag = 1 
            case = 5 
  
# Case 7: LDR based tracking and start and stop based on LDR values 
    if case == 7: 
        print("LDR based sunrise detection") 
        Left_side, Right_side, Middle_side = get_LDR() 
        if Middle_side < Sunrise_value: 
            case = 3 
        else: 
            case = 8 
  
# Case 8: Thirty minute time check. 
    if case == 8: 
        print("In case 8") 
        if init_thirty == 0: 
            hour_thirty, min_thirty = get_timeTest() 
            print("Time to compare for an hour is {}:{}".format(hour_thirty, min_thirty)) 
            init_thirty = 1 
        while True: 
            alert_thirty = thirty_check(hour_thirty, min_thirty) 
            if alert_thirty == 1: 
                print("Alert, 30 minutes") 
                case = 2 
                init_thirty = 0 
                break 
            elif alert_thirty == 2: 
                case = 1 
                init_thirty = 0 
                break 
             
             
