cmake_minimum_required(VERSION 3.2)
AUX_SOURCE_DIRECTORY(. THRE_SRC)
SET(THREDIS thRedis)

ADD_EXECUTABLE(${THREDIS} example.c)

#INCLUDE_DIRECTORIES(hiredis/)

TARGET_LINK_LIBRARIES(${THREDIS} libhiredis.a)


ADD_CUSTOM_COMMAND(TARGET ${THREDIS}
	PRE_BUILD
	COMMAND cd hiredis && make
#	COMMAND cp hiredis/libhiredis.a . 
)







