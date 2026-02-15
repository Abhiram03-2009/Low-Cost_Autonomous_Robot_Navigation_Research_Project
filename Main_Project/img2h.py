# img2h.py

import os
from PIL import Image
import numpy as np

INPUT_DIR = "images"
OUTPUT_DIR = "headers"
IMAGE_WIDTH = 96
IMAGE_HEIGHT = 96

os.makedirs(OUTPUT_DIR, exist_ok=True)

def process_image(img_path, var_name):
    img = Image.open(img_path).resize((IMAGE_WIDTH, IMAGE_HEIGHT)).convert("L")
    img_array = np.array(img).flatten()
    
    with open(os.path.join(OUTPUT_DIR, f"{var_name}.h"), "w") as f:
        f.write(f"#ifndef {var_name.upper()}_H\n#define {var_name.upper()}_H\n\n")
        f.write(f"const unsigned char {var_name}[{len(img_array)}] = {{\n")
        for i, pixel in enumerate(img_array):
            f.write(f"{pixel}, ")
            if (i + 1) % 16 == 0:
                f.write("\n")
        f.write("\n};\n#endif\n")

# Convert all images in the folder
for filename in os.listdir(INPUT_DIR):
    if filename.endswith(".jpg") or filename.endswith(".png"):
        name = os.path.splitext(filename)[0].lower().replace(" ", "_")
        process_image(os.path.join(INPUT_DIR, filename), name)

print("✅ Image conversion complete.")
