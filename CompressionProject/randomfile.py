import os
import string
import random

file_size = 1024 * 1024  # 10MB in bytes
file_name = "random.txt"

with open(file_name, "w") as f:
    while os.path.getsize(file_name) < file_size:
        random_string = ''.join(random.choices(string.ascii_letters + string.digits, k=1024))
        f.write(random_string)

print(f"File '{file_name}' created with a size of {os.path.getsize(file_name)} bytes.")
