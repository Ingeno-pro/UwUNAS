# UwUNAS
An open source NAS project 

# Requierements 

----blkid  

sudo apt install util-linux

for installing with source code : 
sudo apt install libblkid-dev

----bcm2835lib 

install instruction here : https://www.airspayce.com/mikem/bcm2835/


----qemu

For emulate a raspberry pi, please use 
qemu-system-aarch64 -M raspi3b C:\path\to\your\image.img
Here is a tutorial to make a raspberry pi img: https://www.youtube.com/watch?v=DSv9bDkPzsw
to resize : qemu-img resize <imagefile> <new-size>