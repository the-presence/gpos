# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
#SET(CMAKE_C_COMPILER   /opt/alertme/nano1/usr/bin/arm-buildroot-linux-uclibcgnueabi-gcc)
#SET(CMAKE_CXX_COMPILER /opt/alertme/nano1/usr/bin/arm-buildroot-linux-uclibcgnueabi-g++)

# where is the target environment
#SET(CMAKE_FIND_ROOT_PATH  /opt/alertme/nano1/usr /opt/alertme/nano1/usr/arm-buildroot-linux-uclibcgnueabi)


# specify the cross compiler (temporary fix)
SET(CMAKE_C_COMPILER   /usr/local/nano1/usr/bin/arm-buildroot-linux-uclibcgnueabi-gcc)
SET(CMAKE_CXX_COMPILER /usr/local/nano1/usr/bin/arm-buildroot-linux-uclibcgnueabi-g++)

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH  /usr/local/nano1/usr /usr/local/nano1/usr/arm-buildroot-linux-uclibcgnueabi)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)