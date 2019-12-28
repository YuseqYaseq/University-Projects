import cv2
import numpy as np
import imutils

white = (255, 255, 255)
black = (0, 0, 0)
width = 700
height = 700
img_corner = (200, 500)
thickness = 15


def get_hu_moment(let, font=cv2.FONT_ITALIC, scale=15, rotation=0, translation=(0, 0), blur=0):
    img = np.zeros((height, width, 1), np.uint8)
    cv2.putText(img, let, img_corner, font, scale, white, thickness)
    img = imutils.rotate(img, rotation)
    img = imutils.translate(img, translation[0], translation[1])
    if blur > 0:
        blur = blur * 2 + 1
        kernel = np.ones((blur, blur), np.float32) / (blur*blur)
        img = cv2.filter2D(img, -1, kernel)
    cv2.namedWindow("img")
    cv2.imshow("img", img)
    print("translation: ", translation, "; scale = ", scale, "; rotation= ", rotation, "; blur= ", blur, ";", sep='')
    cv2.waitKey(0)
    return cv2.HuMoments(cv2.moments(img)).flatten()


# Relative percent difference
def calculate_error(letter, font=cv2.FONT_ITALIC, scale=15, rotation=0, translation=(0, 0), blur=0):
    default_hu = get_hu_moment(letter)
    modified_hu = get_hu_moment(letter, font=font, scale=scale, rotation=rotation, translation=translation, blur=blur)
    rpd = 2*(default_hu - modified_hu)/(abs(default_hu) + abs(modified_hu))
    abs_error = abs(default_hu - modified_hu)
    return rpd, abs_error


def compare_letters(letter1, letter2):
    hu1 = get_hu_moment(letter1)
    hu2 = get_hu_moment(letter2)
    rpd = 2*(hu1 - hu2)/(abs(hu1) + abs(hu2))
    abs_error = abs(hu1 - hu2)
    print("hu1:", hu1)
    print("hu2:", hu2)
    return rpd, abs_error


def main():
    letters = ["P", "R", "W"]

    for letter in letters:
        print(letter)
        rpd, abs_err = calculate_error(letter, scale=23, rotation=0)
        print("Relative percent difference:", rpd)
        print("Absolute difference:", abs_err)
        rpd, abs_err = calculate_error(letter, rotation=180)
        print("Relative percent difference:", rpd)
        print("Absolute difference:", abs_err)
        rpd, abs_err = calculate_error(letter, rotation=30, translation=(-50, 50))
        print("Relative percent difference:", rpd)
        print("Absolute difference:", abs_err)
        rpd, abs_err = calculate_error(letter, font=cv2.FONT_HERSHEY_COMPLEX, scale=20)
        print("Relative percent difference:", rpd)
        print("Absolute difference:", abs_err)
        rpd, abs_err = calculate_error(letter, translation=(100, 100), blur=5)
        print("Relative percent difference:", rpd)
        print("Absolute difference:", abs_err)

    rpd, abs_err = compare_letters(letters[0], letters[1])
    print("Relative percent difference:", rpd)
    print("Absolute difference:", abs_err)

    rpd, abs_err = compare_letters(letters[0], letters[2])
    print("Relative percent difference:", rpd)
    print("Absolute difference:", abs_err)


main()
