# Compiler và cờ biên dịch
CC = gcc
CFLAGS = -I./common -Wall
LDFLAGS = -lpaho-mqtt3c

# Tên file nguồn và file thực thi
SRC = main1.c
OBJ = mqtt_client.o
EXEC = main1

# Quy tắc tạo file thực thi
$(EXEC): $(SRC) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Quy tắc tạo file .o từ mqtt_client.c
mqtt_client.o: common/mqtt_client.c common/mqtt_client.h
	$(CC) $(CFLAGS) -c $< -o $@

# Quy tắc dọn dẹp
clean:
	rm -f $(OBJ) $(EXEC)