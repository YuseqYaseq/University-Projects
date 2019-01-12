from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw 

import os, os.path
import errno

result_size = (256, 256)

font_size = 130
fonts = ["Arial.ttf",
         #"Arial_Italic.ttf",
         #"Arial_Bold.ttf",
         "Times_New_Roman.ttf"
]

bg_fg_colors = [
    #[(  0,   0,   0), (255, 255, 255)], #white text on black background
    [(255, 255, 255), (  0,   0,   0)], #black text on white background
    #[(255,   0,   0), (  0, 255, 255)]  #cyan  text on red   background
]

scales = [
    [1.00, 1.00],
    [1.00, 0.50], #scale image to (100%, 50%) of the original size
    [0.50, 1.00],
    #[0.25, 1.00],
    #[1.00, 0.25]
]

angles = [
    0,
    20,
    #90,
    #270,
    340
]

def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc: # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else: raise

def get_width_height(word, font):
    ascent, descent = font.getmetrics()
    (width, baseline), (offset_x, offset_y) = font.font.getsize(word)
    return width, (ascent + descent)

def generate_image(word, font, bg, fg, scale, angle):
    #add alpha channel    
    bg += (255,)
    font = ImageFont.truetype(font, font_size)
    width, height = (get_width_height(word, font))
    img = Image.new('RGBA', (width, height), color=bg)
    draw = ImageDraw.Draw(img)
    draw.text((0, 0), word, font=font, fill=fg)
    img = img.resize((int(width * scale[0]), int(height * scale[1])), Image.ANTIALIAS)
    img = img.rotate(angle, expand = 1)
    img = img.resize(result_size, Image.ANTIALIAS)
    
    background = Image.new("RGBA", img.size, bg)
    background.paste(img, mask=img.split()[-1])
    return background

def save_img_as_png(img, name):
    img.save(name + '.png')

def save_img_as_txt(img, name):
    fil = open(name + '.txt', 'w')
    row, column = img.size
    for y in range(column):
        for x in range(row):
            r, g, b, a=img.getpixel((x, y))
            fil.write(str(r) + ' ' + str(g) + ' ' + str(b) + ' ')
        fil.write('\n')
    fil.close()

def get_words_from_file(filename):
    words = []
    with open(filename, 'r') as f:
        for line in f:
            line = line[:-1] #remove \n
            words.append(line)
    return words

def generate_images_from_file(filename, directory):
    words = get_words_from_file(filename)
    for word in words:
        #create pics directory if it doesn't exist
        mkdir_p(directory + word)
        
        #generate image for every font, color, scale and rotation combination
        for font in fonts:
            for bg_fg_color in bg_fg_colors:
                for scale in scales:
                    for angle in angles:
                        img = generate_image(word, font, bg_fg_color[0], bg_fg_color[1], scale, angle)
                        save_img_as_png(img, directory + word + "/" +
                            font + "_" + str(bg_fg_color) + "_" + str(scale) + "_" + str(angle))
                        save_img_as_txt(img, directory + word + "/" +
                            font + "_" + str(bg_fg_color) + "_" + str(scale) + "_" + str(angle))

generate_images_from_file("top_10_words.txt", "pics/")




