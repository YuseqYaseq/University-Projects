import re
import json
import pygame, sys
from pygame.locals import *


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
    
    pygame.init()
    
    DISPLAY = pygame.display.set_mode((width,height), 0, 24)
    
    
    DISPLAY.fill(bg_colour)
    
    for figure in data['Figures']:
        colour = fg_colour
        if 'color' in figure:
            colour = cparser.parse(figure['color'])
        if figure['type'] == 'point':
            pygame.draw.rect(DISPLAY, colour, (figure['x'], figure['y'], 2, 2))
        elif figure['type'] == 'rectangle':
            pygame.draw.rect(DISPLAY, colour, (figure['x'], figure['y'], figure['width'], figure['height']))
        elif figure['type'] == 'polygon':
            pygame.draw.polygon(DISPLAY, colour, figure['points'])
        elif figure['type'] == 'square':
            pygame.draw.rect(DISPLAY, colour, (figure['x'], figure['y'], figure['size'], figure['size']))
        elif figure['type'] == 'circle':
            pygame.draw.circle(DISPLAY, colour, (figure['x'], figure['y']), figure['radius'])
    
    
    #pygame.draw.rect(DISPLAY, (255,0,0), (200, 150, 2, 2))
    
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            pygame.display.update()

main()










