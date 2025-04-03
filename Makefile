# Compiler và cờ biên dịch
CC = gcc
CFLAGS = -I./common -Wall
LDFLAGS = -lpaho-mqtt3c

# Tên file nguồn và file thực thi
SRC1 = main1.c
SRC2 = main2.c
OBJ = ./common/mqtt_client.o
EXEC1 = main1
EXEC2 = main2

# Quy tắc mặc định: tạo cả main1 và main2
all: $(EXEC1) $(EXEC2)

# Quy tắc tạo file thực thi cho main1
$(EXEC1): $(SRC1) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Quy tắc tạo file thực thi cho main2
$(EXEC2): $(SRC2) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Quy tắc tạo file .o từ mqtt_client.c
$(OBJ): ./common/mqtt_client.c ./common/mqtt_client.h
	$(CC) $(CFLAGS) -c $< -o $@

# Quy tắc dọn dẹp
clean:
	rm -f $(OBJ) $(EXEC1) $(EXEC2)