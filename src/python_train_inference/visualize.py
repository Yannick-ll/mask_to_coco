import pixellib
from pixellib.custom_train import instance_custom_training

vis_img = instance_custom_training()
vis_img.load_dataset("/home/deploy/app/tests/database/CholecSeg8k_Mine/Final")
vis_img.visualize_sample()
import pixellib
from pixellib.custom_train import instance_custom_training
vis_img = instance_custom_training()
