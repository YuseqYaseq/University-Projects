import re
import json
import argparse
import pygame, sys
from pygame.locals import *
from PIL import Image, ImageDraw

class ColourParser:
    def __init__(self):
        #pattern '#RRGGBB'
        self.colour_pattern1 = re.compile('^#[0-9A-F]{6}$', re.IGNORECASE)
        self.hex_num_pattern = re.compile('[0-9A-F]{2}', re.IGNORECASE)

        #pattern '(RRR, GGG, BBB)'
        self.colour_pattern2 = re.compile('^\([0-9]+,[ ]*[0-9]+,[ ]*[0-9]+\)$')
        self.dec_num_pattern = re.compile('[0-9]+')
        
        #map for a custom Palette
        self.colours = {}
    
    #converts strings to (R, G, B) tuples
    def parse(self, colour_value):
        if re.search(self.colour_pattern1, colour_value):
            #find all 3 colour values in the pattern, convert them to int and return them in a tuple
            return tuple(map(lambda x: int(x, 16), re.findall(self.hex_num_pattern, colour_value)))
        elif re.search(self.colour_pattern2, colour_value):
            return tuple(map(lambda x: int(x), re.findall(self.dec_num_pattern, colour_value)))
        elif colour_value in self.colours:
            return self.colours[colour_value]
        else:
            raise Exception('Unknown colour format!', colour_value)
    
    #saves new colour in a Palette
    def add(self, name, tup):
        self.colours[name] = tup 
    

def main():
    
    #parse cmd line
    aparser = argparse.ArgumentParser(description='Parse json containing image info and print it on the screen or to a PNG file.')
    aparser.add_argument('input', help='path to json file')
    aparser.add_argument('-o', '--output', help='Output png file. If none is provided results will be printed on screen')
    args = aparser.parse_args()
    
    #screen or png?
    png = True
    if args.output is None:
        png = False
    #if output doesn't have .png extension we have to add it manually
    elif args.output[-4:] != '.png':
        args.output += '.png'
    
    #init colour parser
    cparser = ColourParser()
    
    #load json file
    with open('sample.json') as json_file:
        data = json.load(json_file)
    
    #get palette colours
    for colour in data['Palette']:
        colour_value = data['Palette'][colour]
        cparser.add(colour, cparser.parse(colour_value))
    
    width = data['Screen']['width']
    height = data['Screen']['height']
    bg_colour = cparser.parse(data['Screen']['bg_color'])
    fg_colour = cparser.parse(data['Screen']['fg_color'])
    
    ###### SAVE TO FILE ######
    if png:
        size = (width, height)
        
        #create new image
        image = Image.new('RGB', size, bg_colour)
        draw = ImageDraw.Draw(image)
        
        for figure in data['Figures']:
            colour = fg_colour
            if 'color' in figure:
                colour = cparser.parse(figure['color'])
            if figure['type'] == 'point':
                draw.point([figure['x'], figure['y']], colour)
            elif figure['type'] == 'rectangle':
                draw.rectangle([figure['x'], figure['y'], figure['x']+figure['width'], figure['y']+figure['height']], colour)
            elif figure['type'] == 'polygon':
                #draw.polygon expects tuples so we need to map points to them
                list_of_points = list(map(lambda x: tuple(x), figure['points']))
                draw.polygon(list_of_points, colour)
            elif figure['type'] == 'square':
                draw.rectangle([figure['x'], figure['y'], figure['x']+figure['size'], figure['y']+figure['size']], colour)
            elif figure['type'] == 'circle':
                x1 = figure['x'] - figure['radius']
                y1 = figure['y'] - figure['radius']
                x2 = figure['x'] + figure['radius']
                y2 = figure['y'] + figure['radius'] 
                draw.ellipse([x1,y1,x2,y2], colour)
        
        image.save(args.output)
        print('Image successfully saved.')
    ###### DRAW ON SCREEN ######
    else:
        pygame.init()
        
        DISPLAY = pygame.display.set_mode((width,height), 0, 24)
        DISPLAY.fill(bg_colour)
        
        for figure in data['Figures']:
            colour = fg_colour
            if 'color' in figure:
                colour = cparser.parse(figure['color'])
            if figure['type'] == 'point':
                pygame.draw.rect(DISPLAY, colour, (figure['x'], figure['y'], 1, 1))
            elif figure['type'] == 'rectangle':
                pygame.draw.rect(DISPLAY, colour, (figure['x'], figure['y'], figure['width'], figure['height']))
            elif figure['type'] == 'polygon':
                pygame.draw.polygon(DISPLAY, colour, figure['points'])
            elif figure['type'] == 'square':
                pygame.draw.rect(DISPLAY, colour, (figure['x'], figure['y'], figure['size'], figure['size']))
            elif figure['type'] == 'circle':
                pygame.draw.circle(DISPLAY, colour, (figure['x'], figure['y']), figure['radius'])
        
        #wait until window is closed
        while True:
            for event in pygame.event.get():
                if event.type == QUIT:
                    pygame.quit()
                    sys.exit()
                pygame.display.update()

main()










