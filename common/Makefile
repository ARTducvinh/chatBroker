# Compiler và cờ biên dịch
CC = gcc
CFLAGS = -c -I.

# Tên file nguồn và file đối tượng
SRC = mqtt_client.c
OBJ = mqtt_client.o

# Quy tắc tạo file .o
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

# Quy tắc dọn dẹp
clean:
	rm -f $(OBJ)