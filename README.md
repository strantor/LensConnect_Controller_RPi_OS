This is a version of Computar LensConnect Python scripts which has been made to run on Raspberry Pi. It is tested
and working as of 1/13/2024 on Raspberry Pi 4B running the latest version (fully updated/upgraded) of RPi OS 64 
bit (Debian GNU/Linux 12 (bookworm)).

The python files are from the LensConnect_SampleProgram_Python_x64_1.0.0 on the computar global website 
(https://www.computar-global.com/product-detail/file-confidential/LensConnect_SampleProgram_Python_x64_1.0.0.zip)
but the precompiled binary drivers (libslab***.so.1.o and such) which are part of that download have been deleted in
this repo because those files don't just "work" as computar seems to expect because (1) they have dependencies 
that are not stated anywhere in any documentation whatsoever, and (2) they are just locally stored and locally 
imported in the script rather than properly installed and registered in the OS with appropriate permissions, so 
Linux will not allow you to import them. It gives "file not found" errors which are misleading because clearly 
the files are RIGHT THERE and the scripts point right to them. What the errors really mean is "file not allowed 
to be opened." 

The Python files in this repo have been very slightly modified so that they no longer illegally point to the local 
precompiled binaries (ex: "./libslabhiddevice.so.1.0") but instead to binaries that have been properly installed 
in the os (ex: "/usr/local/lib/libslabhiddevice.so.1.0"). 
But of course these won't exist if you haven't installed them yet, so the C sample project 
(https://www.computar-global.com/product-detail/file-confidential/LensConnect_SampleProgram_Linux_C_x86_x64_1.0.0.zip) 
which contains the source of the binaries is also included (LensConnect_SampleProgram_Linux_C_x86_x64_1.0.0 folder) 
only for the purpose of compliling and installing the binaries. But they won't compile without the dependencies, so
after downloading this repo do the following:

1. sudo apt-get install libusb-1.0-0-dev
2. sudo apt-get install g++
3. sudo apt-get install libudev1
4. sudo apt-get install libudev-dev
5. Go to the following location:
LensConnect_SampleProgram_Linux_C_x86_x64_1.0.0/LensConnect_Controller/CP2112/srcpkg/slabhiddevice
and run the following commands:
sudo make
sudo make install
6. go to the following folder:
LensConnect_SampleProgram_Linux_C_x86_x64_1.0.0/LensConnect_Controller/CP2112/srcpkg/slabhidtosmbus
and run the following commands:
sudo make
sudo make install

Now in usr/local/lib you should see the following files:
libslabhiddevice.so      libslabhidtosmbus.so      
libslabhiddevice.so.1    libslabhidtosmbus.so.1
libslabhiddevice.so.1.0  libslabhidtosmbus.so.1.0

7. go to:
LensConnect_SampleProgram_Linux_C_x86_x64_1.0.0/LensConnect_Controller/CP2112/srcpkg/slabhidtosmbus/doc
and run:
sudo cp SiliconLabs.rules /etc/udev/rules.d
sudo reboot

Now the python scripts should work.