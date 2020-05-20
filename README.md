Team Member Names: Neftali Hernandez
Link to Video: https://drive.google.com/drive/folders/1973qwscnXI_1nRSJYK5tpG41cBTdbW8G?usp=sharing

Instruction on Executing Video:
On Argon:
1. First need to download Virtual Studio code and install the Particle Workbench Extension to connect to Particle Argon device
2. Open up the folder with the rfid_....ino file.
3. Next we assemble device and get ready to cloud falsh by clicking Command+P and typing >Particle:Cloud Flash
4. We open up serial monitor on Virtual Studio Code by running Command+P and typing >Particle:Serial Monitor
5. Then we scan the RFID devices

On RPI:
1. I connected the RPI to monitor with keyboard and mouse and downloaded Particle agent
2. When all particle setup is done for RPI we can see our device on the Particle App
3. Open web browser and login to build.particle.io
4. Search for correct project name and flash code

I ended up Installing the MFRC522.h and MFRC522.cpp library to utilize this device on Argon code.
