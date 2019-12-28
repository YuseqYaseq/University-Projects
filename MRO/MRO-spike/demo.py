import random
from abc import abstractmethod, ABC

import cv2
import numpy as np
from azure.cognitiveservices.vision.computervision import ComputerVisionClient
from azure.cognitiveservices.vision.computervision.models import TextOperationStatusCodes
from msrest.authentication import CognitiveServicesCredentials

import os
import sys
import time

import asyncio, io, glob, os, sys, time, uuid, requests
from urllib.parse import urlparse
from io import BytesIO
from PIL import Image, ImageDraw
from azure.cognitiveservices.vision.face import FaceClient
from msrest.authentication import CognitiveServicesCredentials
import matplotlib.pyplot as plt
from azure.cognitiveservices.vision.face.models import TrainingStatusType, Person, SnapshotObjectType, \
    OperationStatusType

TEMP_IMAGE_NAME = "temp.png"

"""
    Implement subclasses, using those clients.
"""
CLIENTS = {
    "FaceClient": FaceClient,  # for cringe detector
    "ComputerVisionClient": ComputerVisionClient  # for text bounding
}

current_milli_time = lambda: int(round(time.time() * 1000))

"""
    Get the endpoint URL from the command line (first argument) and create the .apipass file with subscription key
    inside (don't push it to GitHub!). You can also implement a concrete implementation with given client and endpoint URL.
"""


class MCVModelUsage(ABC):
    def __init__(self, endpoint_url, subscription_key, client):
        self._endpoint_url = endpoint_url
        self._subscription_key = subscription_key
        self._content_url = ""
        self._image = None
        self._cv_client = client(self._endpoint_url, self._subscription_key)
        self._bounding_boxes = []

    def feed_image(self, image):
        self._image = image

    def convert_image(self):
        cv2.imwrite(TEMP_IMAGE_NAME, self._image)

    @abstractmethod
    def show_results_with_bounding_boxes(self):
        pass

    @abstractmethod
    def do_work(self):
        pass


class MCVModelUsageConcreteImplementationForCringe(MCVModelUsage, ABC):
    def __init__(self):
        MCVModelUsage.__init__(self, sys.argv[1],
                               CognitiveServicesCredentials(open(".apipass", "r").readline()), CLIENTS["FaceClient"])


class MCVModelUsageConcreteImplementationForTextBounding(MCVModelUsage, ABC):
    def __init__(self):
        MCVModelUsage.__init__(self, sys.argv[1],
                               CognitiveServicesCredentials(open(".apipass", "r").readline()),
                               CLIENTS["ComputerVisionClient"])


class MCVImageDescriptorForCringe(MCVModelUsageConcreteImplementationForCringe):
    """
        Cringe weights.
    """
    CRINGE_PARAMETERS = {
        "neutral": 0.6,
        "disgust": 0.2,
        "contempt": 0.2
    }

    def __init__(self):
        super().__init__()
        self._cringe_parameters = MCVImageDescriptorForCringe.CRINGE_PARAMETERS

    def do_work(self):
        pass  # TODO: implement this

    def show_results_with_bounding_boxes(self):
        pass  # TODO: implement this


class MCVImageDescriptorForTextBounding(MCVModelUsageConcreteImplementationForTextBounding):

    def __init__(self):
        super().__init__()

    def do_work(self):
        recognize_printed_results = self._cv_client.batch_read_file_in_stream(open(TEMP_IMAGE_NAME, "rb"), raw=True)
        operation_location_remote = recognize_printed_results.headers["Operation-Location"]
        # Grab the ID from the URL
        operation_id = operation_location_remote.split("/")[-1]

        # Call the "GET" API and wait for it to retrieve the results
        while True:
            get_printed_text_results = self._cv_client.get_read_operation_result(operation_id)
            if get_printed_text_results.status not in ['NotStarted', 'Running']:
                break

        # Print the detected text, line by line
        if get_printed_text_results.status == TextOperationStatusCodes.succeeded:
            for text_result in get_printed_text_results.recognition_results:
                for line in text_result.lines:
                    print(line.text)
                    print(line.bounding_box)
                    self._bounding_boxes.append(line.bounding_box)

    def show_results_with_bounding_boxes(self):
        plt.close()
        plt.ion()
        self._image = cv2.cvtColor(self._image, cv2.COLOR_BGR2RGB)
        for bounding_box in self._bounding_boxes:
            pts = np.array([[bounding_box[0], bounding_box[1]], [bounding_box[2], bounding_box[3]], [bounding_box[4],
                                                                                                     bounding_box[5]],
                            [bounding_box[6], bounding_box[7]]], np.int32)
            pts = pts.reshape((-1, 1, 2))
            cv2.polylines(self._image, [pts], True,
                          (random.randint(0, 256), random.randint(0, 256), random.randint(0, 256)), 10)
        self._bounding_boxes = []
        plt.imshow(self._image)
        # plt.draw()
        plt.pause(0.05)
        plt.show()


cam = cv2.VideoCapture(0)

"""
    Parameters:
    1 - endpoint URL
    2 - CringeDetector or TextBounding
    3 - transactions per second
"""
if __name__ == "__main__":
    plt.ion()
    print(sys.argv)
    demo_type = sys.argv[2]
    tps = float(sys.argv[3])
    if tps <= 0:
        raise ValueError("TPS must be positive. Aborting.")
    given_frame_time_millis = 1 / tps * 1000
    demo = None
    if demo_type == "CringeDetector":
        demo = MCVImageDescriptorForCringe()
    elif demo_type == "TextBounding":
        demo = MCVImageDescriptorForTextBounding()
    else:
        raise ValueError("CringeDetector or TextBounding should be used for demo type. Aborting.")
    success = True
    while success:
        begin_time = current_milli_time()
        if cam.isOpened():
            success, frame = cam.read()
        else:
            success = False
            break
        demo.feed_image(frame)
        demo.convert_image()
        print("doing work")
        demo.do_work()
        demo.show_results_with_bounding_boxes()
        end_time = current_milli_time()
        frame_time = end_time - begin_time
        if frame_time < given_frame_time_millis:
            print("started sleeping")
            time.sleep((given_frame_time_millis - frame_time) / 1000)
            print("stopped sleeping")
        else:
            print("Warning, couldn't meet the TPS requirement: too slow!")
