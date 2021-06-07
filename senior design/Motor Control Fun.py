# This file contains the individual functions for retrieving motor 
# position and moving each motor. Uses USB connection and terminal 
# to communicate with motor driver boards. 
# Authors: Cameron Reynolds, Matthew Bradley, Benjamin Svetlov 
import subprocess 
import yaml 
import time 
 
def ticcmd(*args): 
  return subprocess.check_output(['ticcmd'] + list(args)) 
 
def arm1move(target): 
    ticcmd('-d','00332201','--position', str(target)) 
 
def arm0move(target): 
    ticcmd('-d','00332200','--position', str(target)) 
 
def arm7move(target): 
    ticcmd('-d','00332207','--position', str(target)) 
 
def energizearms(): 
    ticcmd('-d','00332207','--exit-safe-start','--energize')# Start motors 
    ticcmd('-d','00332200','--exit-safe-start','--energize') 
    ticcmd('-d','00332201','--exit-safe-start','--energize') 
     
 
def posarms0(): 
    status = yaml.load(ticcmd('-d','00332200','-s','--full')) 
    position = status['Current position'] 
    return position  
 
def posarms1(): 
    status = yaml.load(ticcmd('-d','00332201','-s','--full')) 
    position = status['Current position'] 
    return position  
 
def posarms7(): 
    status = yaml.load(ticcmd('-d','00332207','-s','--full')) 
    position = status['Current position'] 
    return position 
 
def allpos(): 
    status = yaml.load(ticcmd('-d','00332200','-s','--full')) 
    position0 = status("Current position") 
     
    status = yaml.load(ticcmd('-d','00332201','-s','--full')) 
    position1 = status("Current position") 
     
    status = yaml.load(ticcmd('-d','00332207','-s','--full')) 
    position7 = status("Current position") 
 
    return  position0,position1,position7 
