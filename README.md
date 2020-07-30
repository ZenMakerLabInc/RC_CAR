# RC_CAR
 Zen Maker Lab's RC Car Code.  Zenmakerlab zen makerlab
RCCAR

# Blynky App Setup
Step 0) Prepare your email to make a blynk account

Step 1) Download the Blynk app on your phone

Step 2) Open and creat an account

Step 3) Create a new project Project Name: "RCcar" Device: "Arduino Nano" Connection Type: "BLE"

Step 4) Click on the screen and drag on Joystick and BLE

Step 5) Click on the joystick and set output to merge, V1 [0] for 0 to 255 and [1] for 0 to 255

Step 6) Click the hex nut at the top and find the authorization code. Send it to your laptop, via email or some alternative method.

# Programming the Arduino
Step 7) Download and install the arduino IDE from here: https://www.arduino.cc/en/main/software

Step 8) Download the files from this repository

Step 9) Add the 'library' and 'tools' folders from the zip file into your arduino sketch library

Step 10) Replace the authorization code in the RC_Car.ino file with your authorization code. (** For Kevin, please use RC_Car_Kevin.ino **)

Step 11) Plug in arduino to your computer, set the port "COM3" or "COM6" and set the device to arduino nano. Then upload the new sketch to your ardunio.

# Connect to the RCCar by bluetooth
Step 12) Turn bluetooth on your phone and open the blynk app

Step 13) Open the RCcar project and select the BLE module. You will have to connect to the BLE device on your ardunio. Then hit the play button in the top right corner.

