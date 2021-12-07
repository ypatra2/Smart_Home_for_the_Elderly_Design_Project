# Smart Home for the Elderly Design Project
A Smart Home designed to cater to the needs of the Elderly by enabling Home Automation and ensuring Home Security using Arduino Mega 2560


# Summary
This project aims to foster a safe, secure and comfortable lifestyle for senior citizens. According to a survey conducted in America by AARP (American Association of Retired Persons), over 90% of senior citizens would prefer to stay in their homes most of the time. Keeping this thought in mind, we have created an integrated Smart Home system to cater to the miscellaneous needs of the elderly.  We have implemented home security with the aid of RFID for system authorisation and WiFi module to send UID and timestamp data to ThingSpeak. We have executed home safety with the help of an alarm system and also used an e-paper to display and edit reminders. Moving on, we also developed a mobile app to promote safety and comfortable living. The app has one screen that can control light and fan via bluetooth, and once they’re turned on, they are automated and regulated by ambient light and temperature respectively.  Other features of the app are temperature data monitoring, location tracking and emergency call.  This integrated smart home system can meet miscellaneous needs of the elderly. 

# Introduction
By 2050, Hong Kong is forecasted by the World Health Organization to rank fifth in the world for cities with the largest percentage of older adults. Roughly one in four people will be over 65 by then. Moreover, most of these old people live alone or with their old partners. To accommodate this large number of people, we need ageing in place: letting old people grow old at the place they live instead of moving to old people care homes. These old people with reduced mobility to do mundane chores, susceptible to malicious thieves and dealing with dementia or Alzheimer need an all-in-one home system that can make their life significantly easier. Moreover, this demographic is slow to adopt new and complicated technology. Thus, it is important to design a system which is easy to use and needs minimal involvement of the users.
 To achieve that, our project makes use of IoT and automation to build smart homes catered to old people. The system implements the use of secure home access, automated fan and lights, emergency location tracking and SOS system, ultrasonic proximity sensor for extreme heat and electric sources and an editable reminder system for medicinal and appointment reminders. All these combined ensure security and ease of life for the golden years of the seniors. Secure access to homes can be achieved with the use of unique RFID tags in the form of keychains or as a chip in bracelets, alarms can be set to go off if unauthorized access is initiated, bluetooth and sensors have been used to control fan and light and a display system which shows reminders and is  visible throughout the day even without power.
The location tracking system uses Google Firebase to track longitude and latitude of the user with the help of GPS tracker implemented in wearable devices such as a wristband. This helps caretakers or family members locate old people who leave home and get lost due to forgetfulness. The SOS system enables one tap call to contact during emergencies. All of these features ensure ease of use, security and safety of old individuals.

# Objectives

1. Provide a safe, comfortable and convenient living space for the elderly
2. Enable Home Automation using Bluetooth and Wi-Fi
3. Enhance Home Security using RFID and Wi-Fi
4. Create a self-sustainable system using IoT with minimal human intervention that solves problems faced by the elderly
5. Implementing an Energy-Efficient system that fosters Sustainable Development

# Function Specification

* Implement RFID Technology for authenticating access to a ‘Home Safe’ and home access. <br />
* Automate fan speed control using readings from temperature sensor. 	<br />
* Automate light intensity of lamp using  light sensor readings of ambient light.<br />
* Use of Bluetooth app to remotely turn on or off room lamps and fans.<br />
* Send temperature data to the Cloud using the Wi-Fi module. <br />
* Implement an alert system with  ultrasonic distance module and buzzer to caution the user from items of danger.<br />
* Implement an editable reminder system and display important reminders on E-paper throughout the day.<br />
* Display sensitive and crucial information on OLED such as bank balance, credit card number etc when tapping the RFID reader with an authorized tag.<br />
* Generate timestamps of user entry to home  and unauthorized attempted entry.<br />
* Implement Geolocation Tracking and SOS system with the aid of a phone app.<br />


# Hardware Design:

<img width="550" alt="image" src="https://user-images.githubusercontent.com/86041798/145038694-8333a4c3-5ad9-4c27-af6c-316d7cc3bcd7.png">
<img width="601" alt="image" src="https://user-images.githubusercontent.com/86041798/145038643-c3d7a314-b705-4df2-8efc-a6a030e7ec33.png">
<img width="519" alt="image" src="https://user-images.githubusercontent.com/86041798/145038801-9d70e3d6-ffaa-41c7-87cd-17410517f308.png">
<img width="641" alt="image" src="https://user-images.githubusercontent.com/86041798/145039200-e37590bf-135a-43d2-b3f7-89851f4dc8aa.png">
<img width="532" alt="image" src="https://user-images.githubusercontent.com/86041798/145039379-45bf8b89-0b08-4510-aa8f-a6d748760e02.png">
<img width="532" alt="image" src="https://user-images.githubusercontent.com/86041798/145039440-55180e9f-1861-47d4-b594-45f798d20e64.png">
<img width="599" alt="image" src="https://user-images.githubusercontent.com/86041798/145039628-0078dc31-8909-44c6-bddf-521adab06ab9.png">

