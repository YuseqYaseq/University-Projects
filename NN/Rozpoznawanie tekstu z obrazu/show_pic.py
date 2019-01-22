from PIL import Image
def main():
    with open("cmake-build-debug/test.txt", 'r') as fil:
        # f = f.split('\n')
        no_ex = int(fil.readline())
        for ex in range(no_ex):
            img_path = "src/" + fil.readline()[:-5] + ".png"
            real_img = Image.open(img_path)
            real_img.show()
            f_no = int(fil.readline())
            for f in range(f_no):
                height, width = tuple(map(int, fil.readline().split(' ')))
                img = Image.new('RGB', (width, height))
                pixels = img.load()
                for y in range(height):
                    vals = fil.readline().split(' ')
                    if vals[-1] == '\n':
                        vals = vals[:-1]                
                    for x in range(width):
                        val = int(float(vals[x]))                    
                        if(x < 10 and y < 10):
                            print("x= ", x, ", y= ", y, ", val= ", val, "      ", y * width + x) 
                        pixels[x,y] = (val, val, val)
                img.show()
                fil.readline()
main()
