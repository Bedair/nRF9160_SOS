cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(SOS)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/IoHwAbs_LED.c)
target_sources(app PRIVATE src/IoHwAbs_Switch.c)
target_sources(app PRIVATE src/App_GNSS.c)
target_sources(app PRIVATE src/App_SMS.c)
target_sources(app PRIVATE src/App_Modem.c)