# Flowchart
<img width="640" alt="image" src="https://user-images.githubusercontent.com/86041798/145039785-f5df7335-46ab-47ba-8c54-2f1d9f5c1e52.png">

According to the flowchart shown above, the Arduino program first reads the temperature data using the LM-35 temperature sensor. This value is temporarily stored in a global variable and is used for sending the temperature reading shortly afterwards. After this, if condition statements continuously monitor if an RFID tag is getting tapped on the PCD in the loop() function. The program has a preprogrammed RFID UID should be allowed to enter the house and access the database when its tag is tapped on the PCD. If an RFID tag is detected by the MFRC522 RFID Reader, it stores the UID of the tapped RFID tag in the form of a string and checks if it matches with the preprogrammed authorized string. If a match does not occur then the string “Unknown: Unauthorized” is set as the parameter of the ThingSpeak RFID field (setField function). If a match occurs then the name of the user, for instance, “Yuvraj: Authorized User” is set as the parameter of the ThingSpeak RFID Field (setField function). Serial Communication is used by the Arduino to communicate with the RFID Reader and the Wi-Fi module. Arduino uses the Wi-Fi module to connect to an access point after which it is connected to the internet. The Arduino has been programmed to send sensor data to the ThingSpeak cloud in two possible cases. First, the Arduino sends the Temperature reading (previously stored in a global variable) using the ThingSpeak.writeField() function every minute and the program keeps a track of the time elapsed using the millis() function. Arduino sends the temperature data and a string “No RFID” to ThingSpeak indicating that no RFID tag was tapped on the reader at the time. The Temperature data is continuously displayed on the OLED as long as no RFID is tapped on the Reader. The second case occurs when the RFID tag is tapped on the Reader. If a tag is detected, the program verifies if the UID is authorized. If the user is authorized, the buzzer makes a single beep sound and the sensitive information of the user is displayed on the OLED Screen. After this, the name of the user along with the temperature reading is sent to ThingSpeak. However, if the UID does not match with the preprogrammed UID, the Arduino understands that an unauthorized break-in attempt is being made. An alarm is triggered with the buzzer to alert the elderly person and the temperature data along with the string “Unknown: Unauthorized” is sent to ThingSpeak.The data received by ThingSpeak is used and processed using MATLAB. MATLAB Visualization is used to create an hourly temperature monitoring plot of the data that is also sent to the Android App that we have designed using the MIT App Inventor. MATLAB Application is designed for the MATLAB Analysis. Using the strings of the tapped RFID information sent to ThingSpeak, a timetable is created that helps view the approximate timestamp at which the Unauthorized break-in attempt was made. 

<img width="432" alt="image" src="https://user-images.githubusercontent.com/86041798/145040086-a49f7d61-8f5e-4559-9281-5d8e80d83ec4.png">
<img width="432" alt="image" src="https://user-images.githubusercontent.com/86041798/145040182-9948d958-a113-490c-a5fd-e8ec430e8a74.png">
<img width="640" alt="image" src="https://user-images.githubusercontent.com/86041798/145040296-209c5fc9-a102-4e4d-8110-2ef997e38552.png">


# Android App for the Elderly <br />
The App for the Smart Home is designed using MIT App Inventor with features such as temperature monitoring using ThingSpeak and MATLAB Visualization, Remote Bluetooth Control of lights and fans of the room using HC-05 Bluetooth Module, Realtime Location Tracking (connected to Google Firebase Realtime Database) and Emergency Calling with a Phone Client.

<img width="592" alt="image" src="https://user-images.githubusercontent.com/86041798/145040377-97a00bdb-a7e3-4491-9de1-1d9de89dbc00.png">
<img width="426" alt="image" src="https://user-images.githubusercontent.com/86041798/145040449-2211a0ff-0c62-4823-b094-b6da32afe61e.png">
<img width="371" alt="image" src="https://user-images.githubusercontent.com/86041798/145040502-5e88e6fe-82cb-4422-bd38-af78ffb1e3fb.png">
<img width="291" alt="image" src="https://user-images.githubusercontent.com/86041798/145040642-405616cd-ceb7-44b1-9dfd-694b9dd7329c.png">

# **Energy Efficiency using LDR Sensor and Temperature Sensor** <br />
Arduino has been programmed to automate the speed of the fan and brightness of the lights based on the temperature of the room and ambient light of the room respectively which makes the solution energy efficient. The LED lamp and the Fan are controlled using a driver board each with appropriate connections to the PCB used for the Arduino Mega and the Arduino Micro.

# **Alert and Alaram System** <br />
The alert system is implemented to ensure that the elderly do not get injured by objects of danger nearby, like a fireplace, stove, edge of balcony etc. The ultrasonic distance module(HC-SR04) continuously monitors the distance using echolocation. A high pulse of width 10 microsecond is transmitted via the trig pin, then the module will emit 8 square wave pulses of 40kHz and detect if an echo signal has been received. When received, echo pin outputs a square pulse whose width is equal to the time taken by the emitted pulse to transmit and come back. The distance is then calculated with the equation: 𝐷𝑖𝑠𝑡𝑎𝑛𝑐𝑒=𝑡×340𝑚/s×0.5. 
