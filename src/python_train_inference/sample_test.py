import pixellib
from pixellib.instance import custom_segmentation
import cv2

capture = cv2.VideoCapture("/home/deploy/app/tests/database/video/test/gallbladder/raw_videos/vid2.mp4")

segment_camera = custom_segmentation()
segment_camera.inferConfig(num_classes=1, class_names=["BG", "gallbladder"])
segment_camera.load_model("mask_rcnn_models_gallbladder/mask_rcnn_model.002-1.775906.h5")
segment_camera.process_camera(capture, frames_per_second= 10, output_video_name="output_video_gallbladder_20210310_09.mp4", show_frames= True,
frame_name= "frame")