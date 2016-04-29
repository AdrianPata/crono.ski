#CRONO.SKI

**CRONO.SKI** is an electronic timing system for skiers which can be used by other athletes as well. It's main purpose is to assist the training.

##Basic idea

The trainer will set up a [**track**][1] for the athletes to go through as fast as they can, multiple times. All the results are stored for further investigation and are relevant for the training process.

The system will provide the capability to identify the athletes, mark the beginning and the end of the track and measure the time it took for each athlete to go between the two.

##Components
- [**CronoStart**](CronoStart/) is a mobile electronic device which is able to identify the athlete, measure the time and send the results (using GPRS) to a centralized database. It's based on Microchip microcontrollers.
- **CronoHub** is a cloud server which accepts connections from CronoStart devices. It's purpose is to control the virtual groups of CronoStart devices, send and receive messages from them, send informations abut the devices to the CronoWeb interface, receive commands for devices from CronoWeb.
- **CronoWeb** Is a user interface accessible anywhere in the world. It manages trainer accounts, athletes, virtual tracks and CronoStart devices. It centralizes all live and historic data about the tracks, locations and athletes performance.

##Security
The system is permanently connected to the Web and it must face it's threats. All the components will have encryption capabilities and will implement the strongest applicable security standards. 
* AES encryption in microcontrollers
* PBKDF2 and HMAC for key exchange between microcontrollers and TCP/IP server
* SSL for HTTP communications (web services)

![Crono.ski Overview][2]

[Overview link][2]

[1]:http://crono.ski/github_img/Ski%20track%20overview.png
[2]:http://crono.ski/github_img/Crono.ski%20Overview.png
