from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw 

import os, os.path
import errno

font_size = 130
fonts = ["Arial.ttf", "Arial_Italic.ttf", "Arial_Bold.ttf", "Times_New_Roman.ttf"]
bg_fg_colors = [
    [(  0,   0,   0), (255, 255, 255)], #white text on black background
    [(255, 255, 255), (  0,   0,   0)], #black text on white background
    [(255,   0,   0), (  0, 255, 255)]
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

def generate_image(word, font, bg, fg):
    font = ImageFont.truetype(font, font_size)
    img = Image.new('RGB', (get_width_height(word, font)), color=bg)
    draw = ImageDraw.Draw(img)
    draw.text((0, 0), word, font=font, fill=fg)
    #img.resize((1000, 1000), Image.ANTIALIAS)
    return img

def save_img_to(img, name):
    img.save(name + '.png')
       
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
        for font in fonts:
            for bg_fg_color in bg_fg_colors:
                img = generate_image(word, font, bg_fg_color[0], bg_fg_color[1])
                save_img_to(img, directory + word + "/" + font + "_" + str(bg_fg_color))

generate_images_from_file("top_100_words.txt", "pics/")




